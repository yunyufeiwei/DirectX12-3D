#include <windows.h>
#include <iostream>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

//��"<<"��������أ������Ϳ���ͨ��cout�������XMVECTOR����
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

	//����Ƿ�֧��SSE2ָ���Pentium4 �� AMD K8��������汾�Ĵ�������
	if (!XMVerifyCPUSupport())
	{
		cout << "directX math not suppported" << endl;
		return 0;
	}

	//��������
	XMVECTOR n = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	XMVECTOR w = XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);

	//�����ӷ�
	XMVECTOR a = u + v;
	//��������
	XMVECTOR b = u - v;
	//�����˷�
	XMVECTOR c = 10.0f * u;
	//������һ������λ����
	XMVECTOR d = XMVector3Normalize(u);
	//�������
	XMVECTOR e = XMVector3Dot(u, v);	
	//�������
	XMVECTOR f = XMVector3Cross(u, v);
	//����������
	XMVECTOR L = XMVector3Length(u);
	//���proj_n��w)ͶӰ��perp_n��w��͸��
	XMVECTOR projW;
	XMVECTOR perpW;
	XMVector3ComponentsFromNormal(&projW, &perpW, w, n);

	//projW + perpW = w?
	bool equal = XMVector3Equal(projW + perpW, w) != 0;
	bool notEqual = XMVector3NotEqual(projW + perpW, w) != 0;

	//projW��perpW֮��ļн�ӦΪ90��
	XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);
	float angleRadians = XMVectorGetX(angleVec);
	float angleDegrees = XMConvertToDegrees(angleRadians); //����ת�Ƕ�

	cout << "u    =" << u << endl;
	cout << "v    =" << v << endl;
	cout << "w    =" << w << endl;
	cout << "n    =" << n << endl;
	cout << "" << endl;					//ʹ���������������

	cout << "----����������----" << endl;
	cout << "a	= u + v = " << a << endl;
	cout << "b	= u - v = " << b << endl;
	cout << "c	= 10.0f * u " << a << endl;
	cout << "d	= u/|u| = " << d << endl;
	cout << "e	= u �� v = " << e << endl;
	cout << "f	= u x v = " << f << endl;
	cout << "L	= |u| =" << L << endl;
	cout << "projW	= " << projW << endl;
	cout << "perpW	= " << perpW << endl;
	cout << "projW + perpW == w =" << equal << endl;
	cout << "projW + perpW != w = " << notEqual << endl;
	cout << "angle = " << angleDegrees << endl;

	return 0;
}