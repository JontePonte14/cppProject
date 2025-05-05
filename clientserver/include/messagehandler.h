#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <memory>
#include <string>
#include "expected.h"

using byte = unsigned char;

class Connection;
enum class Protocol : byte;

enum Status {
    ProtocolViolation,
    ConnectionClosed,
    FailedTransfer,
    InvalidArguments,
    Success,
};

// Macro used with any function returning a Status enum
#define RETURN_IF_FAILED(expr)              \
    do {                                    \
        Status _status = (expr);            \
        if (_status != Status::Success)     \
            return _status;                 \
    } while (0)

// Helper macros for ASSIGN_OR_RETURN
#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

// Macro used for unpacking an Expected<V, E> object into V if valid, else returning E
#define ASSIGN_OR_RETURN(var, expr)                              \
    auto CONCAT(_result_, __LINE__) = (expr);                    \
    if (!CONCAT(_result_, __LINE__))                             \
        return CONCAT(_result_, __LINE__).error();               \
    decltype(auto) var = std::move(*CONCAT(_result_, __LINE__));

// Macro used for receiving and unpacking a Protocol, checking if it is valid and expected else returning error
#define RECEIVE_AND_VERIFY_PROTOCOL(expected)                           \
    Expected<Protocol, Status> _protocol = receiveProtocol(expected);   \
    if (!_protocol)                                                     \
        return _protocol.error();

class MessageHandler {

    public:
        MessageHandler();
        explicit MessageHandler(const std::shared_ptr<Connection>& connection);
        virtual ~MessageHandler() = default;
        
        auto sendProtocol(const Protocol protocol) const noexcept -> Status;
        auto sendIntParameter(const uint32_t value, const std::string& id = "") const noexcept -> Status;
        auto sendStringParameter(const std::string& param, const std::string& id = "") const noexcept -> Status;

        [[nodiscard]] auto receiveProtocol() const noexcept -> Expected<Protocol, Status>;
        [[nodiscard]] auto receiveProtocol(const Protocol expected) const noexcept -> Expected<Protocol, Status>;
        [[nodiscard]] auto receiveIntParameter() const noexcept -> Expected<uint32_t, Status>;
        [[nodiscard]] auto receiveStringParameter() const noexcept -> Expected<std::string, Status>;

        void setConnection(const std::shared_ptr<Connection>& connection) const noexcept;
        
    protected:
        auto sendByte(const byte b, const byte tries = 1) const noexcept -> Status;
        [[nodiscard]] auto receiveByte(const byte tries = 1) const noexcept -> Expected<byte, Status>;
        
    private:
        mutable std::shared_ptr<Connection> connection;

        auto sendInt(const uint32_t value, const std::string& id = "") const noexcept -> Status;
        [[nodiscard]] auto receiveInt() const noexcept -> Expected<uint32_t, Status>;
};

#endif