#include <iostream>
#include <windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

//����"<<"���㷨�����������ʹ��cout���XMVECTOR����
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
	//����Ƿ�֧��SSE2ָ�
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

	//���v�����ľ���ֵ
	cout << "XMVectorAbs(v) = " << XMVectorAbs(v)<<endl;
	//���w����������ֵ
	cout << "XMVectorCos(w) = " << XMVectorCos(w) << endl;
	//��������ÿ���������������
	cout << "XMVectorLog(u) = " << XMVectorLog(u) << endl;
	//exp()��math.h�ж����ָ����������Ϊ��Ȼ����e������exp��x������ʾe��x�η�
	cout << "XMVectorExp(p) =" << XMVectorExp(p) << endl;
	//����u������p�����η���������ά�ȷֱ����
	cout << "XMVectorPow(u,p) = " << XMVectorPow(u, p) << endl;
	//��������u�Ŀ���
	cout << "XMVectorSqrt(u) = " << XMVectorSqrt(u) << endl;

	cout << "-------------------------" << endl;

	//��������XMVectorSwizzle(v,E0,E1,E2,E3)����2/3/4/5�������ֱ���������ź�������xyzwֵΪԭ�����ĵڼ���������https://learn.microsoft.com/zh-cn/windows/win32/api/directxmath/nf-directxmath-xmvectorswizzle
	cout << "XMVectorSwizzle(u,2,2,1,3) = " << XMVectorSwizzle(u, 2, 2, 1, 3) << endl;
	cout << "XMVectorSwizzle(u,2,1,0,3) =" << XMVectorSwizzle(u, 2, 1, 0, 3) << endl;

	cout << "-------------------------" << endl;

	//���������ĳ˷�
	cout << "XMVectorMultiply(u,v) = " << XMVectorMultiply(u, v) << endl;
	//���������ķ�Χ�޶���0~1
	cout << "XMVectorSaturate(q) = " << XMVectorSaturate(q) << endl;
	//���������������Сֵ
	cout << "XMVectorMin(p , v) = " << XMVectorMin(p, v) << endl;
	//����������������ֵ
	cout << "XMVectorMax(p , v) = " << XMVectorMax(p, v) << endl;

	return 0;
}