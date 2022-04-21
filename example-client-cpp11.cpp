// Compile with:
// g++ -std=gnu++0x example-client-cpp11.cpp -o example-client-cpp11
#include "easywsclient.hpp"
//#include "easywsclient.cpp" // <-- include only if you don't want compile separately
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>


using easywsclient::WebSocket;

static WebSocket::pointer ws = NULL;

void handle_message(const std::string& message)
{
	printf(">>> %s\n", message.c_str());
	if (message == "world") { ws->close(); }
}


int main()
{
    //using namespace std;
    
#ifdef _WIN32
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        return 1;
    }
#endif

    std::fstream file;
    file.open("d:\\test.json", std::ofstream::in);

    if (!file.is_open())
    {
        std::cout << "json file error!";
    }

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string contents(buffer.str());

    ws = WebSocket::from_url("ws://localhost:9100");
    //std::unique_ptr<WebSocket> ws(WebSocket::from_url("ws://localhost:9100"));
    assert(ws);
    ws->send(contents);
    while(ws->getReadyState() != WebSocket::CLOSED) {
        //WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
        ws->poll();
        ws->dispatch(handle_message);       
    }
	//while (ws->getReadyState() != WebSocket::CLOSED) {
	//	WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
	//	ws->poll();
	//	ws->dispatch([wsp](const std::string& message) {
	//		printf(">>> %s\n", message.c_str());
	//		if (message == "world") { wsp->close(); }
	//		});
	//}
    
#ifdef _WIN32
    WSACleanup();
#endif
    // N.B. - unique_ptr will free the WebSocket instance upon return:
    return 0;
}
