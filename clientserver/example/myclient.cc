/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "client_commanddecoder.h"
#include "messagehandler.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;


/* Creates a client for the given args, if possible.
 * Otherwise exits with error code.
 */
std::shared_ptr<Connection> init(int argc, char* argv[])
{
        if (argc != 3) {
                cerr << "Usage: myclient host-name port-number" << endl;
                exit(1);
        }

        int port = -1;
        try {
                port = std::stoi(argv[2]);
        } catch (std::exception& e) {
                cerr << "Wrong port number. " << e.what() << endl;
                exit(2);
        }

        auto conn = std::make_shared<Connection>(argv[1], port);
        if (!conn->isConnected()) {
                cerr << "Connection attempt failed" << endl;
                exit(3);
        }

        return conn;
}

int app(const std::shared_ptr<Connection>& conn)
{
        cout << "Connected to server, To see commands type help_com ";
        string com;
        Client_commanddecoder comdec(conn);
 
        
        while (true) {
                cout << "Type a command: " << endl;
                try {
                        
                        comdec.com_decode(cin);
                        
                        
                } catch (ConnectionClosedException&) {
                        cout << " no reply from server. Exiting." << endl;
                        return 1;
                }
        }
        cout << "\nexiting.\n";
        return 0;
}

int main(int argc, char* argv[])
{
        auto conn = init(argc, argv);
        return app(conn);
}
