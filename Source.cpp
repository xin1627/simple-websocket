//#include "easywsclient.hpp"
//#include <assert.h>
//#include <stdio.h>
//#include <string>
//
//using easywsclient::WebSocket;
//static WebSocket::pointer ws = NULL;
//
//void handle_message(const std::string& message)
//{
//	printf(">>> %s\n", message.c_str());
//	if (message == "world") { ws->close(); }
//}
//
//int main()
//{
//	ws = WebSocket::from_url("ws://localhost:8126/foo");
//	assert(ws);//�ж�ws�����Ƿ�Ϊ��null
//	ws->send("goodbye");
//	ws->send("hello");
//	//�������Ҫ���̣߳�������һ��thread ά����ws��������������
//	while (ws->getReadyState() != WebSocket::CLOSED) //�ж�ws�Ƿ���������
//	{
//		ws->poll();//�������Ҫ���ã������ܷ��ͣ����͸����ն����첽�ģ����������poll�������⴦���
//		ws->dispatch(handle_message);
//	}
//	delete ws;
//	return 0;
//}