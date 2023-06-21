#pragma once

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

class PiQtSocket : public QMainWindow
{
    Q_OBJECT

public:
    PiQtSocket(QWidget *parent = nullptr);
    ~PiQtSocket();

public slots:
    void on_client_send_clicked();
    void on_client2_send_clicked();
    void onMessageReceived(QString message);
private:
    Ui::PiQtSocketClass ui;

    SOCKET client_socket;
    SOCKET client2_socket;
    SOCKET server_socket;
    sockaddr_in server_addr;

    QLineEdit* clientText;
    QLineEdit* client2Text;

    vector<QLabel*> vec1;
    vector<QLabel*> vec2;
    QLabel* client1Label;
    QLabel* client2Label;

    sockaddr_in* client_addr_in;
    sockaddr_in* client2_addr_in;

};
