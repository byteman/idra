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
     /*load 按键编码到红外发射器中*/
     int load();
     /*添加按键和键编码*/
     int addKey(AnsiString keyName, AnsiString keyCodec);
     /*保存按键和键编码*/
     int saveKey();
     /*取消保存*/
     int cancelKey();
     /*修改遥控器的名称*/
     int setDeviceName(AnsiString name);
private:
     TDeviceKey  keylist;
     AnsiString  m_name;
};
#endif
