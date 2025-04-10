cmake_minimum_required(VERSION 3.14)
target_sources(clientserver
    PRIVATE
        connection.cc
        server.cc
        messagehandler.cc
        commandhandler.cc
        databaseserver.cc
)
