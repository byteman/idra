//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "FormIdraSet.h"
#include "FormKey.h"
#include "IdraDevice.h"
#include "CppSQLite3.h"
#include "RemoteControllerMgr.h"
#include "FormRemoteController.h"
#include "KeyGroup.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "YbCommDevice"
#pragma link "RzPanel"
#pragma link "RzStatus"
#pragma resource "*.dfm"
TForm1 *Form1;

static bool bLearn = false;
static KeyGroup* keyGroupUser = NULL;
static KeyGroup* keyGroupStand = NULL;
static TButton*  pSelectButton = NULL;
typedef std::map<AnsiString,TButton*> TButtonMap;
static const char* gStandKeyList[] =
{
        "待机","静音","首页","菜单","确定",
        "向上","向下","向左","向右","返回",
        "退出","1",   "2",   "3",   "4",
        "5",   "6",   "7",   "8",   "9",
        "0",  "删除"
};


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::loadKeys(void)
{
     TKeyNameList nameList;
     if(keyGroupStand->getKeyNum() == 0)
     {
         RemoteControllerMgr::get()->getStandKeyList(nameList);
         keyGroupStand->addKeyButtonGroup(nameList);
     }

     nameList.clear();
     RemoteControllerMgr::get()->listKey(nameList, TYPE_USER);
     keyGroupUser->clearButtons();
     keyGroupUser->addKeyButtonGroup(nameList);
     
}

void __fastcall TForm1::updateCurrDeviceName()
{
     AnsiString deviceName;
     if( RemoteControllerMgr::get()->getCurrentCtrlDeviceName(deviceName) )
     {
        cbbDevice->Text = deviceName;
        statusName->Caption      = "当前遥控器为:"+deviceName;
     }
     else statusName->Caption = "没有选中遥控器";
}
void __fastcall TForm1::updateDeviceList()
{
     TDeviceNameList devList;

     size_t num = RemoteControllerMgr::get()->listAllDevice(devList);
     cbbDevice->Clear();
     for(size_t i = 0; i < num ; i++)
     {
        cbbDevice->AddItem(devList.at(i), this);
     }
     updateCurrDeviceName();

}

