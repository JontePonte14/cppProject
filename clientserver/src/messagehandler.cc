#include "messagehandler.h"
#include "connectionclosedexception.h"
#include "connection.h"
#include "protocol.h"
#include <iostream>

class ConnectionClosedException;

#define RETURN_IF_FAILED(expr)              \
    do {                                    \
        Status _status = (expr);            \
        if (_status != Status::Success)     \
            return _status;                 \
    } while (0)


MessageHandler::MessageHandler()
    : connection()
{ 
}

MessageHandler::MessageHandler(const std::shared_ptr<Connection>& connection)
    : connection(connection)
{ }

auto MessageHandler::sendProtocol(const Protocol protocol) noexcept -> Status
{
    std::cout << "Sent protocol " << to_string(protocol) << std::endl;
    return sendByte(to_code(protocol));
}

auto MessageHandler::sendInt(const uint32_t value, const std::string& id) noexcept -> Status
{
    const auto b1 = static_cast<byte>(value >> 24);
    const auto b2 = static_cast<byte>(value >> 16);
    const auto b3 = static_cast<byte>(value >> 8);
    const auto b4 = static_cast<byte>(value);

    RETURN_IF_FAILED(sendByte(b1));
    RETURN_IF_FAILED(sendByte(b2));
    RETURN_IF_FAILED(sendByte(b3));
    RETURN_IF_FAILED(sendByte(b4));

    
    std::cout << "Sent int " << (id == "" ? "= " : "[" + id + "] = ") << (b1 | b2 | b3 | b4) << std::endl;
    return Status::Success;
}

auto MessageHandler::sendIntParameter(const uint32_t param, const std::string& id) noexcept -> Status
{
    RETURN_IF_FAILED(sendProtocol(Protocol::PAR_NUM));
    RETURN_IF_FAILED(sendInt(param));

    return Status::Success;
}

auto MessageHandler::sendStringParameter(const string& param, const std::string& id) noexcept -> Status
{
    RETURN_IF_FAILED(sendProtocol(Protocol::PAR_STRING));
    RETURN_IF_FAILED(sendIntParameter(param.length(), "# of chars"));

    for (byte c : param) {
        RETURN_IF_FAILED(sendByte(c));
    }

    std::cout << "Sent string " << (id == "" ? "= " : "[" + id + "] = ") << param << std::endl;

    return Status::Success;
}

auto MessageHandler::receiveProtocol() noexcept -> Protocol
{
    const auto code = receiveByte();

    if (code) {
        std::cout << "Received protocol " << to_string(from_code(*code)) << std::endl;
        return from_code(*code);
    }

    return Protocol::UNDEFINED;
}

auto MessageHandler::receiveInt() noexcept -> Expected<uint32_t, Status>
{
    uint32_t value { 0 };
    Expected<byte, Status> b;

    for(char i = 24; i >= 0; i -= 8) {
        const auto b = receiveByte();

        if (b) {
            value |= static_cast<uint32_t>(*b) << i;
        } else {
            return b.error();
        }
    }

    std::cout << "Received int " << value << std::endl;

    return value;
}

auto MessageHandler::receiveIntParameter() noexcept -> Expected<uint32_t, Status>
{
    const auto code = receiveProtocol();

    return (code == Protocol::PAR_NUM) ? receiveInt() : Status::ProtocolViolation;
}

auto MessageHandler::receiveStringParameter() noexcept -> Expected<std::string, Status>
{
    const auto code = receiveProtocol();

    if (code != Protocol::PAR_STRING) {
        return Status::ProtocolViolation;
    }

    const auto params = receiveInt();

    if (!params) {
        return params.error();
    }

    const auto n = *params;

    if (n < 1) {
        return Status::InvalidArguments;
    }
    
    string param;
    Expected<byte, Status> b;

    param.reserve(n);

    for (uint32_t i = 0; i < n; ++i) {
        b = receiveByte();
        
        if (!b) {
            return b.error();
        }

        param += *b;
    }

    std::cout << "Received string " << param << std::endl;

    return param;
}

auto MessageHandler::sendByte(const byte value, const byte tries) noexcept -> Status
{
    return connection->isConnected() ? [&]() {
        for (byte i = 0; i < tries; ++i) {
            try {
                connection->write(value);
                return Status::Success;
            } catch (const ConnectionClosedException& e) {
                // IMPLEMENT LOGGING IF TIME ALLOWS
            }
        }
        return Status::FailedTransfer;
    }() : Status::ConnectionClosed;
}

auto MessageHandler::receiveByte(const byte tries) noexcept -> Expected<byte, Status>
{
    if (connection->isConnected()) {
        for(byte i = 0; i < tries; ++i) {
            try {
                return connection->read();
            } catch (const ConnectionClosedException& error) {
                // IMPLEMENT LOGGING IF TIME ALLOWS
            }
        }

        return Status::FailedTransfer;
    } else { 
        return Status::ConnectionClosed;
    }
}

void MessageHandler::setConnection(const std::shared_ptr<Connection>& connection) noexcept
{
    this->connection = connection;
}
