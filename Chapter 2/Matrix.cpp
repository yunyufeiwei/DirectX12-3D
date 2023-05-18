#include <iostream>
#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

//����"<<"����������XMVECTOR����
ostream& XM_CALLCONV operator << (ostream& os, FXMVECTOR v)
{
    XMFLOAT4 dest;
    XMStoreFloat4(&dest, v);

    os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << ")";
    return os;
}
//����"<<"����������XMMATRIX����
ostream& XM_CALLCONV operator << (ostream& os, FXMMATRIX m)
{
    for (int i = 0; i < 4; i++)
    {
        os << XMVectorGetX(m.r[i]) << "\t";
        os << XMVectorGetY(m.r[i]) << "\t";
        os << XMVectorGetZ(m.r[i]) << "\t";
        os << XMVectorGetW(m.r[i]);
        os << endl;
    }
    return os;
}

int main()
{
    if (!XMVerifyCPUSupport())
    {
        cout << "directx math not supported" << endl;
        return 0;
    }

    XMMATRIX A( 1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 2.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 4.0f, 0.0f,
                1.0f, 2.0f, 3.0f, 1.0f);
    //XMMatrixIdentity��λ����
    XMMATRIX B = XMMatrixIdentity();
    //����˷�
    XMMATRIX C = A * B;
    //ת�þ���
    XMMATRIX D = XMMatrixTranspose(A);
    //��������ʽ
    XMVECTOR det = XMMatrixDeterminant(A);
    //�����
    XMMATRIX E = XMMatrixInverse(&det, A);
    //ԭ�������������˵��ڵ�λ����
    XMMATRIX F = A * E;

    cout << "A = " << endl << A << endl;
    cout << "B = " << endl << B << endl;
    cout << "C = A * B = " << endl << C << endl;
    cout << "D = transpose(A) = " << endl << D << endl;
    cout << "det = determinant(A) = " << det << endl << endl;
    cout << "E = inverse(A) = " << endl << E << endl;
    cout << "F = A * E =" << endl << F << endl;

    /*XMMATRIX mat1(-2.0f, 0.0f, 3.0f,
               4.0f, 1.0f, -1.0f);
    XMMATRIX mat2(2.0f, -1.0f,
        0.0f, 6.0f,
        2.0f, -3.0f);
    XMMATRIX mat = mat1 * mat2;
    cout << mat << endl;*/

    return 0;
}

