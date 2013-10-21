//---------------------------------------------------------------------------


#pragma hdrstop

#include "UserCase.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
UserCase::UserCase(AnsiString name,AnsiString context,int intervalMS)
{
    m_name    = name;
    //m_context =  context;
    m_interval_ms = intervalMS;
    m_context = new TStringList;
    m_context->CommaText = context;
    m_index = 0;
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
