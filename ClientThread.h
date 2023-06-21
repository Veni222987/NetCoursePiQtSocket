#pragma once
#include <qthread.h>
#include <QtWidgets/QMainWindow>
#include "ui_PiQtSocket.h"

#include <tchar.h>
#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>   
#include <string.h>  
#include <string>
#include <Ws2tcpip.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

#define BUFFER_SIZE 2048

using namespace std;
class ClientThread : public QThread
{
    Q_OBJECT

public:
    ClientThread(QObject* parent = nullptr);
    void run() override;

signals:
    void messageReceived(QString message);

private:
    SOCKET client_socket;
    SOCKET client2_socket;
    sockaddr_in server_addr;

    SOCKET server_socket;
};


