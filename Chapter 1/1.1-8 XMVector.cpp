//#include <iostream>
//#include <windows.h>
////#include "../Common/MathHelper.h"           //ʹ��../������һ��Ŀ¼������Ƕ༶��������
//#include <DirectXMath.h>
//#include <DirectXpackedVector.h>
//using namespace std;
//using namespace DirectX;
//using namespace DirectX::PackedVector;
//
//ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
//{
//    XMFLOAT3 dest;
//    XMStoreFloat3(&dest, v);
//
//    os << "(" << dest.x << "," << dest.y << "," << dest.z << ")";
//    return os;
//}
//
//int main()
//{
//    cout.setf(ios_base::boolalpha);
//
//    if (!XMVerifyCPUSupport())
//    {
//        cout << "directx math nont supported" << endl;
//        return 0;
//    }
//
//    XMVECTOR p = XMVectorZero();                                    //XMVectorZero()����0����
//    XMVECTOR q = XMVectorSplatOne();                                //����������1,1,1,1��
//    XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);               //XMVectorSet��float x ,float y ,float z,float w)����������float x ,float y ,float z,float w)
//    XMVECTOR v = XMVectorReplicate(-2.0f);                          //XMVectorReplicate(float Value)��������(value,value,value,value)
//    XMVECTOR w = XMVectorSplatZ(u);                                 //XMVectorSplatZ(vz,vz,vz,vz)��������(vz,vz,vz,vz)
//
//    cout << "p = " << p << endl;
//    cout << "q = " << q << endl;
//    cout << "u = " << u << endl;
//    cout << "v = " << v << endl;
//    cout << "w = " << w << endl;
//
//    return 0;
//}