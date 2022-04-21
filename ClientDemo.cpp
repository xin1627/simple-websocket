////
//// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
////
//// Distributed under the Boost Software License, Version 1.0. (See accompanying
//// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////
//// Official repository: https://github.com/boostorg/beast
////
////------------------------------------------------------------------------------
////
//// Example: WebSocket server, synchronous
////
////------------------------------------------------------------------------------
//#include <boost/beast/core.hpp>
//#include <boost/beast/websocket.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <cstdlib>
//#include <functional>
//#include <iostream>
//#include <string>
//#include <thread>
//#include <codecvt>
//namespace beast = boost::beast;         // from <boost/beast.hpp>
//namespace http = beast::http;           // from <boost/beast/http.hpp>
//namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
//namespace net = boost::asio;            // from <boost/asio.hpp>
//using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
//std::wstring string_to_wstring(const std::string& s)
//{
//	using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
//	static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
//	return conv.from_bytes(s);
//}
//std::string wstring_to_string(const std::wstring& s)
//{
//	using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
//	static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
//	return conv.to_bytes(s);
//}
//std::string ansi_to_utf8(const std::string& s)
//{
//	static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
//	return conv.to_bytes(string_to_wstring(s));
//}
//std::string utf8_to_ansi(const std::string& s)
//{
//	static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
//	return wstring_to_string(conv.from_bytes(s));
//}
////------------------------------------------------------------------------------
//// Echoes back all received WebSocket messages
//void
//do_session(tcp::socket& socket)
//{
//	try
//	{
//		// Construct the stream by moving in the socket
//		websocket::stream<tcp::socket> ws{ std::move(socket) };
//		// Set a decorator to change the Server of the handshake
//		ws.set_option(websocket::stream_base::decorator(
//			[](websocket::response_type& res)
//			{
//				res.set(http::field::server,
//					std::string(BOOST_BEAST_VERSION_STRING) +
//					" websocket-server-sync");
//			}));
//		// Accept the websocket handshake
//		ws.accept();
//		for (;;)
//		{
//			// This buffer will hold the incoming message
//			beast::flat_buffer buffer;
//			// Read a message
//			ws.read(buffer);
//			auto out = beast::buffers_to_string(buffer.cdata());
//			std::cout << utf8_to_ansi(out) << std::endl;
//			// Echo the message back
//			ws.text(ws.got_text());
//			ws.write(buffer.data());
//		}
//	}
//	catch (beast::system_error const& se)
//	{
//		// This indicates that the session was closed
//		if (se.code() != websocket::error::closed)
//			std::cerr << "Error: " << se.code().message() << std::endl;
//	}
//	catch (std::exception const& e)
//	{
//		std::cerr << "Error: " << e.what() << std::endl;
//	}
//}
////------------------------------------------------------------------------------
//int main(int argc, char** argv)
//{
//	try
//	{
//		// The io_context is required for all I/O
//		net::io_context ioc;
//		// These objects perform our I/O
//		tcp::resolver resolver{ ioc };
//		websocket::stream<tcp::socket> ws{ ioc };
//		auto const address = net::ip::make_address("127.0.0.1");
//		auto const port = static_cast<unsigned short>(std::atoi("9100"));
//		tcp::endpoint endpoint{ address, port };
//		// Look up the domain name
//		auto const results = resolver.resolve(endpoint);
//		// Make the connection on the IP address we get from a lookup
//		net::connect(ws.next_layer(), results.begin(), results.end());
//		//net::connect(ws.next_layer(), host, port);
//		// Set a decorator to change the User-Agent of the handshake
//		ws.set_option(websocket::stream_base::decorator(
//			[](websocket::request_type& req)
//			{
//				req.set(http::field::user_agent,
//					std::string(BOOST_BEAST_VERSION_STRING) +
//					" websocket-client-coro");
//			}));
//		// Perform the websocket handshake
//		ws.handshake("0.0.0.0", "/");
//		while (true)
//		{
//			std::string text;
//			std::cin >> text;
//			// Send the message
//			ws.write(net::buffer(ansi_to_utf8(text)));
//			// This buffer will hold the incoming message
//			beast::flat_buffer buffer;
//			// Read a message into our buffer
//			ws.read(buffer);
//			std::string out;
//			out = beast::buffers_to_string(buffer.cdata());
//			std::cout << utf8_to_ansi(out) << std::endl;
//		}
//		// Close the WebSocket connection
//		ws.close(websocket::close_code::normal);
//	}
//	catch (std::exception const& e)
//	{
//		std::cerr << "Error: " << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//	return EXIT_SUCCESS;
//}