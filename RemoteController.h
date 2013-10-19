//---------------------------------------------------------------------------

#ifndef RemoteControllerH
#define RemoteControllerH
#include <classes.hpp>

#include <vector>
#include <map>
#include "CppSQLite3.h"
#include "IdraDevice.h"

enum TKeyType{
   TYPE_STAND = 0,
   TYPE_USER,
   TYPE_INVALID
};
struct TKey
{
   TKey()
   {
       codec = "";
       keyType = TYPE_INVALID;
   }
   TKey(AnsiString _codec, TKeyType _userKey=TYPE_STAND)
   {
        codec   = _codec;
        keyType = _userKey;
   }
   AnsiString codec;
   TKeyType   keyType;

};
typedef std::map<AnsiString,TKey>  TDeviceKeyMap;

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
     //RemoteController();
     RemoteController(RemoteControlInfo* pInfo);
     ~RemoteController();
     /*load �������뵽���ⷢ������*/
     bool load();
     int unLoad();
     bool isLoad();

     /*�жϼ����Ƿ����*/
     bool existKeyName(AnsiString keyName);

     /*��Ӱ����ͼ�����*/
     bool addKey(AnsiString keyName, AnsiString keyCodec,TKeyType type=TYPE_STAND);

     /*���°�����Ӧ�ļ�����*/
     bool updateKey(AnsiString keyName, AnsiString keyCodec);

     /*�޸�ң����������*/
     bool  setDeviceName(AnsiString name);
     /*��ȡ��������Ӧ�ı���*/
     bool getKeyCodec(AnsiString keyName,AnsiString &codec);
     /*�г���ң�������еİ�������*/
     bool listKey(TKeyNameList& keylist,TKeyType type=TYPE_STAND);
   
     AnsiString  m_name;


private:
     TDeviceKeyMap      m_keyMap;
     RemoteControlInfo *m_info;
     CppSQLite3DB       m_db;
     bool m_load;
     


     
};
#endif
