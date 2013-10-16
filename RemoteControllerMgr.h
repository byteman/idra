//---------------------------------------------------------------------------

#ifndef RemoteControllerMgrH
#define RemoteControllerMgrH
#include "RemoteController.h"
#include "IdraDevice.h"
#include "CppSQLite3.h"
#include  <vector>
//---------------------------------------------------------------------------

typedef std::vector<AnsiString> TDeviceNameList;
class RemoteControllerMgr
{
public:
      RemoteControllerMgr();
      bool load();
      bool openDevice(int port);
      bool setCurrentCtrlDevice(AnsiString deviceName);
      RemoteController* getCurrentCtrlDevice();
      TDeviceNameList  m_device_list;
private:
      CppSQLite3DB m_db;
      IDraDevice   m_idra;
      TDeviceInfo  m_device_info_list;
      RemoteController m_curDev;
      bool m_idra_ok;

};
#endif
