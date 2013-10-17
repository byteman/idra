//---------------------------------------------------------------------------

#ifndef RemoteControllerH
#define RemoteControllerH
#include <classes.hpp>

#include <vector>
#include <map>
#include "CppSQLite3.h"
#include "IdraDevice.h"

typedef std::map<AnsiString,AnsiString>  TDeviceKeyMap;
typedef std::vector<AnsiString> TKeyNameList;
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
     RemoteController();
    
     /*load 按键编码到红外发射器中*/
     bool load(AnsiString name);
     int unLoad();
     bool isLoad();

     /*判断键名是否存在*/
     bool existKeyName(AnsiString keyName);

     /*添加按键和键编码*/
     bool addKey(AnsiString keyName, AnsiString keyCodec);

     /*更新按键对应的键编码*/
     bool updateKey(AnsiString keyName, AnsiString keyCodec);

     /*修改遥控器的名称*/
     int  setDeviceName(AnsiString name);
     /*获取按键所对应的编码*/
     bool getKeyCodec(AnsiString keyName,AnsiString &codec);
     /*列出该遥控器所有的按键名称*/
     bool listKey(TKeyNameList& keylist);
     AnsiString  m_name;


private:
     TDeviceKeyMap  m_keyMap;

     CppSQLite3DB m_db;
     bool m_load;


     
};
#endif
