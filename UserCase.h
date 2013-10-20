//---------------------------------------------------------------------------

#ifndef UserCaseH
#define UserCaseH
#include <classes.hpp>
#include <list>

//typedef std::list<AnsiString>
//---------------------------------------------------------------------------
class UserCase
{
public:
    UserCase(AnsiString name,AnsiString context="",int intervalMS=1000);
    bool getKeyList(TStringList* keyList);
    int  getInterval();
    void reset();

    bool getNextKey(AnsiString& key);
private:
    AnsiString m_name;
    AnsiString m_context;
    int m_interval_ms;
};
#endif
