//---------------------------------------------------------------------------

#ifndef IdraDeviceH
#define IdraDeviceH
#include <iostream>
#include <vector>
#include <classes.hpp>
//---------------------------------------------------------------------------
enum IDRA_ERR{
   IDRA_ERR_OK,
};
typedef  std::vector<unsigned char> TKeyCodec;
class IDraDevice
{
public:
     IDRA_ERR openDev(int port ,int bps=9600);
     IDRA_ERR closeDev();
    /* ����ģ�鷢��һ������*/
     IDRA_ERR sendKey(int key);
     /* ����һ�������ı��뵽�����豸��*/
     IDRA_ERR downloadKey(int key, TKeyCodec codec);
     /* ����һ�������ı��뵽�����豸��*/
     IDRA_ERR downloadKey(int key, AnsiString codec);
     /* �����豸ѧϰһ��������������ѧϰ���ı���ֵ,���ó�ʱʱ��*/
     IDRA_ERR learnKey(int key, AnsiString& codec,int timeoutS);
private:

};
#endif
