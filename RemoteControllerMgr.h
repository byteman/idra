//---------------------------------------------------------------------------

#ifndef RemoteControllerMgrH
#define RemoteControllerMgrH
#include "RemoteController.h"
#include "IdraDevice.h"
#include "CppSQLite3.h"
#include  <vector>
//---------------------------------------------------------------------------

typedef std::vector<AnsiString> TDeviceNameList;
typedef std::vector<RemoteController*> TDeviceMap;
class RemoteControllerMgr
{
public:
      RemoteControllerMgr();
      static RemoteControllerMgr* get();
      bool load();
      bool unLoad();
      bool openDevice(int port = 1);

      RemoteController* existDevice( AnsiString& name);
      bool setCurrentCtrlDevice(AnsiString deviceName);
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
private:
      void deleteFromDeviceList(AnsiString &name);
      void handleIdraError(IDRA_ERR err);
      RemoteController* addDevice();
      bool checkDB(CppSQLite3DB& db);
      CppSQLite3DB m_db;
      IDraDevice   m_idra;
      RemoteController *m_curDev;
      TDeviceMap   m_devices;
      int          m_port;
      bool m_idra_ok;
      TDeviceNameList m_standKey_list;

};
#endif
