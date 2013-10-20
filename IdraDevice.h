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

     IDRA_ERR learnKey(unsigned char codec[128],int timeoutS=5);
     IDRA_ERR sendKey(unsigned char codec[128]);
     IDRA_ERR readKey(int addr,unsigned char codec[128]);
     bool checkDevice(int port);
private:
     unsigned char cmd[256];
     int m_port;
     int m_bps;
     bool m_ok;
};
#endif
