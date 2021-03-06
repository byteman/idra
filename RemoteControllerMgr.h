//---------------------------------------------------------------------------

#ifndef RemoteControllerMgrH
#define RemoteControllerMgrH
#include "RemoteController.h"
#include "IdraDevice.h"
#include "CppSQLite3.h"
#include "UserCase.h"
#include  <vector>
#include  <map>
#include <Classes.hpp>
#include <ExtCtrls.hpp>
//#include <QExtCtrls.hpp>
//---------------------------------------------------------------------------

class  UserCase;
typedef std::vector<AnsiString> TDeviceNameList;
typedef std::vector<RemoteController*> TDeviceMap;
typedef std::map<AnsiString, UserCase*> TUserCaseMap;


enum  KEY_STATE
{
     KEY_ADD,
     KEY_MODIFY,
     KEY_INSERT
};
class RemoteControllerMgr
{
public:
      RemoteControllerMgr();
      static RemoteControllerMgr* get();
      bool load();
      bool unLoad();
      int openDevice(int port = 1);
      bool checkPortStatus();
      void startPortCheck();
      bool portStatus(void){return m_idra_ok;}
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
      bool learnKeyValue(AnsiString &keyValue, int timeS);
      /*
      用当前的遥控器检测是否收到外部遥控器的数据。
      */
      bool getKey(AnsiString &keyName, int timeS);
      bool deleteKey(AnsiString keyName);
      bool modifyKey(AnsiString keyName,AnsiString newKeyName);
      bool sendKey(AnsiString keyName);

      bool isStandKey(AnsiString keyName);
      size_t RemoteControllerMgr::getStandKeyList(TKeyNameList& list);
      bool listKey(TKeyNameList& keylist,TKeyType type=TYPE_STAND);
      bool getCurrentCtrlDeviceName(AnsiString &name);

      //usercase  record&save
      void recordKey(AnsiString keyName);
      void StartRecord(bool byDevice=false,TNotifyEvent  event=NULL);
      void StopRecord();
      bool SaveRecordToUserCase(AnsiString ucName="");
      bool InsertUserCaseToMap(AnsiString ucName);
      bool checkExistUcTable(AnsiString ucName);
      bool deleteInvalidUcItem(AnsiString ucName);
      //usercase play
      
      bool SetCurrUserCase(AnsiString ucName);
      bool StartPlayUserCase(AnsiString ucName);
      bool StopUserCase(AnsiString ucName);
      bool deleteUserCase(AnsiString ucName);
      bool deleteUserCaseFromMap(AnsiString ucName);
      bool deleteUserCaseFromDB(AnsiString ucName);
      bool deleteUcKey(int key);
      //usercase load&create
      bool loadUserCase();
      bool AddUserCase(AnsiString ucName,AnsiString deviceName);
      bool DBExistUserCase(AnsiString ucName);
      bool createNewUserCase(AnsiString ucName,AnsiString device);
      bool addNewUserCaseToDB(AnsiString ucName);               
      bool existUserCase(AnsiString ucName);
      void setKeyState(KEY_STATE state,int keyIdx);
      bool modifyUcName(AnsiString ucName, AnsiString ucNewName);
      bool updateUcName(AnsiString& curName, AnsiString &newName);

      //获取用例列表
      size_t getUCList(TKeyNameList& list);
      UserCase* getUserCase(AnsiString ucName);
      UserCase* getCurrUserCase();
      //获取某个用例的按键列表
      TStringList* getUCKeyList(AnsiString ucName);
      bool getUcKeyList(AnsiString ucName,TUserCaseKeyList& keyList);
      int  getUcKeyTime(AnsiString ucName,int indexKey);

private:
      void __fastcall tmr1Timer(TObject *Sender);
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
      bool m_record;     //是否在录制状态。
      bool m_by_device; //通过遥控器来录制。
      TDeviceNameList m_standKey_list;
      TUserCaseMap    m_userCaseMap;
      TStringList     *m_keyList;
      UserCase*       m_curUserCase; //当前的选中的用例，或者新建的用例。
      DWORD           m_record_time;  //记录的按键时间。
      TTimer*         m_timer;
      TNotifyEvent    m_timer_notify;
      KEY_STATE       m_state;
      int             m_last_key;

};
#endif
