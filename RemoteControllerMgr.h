//---------------------------------------------------------------------------

#ifndef RemoteControllerMgrH
#define RemoteControllerMgrH
#include "RemoteController.h"
#include "IdraDevice.h"
#include "CppSQLite3.h"
#include "UserCase.h"
#include  <vector>
#include  <map>
//---------------------------------------------------------------------------

typedef std::vector<AnsiString> TDeviceNameList;
typedef std::vector<RemoteController*> TDeviceMap;
typedef std::map<AnsiString, UserCase*> TUserCaseMap;
class RemoteControllerMgr
{
public:
      RemoteControllerMgr();
      static RemoteControllerMgr* get();
      bool load();
      bool unLoad();
      int openDevice(int port = 1);

      RemoteController* existDevice( AnsiString& name);
      bool setCurrentCtrlDevice(AnsiString deviceName);
      bool setCurrentCtrlDevice(int index,AnsiString &deviceName);
      RemoteController* getCurrentCtrlDevice();
      RemoteController* createNewCtrlDevice(RemoteControlInfo& info);
      RemoteController* createNewCtrlDevice(AnsiString& devName);
      bool deleteCtrlDevice(AnsiString& devName);
      bool existDeviceName(AnsiString deviceName);
      bool updateDeviceName(AnsiString& curName, AnsiString &newName);
      size_t listAllDevice(TDeviceNameList& devList);
      TDeviceNameList  m_device_list;
      
      bool learnKey(AnsiString keyName, int timeS);
      bool deleteKey(AnsiString keyName);
      bool modifyKey(AnsiString keyName,AnsiString newKeyName);
      bool sendKey(AnsiString keyName);

      bool isStandKey(AnsiString keyName);
      size_t RemoteControllerMgr::getStandKeyList(TKeyNameList& list);
      bool listKey(TKeyNameList& keylist,TKeyType type=TYPE_STAND);
      bool getCurrentCtrlDeviceName(AnsiString &name);

      //usercase  record&save
      void recordKey(AnsiString keyName);
      void StartRecord();
      void StopRecord();
      bool SaveRecordToUserCase(AnsiString ucName);
      //usercase play
      bool StartPlayUserCase(AnsiString ucName);
      bool StopUserCase(AnsiString ucName);
      bool deleteUserCase(AnsiString ucName);
      //usercase load&create
      bool loadUserCase();
      //获取用例列表
      size_t getUCList(TKeyNameList& list);
      //获取某个用例的按键列表
      bool getUCKeyList(AnsiString ucName,TStringList* list);
private:
      void deleteFromDeviceList(AnsiString &name);
      void handleIdraError(IDRA_ERR err);
      bool createDeviceTable();
      bool createUserCaseTable();
      RemoteController* addDevice();
      bool checkDB(CppSQLite3DB& db);
      CppSQLite3DB m_db;
      IDraDevice   m_idra;
      RemoteController *m_curDev;
      TDeviceMap   m_devices;
      int          m_port;
      bool m_idra_ok;
      bool m_record;
      TDeviceNameList m_standKey_list;
      TUserCaseMap    m_userCaseMap;
      TStringList *m_keyList;

};
#endif
