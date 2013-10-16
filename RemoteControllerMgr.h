//---------------------------------------------------------------------------

#ifndef RemoteControllerMgrH
#define RemoteControllerMgrH
#include "RemoteController.h"
#include "CppSQLite3.h"
#include  <vector>
//---------------------------------------------------------------------------

typedef std::vector<AnsiString> TDeviceNameList;
class RemoteControllerMgr
{
public:
      RemoteControllerMgr();
      bool load();
      RemoteController* setCurrentCtrlDevice(AnsiString deviceName);
      RemoteController* getCurrentCtrlDevice();
private:
      CppSQLite3DB m_db;
      TDeviceInfo  m_device_info_list;
      TDeviceNameList  m_device_list;
};
#endif
