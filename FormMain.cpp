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

static bool bLearn = false;
static RemoteController* gDev = NULL;

static RemoteControllerMgr rcmgr;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{


      //db.execDML("create table tbl1 id(Text)");

      if(!rcmgr.openDevice(6))
      {
          ShowMessage("红外设备打开失败");
          //Application->Terminate();
      }
     cbbDevice->Clear();

     rcmgr.load();

     for(int i = 0; i < rcmgr.m_device_list.size();i++)
     {
        cbbDevice->AddItem(rcmgr.m_device_list.at(i), this);
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
          if(rcmgr.learnKey("待机", 5))
          {
             ShowMessage("学习成功");
          }
          else
          {
             ShowMessage("学习失败");
          }
          btn1->Enabled = true;
      }
      else
      {
          if(!rcmgr.sendKey("待机"))
          {
              ShowMessage("发送失败");
          }
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

void __fastcall TForm1::addKeyButton(AnsiString name,TObject *Sender)
{
      //
      TButton* btn = new TButton(this);
      btn->Width = 50;
      btn->Height = 40;

     // btn->Left = 
}

void __fastcall TForm1::btn23Click(TObject *Sender)
{

     if( rcmgr.setCurrentCtrlDevice(cbbDevice->Text))
     {

         ShowMessage("切换成功");

         TKeyNameList keyList;
         rcmgr.getCurrentCtrlDevice()->listKey(keyList);

         for(size_t i = 0; i < keyList.size();i++)
         {
             mmoInfo->Lines->Add(keyList.at(i));
         }
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn2Click(TObject *Sender)
{
     if(bLearn)
      {
          unsigned char codec[128];
          btn2->Enabled = false;
          if(rcmgr.learnKey("静音", 5))
          {
             ShowMessage("学习成功");
          }
          else
          {
             ShowMessage("学习失败");
          }
          btn2->Enabled = true;
      }
      else
      {
          if(!rcmgr.sendKey("静音"))
          {
              ShowMessage("发送失败");
          }
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn6Click(TObject *Sender)
{
     if(bLearn)
      {
          unsigned char codec[128];
          btn6->Enabled = false;
          if(rcmgr.learnKey("向上", 5))
          {
             ShowMessage("学习成功");
          }
          else
          {
             ShowMessage("学习失败");
          }
          btn6->Enabled = true;
      }
      else
      {
          if(!rcmgr.sendKey("向上"))
          {
              ShowMessage("发送失败");
          }
      }
}
//---------------------------------------------------------------------------

