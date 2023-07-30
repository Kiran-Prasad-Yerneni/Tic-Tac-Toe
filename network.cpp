#include "network.h"

Network::Network()
    : connection(-1)
{

}

void Network::createServer()
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

int Network::recieve()
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


void Network::createClient()
{
    do
    {
        connection = socket(AF_INET, SOCK_STREAM, 0);
    }
    while(connection < 0);

    int connectionStatus;
    do
    {
        connectionStatus = connect(connection, (struct sockaddr*) & serverAddr , sizeof(serverAddr));
    }
    while(connectionStatus < 0);
}

void Network::sendInd(int ind)
{
    int connectionStatus;
    do
    {
        connectionStatus = send(connection, &ind, sizeof(ind), 0);
    }
    while(connectionStatus < 0);
}

void Network::closeConnection()
{
    if(connection != -1) {
        close(connection);
    }
    connection = -1;
}

bool Network::isConnected()
{
    return connection != -1;
}

void Network::setServerAddress(sockaddr_in serverAddr)
{
    this->serverAddr = serverAddr;
}
