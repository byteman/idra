//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteControllerMgr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RemoteControllerMgr::RemoteControllerMgr()
{
      m_idra_ok = false;
      m_curDev  = NULL;
}
bool RemoteControllerMgr::openDevice(int port)
{
     if(!m_idra.openDev(port, 9600) == IDRA_ERR_OK) return false;

     m_idra_ok = true;
     return true;
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

     if(m_curDev)
     {
         delete m_curDev;

     }
     m_curDev = new RemoteController();
     
     if(!m_curDev->load(deviceName,&m_idra)) return false;

     return true;
}
RemoteController* RemoteControllerMgr::getCurrentCtrlDevice()
{
     return  m_curDev;
}
bool RemoteControllerMgr::learnKey(AnsiString keyName, int timeS)
{
    if(!m_idra_ok) return false;

    char codec[128] = {0,};

    if(m_idra.learnKey((unsigned char*)codec, timeS) != IDRA_ERR_OK) return false;

    if(m_curDev->existKeyName(keyName))
    {
        return m_curDev->updateKey(keyName, codec);
    }

    return m_curDev->addKey(keyName, codec);
}
bool RemoteControllerMgr::sendKey(AnsiString keyName)
{
    if(!m_idra_ok) return false;

    if(m_curDev == NULL) return false;

    unsigned char cmd[128];
    AnsiString codec;
    if(!m_curDev->getKeyCodec(keyName, codec)) return false;

    memcpy(cmd, codec.data(),128);
    
    return (m_idra.sendKey(cmd) == IDRA_ERR_OK);

}
