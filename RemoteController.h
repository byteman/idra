//---------------------------------------------------------------------------

#ifndef RemoteControllerH
#define RemoteControllerH
#include <classes.hpp>

#include <vector>
struct DeviceKey{
    DeviceKey()
    {
       num = 0;
       label = "";
    }
    DeviceKey(int _num, AnsiString _label):
    num(_num),
    label(_label)
    {

    }
   int          num;
   AnsiString   label;
   AnsiString   codec;
};

typedef std::vector<DeviceKey>  TDeviceKey;
//---------------------------------------------------------------------------
class RemoteController{
public:
     RemoteController(AnsiString name);
     /*load �������뵽���ⷢ������*/
     int load();
     /*��Ӱ����ͼ�����*/
     int addKey(AnsiString keyName, AnsiString keyCodec);
     /*���水���ͼ�����*/
     int saveKey();
     /*ȡ������*/
     int cancelKey();
     /*�޸�ң����������*/
     int setDeviceName(AnsiString name);
private:
     TDeviceKey  keylist;
     AnsiString  m_name;
};
#endif
