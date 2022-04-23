// SendMessage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <afxwin.h>
#include <fstream>
#include <sstream>
#include <chrono>

int main()
{
	auto  start = std::chrono::high_resolution_clock::now();

	std::fstream file;
	file.open("d:\\1.1.2.Õý¶à±ßÐÎ.json", std::ofstream::in);

	if (!file.is_open())
	{
		std::cout << "json file error!";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string contents(buffer.str());
	CString jsonStr(contents.c_str());

	std::string STDStr(CW2A(jsonStr.GetString()));

	CString strMapName(_T("CubeHandleMemory"));  // Share Memory Name
	LPVOID pBuf;                         // Share Memory Pointer
	HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, (LPCTSTR)strMapName);
	HWND hWnd;
	if (NULL != hMap)
	{
		pBuf = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		CString str((TCHAR*)pBuf);
		hWnd = (HWND)_ttoi(str);
		::SendMessage(hWnd, WM_SETTEXT, 40100, (LPARAM)(LPCTSTR)jsonStr);
		LRESULT res = ::SendMessage(hWnd, 40100, 41001, 1001);

		auto  end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "total time:" << diff.count() * 1000 << "ms" << std::endl;
	}
}