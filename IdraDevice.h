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
    /* 红外模块发射一个按键*/
     IDRA_ERR sendKey(int key);
     /* 下载一个按键的编码到红外设备中*/
     IDRA_ERR downloadKey(int key, TKeyCodec codec);
     /* 下载一个按键的编码到红外设备中*/
     IDRA_ERR downloadKey(int key, AnsiString codec);
     /* 红外设备学习一个按键，并返回学习到的编码值,设置超时时间*/
     IDRA_ERR learnKey(int key, AnsiString& codec,int timeoutS);
private:

};
#endif
