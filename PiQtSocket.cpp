#include "PiQtSocket.h"
#include <winsock2.h>
#include "ClientThread.h"

PiQtSocket::PiQtSocket(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	clientText = this->findChild<QLineEdit*>("clientText");
	client2Text = this->findChild<QLineEdit*>("client2Text");

	client1Label = this->findChild<QLabel*>("client1Label");
	client2Label = this->findChild<QLabel*>("client2Label");
	vec1.push_back(client1Label);
	vec2.push_back(client2Label);

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{

	}
	/*
	�����ͻ����׽��֣�client_socket
	������UDP
	������Ƿ񴴽��ɹ�
	*/
	client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (client_socket == INVALID_SOCKET) {
		//���������socket��Ч�����������
		perror("socket error !\n");
		qDebug() << "client socket error";
	}
	/*
	������ַ��server_addr�������ö˿ں�IP
	*/
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	//Ҫ���ӵķ������˿ں� 8887
	server_addr.sin_port = htons(8887);
	//�󶨷������ĵ�ַ127.0.0.1
	PCWSTR ip = L"127.0.0.1";
	InetPton(AF_INET, ip, &server_addr.sin_addr.s_addr);
	qDebug() << "client 1 Initialized";


	client2_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (client2_socket == INVALID_SOCKET) {
		//���������socket��Ч�����������
		perror("socket error !\n");
		qDebug() << "client socket error";
	}
	/*
	������ַ��server_addr�������ö˿ں�IP
	*/
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	//Ҫ���ӵķ������˿ں� 8887
	server_addr.sin_port = htons(8887);
	//�󶨷������ĵ�ַ127.0.0.1
	InetPton(AF_INET, ip, &server_addr.sin_addr.s_addr);
	qDebug() << "client 2 Initialized";

	//while (1)
	//{
	//	sockaddr_in server_addr;
	//	int server_addr_length = sizeof(server_addr);
	//	char buffer[BUFFER_SIZE];
	//	memset(buffer, 0, BUFFER_SIZE);
	//	int bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (sockaddr*)&server_addr, &server_addr_length);
	//	if (bytes_received == SOCKET_ERROR) {
	//		std::cerr << "recvfrom failed: " << WSAGetLastError() << std::endl;
	//		closesocket(server_socket);
	//		WSACleanup();
	//	}
	//	//��Ⱦ���ͻ���1
	//	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, buffer, bytes_received, NULL, 0);
	//	wchar_t* wstr = new wchar_t[wchars_num];
	//	MultiByteToWideChar(CP_UTF8, 0, buffer, bytes_received, wstr, wchars_num);
	//	int str_len = WideCharToMultiByte(CP_ACP, 0, wstr, wchars_num, NULL, 0, NULL, NULL);
	//	char* str = new char[str_len];
	//	WideCharToMultiByte(CP_ACP, 0, wstr, wchars_num, str, str_len, NULL, NULL);

	//	clientText->text()=str;

	//	char buffer2[BUFFER_SIZE];
	//	memset(buffer2, 0, BUFFER_SIZE);
	//	int bytes_received2 = recvfrom(client2_socket, buffer2, BUFFER_SIZE, 0, (sockaddr*)&server_addr, &server_addr_length);
	//	if (bytes_received2 == SOCKET_ERROR) {
	//		std::cerr << "recvfrom failed: " << WSAGetLastError() << std::endl;
	//		closesocket(server_socket);
	//		WSACleanup();
	//	}

	//	//��Ⱦ���ͻ���2
	//	int wchars_num2 = MultiByteToWideChar(CP_UTF8, 0, buffer2, bytes_received2, NULL, 0);
	//	wchar_t* wstr2 = new wchar_t[wchars_num2];
	//	MultiByteToWideChar(CP_UTF8, 0, buffer2, bytes_received2, wstr2, wchars_num2);
	//	int str_len2 = WideCharToMultiByte(CP_ACP, 0, wstr2, wchars_num2, NULL, 0, NULL, NULL);
	//	char* str2 = new char[str_len2];
	//	WideCharToMultiByte(CP_ACP, 0, wstr2, wchars_num2, str2, str_len2, NULL, NULL);
	//	client2Text->text() = str2;
	//}
}

//PiQtSocket::PiQtSocket(QWidget* parent)
//	: QMainWindow(parent)
//{
//	ui.setupUi(this);
//	clientText = this->findChild<QLineEdit*>("clientText");
//	client2Text = this->findChild<QLineEdit*>("client2Text");
//
//	// ����ClientThread����
//	ClientThread* clientThread = new ClientThread(this);
//	connect(clientThread, &ClientThread::messageReceived, this, &PiQtSocket::onMessageReceived);
//	clientThread->start();
//}

void PiQtSocket::onMessageReceived(QString message)
{
	// �ڽ�������ʾ���յ�����Ϣ
	clientText->setText(message);
	client2Text->setText(message);
}

PiQtSocket::~PiQtSocket()
{
	closesocket(client_socket);

	WSACleanup();
}

void PiQtSocket::on_client_send_clicked()
{
	qDebug() << "clicke send";
	//�ͻ��˷��Ͱ�ť����¼�
	QString QS = clientText->text();

	QByteArray utf8_data = QS.toUtf8();
	const char* sendbuf = utf8_data.data();

	if (sendto(client_socket, sendbuf, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, sizeof(SOCKADDR)) == -1)
	{
		qDebug() << "send error";
	}
	/*QLabel* newLabel = new QLabel(this->vec2[vec2.size()-1]);
	qDebug() << "1�յ���" << QS;
	newLabel->setText(QS);
	for (auto i : vec2) {
		i->move(i->x(), i->y() - newLabel->height());
	}
	vec2.push_back(newLabel);*/
	client2Label->setText(QS);
	clientText->clear();
}

void PiQtSocket::on_client2_send_clicked()
{
	qDebug() << "clicke send";
	//�ͻ��˷��Ͱ�ť����¼�
	QString QS = client2Text->text();

	QByteArray utf8_data = QS.toUtf8();
	const char* sendbuf = utf8_data.data();

	if (sendto(client2_socket, sendbuf, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, sizeof(SOCKADDR)) == -1)
	{
		qDebug() << "send error";
	}
	/*QLabel* newLabel = new QLabel(this->vec1[vec1.size() - 1]);
	qDebug()<<"2�յ���"<<QS;
	newLabel->setText(QS);
	for (auto i : vec1) {
		i->move(i->x(), i->y() - newLabel->height());
	}
	vec1.push_back(newLabel);*/
	client1Label->setText(QS);
	client2Text->clear();
}