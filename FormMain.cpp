//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "FormIdraSet.h"
#include "FormKey.h"
#include "IdraDevice.h"
#include "CppSQLite3.h"
#include "RemoteControllerMgr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "YbCommDevice"
#pragma link "RzPanel"
#pragma link "RzStatus"
#pragma resource "*.dfm"
TForm1 *Form1;
static IDraDevice idra;
static bool bLearn = false;
static RemoteController* gDev = NULL;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{


      //db.execDML("create table tbl1 id(Text)");

      if(idra.openDev(1,9600) != IDRA_ERR_OK)
      {
          ShowMessage("红外设备打开失败");
          //Application->Terminate();
      }



}
//---------------------------------------------------------------------------


void __fastcall TForm1::mmIdraClick(TObject *Sender)
{
    frmIdraSet->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmAddKeyClick(TObject *Sender)
{
      Form2->ShowModal();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::btn1Click(TObject *Sender)
{
      //
      if(bLearn)
      {
          unsigned char codec[128];
          btn1->Enabled = false;
          if(idra.learnKey(codec, 5) == IDRA_ERR_OK)
          {
             ShowMessage("学习成功");
          }
          else
          {
             ShowMessage("学习失败");
          }
          btn1->Enabled = true;
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn24Click(TObject *Sender)
{
     if( bLearn)
     {
         btn24->Caption = "开始学习";
     }
     else
     {
         btn24->Caption = "停止学习";
     }
     bLearn = !bLearn;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnPlayClick(TObject *Sender)
{
      //
      char buf[10]= {0x11,0x33,0x55,0x77};
      AnsiString text = buf;

}
//---------------------------------------------------------------------------



