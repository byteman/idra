//---------------------------------------------------------------------------

#ifndef ByConfigH
#define ByConfigH
#include <iostream>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
class TByConfigImpl
{
public:
      TByConfigImpl();
      virtual bool Open(string path);
      virtual bool Close();
      
      virtual double ReadFloat(const string Section, const string Ident, double Default) = 0;
      virtual int    ReadInteger(const string Section, const string Ident, int Default) = 0;
      virtual string ReadString(const string Section, const string Ident, const string Default) = 0;
      virtual bool   WriteFloat(const string Section, const string Ident, double Value,int dot_cont=2) = 0;
      virtual bool   WriteInteger(const string Section, const string Ident, int Value) = 0;
      virtual bool   WriteString(const string Section, const string Ident, const string Value) = 0;
      virtual bool   WriteBool(const string Section, const string Ident, bool Value) = 0;
      virtual bool   ReadBool(const string Section, const string Ident, bool Default) = 0;
      virtual bool   ValueExists(const string Section, const string Ident) = 0;
      virtual bool   SectionExists(const string Section) = 0;
      virtual bool   setProperty(const std::string& name, const std::string& value);
      std::string    getProperty(const std::string& name) const;
protected:
      virtual ~TByConfigImpl();
};
#endif
