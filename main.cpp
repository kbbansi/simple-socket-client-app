#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <csignal>

using namespace std;

#define PORT 9000
int clientSocket;
struct sockaddr_in srv;

int main() {
    cout << "Hello, Client Socket" << endl;
    int nRet;

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket < 0) {
        cout << "ERR!! Client Socket not connected " << clientSocket << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Client socket connected successfully " << clientSocket << endl;
    }

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(srv.sin_zero), 0, 8);

    // connect!
    nRet = connect(clientSocket, (struct sockaddr*) & srv, sizeof(srv));
    if (nRet < 0) {
        cout << "Unable to establish connection to server " << nRet << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Connecting....." << endl;
        char buffer[255] = {0, };
        recv(clientSocket, buffer, 255, 0);
        cout << buffer << endl;
        cout << "Send message to Server > " << endl;

        string message;

        do {
            getline(cin, message);
             nRet = send(clientSocket, message.c_str(), message.size() + 1, 0);
            if (nRet == -1) {
                cout << "An error occurred in sending your message " << nRet << endl;
                continue;
            }

            int servRes = recv(clientSocket, buffer, 256, 0 );
            if (servRes > 0) {
                cout << "Server says > " << buffer << endl;
            } else {
                cout << "Server did return any response " << servRes << endl;
                exit(EXIT_FAILURE);
            }
        } while (!message.empty());
    }

}
