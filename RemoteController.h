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
    DeviceKey(int _num, AnsiSring _label):
    num(_num),
    label(_label)
    {

    }
   int          num;
   AnsiString   label;
};

typedef std::vector<DeviceKey>  TDeviceKey;
//---------------------------------------------------------------------------
class RemoteController{
public:
     RemoteController(AnsiString name);
     int load();
private:
    TDeviceKey  keylist;
    AnsiString  m_name;
};
#endif
