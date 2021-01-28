#include "head.h"


//***********主函数***************
int WINAPI WinMain(HINSTANCE hInstance,		//当前实例句柄
					HINSTANCE hPreInstance,	//先前实例句柄
					LPSTR lpCmdLine,		//命令行指针
					int nShowCmd)			//显示的格式
{			
	
	//1.定义窗口
	WNDCLASSEX window = { 0 };				//window 窗口
	window.cbSize = sizeof(WNDCLASSEX);		//窗口在内存中的大小
	window.cbClsExtra = 0;					//程序的附加内存
	window.cbWndExtra = 0;					//窗口的附加内存

	//GetStockObject 检索预定义的备用刷子
	window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	window.hInstance = hInstance;			//当前实例句柄
	window.style = CS_HREDRAW|CS_VREDRAW;	//窗口样式
	window.lpfnWndProc = WndProc;			//窗口的过程函数
	window.lpszClassName = L"for our dreams";//标题

	window.lpszMenuName = NULL;				//菜单
	window.hCursor = NULL;					//鼠标样式
	window.hIcon = NULL;					//像标

	//2.注册窗口
	RegisterClassEx(&window);			

	//3.创建窗口
	HWND hwnd = CreateWindow(L"for our dreams",	//窗口类
				L"梦幻西游",						//标题
				WS_OVERLAPPEDWINDOW,			//窗口风格
				CW_USEDEFAULT,CW_USEDEFAULT,	//初始化位置
				WND_WIDTH,WND_HEIGHT,			//宽高
				NULL,NULL,hInstance,NULL);


	//4.显示窗口,更新窗口
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);


	//主函数中，对整个程序数据初始化
	if (!GameInit(hwnd)){
		return -1;
	}

	//定义消息
	MSG msg = { 0 }; 
	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			if (Timer()){ //间隔大于80ms
				GamePaint(hwnd);
			}
		}
		
	}
	return 0;
}