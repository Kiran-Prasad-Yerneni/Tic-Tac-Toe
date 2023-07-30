#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Multiplayer
{
private:
    int port;
    int connection;
    sockaddr_in serverAddr, clientAddr;
public:
    Multiplayer();

    void createServer();

    int recieve();

    void sendInd(int ind);

    void createClient();

    void closeConnection();

    bool isConnected();

    void setServerAddress(struct sockaddr_in serverAddr);

    void updatePort(int new_port);

//    char * showMyIP(char *);
    int showMyPort();
};

#endif // MULTIPLAYER_H
