#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <memory>
#include <string>
#include "expected.h"

using byte = unsigned char;
using string = std::string;

class Connection;
enum class Protocol : byte;

enum Error {
    ProtocolViolation,
    ConnectionClosed,
    FailedTransfer,
    InvalidArguments,
};

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
        [[nodiscard]] auto receiveInt() noexcept -> Expected<uint32_t, Error>;
        [[nodiscard]] auto receiveIntParameter() noexcept -> Expected<uint32_t, Error>;
        [[nodiscard]] auto receiveStringParameter() noexcept -> Expected<string, Error>;

        void setConnection(const std::shared_ptr<Connection>& connection) noexcept;
        
    protected:
        auto sendByte(const byte b, const byte tries = 1) noexcept -> bool;
        [[nodiscard]] auto receiveByte(const byte tries = 1) noexcept -> Expected<byte, Error>;
        
    private:
        std::shared_ptr<Connection> connection;
};

#endif