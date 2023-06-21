#include "ClientThread.h"
ClientThread::ClientThread(QObject* parent)
    : QThread(parent)
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        // ��ʼ��ʧ��
    }

    // �����ͻ����׽��֣�client_socket
    // ������UDP
    // ������Ƿ񴴽��ɹ�
    client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client_socket == INVALID_SOCKET) {
        // ���������socket��Ч�����������
        perror("socket error !\n");
        qDebug() << "client socket error";
    }

    // ������ַ��server_addr�������ö˿ں�IP
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // Ҫ���ӵķ������˿ں� 8887
    server_addr.sin_port = htons(8887);
    // �󶨷������ĵ�ַ127.0.0.1
    PCWSTR ip = L"127.0.0.1";
    InetPton(AF_INET, ip, &server_addr.sin_addr.s_addr);
}

void ClientThread::run()
{
    while (1)
    {
        sockaddr_in server_addr;
        int server_addr_length = sizeof(server_addr);
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (sockaddr*)&server_addr, &server_addr_length);
        if (bytes_received == SOCKET_ERROR) {
            std::cerr << "recvfrom failed: " << WSAGetLastError() << std::endl;
            closesocket(server_socket);
            WSACleanup();
        }

        // ��Ⱦ���ͻ���1
        int wchars_num = MultiByteToWideChar(CP_UTF8, 0, buffer, bytes_received, NULL, 0);
        wchar_t* wstr = new wchar_t[wchars_num];
        MultiByteToWideChar(CP_UTF8, 0, buffer, bytes_received, wstr, wchars_num);
        QString qs = QString::fromWCharArray(wstr);
        emit messageReceived(qs);

        char buffer2[BUFFER_SIZE];
        memset(buffer2, 0, BUFFER_SIZE);
        int bytes_received2 = recvfrom(client2_socket, buffer2, BUFFER_SIZE, 0, (sockaddr*)&server_addr, &server_addr_length);
        if (bytes_received2 == SOCKET_ERROR) {
            std::cerr << "recvfrom failed: " << WSAGetLastError() << std::endl;
            closesocket(server_socket);
            WSACleanup();
        }

        // ��Ⱦ���ͻ���2
        int wchars_num2 = MultiByteToWideChar(CP_UTF8, 0, buffer2, bytes_received2, NULL, 0);
        wchar_t* wstr2 = new wchar_t[wchars_num2];
        MultiByteToWideChar(CP_UTF8, 0, buffer2, bytes_received2, wstr2, wchars_num2);
        QString qs2 = QString::fromWCharArray(wstr2);
        emit messageReceived(qs2);
    }
}
