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
    
     /*load �������뵽���ⷢ������*/
     int load();
     int unLoad();
     /*��Ӱ����ͼ�����*/
     int addKey(AnsiString keyName, AnsiString keyCodec);
     /*���水���ͼ�����*/
     int saveKey();
     /*ȡ������*/
     int cancelKey();
     /*�޸�ң����������*/
     int setDeviceName(AnsiString name);
     int sendKey(AnsiString keyName);

     AnsiString  m_name;


private:
     TDeviceKeyMap  m_keyMap;
     IDraDevice *m_idra;
     CppSQLite3DB m_db;


     
};
#endif
