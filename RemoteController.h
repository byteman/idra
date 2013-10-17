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
    
     /*load �������뵽���ⷢ������*/
     bool load(AnsiString name);
     int unLoad();
     bool isLoad();

     /*�жϼ����Ƿ����*/
     bool existKeyName(AnsiString keyName);

     /*��Ӱ����ͼ�����*/
     bool addKey(AnsiString keyName, AnsiString keyCodec);

     /*���°�����Ӧ�ļ�����*/
     bool updateKey(AnsiString keyName, AnsiString keyCodec);

     /*�޸�ң����������*/
     int  setDeviceName(AnsiString name);
     /*��ȡ��������Ӧ�ı���*/
     bool getKeyCodec(AnsiString keyName,AnsiString &codec);
     /*�г���ң�������еİ�������*/
     bool listKey(TKeyNameList& keylist);
     AnsiString  m_name;


private:
     TDeviceKeyMap  m_keyMap;

     CppSQLite3DB m_db;
     bool m_load;


     
};
#endif
