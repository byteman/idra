//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteControllerMgr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RemoteControllerMgr::RemoteControllerMgr()
{
      m_idra_ok = false;
}
bool RemoteControllerMgr::openDevice(int port)
{
     if(!m_idra.openDev(port, 9600) == IDRA_ERR_OK) return false;

     m_idra_ok = true;
     return false;
}
bool RemoteControllerMgr::load()
{
    m_db.open("idra.db3");

    CppSQLite3Query qry =  m_db.execQuery("select * from tbl_tv_devices ");

    while(!qry.eof())
    {
         RemoteControlInfo  m_info;
         m_info.m_name = qry.fieldValue("name");
         m_info.m_vendor = qry.fieldValue("vendor");
         m_info.m_softVer = qry.fieldValue("version");
         m_info.m_city = qry.fieldValue("city");
         m_info.m_hardVer = qry.fieldValue("hardVer");
         m_info.m_platform = qry.fieldValue("platform");
         m_info.m_cpu = qry.fieldValue("cpu");

         m_device_info_list[m_info.m_name] = m_info;
         m_device_list.push_back(m_info.m_name);

         qry.nextRow();


    }

    qry.finalize();

    
    return true;
}
bool RemoteControllerMgr::setCurrentCtrlDevice(AnsiString deviceName)
{
     if(!m_idra_ok) return false;
     
     if(0 != m_curDev.load(deviceName,&m_idra)) return false;

     return true;
}
RemoteController* RemoteControllerMgr::getCurrentCtrlDevice()
{

}