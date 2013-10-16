//---------------------------------------------------------------------------

#ifndef IdraDeviceH
#define IdraDeviceH
#include <iostream>
#include <vector>
#include <classes.hpp>
//---------------------------------------------------------------------------
enum IDRA_ERR{
   IDRA_ERR_OK,
   IDRA_BADPORT,
   IDRA_OPENFAIL ,
   IDRA_TIMEOUT,
   IDRA_INVALID,
   IDRA_UNKNOWN,
};
typedef  std::vector<unsigned char> TKeyCodec;
class IDraDevice
{
public:
     IDraDevice();
     IDRA_ERR openDev(int port ,int bps=9600);
     IDRA_ERR closeDev();
    /* 红外模块发射一个按键*/
     IDRA_ERR sendKey(int key);
     /* 下载一个按键的编码到红外设备中*/
     IDRA_ERR downloadKey(int key, TKeyCodec codec);
     /* 下载一个按键的编码到红外设备中*/
     IDRA_ERR downloadKey(int key, AnsiString codec);
     /* 红外设备学习一个按键，并返回学习到的编码值,设置超时时间*/
     IDRA_ERR learnKey(int key, AnsiString& codec,int timeoutS);


     IDRA_ERR learnKey(unsigned char codec[128],int timeoutS=5);
     IDRA_ERR sendKey(unsigned char codec[128]);
private:
     unsigned char cmd[256];
     int m_port;
     int m_bps;
     bool m_ok;
};
#endif
