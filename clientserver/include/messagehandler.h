#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <memory>
#include <string>

class Connection;
enum class Protocol;

using byte = unsigned char;

class MessageHandler final {

    friend class CommandHandler;
    
    using string = std::string;

    public:
        MessageHandler();
        MessageHandler(const std::shared_ptr<Connection>&);
        ~MessageHandler() = default;
        
        void sendCode(const Protocol);
        void sendInt(int);
        void sendIntParameter(int);
        void sendStringParameter(const string&);

        auto receiveCode() -> byte;
        auto receiveInt() -> int;
        auto receiveIntParameter() -> int;
        auto receiveStringParameter() -> std::string;

    private:
        std::shared_ptr<Connection> connection;

        void sendByte(byte);
        auto receiveByte() -> byte;

        void setConnection(const std::shared_ptr<Connection>&);
};

#endif