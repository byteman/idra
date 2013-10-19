//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteControllerMgr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static const char* gStandKeyList[] =
{
        "待机","静音","首页","菜单","确定",
        "向上","向下","向左","向右","返回",
        "退出","1",   "2",   "3",   "4",
        "5",   "6",   "7",   "8",   "9",
        "0",  "删除"
};

#define STAND_KEY_NUM (sizeof(gStandKeyList)/sizeof(char*))
size_t RemoteControllerMgr::getStandKeyList(TKeyNameList& list)
{
     list = m_standKey_list;
}

RemoteControllerMgr::RemoteControllerMgr():
        m_idra_ok(false),
        m_curDev(NULL),
        m_port(0)
{
        for(int i = 0; i < STAND_KEY_NUM; i++)
        m_standKey_list.push_back(gStandKeyList[i]);
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
                    //加载码表不成功。
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
     
     if(pDev) return NULL; //设备已经存在.
     
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
    {        if((*it)->m_name == name)        {            it = m_devices.erase(it);  //正确的做法，erase返回下一个有效it        }        else        {            it++;        }    }

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

        m_db.execDML(sql); //有可能没有这个表

        ok = true;
     }
     catch(CppSQLite3Exception& e)
     {

     }

     //delete from memory list

     deleteFromDeviceList(devName);

     if(m_devices.size() > 0)
        m_curDev = m_devices.at(0);
     else    m_curDev = NULL;
     //setCurrentCtrlDevice();

     return ok;

}
bool RemoteControllerMgr::getCurrentCtrlDeviceName(AnsiString &name)
{
    if(m_curDev == NULL) return false;

    name = m_curDev->m_name;
    return true;
}
bool RemoteControllerMgr::listKey(TKeyNameList& keylist,TKeyType type)
{
     if(m_curDev == NULL) return false;
     return m_curDev->listKey(keylist,type);
}
RemoteController* RemoteControllerMgr::getCurrentCtrlDevice()
{
     return  m_curDev;
}
//为当前遥控器学习按键编码
bool RemoteControllerMgr::learnKey(AnsiString keyName,int timeS)
{
    if(!m_idra_ok) return false;
    if(!m_curDev)  return false;
    
    char codec[128] = {0,};

    if(m_idra.learnKey((unsigned char*)codec, timeS) != IDRA_ERR_OK) return false;

    if(m_curDev->existKeyName(keyName))   //修改按键编码
    {
        return m_curDev->updateKey(keyName, codec);
    }
    TKeyType type = TYPE_USER;
    if(isStandKey(keyName))type = TYPE_STAND;

    return m_curDev->addKey(keyName, codec, type); //新增加按键编码
}
//通过当前遥控器发送编码
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

static  RemoteControllerMgr *mgr = NULL;
RemoteControllerMgr* RemoteControllerMgr::get()
{
     if(mgr == NULL)
     {
         mgr = new RemoteControllerMgr();
     }
     return mgr;
}
bool RemoteControllerMgr::isStandKey(AnsiString keyName)
{
   //
   for(size_t i = 0 ;i <  m_standKey_list.size(); i++)
   {
       if(keyName == m_standKey_list.at(i))
          return true;
   }
   return false;
}
