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

auto MessageHandler::receiveInt() noexcept -> Expected<uint32_t, Error>
{
    uint32_t value { 0 };
    Expected<byte, Error> b;

    for(char i = 24; i >= 0; i -= 8) {
        const auto b = receiveByte();

        if (b) {
            value |= static_cast<uint32_t>(*b) << i;
        } else {
            return b.error();
        }
    }

    return value;
}

auto MessageHandler::receiveIntParameter() noexcept -> Expected<uint32_t, Error>
{
    const auto code = receiveProtocol();

    return (code == Protocol::PAR_NUM) ? receiveInt() : Error::ProtocolViolation;
}

auto MessageHandler::receiveStringParameter() noexcept -> Expected<std::string, Error>
{
    const auto code = receiveProtocol();

    if (code != Protocol::PAR_STRING) {
        return Error::ProtocolViolation;
    }

    const auto params = receiveInt();

    if (!params) {
        return params.error();
    }

    const auto n = *params;

    if (n < 1) {
        return Error::InvalidArguments;
    }
    
    string param;
    Expected<byte, Error> b;

    param.reserve(n);

    for (uint32_t i = 0; i < n; ++i) {
        b = receiveByte();
        
        if (!b) {
            return b.error();
        }

        param += *b;
    }

    return param;
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

auto MessageHandler::receiveByte(const byte tries) noexcept -> Expected<byte, Error>
{
    if (connection->isConnected()) {
        for(byte i = 0; i < tries; ++i) {
            try {
                return connection->read();
            } catch (const ConnectionClosedException& error) {
                // IMPLEMENT LOGGING IF TIME ALLOWS
            }
        }

        return Error::FailedTransfer;
    } else { 
        return Error::ConnectionClosed;
    }
}

void MessageHandler::setConnection(const std::shared_ptr<Connection>& connection) noexcept
{
    this->connection = connection;
}
