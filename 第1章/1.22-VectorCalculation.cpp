#include <iostream>
#include <windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

//重载"<<"运算法，这样便可以使用cout输出XMVECTOR对象
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	os << "(" << dest.x << "," << dest.y << "," << dest.z << "," << dest.w << ")";
	return os;
}

int main()
{
	cout.setf(ios_base::boolalpha);
	//检查是否支持SSE2指令集
	if (!XMVerifyCPUSupport())
	{
		cout << "directx math not supported" << endl;
		return 0;
	}

	XMVECTOR p = XMVectorSet(2.0f, 2.0f, 1.0f, 0.0f);
	XMVECTOR q = XMVectorSet(2.0f, -0.5f, 0.5f, 0.1f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 4.0f, 8.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 2.5f);
	XMVECTOR w = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);

	//输出v向量的绝对值
	cout << "XMVectorAbs(v) = " << XMVectorAbs(v)<<endl;
	//输出w向量的余弦值
	cout << "XMVectorCos(w) = " << XMVectorCos(w) << endl;
	//计算向量每个组件的两个基数
	cout << "XMVectorLog(u) = " << XMVectorLog(u) << endl;
	//exp()是math.h中定义的指数函数，底为自然对数e。比如exp（x），表示e的x次方
	cout << "XMVectorExp(p) =" << XMVectorExp(p) << endl;
	//计算u向量的p向量次方，向量的维度分别输出
	cout << "XMVectorPow(u,p) = " << XMVectorPow(u, p) << endl;
	//计算向量u的开方
	cout << "XMVectorSqrt(u) = " << XMVectorSqrt(u) << endl;

	cout << "-------------------------" << endl;

	//向量重排XMVectorSwizzle(v,E0,E1,E2,E3)，第2/3/4/5个参数分别决定了重排后向量的xyzw值为原向量的第几个索引。https://learn.microsoft.com/zh-cn/windows/win32/api/directxmath/nf-directxmath-xmvectorswizzle
	cout << "XMVectorSwizzle(u,2,2,1,3) = " << XMVectorSwizzle(u, 2, 2, 1, 3) << endl;
	cout << "XMVectorSwizzle(u,2,1,0,3) =" << XMVectorSwizzle(u, 2, 1, 0, 3) << endl;

	cout << "-------------------------" << endl;

	//计算向量的乘法
	cout << "XMVectorMultiply(u,v) = " << XMVectorMultiply(u, v) << endl;
	//计算向量的范围限定在0~1
	cout << "XMVectorSaturate(q) = " << XMVectorSaturate(q) << endl;
	//输出两个向量的最小值
	cout << "XMVectorMin(p , v) = " << XMVectorMin(p, v) << endl;
	//输出两个向量的最大值
	cout << "XMVectorMax(p , v) = " << XMVectorMax(p, v) << endl;

	return 0;
}