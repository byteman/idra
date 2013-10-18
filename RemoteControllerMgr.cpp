//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteControllerMgr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RemoteControllerMgr::RemoteControllerMgr():
        m_idra_ok(false),
        m_curDev(NULL),
        m_port(0)
{
        //
}
bool RemoteControllerMgr::openDevice(int port)
{
     m_idra_ok = false;
     if(!m_idra.openDev(port, 9600) == IDRA_ERR_OK)
     {
         for(int i = 1; i < 10; i++)
         {
              if(m_idra.openDev(port, 9600) == IDRA_ERR_OK)
              {
                  m_idra_ok = true;
                  m_port    = port;
                  break;
              }
         }
         return m_idra_ok;
     }
     m_idra_ok = true;
     m_port = port;
     return true;
}
bool RemoteControllerMgr::unLoad()
{
     for(size_t i = 0 ; i < m_devices.size(); i++)
     {
         if(m_devices.at(i) != NULL)
         {
             delete  m_devices.at(i);
         }

     }
     m_devices.clear();
}
bool RemoteControllerMgr::load()
{
    try
    {
          m_db.open("idra.db3");

          CppSQLite3Query qry =  m_db.execQuery("select * from tbl_tv_devices ");

          unLoad();

          while(!qry.eof())
          {
               RemoteControlInfo  *m_info = new RemoteControlInfo();
               m_info->m_name = qry.fieldValue("name");
               m_info->m_vendor = qry.fieldValue("vendor");
               m_info->m_softVer = qry.fieldValue("version");
               m_info->m_city = qry.fieldValue("city");
               m_info->m_hardVer = qry.fieldValue("hardVer");
               m_info->m_platform = qry.fieldValue("platform");
               m_info->m_cpu = qry.fieldValue("cpu");

               RemoteController* pDev = new  RemoteController(m_info);
               if(!pDev->load())
               {
                    //��������ɹ���
               }
               m_devices.push_back(pDev);

               qry.nextRow();


          }

          qry.finalize();

          return true;

    }
    catch(CppSQLite3Exception& e)
    {

    }

    return false;
}
RemoteController* RemoteControllerMgr::existDevice( AnsiString& name)
{
     RemoteController* pDev = NULL;

     for(size_t i = 0 ; i < m_devices.size(); i++)
     {
         if(m_devices.at(i)->m_name == name)
         {
             pDev  =  m_devices.at(i);
             break;
         }

     }
     return pDev;
}
bool RemoteControllerMgr::setCurrentCtrlDevice(AnsiString deviceName)
{
     if(!m_idra_ok) return false;

     RemoteController* pDev =  existDevice(deviceName);
     if(pDev == NULL) return false;

     m_curDev = pDev;

     return true;
}
RemoteController* RemoteControllerMgr::createNewCtrlDevice(AnsiString& devName)
{
     bool ok = false;

     RemoteController* pDev =  existDevice(devName);
     
     if(pDev) return NULL; //�豸�Ѿ�����.
     
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
     sql.format("CREATE TABLE tbl_ctrl_%s ([key] TEXT(50) NOT NULL, codec TEXT,type  INT  NOT NULL );", devName);

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
//////////////////////////add new device to devices list////////////////////////////////////
     RemoteControlInfo  *m_info = new RemoteControlInfo();
     m_info->m_name =  devName;
     
     pDev = new RemoteController(m_info);

     m_devices.push_back(pDev);
////////////////////////////////////////////////////////////////     
     return pDev;

}

bool RemoteControllerMgr::updateDeviceName(AnsiString& curName, AnsiString &newName)
{
     bool ok = false;
     CppSQLite3Buffer sql;

     if(existDevice(newName)) return false;
     
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
     RemoteController* pDev = existDevice(curName);
     if(pDev->setDeviceName(newName))
     {
          //
     }
     return ok;
}

size_t RemoteControllerMgr::listAllDevice(TDeviceNameList& devList)
{
     devList.clear();
     for(size_t i = 0 ; i < m_devices.size(); i++)
     {
         //
         devList.push_back(m_devices.at(i)->m_name);
     }

     return devList.size();
}
void RemoteControllerMgr::deleteFromDeviceList(AnsiString &name)
{
    for(TDeviceMap::iterator it = m_devices.begin(); it!=m_devices.end(); )
    {        if((*it)->m_name == name)        {            it = m_devices.erase(it);  //��ȷ��������erase������һ����Чit        }        else        {            it++;        }    }

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

     //delete from memory list

     deleteFromDeviceList(devName);
     
     return ok;

}

RemoteController* RemoteControllerMgr::getCurrentCtrlDevice()
{
     return  m_curDev;
}
//Ϊ��ǰң����ѧϰ��������
bool RemoteControllerMgr::learnKey(AnsiString keyName, int timeS)
{
    if(!m_idra_ok) return false;
    if(!m_curDev)  return false;
    
    char codec[128] = {0,};

    if(m_idra.learnKey((unsigned char*)codec, timeS) != IDRA_ERR_OK) return false;

    if(m_curDev->existKeyName(keyName))   //�޸İ�������
    {
        return m_curDev->updateKey(keyName, codec);
    }

    return m_curDev->addKey(keyName, codec); //�����Ӱ�������
}
//ͨ����ǰң�������ͱ���
bool RemoteControllerMgr::sendKey(AnsiString keyName)
{
    if(!m_idra_ok)       return false;
    if(m_curDev == NULL) return false;

    unsigned char cmd[128];
    AnsiString codec;
    if(!m_curDev->getKeyCodec(keyName, codec)) return false;

    memcpy(cmd, codec.data(),128);
    
    return (m_idra.sendKey(cmd) == IDRA_ERR_OK);

}
