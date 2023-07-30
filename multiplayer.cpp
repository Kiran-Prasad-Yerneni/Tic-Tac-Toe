#include "multiplayer.h"

Multiplayer::Multiplayer()
    : connection(-1)
    , port(5500)
{
//    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Multiplayer::createServer()
{
    int serverSocketHandler;
    do
    {
        serverSocketHandler = socket(AF_INET , SOCK_STREAM , 0);
    }
    while(serverSocketHandler < 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bindStatus;
    do
    {
        bindStatus = bind(serverSocketHandler , (struct sockaddr*) & serverAddr , sizeof(serverAddr));
    }
    while(bindStatus < 0);
    int listenStatus;
    do
    {
        listenStatus = listen(serverSocketHandler , 1);
    }
    while(listenStatus < 0);

    int clientSocketHandler;
    socklen_t len = sizeof(clientAddr);

    do
    {
        connection = accept(serverSocketHandler , (struct sockaddr*) & clientAddr , &len);
    }
    while(connection < 0);
    close(serverSocketHandler);
}

int Multiplayer::recieve()
{
    int ind;
    int rMsgSize;
    do
    {
        rMsgSize = recv(connection, &ind, sizeof(ind), 0);
    }
    while(rMsgSize < 0);
    if(rMsgSize == 0)
    {
        closeConnection();
        return -1;
    }
    return ind;
}


void Multiplayer::createClient()
{
    do
    {
        connection = socket(AF_INET, SOCK_STREAM, 0);
    }
    while(connection < 0);

    int connectionStatus = connect(connection, (struct sockaddr*) & serverAddr , sizeof(serverAddr));
}

void Multiplayer::sendInd(int ind)
{
    int connectionStatus;
    do
    {
        connectionStatus = send(connection, &ind, sizeof(ind), 0);
    }
    while(connectionStatus < 0);
}

void Multiplayer::closeConnection()
{
    if(connection != -1) {
        close(connection);
    }
    connection = -1;
}

bool Multiplayer::isConnected()
{
    return connection != -1;
}

void Multiplayer::setServerAddress(sockaddr_in serverAddr)
{
    this->serverAddr = serverAddr;
}

void Multiplayer::updatePort(int new_port)
{
    port = new_port;
}

//char* Multiplayer::showMyIP(char *str)
//{
//    inet_ntop(AF_INET, &(serverAddr.sin_addr), str, INET_ADDRSTRLEN);
//    return inet_ntoa(serverAddr.sin_addr);
//    return str;
//}

int Multiplayer::showMyPort()
{
    return port;
}
