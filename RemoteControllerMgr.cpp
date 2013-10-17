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
     bool find = false;
     if(!m_idra.openDev(port, 9600) == IDRA_ERR_OK)
     {
         for(int i = 1; i < 10; i++)
         {
              if(m_idra.openDev(port, 9600) == IDRA_ERR_OK)
              {
                  find = true;
                  break;
              }
         }
         if(!find) return false;
     }

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
bool RemoteControllerMgr::existDevice( AnsiString& name)
{

}
bool RemoteControllerMgr::setCurrentCtrlDevice(AnsiString deviceName)
{
     if(!m_idra_ok) return false;

     if(m_curDev)
     {
         delete m_curDev;
     }
     m_curDev = new RemoteController();
     
     if(!m_curDev->load(deviceName)) return false;

     return true;
}
RemoteController* RemoteControllerMgr::createNewCtrlDevice(AnsiString& devName)
{
     bool ok = false;
     CppSQLite3Buffer sql;
     sql.format("insert or rollback into tbl_tv_devices (name) values(%Q)",devName);

     try{

        if( m_db.execDML(sql) > 0)
        {
            ok = true;
        }
     }
     catch(CppSQLite3Exception& e)
     {

     }
     if(!ok) return NULL;
     ok = false;
     sql.format("CREATE TABLE tbl_ctrl_%s ([key] TEXT(50) NOT NULL, codec TEXT);", devName);

     try
     {

        if( m_db.execDML(sql) > 0)
        {
            ok = true;
        }
     }
     catch(CppSQLite3Exception& e)
     {

     }
     if(!ok) return NULL;

     if(!setCurrentCtrlDevice(devName)) return NULL;

     return getCurrentCtrlDevice();
}

bool RemoteControllerMgr::updateDeviceName(AnsiString& curName, AnsiString &newName)
{
     bool ok = false;
     CppSQLite3Buffer sql;

     if(existDeviceName(newName)) return false;
     
     sql.format("update or rollback tbl_tv_devices set name=%Q where name=%Q",newName,curName);

     try{

        if( m_db.execDML(sql) > 0)
        {
            ok = true;
        }
     }
     catch(CppSQLite3Exception& e)
     {

     }

     if(!ok) return false;
     ok = false;
     sql.format("alter table tbl_ctrl_%s rename to tbl_ctrl_%s",curName,newName);
     try
     {

        m_db.execDML(sql);

        ok = true;

     }
     catch(CppSQLite3Exception& e)
     {

     }
     
     return ok;
}
RemoteController* RemoteControllerMgr::createNewCtrlDevice(RemoteControlInfo& info)
{
     bool ok = false;
     CppSQLite3Buffer sql;
     sql.format("insert or rollback into tbl_tv_devices (name,vendor) values(%Q,%Q)",info.m_name,info.m_vendor);

     try{

        if( m_db.execDML(sql) > 0)
        {
            ok = true;
        }
     }
     catch(CppSQLite3Exception& e)
     {

     }
     if(!ok) return NULL;
     ok = false;
     sql.format("CREATE TABLE tbl_ctrl_%s ([key] TEXT(50] NOT NULL, codec TEXT)", info.m_name);

      try{

        if( m_db.execDML(sql) > 0)
        {
            ok = true;
        }
     }
     catch(CppSQLite3Exception& e)
     {

     }
     if(!ok) return NULL;

     if(!setCurrentCtrlDevice(info.m_name)) return NULL;

     return getCurrentCtrlDevice();

}
bool RemoteControllerMgr::deleteCtrlDevice(AnsiString& devName)
{
//
     bool ok = false;
     CppSQLite3Buffer sql;
     sql.format("delete from tbl_tv_devices where name=%Q;",devName);

     try{

        if( m_db.execDML(sql) > 0)
        {
            ok = true;
        }
     }
     catch(CppSQLite3Exception& e)
     {

     }
     if(!ok) return NULL;
     ok = false;
     sql.format("DROP TABLE IF EXISTS tbl_ctrl_%s;", devName);

     try
     {

        m_db.execDML(sql); //�п���û�������

        ok = true;
     }
     catch(CppSQLite3Exception& e)
     {

     }

     return ok;

}
bool RemoteControllerMgr::existDeviceName(AnsiString deviceName)
{
     return (m_device_info_list.find(deviceName) != m_device_info_list.end());
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