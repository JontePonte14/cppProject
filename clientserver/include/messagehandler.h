#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <memory>
#include <string>
#include <optional>

using byte = unsigned char;
using string = std::string;

class Connection;
enum class Protocol : byte;

class MessageHandler {

    public:
        MessageHandler();
        explicit MessageHandler(const std::shared_ptr<Connection>& connection);
        virtual ~MessageHandler() = default;
        
        auto sendProtocol(const Protocol protocol) noexcept -> bool;
        auto sendInt(const uint32_t value) noexcept -> bool;
        auto sendIntParameter(const uint32_t value) noexcept -> bool;
        auto sendStringParameter(const string& param) noexcept -> bool;

        [[nodiscard]] auto receiveProtocol() noexcept -> Protocol;
        [[nodiscard]] auto receiveInt() noexcept -> std::optional<uint32_t>;
        [[nodiscard]] auto receiveIntParameter() noexcept -> std::optional<uint32_t>;
        [[nodiscard]] auto receiveStringParameter() noexcept -> std::optional<string>;

    protected:
        auto sendByte(const byte b, const byte tries = 1) noexcept -> bool;
        [[nodiscard]] auto receiveByte(const byte tries = 1) noexcept -> std::optional<byte>;

        void setConnection(const std::shared_ptr<Connection>& connection) noexcept;
        
    private:
        std::shared_ptr<Connection> connection;
};

#endif