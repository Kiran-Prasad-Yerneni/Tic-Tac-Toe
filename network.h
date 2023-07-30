#ifndef NETWORK_H
#define NETWORK_H
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Network
{
private:
    const int port = 5500;
    int connection;
    struct sockaddr_in serverAddr, clientAddr;
public:
    Network();

    void createServer();

    int recieve();

    void sendInd(int ind);

    void createClient();

    void closeConnection();

    bool isConnected();

    void setServerAddress(struct sockaddr_in serverAddr);
};

#endif // NETWORK_H
