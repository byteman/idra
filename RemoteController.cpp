//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteController.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


RemoteController::~RemoteController()
{
     if(m_info)
     {
         delete m_info;
         m_info  = NULL;
     }

}
RemoteController::RemoteController(RemoteControlInfo* pInfo):
        m_load(false)
{
    m_name = pInfo->m_name;
    m_info = pInfo;
    m_keyMap.clear();

}
bool RemoteController::load()
{
    m_keyMap.clear();
    m_db.open("idra.db3");

    CppSQLite3Buffer sql;
    sql.format("select * from tbl_ctrl_%s",m_name);

    try
    {
        CppSQLite3Query qry = m_db.execQuery(sql);
        while(!qry.eof())
        {
             TKey key;
             AnsiString name    =  qry.fieldValue("key");
             key.codec          =  qry.fieldValue("codec");
             key.keyType        =  qry.getIntField("type");
             m_keyMap[name]     =  key;
             qry.nextRow();
        }
        qry.finalize();
        m_load = true;

        return true;
    }
    catch(CppSQLite3Exception& e)
    {


    }

    return false;
      
}
int RemoteController::unLoad()
{
    //m_db.close();
    m_name = "";
    m_load = false;
    
}
bool RemoteController::existKeyName(AnsiString keyName)
{
   bool exist = false;

   if(!m_load) return false;

   try
   {
       CppSQLite3Buffer sql;
       sql.format("select * from tbl_ctrl_%s where key=%Q",m_name,keyName);
       CppSQLite3Query qry =  m_db.execQuery(sql);

       if(!qry.eof()) exist = true;

       qry.finalize();
   }
   catch(CppSQLite3Exception& e)
   {

   }


   return exist;
}

bool RemoteController::updateKey(AnsiString keyName, AnsiString keyCodec)
{
    CppSQLite3Buffer sql;
    sql.format("update or rollback tbl_ctrl_%s set codec=%Q where key=%Q",m_name, keyCodec,keyName);
    if(!m_load) return false;
    try
    {
         int ret = m_db.execDML(sql);
         if(ret > 0)
         {
            m_keyMap[keyName] = keyCodec;
            return true;
         }
    }
    catch(CppSQLite3Exception& e)
    {

    }

    return false;
   
}
bool RemoteController::addKey(AnsiString keyName, AnsiString keyCodec,TKeyType type)
{
    CppSQLite3Buffer sql;
    sql.format("insert or rollback into tbl_ctrl_%s (key,codec,type) values(%Q,%Q,%d)",m_name, keyName, keyCodec,type);
    if(!m_load) return false;
    try
    {
         int ret = m_db.execDML(sql);
         if(ret > 0)
         {
            m_keyMap[keyName] = keyCodec;
            return true;
         }
    }
    catch(CppSQLite3Exception& e)
    {

    }

    return false;
   
}
bool  RemoteController::setDeviceName(AnsiString name)
{
    m_name = name;
    if(m_info) m_info->m_name = name;

    return true;
}
bool RemoteController::getKeyCodec(AnsiString keyName,AnsiString &codec)
{
    if(!m_load) return false;
    if(m_keyMap.find(keyName) == m_keyMap.end())
    {
        return false;
    }
    codec = m_keyMap[keyName].codec;

    return true;

}

bool RemoteController::listKey(TKeyNameList& keylist,TKeyType type)
{
    if(!m_load) return false;
    TDeviceKeyMap::iterator iter = m_keyMap.begin();
    for( ; iter != m_keyMap.end(); iter++ )
    {
       if(iter->second.keyType == type)
           keylist.push_back(iter->first);
    }

    return true;


}
bool RemoteController::isLoad()
{
    return m_load;
}
