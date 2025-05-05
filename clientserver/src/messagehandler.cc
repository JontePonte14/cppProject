#include "messagehandler.h"
#include "connectionclosedexception.h"
#include "connection.h"
#include "protocol.h"
#include <iostream>
#include "logger.h"

class ConnectionClosedException;

MessageHandler::MessageHandler()
    : connection()
{ 
}

MessageHandler::MessageHandler(const std::shared_ptr<Connection>& connection)
    : connection(connection)
{ }

auto MessageHandler::sendProtocol(const Protocol protocol) const noexcept -> Status
{
    Logger::log("NETWORK", "Sent protocol " + std::string(to_string(protocol)));

    return sendByte(to_code(protocol));
}

auto MessageHandler::sendIntParameter(const uint32_t param, const std::string& id) const noexcept -> Status
{
    RETURN_IF_FAILED(sendProtocol(Protocol::PAR_NUM));
    RETURN_IF_FAILED(sendInt(param, id));

    return Status::Success;
}

auto MessageHandler::sendStringParameter(const std::string& param, const std::string& id) const noexcept -> Status
{
    RETURN_IF_FAILED(sendProtocol(Protocol::PAR_STRING));
    RETURN_IF_FAILED(sendIntParameter(param.length(), "# of chars"));

    for (const byte c : param) {
        RETURN_IF_FAILED(sendByte(c));
    }

    Logger::log("NETWORK",  "Sent string " + (id == "" ? "= " : "[" + id + "] = ") + param);

    return Status::Success;
}

auto MessageHandler::receiveProtocol() const noexcept -> Expected<Protocol, Status>
{
    ASSIGN_OR_RETURN(code, receiveByte());
    const auto protocol = from_code(code);

    Logger::log("NETWORK", "Received protocol " + std::string(to_string(protocol)));

    return protocol;
}

auto MessageHandler::receiveProtocol(const Protocol expected) const noexcept -> Expected<Protocol, Status>
{
    ASSIGN_OR_RETURN(code, receiveByte());
    const auto protocol = from_code(code);

    Logger::log("NETWORK", "Received protocol " + std::string(to_string(protocol)));

    if (protocol != expected) {
        return Status::ProtocolViolation;
    }

    return protocol;
}

auto MessageHandler::receiveIntParameter() const noexcept -> Expected<uint32_t, Status>
{
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::PAR_NUM);
    ASSIGN_OR_RETURN(param, receiveInt());

    return param;
}

auto MessageHandler::receiveStringParameter() const noexcept -> Expected<std::string, Status>
{
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::PAR_STRING);
    ASSIGN_OR_RETURN(n, receiveIntParameter());

    if (n < 1) {
        return Status::InvalidArguments;
    }
    
    std::string param;
    Expected<byte, Status> b;

    param.reserve(n);

    for (uint32_t i = 0; i < n; ++i) {
        ASSIGN_OR_RETURN(b, receiveByte());
        param += b;
    }

    Logger::log("NETWORK", "Received string " + param);

    return param;
}

auto MessageHandler::sendByte(const byte value, const byte tries) const noexcept -> Status
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

auto MessageHandler::receiveByte(const byte tries) const noexcept -> Expected<byte, Status>
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

void MessageHandler::setConnection(const std::shared_ptr<Connection>& connection) const noexcept
{
    this->connection = connection;
}

auto MessageHandler::sendInt(const uint32_t value, const std::string& id) const noexcept -> Status
{
    const auto b1 = static_cast<byte>(value >> 24);
    const auto b2 = static_cast<byte>(value >> 16);
    const auto b3 = static_cast<byte>(value >> 8);
    const auto b4 = static_cast<byte>(value);

    RETURN_IF_FAILED(sendByte(b1));
    RETURN_IF_FAILED(sendByte(b2));
    RETURN_IF_FAILED(sendByte(b3));
    RETURN_IF_FAILED(sendByte(b4));
   
    Logger::log("NETWORK",  "Sent int " + (id == "" ? "= " : "[" + id + "] = ") + std::to_string(value));

    return Status::Success;
}

auto MessageHandler::receiveInt() const noexcept -> Expected<uint32_t, Status>
{
    uint32_t value { 0 };

    for(char i = 24; i >= 0; i -= 8) {
        ASSIGN_OR_RETURN(b, receiveByte());
        value |= static_cast<uint32_t>(b) << i;
    }

    Logger::log("NETWORK", "Received int " + std::to_string(value));

    return value;
}