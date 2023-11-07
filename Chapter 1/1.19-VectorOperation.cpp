#include <windows.h>
#include <iostream>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

//对"<<"运算符重载，这样就可以通过cout函数输出XMVECTOR对象
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT3 dest;
	XMStoreFloat3(&dest , v);

	os << "(" << dest.x << "," << dest.y << "," << dest.z << ")";
	return os;
}

int main()
{
	cout.setf(ios_base::boolalpha);

	//检查是否支持SSE2指令集（Pentium4 ， AMD K8及其后续版本的处理器）
	if (!XMVerifyCPUSupport())
	{
		cout << "directX math not suppported" << endl;
		return 0;
	}

	//定义向量
	XMVECTOR n = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	XMVECTOR w = XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);

	//向量加法
	XMVECTOR a = u + v;
	//向量减法
	XMVECTOR b = u - v;
	//标量乘法
	XMVECTOR c = 10.0f * u;
	//向量归一化（单位化）
	XMVECTOR d = XMVector3Normalize(u);
	//向量点积
	XMVECTOR e = XMVector3Dot(u, v);	
	//向量叉积
	XMVECTOR f = XMVector3Cross(u, v);
	//求向量长度
	XMVECTOR L = XMVector3Length(u);
	//求出proj_n（w)投影和perp_n（w）透视
	XMVECTOR projW;
	XMVECTOR perpW;
	XMVector3ComponentsFromNormal(&projW, &perpW, w, n);

	//projW + perpW = w?
	bool equal = XMVector3Equal(projW + perpW, w) != 0;
	bool notEqual = XMVector3NotEqual(projW + perpW, w) != 0;

	//projW与perpW之间的夹角应为90度
	XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);
	float angleRadians = XMVectorGetX(angleVec);
	float angleDegrees = XMConvertToDegrees(angleRadians); //弧度转角度

	cout << "u    =" << u << endl;
	cout << "v    =" << v << endl;
	cout << "w    =" << w << endl;
	cout << "n    =" << n << endl;
	cout << "" << endl;					//使用输出空来处理换行

	cout << "----向量计算结果----" << endl;
	cout << "a	= u + v = " << a << endl;
	cout << "b	= u - v = " << b << endl;
	cout << "c	= 10.0f * u " << a << endl;
	cout << "d	= u/|u| = " << d << endl;
	cout << "e	= u · v = " << e << endl;
	cout << "f	= u x v = " << f << endl;
	cout << "L	= |u| =" << L << endl;
	cout << "projW	= " << projW << endl;
	cout << "perpW	= " << perpW << endl;
	cout << "projW + perpW == w =" << equal << endl;
	cout << "projW + perpW != w = " << notEqual << endl;
	cout << "angle = " << angleDegrees << endl;

	return 0;
}