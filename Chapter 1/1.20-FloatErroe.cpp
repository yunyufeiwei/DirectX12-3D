#include <Windows.h>
#include <iostream>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

int main()
{
	cout.precision(8);

	//检查是否支持SSE2指令集（pentium4 , AMD k8及其后续版本的处理器)
	if (!XMVerifyCPUSupport())
	{
		cout << "directx math not supported" << endl;
		return 0;
	}

	XMVECTOR u = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR n = XMVector3Normalize(u);

	//求向量在X方向上的长度
	float LU = XMVectorGetX(XMVector3Length(n));

	//在数学上，此向量的长度应当为1
	cout << LU << endl;
	if (LU == 1.0f)
	{
		cout << "Length 1" << endl;
	}
	else
	{
		cout << "Length not 1" << endl;
	}

	float powLU = powf(LU, 1.0);
	cout << "LU (10∧6) = " << powLU << endl;

	return 0;
}