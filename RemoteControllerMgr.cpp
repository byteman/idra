//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteControllerMgr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RemoteControllerMgr::RemoteControllerMgr()
{

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


    }
}
RemoteController* RemoteControllerMgr::setCurrentCtrlDevice(AnsiString deviceName)
{

}
RemoteController* RemoteControllerMgr::getCurrentCtrlDevice()
{

}