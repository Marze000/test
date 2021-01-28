#include "head.h"


//***********������***************
int WINAPI WinMain(HINSTANCE hInstance,		//��ǰʵ�����
					HINSTANCE hPreInstance,	//��ǰʵ�����
					LPSTR lpCmdLine,		//������ָ��
					int nShowCmd)			//��ʾ�ĸ�ʽ
{			
	
	//1.���崰��
	WNDCLASSEX window = { 0 };				//window ����
	window.cbSize = sizeof(WNDCLASSEX);		//�������ڴ��еĴ�С
	window.cbClsExtra = 0;					//����ĸ����ڴ�
	window.cbWndExtra = 0;					//���ڵĸ����ڴ�

	//GetStockObject ����Ԥ����ı���ˢ��
	window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	window.hInstance = hInstance;			//��ǰʵ�����
	window.style = CS_HREDRAW|CS_VREDRAW;	//������ʽ
	window.lpfnWndProc = WndProc;			//���ڵĹ��̺���
	window.lpszClassName = L"for our dreams";//����

	window.lpszMenuName = NULL;				//�˵�
	window.hCursor = NULL;					//�����ʽ
	window.hIcon = NULL;					//���

	//2.ע�ᴰ��
	RegisterClassEx(&window);			

	//3.��������
	HWND hwnd = CreateWindow(L"for our dreams",	//������
				L"�λ�����",						//����
				WS_OVERLAPPEDWINDOW,			//���ڷ��
				CW_USEDEFAULT,CW_USEDEFAULT,	//��ʼ��λ��
				WND_WIDTH,WND_HEIGHT,			//���
				NULL,NULL,hInstance,NULL);


	//4.��ʾ����,���´���
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);


	//�������У��������������ݳ�ʼ��
	if (!GameInit(hwnd)){
		return -1;
	}

	//������Ϣ
	MSG msg = { 0 }; 
	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			if (Timer()){ //�������80ms
				GamePaint(hwnd);
			}
		}
		
	}
	return 0;
}