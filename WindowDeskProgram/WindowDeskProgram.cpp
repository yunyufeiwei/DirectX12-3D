#include <Windows.h>            //包含Window头文件，其中含有编写Window应用程序所需的所有win32 API结构体、数据类型以及函数的声明

HWND ghMainWnd = 0;             //用于指认所创建的主窗口句柄

bool InitWindowsApp(HINSTANCE instanceHandle, int show);    //封装初始化Windows应用程序所需的代码，如果初始化成功，该函数返回true，否则返回false
int Run();                                                  //封装消息循环代码

//窗口过程会处理窗口所接受到的消息
LRESULT CALLBACK
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdshow)
{
    if (!InitWindowsApp(hInstance, nCmdshow))
        return 0;

    return Run();
}


bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instanceHandle;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"BasicWndClass";

    if (!RegisterClass(&wc))
    {
        MessageBox(0, L"RegisterClass FAILED", 0, 0);
        return false;
    }

    ghMainWnd = CreateWindow(L"BasicWndClass", L"Win32Basic", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

    if (ghMainWnd == 0)
    {
        MessageBox(0, L"CreateWindow FAILED", 0, 0);
        return false
            ;
    }
    ShowWindow(ghMainWnd, show);
    UpdateWindow(ghMainWnd);
}

int Run()
{
    MSG msg = { 0 };

    BOOL bRet = 1;

    while ((bRet = GetMessage(&msg, 0, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            MessageBox(0, L"GetMessage FAILED", L"Error", MB_OK);
            break;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        MessageBox(0, L"Hello,World", L"Hello", MB_OK);
        return 0;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            DestroyWindow(ghMainWnd);
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