void __fastcall TForm1::updateIdraStatus(bool on)
{
     if(on)
     {
        shpIdra->Brush->Color = clGreen;

     }
     else
     {
        shpIdra->Brush->Color = clRed;
        statusName->Caption = "红外设备打开失败";
     }
}
void __fastcall TForm1::disableWork(bool yes)
{
     btnNew->Enabled = !yes;
     btnDel->Enabled = !yes;
     btnModify->Enabled = !yes;
     btnLearn->Enabled = !yes;
     btnPlay->Enabled = !yes;
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
      keyGroupUser  = new KeyGroup(grpUserKey, 5,3,50,40);
      keyGroupStand = new KeyGroup(grpStandKey,5,5,50,40);

      keyGroupUser->RegisterButtonClickEvent(onKeyClick);
      keyGroupUser->RegisterButtonMouseUpEvent(onButtonSelect);

      
      keyGroupStand->RegisterButtonClickEvent(onKeyClick);
      
      if(!RemoteControllerMgr::get()->openDevice(6))
      {

          updateIdraStatus(false);
          disableWork(true);
          //Application->Terminate();
      }
      else
      {
          RemoteControllerMgr::get()->load();
          updateDeviceList();
          updateIdraStatus(true);
          disableWork(false);
      }


}
void __fastcall TForm1::learnKey(TObject *Sender)
{
     if(bLearn)
     {
         btnLearn->Caption = "开始学习";
         updateKeyStatus();
     }
     else
     {
         btnLearn->Caption = "停止学习";
         enableAllKey(true);

     }
     bLearn = !bLearn;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::onKeyClick(TObject *Sender)
{
      TButton* btn  = (TButton*)Sender;  
      if(bLearn)
      {
          unsigned char codec[128];

          btn->Enabled = false;


          if(RemoteControllerMgr::get()->learnKey(btn->Caption, 5))
          {
             ShowMessage("学习成功");
          }
          else
          {
             ShowMessage("学习失败");
          }
          btn->Enabled = true;
      }
      else
      {
          if(!RemoteControllerMgr::get()->sendKey(btn->Caption))
          {
              ShowMessage("发送失败");
          }
      }
}

void __fastcall TForm1::addDevice(TObject *Sender)
{
      frmRemoteDev->ShowModal();
     if(frmRemoteDev->isOk)
     {
         if(RemoteControllerMgr::get()->existDevice(frmRemoteDev->devName))
         {
            ShowMessage("该遥控器已经存在了");
         }
         else
         {
            if(RemoteControllerMgr::get()->createNewCtrlDevice(frmRemoteDev->devName))
            {
                cbbDevice->Text = frmRemoteDev->devName;
                ShowMessage("遥控器新建成功");
            }
            else
            {
                ShowMessage("遥控器新建失败");
            }
         }

     }
     updateDeviceList();

}
void __fastcall TForm1::delDevice(TObject *Sender)
{

    switch (Application->MessageBox("确认删除当前遥控器", "提示", MB_OKCANCEL 
        + MB_ICONQUESTION)) {
        case IDOK: {

            break;
        }
        case IDCANCEL: {
        
            return;
            break;
        }
    }

    if(RemoteControllerMgr::get()->deleteCtrlDevice(cbbDevice->Text))
    {
        ShowMessage("删除成功");
    }
    else  ShowMessage("删除失败");

    updateDeviceList();
}
void __fastcall TForm1::btnDelClick(TObject *Sender)
{
     delDevice(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::modifyDevice(TObject *Sender)
{
     frmRemoteDev->ShowModal();
     if(frmRemoteDev->isOk)
     {
         if(RemoteControllerMgr::get()->existDevice(cbbDevice->Text))
         {
            RemoteControllerMgr::get()->updateDeviceName(cbbDevice->Text,frmRemoteDev->devName);
         }


     }
     updateDeviceList();
}
void __fastcall TForm1::btnModifyClick(TObject *Sender)
{
      modifyDevice(Sender);
}

void __fastcall TForm1::enableAllKey(bool en)
{
    keyGroupStand->enableAll(en);
    keyGroupUser->enableAll(en);
}
void __fastcall TForm1::updateKeyStatus()
{
    TKeyNameList keyList;
    RemoteControllerMgr::get()->listKey(keyList);
    keyGroupStand->enableButtonByNameList(keyList);
    keyList.clear();
    RemoteControllerMgr::get()->listKey(keyList,TYPE_USER);      //获取自定义按键
    keyGroupUser->enableButtonByNameList(keyList);

}
//---------------------------------------------------------------------------
bool __fastcall TForm1::changeDevice(AnsiString name)
{
     if( !RemoteControllerMgr::get()->setCurrentCtrlDevice(name))
     {
         return false;
     }

     loadKeys();
     updateCurrDeviceName();
     updateKeyStatus();

     return true;
}

void __fastcall TForm1::cbbDeviceChange(TObject *Sender)
{
    if(!changeDevice(cbbDevice->Text))
    {
        ShowMessage("切换失败");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::grpUserKeyMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       if(Button == mbRight)
       {
           mmKeyAdd->Enabled = true;
           TPoint pt(X,Y);
           TPoint pt2 = grpUserKey->ClientToScreen(pt);
           pm1->Popup(pt2.x,pt2.y);
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmKeyAddClick(TObject *Sender)
{
     //

     Form2->ShowModal();
     if(Form2->ret)
     {
          AnsiString name = Form2->keyName;
          if(name.Length() == 0)
          {
              ShowMessage("请输入按键名称");
          }
          else
          {
             //rcmgr.getCurrentCtrlDevice()->addKey()
             TKeyNameList keyList;
             AnsiString   deviceName;

             if(RemoteControllerMgr::get()->getCurrentCtrlDeviceName(deviceName))
             {
                 ShowMessage("没有选择遥控器");
                 return;
             }
             if(keyGroupUser->existButtonName(name))
             {
                 ShowMessage("改按键已经存在");
                 return;
             }
             keyGroupUser->addKeyButton(name);
          }
     }
     else
     {
         
     }
     
}
//---------------------------------------------------------------------------
void __fastcall TForm1::onButtonSelect(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{

       if(Button == mbRight)
       {
           TPoint pt(X,Y);

           
           TControl* pCtrl = (TControl*) Sender;
           TPoint pt2 = pCtrl->ClientToScreen(pt);

           //ShortString str = "TButton";

           if(AnsiString(pCtrl->ClassName()) == AnsiString("TButton"))
           {

                pSelectButton =  (TButton*) Sender;
                pm2->Popup(pt2.x,pt2.y);
           }

       }

}
void __fastcall TForm1::mmKeyDelClick(TObject *Sender)
{

   if(pSelectButton)
   {
        ShowMessage(pSelectButton->Caption);
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmKeyMClick(TObject *Sender)
{
    //
     if(pSelectButton)
   {
        ShowMessage(pSelectButton->Caption);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmKeyAdd2Click(TObject *Sender)
{
     mmKeyAddClick(Sender);   
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmAddDevClick(TObject *Sender)
{
    addDevice(Sender);
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnNewClick(TObject *Sender)
{
     addDevice(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmDelDevClick(TObject *Sender)
{
     delDevice(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmMDevClick(TObject *Sender)
{
      modifyDevice(Sender);  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnLearnClick(TObject *Sender)
{
      learnKey(Sender);
}
//---------------------------------------------------------------------------

