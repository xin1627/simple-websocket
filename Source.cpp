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
//	assert(ws);//判断ws对象是否为空null
//	ws->send("goodbye");
//	ws->send("hello");
//	//如果你需要多线程，可以在一个thread 维护该ws的连接重连机制
//	while (ws->getReadyState() != WebSocket::CLOSED) //判断ws是否正常连接
//	{
//		ws->poll();//这个必须要调用，否则不能发送，发送跟接收都是异步的，都是在这个poll函数里监测处理的
//		ws->dispatch(handle_message);
//	}
//	delete ws;
//	return 0;
//}