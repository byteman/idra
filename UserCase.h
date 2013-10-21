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
    TStringList* getKeyList();
    int  getInterval();
    void reset();
    size_t getKeyCount();
    size_t getNextKey(AnsiString& key);
    AnsiString getName();
private:
    AnsiString   m_name;
    TStringList* m_context;
    int m_interval_ms;
    int m_index;
};
#endif
