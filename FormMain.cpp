//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "CppSQLite3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "YbCommDevice"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
      CppSQLite3DB db;
      db.open("idra.db3");

      CppSQLite3Query qry = db.execQuery("select * from tbl_tv_devices_names");

      while(!qry.eof())
      {
           lst1->AddItem(qry.fieldValue("name"));
           qry.nextRow();
      }
      qry.finalize();
      
      db.close();
      //db.execDML("create table tbl1 id(Text)");
}
//---------------------------------------------------------------------------

