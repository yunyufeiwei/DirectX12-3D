//引入当前解决方案中的公共库文件，如果是在当前库的上一层级，则使用../，上两个层级使用../../依次类推 
#include "../Common/d3dApp.h"
#include <DirectXColors.h>
using namespace DirectX;

class InitDirect3DApp :public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();
};

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance):D3DApp(hInstance)
{
}

InitDirect3DApp::~InitDirect3DApp()
{
}
