//---------------------------------------------------------------------------


#pragma hdrstop

#include "UserCase.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
UserCase::UserCase(AnsiString name,AnsiString context,int intervalMS)
{
    m_name    = name;
    tableName = "tbl_uc_"+name;
    //m_context =  context;
    m_interval_ms = intervalMS;
    m_context = new TStringList;
    m_context->CommaText = context;
    m_index = 0;
    m_keyList = new TList();
    loadKey();
}
UserCase::~UserCase()
{
    if(m_context) delete m_context;

    for(int i = 0; i < m_keyList->Count; i++)
        delete m_keyList->Items[i];
    if(m_keyList) delete m_keyList;
}
size_t UserCase::getKeyCount()
{
    return m_context->Count;
}
TStringList* UserCase::getKeyList()
{
    return  m_context;
}
bool UserCase::getKeyList(TStringList* keyList)
{
    //
    keyList->Text =  m_context->Text;
    return true;
}
int  UserCase::getInterval()
{
    return m_interval_ms;
}
void UserCase::reset()
{
     m_index = 0;
}
AnsiString UserCase::getName()
{
    return m_name;
}
size_t UserCase::getNextKey(AnsiString& key)
{
     int ret = m_index;
     key =  m_context->Strings[m_index++];
     if(m_index >= m_context->Count) m_index =  m_context->Count;

     return ret;

}
/*
从数据库中加载用例的按键信息
*/
bool UserCase::loadKey(void)
{
      try
      {
          m_db.open("idra.db3");
          
          if(!m_db.tableExists(tableName.c_str())) return false;

          CppSQLite3Buffer sql;
          sql.format("select * from %s",tableName);
          CppSQLite3Query qry = m_db.execQuery(sql);

          while(!qry.eof())
          {
              AnsiString name = qry.fieldValue("name");
              int keyS = qry.getIntField("keytime",1000);

              UserCaseKey* pKey = new UserCaseKey(name,keyS);
              m_keyList->Add(pKey);
              
          }
      }
      catch(CppSQLite3Exception& e)
      {


      }
}
//run
bool UserCase::run(int &index)
{
     if( (m_index+1) >= m_keyList->Count)
     {
         index = m_index;
         return false;
     }
     UserCaseKey* pKey = (UserCaseKey*)m_keyList->Items[m_index];

     pKey->count+=1000;
     if(pKey->count >= pKey->time)
     {
         RemoteControllerMgr::get()->sendKey(pKey->keyName);
     }
}
