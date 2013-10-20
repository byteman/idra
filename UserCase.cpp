//---------------------------------------------------------------------------


#pragma hdrstop

#include "UserCase.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
UserCase::UserCase(AnsiString name,AnsiString context,int intervalMS)
{
    m_name    = name;
    m_context =  context;
}
bool UserCase::getKeyList(TStringList* keyList)
{
    //
    keyList->CommaText = m_context;
    return true;
}
int  UserCase::getInterval()
{

}
void UserCase::reset()
{

}

bool UserCase::getNextKey(AnsiString& key)
{

}
