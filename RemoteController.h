//---------------------------------------------------------------------------

#ifndef RemoteControllerH
#define RemoteControllerH
#include <classes.hpp>

#include <vector>
#include <map>
#include "CppSQLite3.h"
#include "IdraDevice.h"

typedef std::map<AnsiString,AnsiString>  TDeviceKeyMap;

struct RemoteControlInfo
{
     AnsiString  m_name;
     AnsiString  m_vendor;
     AnsiString  m_softVer;
     AnsiString  m_hardVer;
     AnsiString  m_platform;
     AnsiString  m_property;
     AnsiString  m_city;
     AnsiString  m_cpu;
};
typedef std::map<AnsiString, RemoteControlInfo>  TDeviceInfo;
//---------------------------------------------------------------------------
class RemoteController{
public:
     RemoteController(AnsiString name,IDraDevice* pIdra);
    
     /*load 按键编码到红外发射器中*/
     int load();
     int unLoad();
     /*添加按键和键编码*/
     int addKey(AnsiString keyName, AnsiString keyCodec);
     /*保存按键和键编码*/
     int saveKey();
     /*取消保存*/
     int cancelKey();
     /*修改遥控器的名称*/
     int setDeviceName(AnsiString name);
     int sendKey(AnsiString keyName);

     AnsiString  m_name;


private:
     TDeviceKeyMap  m_keyMap;
     IDraDevice *m_idra;
     CppSQLite3DB m_db;


     
};
#endif
