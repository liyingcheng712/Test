// ConsoleApplication3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <chrono>
#include "CpuUsage.h"
#include <windows.h>
#include <mutex>

DWORD WINAPI EatItThreadProc(LPVOID lpParam);
DWORD WINAPI WatchItThreadProc(LPVOID lpParam);
CpuUsage usage;

using namespace std;
void fun() {
	cout << std::this_thread::get_id() << endl;
	while (1);
}
void fun1() {
	cout << std::this_thread::get_id() << endl;
	while (true)
	{

	}
	std::this_thread::sleep_for(std::chrono::microseconds(100000));

}
int main(int argc ,char* argv[])
{
	//创建线程消耗cpu时间
	CreateThread(NULL,0,EatItThreadProc,NULL,0,NULL);
	CreateThread(NULL, 0, EatItThreadProc, NULL, 0, NULL);
		//创建线程监视当前进程的cpu占用率
	CreateThread(NULL,0,WatchItThreadProc,NULL,0,NULL);
	CreateThread(NULL, 0, WatchItThreadProc, NULL, 0, NULL);
	while (true) {
		Sleep(1000);
	}
	return 0;
	
}
DWORD WINAPI WatchItThreadProc(LPVOID lpParam) {
	while (true) {
		double cpuUsage = (double)usage.GetUsage();
		printf("Thread id %d:%0.2f%% cpu usage\n",::GetCurrentThreadId(),cpuUsage);
		Sleep(1000);
	}
}
DWORD WINAPI EatItThreadProc(LPVOID lpPram) {
	ULONGLONG accum = 0;
	int *p;
	while (true) {
		p = new int[10];
		delete p;
		accum++;
	}
	
	printf("%64d\n",accum);
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
