//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteController.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RemoteController::RemoteController()
{
     m_idra = NULL;
     m_name = "";
}
bool RemoteController::load(AnsiString name,IDraDevice* pIdra)
{
    m_name = name ;
    m_idra = pIdra;
    m_db.open("idra.db3");

    CppSQLite3Buffer sql;
    sql.format("select * from tbl_ctrl_%s",m_name);
    CppSQLite3Query qry = m_db.execQuery(sql);

    m_keyMap.clear();
    
    while(!qry.eof())
    {

         AnsiString key = qry.fieldValue("key");
         m_keyMap[key] =  qry.fieldValue("codec");
         
         qry.nextRow();
    }
    qry.finalize();

    return true;
      
}
int RemoteController::unLoad()
{
    m_db.close();
}
bool RemoteController::existKeyName(AnsiString keyName)
{
   bool exist = false;

   CppSQLite3Buffer sql;
   sql.format("select * from tbl_ctrl_%s where key=%Q",m_name,keyName);
   CppSQLite3Query qry =  m_db.execQuery(sql);

   if(!qry.eof()) exist = true;

   qry.finalize();

   return exist;
}

bool RemoteController::updateKey(AnsiString keyName, AnsiString keyCodec)
{
    CppSQLite3Buffer sql;
    sql.format("update or rollback tbl_ctrl_%s set codec=%Q where key=%Q",m_name, keyCodec,keyName);

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
bool RemoteController::addKey(AnsiString keyName, AnsiString keyCodec)
{
    CppSQLite3Buffer sql;
    sql.format("insert or rollback into tbl_ctrl_%s (key,codec) values(%Q,%Q)",m_name, keyName, keyCodec);

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

bool RemoteController::getKeyCodec(AnsiString keyName,AnsiString &codec)
{
    if(m_keyMap.find(keyName) == m_keyMap.end())
    {
        return false;
    }
    codec = m_keyMap[keyName];

    return true;

}



bool RemoteController::listKey(TKeyNameList& keylist)
{
    TDeviceKeyMap::iterator iter = m_keyMap.begin();
    for( ; iter != m_keyMap.end(); iter++ )
    {
       keylist.push_back(iter->first);
    }

    return true;


}
