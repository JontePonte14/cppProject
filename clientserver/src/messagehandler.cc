#include "messagehandler.h"
#include "connectionclosedexception.h"
#include "connection.h"
#include "protocol.h"

class ConnectionClosedException;

MessageHandler::MessageHandler()
    : connection()
{ 
}

MessageHandler::MessageHandler(const std::shared_ptr<Connection>& connection)
    : connection(connection)
{ }

auto MessageHandler::sendProtocol(const Protocol protocol) noexcept -> bool
{
    return sendByte(to_code(protocol));
}

auto MessageHandler::sendInt(const uint32_t value) noexcept -> bool
{
    return
        sendByte(static_cast<byte>(value >> 24)) &&
        sendByte(static_cast<byte>(value >> 16)) &&
        sendByte(static_cast<byte>(value >> 8)) &&
        sendByte(static_cast<byte>(value));
}

auto MessageHandler::sendIntParameter(const uint32_t param) noexcept -> bool
{
    return sendProtocol(Protocol::PAR_NUM) && sendInt(param);
}

auto MessageHandler::sendStringParameter(const string& param) noexcept -> bool
{
    return sendProtocol(Protocol::PAR_STRING) && sendInt(param.length()) ? [&]() {
        for (byte c : param) {
            if(!sendByte(c)) {
                return false;
            }
        }

        return true;

    }() : false;
}

auto MessageHandler::receiveProtocol() noexcept -> Protocol
{
    const auto code = receiveByte();

    return code ? from_code(*code) : Protocol::UNDEFINED;
}

auto MessageHandler::receiveInt() noexcept -> std::optional<uint32_t>
{
    uint32_t value { 0 };
    std::optional<byte> b;

    for(char i = 24; i >= 0; i -= 8) {
        b = receiveByte();

        if (b) {
            value |= static_cast<uint32_t>(*b) << i;
        } else {
            return std::nullopt;
        }
    }

    return value;
}

auto MessageHandler::receiveIntParameter() noexcept -> std::optional<uint32_t>
{
    const auto code = receiveProtocol();

    return (code == Protocol::PAR_NUM) ? receiveInt() : std::nullopt;
}

auto MessageHandler::receiveStringParameter() noexcept -> std::optional<std::string>
{
    const auto code = receiveProtocol();

    if (code == Protocol::PAR_STRING) {
        auto n = receiveInt();

        if (n && *n >= 1) {
            string param;
            std::optional<byte> b;

            param.reserve(*n);

            for (uint32_t i = 0; i < n; ++i) {
                b = receiveByte();
                
                if (!b) {
                    return std::nullopt;
                }

                param += *b;
            }

            return param;
        }
    }

    return std::nullopt;
}

auto MessageHandler::sendByte(const byte value, const byte tries) noexcept -> bool
{
    return connection->isConnected() ? [&]() {
        for (byte i = 0; i < tries; ++i) {
            try {
                connection->write(value);
                return true;
            } catch (const ConnectionClosedException& e) {
                // IMPLEMENT LOGGING IF TIME ALLOWS
            }
        }
        return false;
    }() : false;
}

auto MessageHandler::receiveByte(const byte tries) noexcept -> std::optional<byte>
{
    if (connection->isConnected()) {
        for(byte i = 0; i < tries; ++i) {
            try {
                return std::optional<byte>{connection->read()};
            } catch (const ConnectionClosedException& error) {
                // IMPLEMENT LOGGING IF TIME ALLOWS
            }
        }
    }

    return std::nullopt;
}

void MessageHandler::setConnection(const std::shared_ptr<Connection>& connection) noexcept
{
    this->connection = connection;
}
