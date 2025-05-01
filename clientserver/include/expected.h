#ifndef EXPECTED_H
#define EXPECTED_H

#include <variant>
#include <utility>
#include <stdexcept>

template<typename V, typename E>
class Expected {

public:
    static_assert(!std::is_same_v<V, E>, "V and E cannot be the same type");

    Expected() = default;

    Expected(const V& value) : data(value) { }
    Expected(V&& value) : data(std::move(value)) {}

    Expected(const E& error) : data(std::in_place_index<1>, error) {}
    Expected(E&& error) : data(std::in_place_index<1>, std::move(error)) {}

    [[nodiscard]] auto has_value() const noexcept -> bool { 
        return data.index() == 0; 
    }

    explicit operator bool() const noexcept {
        return has_value();
    }

    // Access value
    [[nodiscard]] auto value() & -> V& { 
        if (!has_value()) {
            throw std::logic_error("Accessing value of an error state Expected");
        }
        return std::get<0>(data); 
    }

    [[nodiscard]] auto value() const& -> const V& { 
        if (!has_value()) {
            throw std::logic_error("Accessing value of an error state Expected");
        }
        return std::get<0>(data); 
    }

    [[nodiscard]] auto value() && -> V&& { 
        if (!has_value()) {
            throw std::logic_error("Accessing value of an error state Expected");
        }
        return std::get<0>(std::move(data)); 
    }

    // Access error
    [[nodiscard]] auto error() & -> E& { 
        if (has_value()) {
            throw std::logic_error("Accessing error of a value state Expected");
        }
        return std::get<1>(data); 
    }

    [[nodiscard]] auto error() const& -> const E& { 
        if (has_value()) {
            throw std::logic_error("Accessing error of a value state Expected");
        }
        return std::get<1>(data); 
    }

    [[nodiscard]] auto error() && -> E&& { 
        if (has_value()) {
            throw std::logic_error("Accessing error of a value state Expected");
        }
        return std::get<1>(std::move(data)); 
    }

    // Unpacking with *
    [[nodiscard]] auto operator*() & -> V& {
        if (!has_value()) {
            throw std::logic_error("Dereferencing an error state Expected");
        }
        return std::get<0>(data);
    }

    [[nodiscard]] auto operator*() const& -> const V& {
        if (!has_value()) {
            throw std::logic_error("Dereferencing an error state Expected");
        }
        return std::get<0>(data);
    }

    [[nodiscard]] auto operator*() && -> V&& {
        if (!has_value()) {
            throw std::logic_error("Dereferencing an error state Expected");
        }
        return std::get<0>(std::move(data));
    }

    // Assignment operators
    auto operator=(const V& value) -> Expected& {
        data = value;
        return *this;
    }

    auto operator=(V&& value) -> Expected& {
        data = std::move(value);
        return *this;
    }

    auto operator=(const E& error) -> Expected& {
        data = std::variant<V, E>(std::in_place_index<1>, error);
        return *this;
    }
    
    auto operator=(E&& error) -> Expected& {
        data = std::variant<V, E>(std::in_place_index<1>, std::move(error));
        return *this;
    }
    
    auto operator=(const Expected& other) -> Expected& {
        data = other.data;
        return *this;
    }

    auto operator=(Expected&& other) noexcept -> Expected& {
        data = std::move(other.data);
        return *this;
    }

private:
    std::variant<V, E> data;
};

#endif
