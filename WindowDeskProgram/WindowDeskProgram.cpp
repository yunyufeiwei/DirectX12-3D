#include <Windows.h>                                        //包含Window头文件，其中含有编写Window应用程序所需的所有win32 API结构体、数据类型以及函数的声明

HWND ghMainWnd = 0;                                         //用于指认所创建的主窗口句柄

//函数回调，在后面实现的函数，需要再前面回调，否则WinMain函数的入口无法获取到函数体的内容
bool InitWindowsApp(HINSTANCE instanceHandle, int show);    //封装初始化Windows应用程序所需的代码，如果初始化成功，该函数返回true，否则返回false
int Run();                                                  //封装消息循环代码

//窗口过程会处理窗口所接受到的消息
LRESULT CALLBACK
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//在Windows应用程序中的WinMain函数就相当于大多数语言中的main()函数
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdshow)
{
    if (!InitWindowsApp(hInstance, nCmdshow))
        return 0;

    return Run();
}

//初始化Windows应用程序所需的代码
bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{
    //通过填写WNDCLASS结构体，并根据描述的特征来创建一个窗口，该结构体类型由Windows系统自己定义
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;             //窗口样式
    wc.lpfnWndProc = WndProc;                       //窗口过程函数的指针
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instanceHandle;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"BasicWndClass";

    //在Windows系统中为上午WNSCLASS注册一个实例，如果注册失败则打印Log，直接返回false
    if (!RegisterClass(&wc))
    {
        MessageBox(0, L"RegisterClass FAILED", 0, 0);
        return false;
    }
    //第一个参数表示了注册的WNDCLASS实力，第二个参数表示了窗口标题，第三个参数表示了窗口的样式，第四个参数表示了x坐标，第五个参数表示了y坐标，第六个参数表示了窗口的宽度，第七个参数表示了窗口的高度
    //第八个参数表示了父窗口，第九个参数表示了菜单句柄，第十个参数表示了应用程序实例句柄，第十一参数表示可以在次设置一些创建窗口所用的其他参数
    ghMainWnd = CreateWindow(L"BasicWndClass", L"Win32Basic", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

    if (ghMainWnd == 0)
    {
        MessageBox(0, L"CreateWindow FAILED", 0, 0);
        return false
            ;
    }
    ShowWindow(ghMainWnd, show);
    UpdateWindow(ghMainWnd);

    return true;    //返回true则初始化成功
}

//消息循环代码
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
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
