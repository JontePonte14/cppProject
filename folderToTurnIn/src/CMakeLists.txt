cmake_minimum_required(VERSION 3.14)
target_sources(clientserver
    PRIVATE
        connection.cc
        server.cc
        messagehandler.cc
        commandhandler.cc
        servercommandhandler.cc
        databaseserver.cc
        client_commandhandler.cc
        client_commanddecoder.cc
        interface.cc
        databaseDS.cc
        databaseMS.cc
        article.cc
        logger.cc
        
)
