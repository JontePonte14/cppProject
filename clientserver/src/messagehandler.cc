#include "messagehandler.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include <iostream>

class ConnectionClosedException;

MessageHandler::MessageHandler()
    : connection()
{ 
    std::cout << "Message handler initialzied" << std::endl;
}

MessageHandler::MessageHandler(const std::shared_ptr<Connection>& connection)
    : connection(connection)
{ }

void MessageHandler::sendCode(const Protocol protocol)
{
    sendByte(static_cast<byte>(protocol));
}

void MessageHandler::sendInt(int value)
{
    sendByte((value >> 24) & 0xFF);
    sendByte((value >> 16) & 0xFF);
    sendByte((value >> 8) & 0xFF);
    sendByte(value & 0xFF);
}

void MessageHandler::sendIntParameter(int param)
{
    sendCode(Protocol::PAR_NUM);
    sendInt(param);
}

void MessageHandler::sendStringParameter(const string& param)
{
    sendCode(Protocol::PAR_STRING);
    sendInt(param.length());

    for (byte c : param) {
        sendByte(c);
    }
}

auto MessageHandler::receiveCode() -> byte
{
    byte code = receiveByte();

    return code;
}

auto MessageHandler::receiveInt() -> int
{
    const int b1 = receiveByte();
    const int b2 = receiveByte();
    const int b3 = receiveByte();
    const int b4 = receiveByte();

    return b1 << 24 | b2 << 16 | b3 << 8 | b4;
}

auto MessageHandler::receiveIntParameter() -> int
{
    int code = receiveCode();

    if (code != static_cast<byte>(Protocol::PAR_NUM)) {
        throw ConnectionClosedException(); // TEMP
    }

    return receiveInt();
}

auto MessageHandler::receiveStringParameter() -> string
{
    int code = receiveCode();

    if (code != static_cast<byte>(Protocol::PAR_STRING)) {
        throw ConnectionClosedException(); // TEMP
    }

    int n = receiveInt();

    if (n < 1) {
        throw ConnectionClosedException(); // TEMP
    }

    string param;

    param.reserve(n);

    for (int i = 0; i < n; ++i) {
        param += receiveByte();
    }

    return param;
}

void MessageHandler::sendByte(byte value)
{
    try {
        connection->write(value);
    } catch (const ConnectionClosedException& e) {
        // TEMP
    }
}

auto MessageHandler::receiveByte() -> byte
{
    return connection->read();
}

void MessageHandler::setConnection(const std::shared_ptr<Connection>& connection)
{
#ifdef NDEBUG
    std::cout << "message handler connection is set" << std::endl;
#endif
    this->connection = connection;
}
