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
#include "bylogger.h"
#include "SysConfig.h"
#include "FormUcSave.h"
#include "FormIdraSet.h"
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
static TStringList* pUcKeyList = NULL;
static UserCase* pUserCase = NULL;
static bool bRecord = false;
static bool bPortStatus = false;
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
    pUcKeyList = new TStringList();
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

     updateKeyStatus(); //更新按键状态
}

int  __fastcall TForm1::findItem(AnsiString item)
{
    for(int i = 0; i < cbbDevice->Items->Count; i++)
    {
       if(item == cbbDevice->Items->Strings[i])
            return i;
    }
    return -1;
}
void __fastcall TForm1::updateCurrDevice()
{
     AnsiString deviceName;

     updateDeviceList();
     if( RemoteControllerMgr::get()->getCurrentCtrlDeviceName(deviceName) )
     {
        cbbDevice->ItemIndex = findItem(deviceName);
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
     btnRecord->Enabled = !yes;
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
      keyGroupUser  = new KeyGroup(grpUserKey, 5,3,50,40);
      keyGroupStand = new KeyGroup(grpStandKey,5,5,50,40);

      keyGroupUser->RegisterButtonClickEvent(onKeyClick);
      keyGroupUser->RegisterButtonMouseUpEvent(onButtonSelect);

      
      keyGroupStand->RegisterButtonClickEvent(onKeyClick);

      SystemConfig config;

      int port = RemoteControllerMgr::get()->openDevice(config.port);
      if(port == -1)
      {
          bylog("红外发射模块通讯异常，请插入");
          updateIdraStatus(false);
          disableWork(true);
          bPortStatus = false;
          //Application->Terminate();
      }
      else
      {
          bylog("红外发射模块通讯正常,串口[%d]",port);
          config.port = port;
          bPortStatus = true;
          config.save();
          if(RemoteControllerMgr::get()->load())
          {
              bylog("加载遥控器数据成功");
          }
          updateCurrDevice();
          updateIdraStatus(true);
          updateUserCaseList();
          disableWork(false);
      }
      statusUC->Caption = "没有选中用例";
      //RemoteControllerMgr::get()->startPortCheck();
      //cbbDevice->Handle


}
void __fastcall TForm1::updateUserCaseList()
{
     //
     TKeyNameList list;

     size_t n = RemoteControllerMgr::get()->getUCList(list);

     lstUserCase->Clear();

     for(size_t i = 0; i < n; i++)
     {
         lstUserCase->AddItem(list.at(i),this);
     }

}
void __fastcall TForm1::learnKey(TObject *Sender)
{
     if(bLearn)
     {

         btnLearn->Caption = "开始学习";
         mmLearnKey->Caption = "学习按键";

         bylog("退出学习模式,进入工作模式");
         updateKeyStatus();
     }
     else
     {
         AnsiString name;
         if(!RemoteControllerMgr::get()->getCurrentCtrlDeviceName(name))
         {
             bylog("当前没有选中遥控器，不能学习!!");
             return;
         }
         btnLearn->Caption = "停止学习";
         mmLearnKey->Caption = "停止学习";
         bylog("退出工作模式,进入学习模式");
         enableAllKey(true);

     }
     btnPlay->Enabled = bLearn;
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

          bylog("正在学习【%s】键,请按遥控器....",btn->Caption);
          if(RemoteControllerMgr::get()->learnKey(btn->Caption, 5))
          {
             bylog("学习【%s】键:成功",btn->Caption);
          }
          else
          {
             bylog("学习【%s】键:失败",btn->Caption);
          }
          btn->Enabled = true;
      }
      else
      {
          if(!RemoteControllerMgr::get()->sendKey(btn->Caption))
          {
              bylog("【%s】键:发送失败,请检查红外模块处于学习状态",btn->Caption);
          }
          else
          {
              bylog("【%s】键:发送成功",btn->Caption);
          }
          if(bRecord)
          {
              updateUcKeyList("");
          }

      }
}

void __fastcall TForm1::addDevice(TObject *Sender)
{
     AnsiString newDeviceName = "";
     frmRemoteDev->Caption = "新建遥控器";
     //frmRemoteDev->Caption
     frmRemoteDev->ShowModal();
     newDeviceName = frmRemoteDev->devName;
     if(frmRemoteDev->isOk)
     {
         if(RemoteControllerMgr::get()->existDevice(newDeviceName))
         {
            bylog("该遥控器已经存在了");
         }
         else
         {
            if(RemoteControllerMgr::get()->createNewCtrlDevice(newDeviceName))
            {
                
                if(!changeDevice(newDeviceName))
                {
                    bylog("切换失败");
                }
                //ShowMessage("遥控器新建成功");
            }
            else
            {
                bylog("遥控器新建失败");
            }
         }

     }
     //updateDeviceList();

}
void __fastcall TForm1::delDevice(TObject *Sender)
{

    if(cbbDevice->ItemIndex == -1)
    {
       ShowMessage("请先选中需要删除的遥控器");
       return;
    }
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
        //ShowMessage("删除成功");
    }
    else  bylog("删除失败");

    AnsiString name;
    if(!RemoteControllerMgr::get()->setCurrentCtrlDevice(0,name))
    {
         updateCurrDevice();
    }
    else
    {
         changeDevice(name);
    }

}
void __fastcall TForm1::btnDelClick(TObject *Sender)
{
     delDevice(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::modifyDevice(TObject *Sender)
{
     AnsiString name;

     if(!RemoteControllerMgr::get()->getCurrentCtrlDeviceName(name))
     {
         bylog("当前没有选中遥控器，无法修改");
         return;
     }
     frmRemoteDev->Caption = "修改遥控器名称";
     frmRemoteDev->ShowModal();
     if(frmRemoteDev->isOk)
     {
         if(RemoteControllerMgr::get()->existDevice(cbbDevice->Text))
         {
             if(RemoteControllerMgr::get()->updateDeviceName(cbbDevice->Text,frmRemoteDev->devName))
             {
                  changeDevice(frmRemoteDev->devName);
             }
         }


     }

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

     loadKeys(); //加载按键GUI
     updateCurrDevice();   //更新


     return true;
}

void __fastcall TForm1::cbbDeviceChange(TObject *Sender)
{
    if(!changeDevice(cbbDevice->Text))
    {
        bylog("切换失败");
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

void __fastcall TForm1::addUserKey(TObject *Sender)
{
     AnsiString   deviceName;

     if(!RemoteControllerMgr::get()->getCurrentCtrlDeviceName(deviceName))
     {
         bylog("没有选择遥控器");
         return;
     }
     Form2->ShowModal();
     if(Form2->ret)
     {
          AnsiString name = Form2->keyName;
          if(name.Length() == 0)
          {
              bylog("请输入按键名称");
          }
          else
          {
             //rcmgr.getCurrentCtrlDevice()->addKey()
             TKeyNameList keyList;

             if(keyGroupUser->existButtonName(name))
             {
                 bylog("改按键已经存在");
                 return;
             }
             keyGroupUser->addKeyButton(name,false);
          }
     }
     else
     {
         
     }
     
}
void __fastcall TForm1::mmKeyAddClick(TObject *Sender)
{
     //
     addUserKey(Sender);

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
        //ShowMessage(pSelectButton->Caption);
        RemoteControllerMgr::get()->deleteKey(pSelectButton->Caption);
        loadKeys();
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
void GUI_OUTPUT(const char* logMsg)
{
    AnsiString text = Now().FormatString("hh:mm:ss  ") + logMsg; 
    Form1->mmoInfo->Lines->Add(text);
}

void __fastcall TForm1::mmLogClearClick(TObject *Sender)
{
     mmoInfo->Clear();   
}
//---------------------------------------------------------------------------
void __fastcall TForm1::createUserCase()
{
      OKBottomDlg->ShowModal();
      if(OKBottomDlg->save)
      {
          AnsiString ucName = OKBottomDlg->lbledtUCname->Text;
          if(ucName!="")
          {
              AnsiString device = "default";
              RemoteControllerMgr::get()->getCurrentCtrlDeviceName(device) ;
              if(RemoteControllerMgr::get()->createNewUserCase(ucName,device))
              {
                  bylog("用例[%s]创建成功",ucName);
                  statusUC->Caption = "当前用例:"+ ucName;
                  RemoteControllerMgr::get()->SetCurrUserCase(ucName);
                  lstStatus->Clear();
              }
              else
              {
                   AnsiString str;
                   str.printf("用例 %s 已经存在了",ucName);
                   ShowMessage(str);
                   bylog("用例[%s]创建失败",ucName);
                   return;
              }
              updateUserCaseList();
              int index = lstUserCase->Items->IndexOf(ucName);
              lstUserCase->ItemIndex = index;

          }
          else  bylog("用例名不能为空");

      }
      else
      {
          return;
      }
      RemoteControllerMgr::get()->StartRecord();
      btnRecord->Caption = "停止录制";
      
      bRecord = true;
}
void __fastcall TForm1::btnRecordClick(TObject *Sender)
{
    //

    if(lstUserCase->ItemIndex == -1)
    {
        ShowMessage("请选中已有用例,或新建用例后，再点录制");
        return;
    }
    if(bRecord)
    {
        btnRecord->Caption = "开始录制";
        btnPlay->Enabled = true;
        RemoteControllerMgr::get()->StopRecord();
        bool save = false;
        switch (Application->MessageBox("是否保存测试用例", "提示", 
            MB_OKCANCEL + MB_ICONQUESTION)) {
            case IDOK: {
                save = true;
                break;
            }
            case IDCANCEL: {

                break;
            }
        }
        if(save)
        {
             RemoteControllerMgr::get()->SaveRecordToUserCase();
        }
        lstUserCase->Enabled = true;
        mmAddUc->Enabled = true;

    }
    else
    {
        btnRecord->Caption = "停止录制";
        btnPlay->Enabled = false;
        lstUserCase->Enabled = false;
        mmAddUc->Enabled = false;
        RemoteControllerMgr::get()->StartRecord();


    }
    bRecord = !bRecord;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::updateUcKeyList(AnsiString &ucName)
{
     static TStringList * list = NULL;
     TUserCaseKeyList keyList;

     if(list == NULL)  list   = new TStringList;

     if(ucName == "") ucName =RemoteControllerMgr::get()->getCurrUserCase()->getName();

     RemoteControllerMgr::get()->getUcKeyList(ucName, keyList);

///////////////////////////////////////////////////
     lstStatus->Clear();
     list->Clear();

     for(size_t i = 0; i < keyList.size(); i++)
     {
         AnsiString item;

         //item = IntToStr(i) + " " + keyList.at(i)->keyName + " " + IntToStr(keyList.at(i)->time);
         //item = keyList.at(i)->keyName;
         item.printf("[%02d]    按键:%s   ",i+1, keyList.at(i)->keyName);
         list->Add(item);
     }
     lstStatus->Items = list;
}
void __fastcall TForm1::lstUserCaseClick(TObject *Sender)
{
    //
     static int old_index = -1;
     int index = lstUserCase->ItemIndex;


     if(index != -1)
     {
          if(old_index != index)
         {
              if(RemoteControllerMgr::get()->SaveRecordToUserCase(""))
              {
                  // bylog("保存用例成功");
              }
              else
              {
                  // bylog("保存用例失败");
              }
              old_index = index;
         }

          AnsiString ucName = lstUserCase->Items->Strings[index];
          updateUcKeyList(ucName);

          pUserCase = RemoteControllerMgr::get()->getUserCase(ucName);
          statusUC->Caption = "当前用例:"+ ucName;
          RemoteControllerMgr::get()->SetCurrUserCase(ucName);
     }
     else
     {
          statusUC->Caption = "没有选中用例";
     }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::lstUserCaseMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       //
       if(Button == mbRight)
       {
             if(lstUserCase->ItemIndex != -1) //选中了才弹出菜单
             {
                TPoint pt(X,Y);
                TPoint pt2 = lstUserCase->ClientToScreen(pt);
                pm3->Popup(pt2.x,pt2.y);
             }

       }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::mmUCDelClick(TObject *Sender)
{
     //
     AnsiString ucName;
     if(lstUserCase->ItemIndex != -1) //选中了才弹出菜单
     {
         ucName =  lstUserCase->Items->Strings[lstUserCase->ItemIndex];
         if(RemoteControllerMgr::get()->deleteUserCase(ucName))
         {
              //lstUserCase->DeleteSelected();
              lstStatus->Clear();
         }
         updateUserCaseList();
     }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::btnPlayClick(TObject *Sender)
{
         AnsiString device ;
         if(!RemoteControllerMgr::get()->getCurrentCtrlDeviceName(device))
         {
               ShowMessage("请先选择遥控器");
               bylog("请先选择遥控器");
               return;
         }
         if(pUserCase)
         {
              if(pUserCase->getKeyCount() > 0)
              {
                   bylog("启动运行用例【%s】",pUserCase->getName());
                   tmr1->Enabled = true;
                   
                   pUserCase->reset();
                   btnPause->Caption = "暂停";
                   btnRecord->Enabled = false;
                   btnPause->Enabled = true;
              }
         }
     
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmr1Timer(TObject *Sender)
{
    //
    if(pUserCase)
    {
     
        int index;
        int time;
        bool ret = pUserCase->run(index,time);
        if(!ret)
        {
             tmr1->Enabled = false;
             bylog("用例运行完毕");
             pUserCase->reset();
             btnPause->Enabled  = false;
             btnRecord->Enabled = true;
             return;
        }
        else
        {
            //bylog();
        }
        lstStatus->ItemIndex = index;
        edtKeyTime->Text =   time;


    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnPauseClick(TObject *Sender)
{
     if(btnPause->Caption == "暂停")
     {
          tmr1->Enabled = false;
          btnPause->Caption = "继续";
     }
     else
     {
          tmr1->Enabled = true;
          btnPause->Caption = "暂停";
     }

}
//---------------------------------------------------------------------------



void __fastcall TForm1::mmLearnKeyClick(TObject *Sender)
{
    learnKey(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
    addUserKey(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::mmIdraClick(TObject *Sender)
{
    frmIdraSet->ShowModal();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::mmRecUcClick(TObject *Sender)
{
     //   
}
//---------------------------------------------------------------------------

void __fastcall TForm1::lstStatusClick(TObject *Sender)
{
     int index = lstUserCase->ItemIndex;

     if(index != -1) //选中了才弹出菜单
     {
          AnsiString ucName =  lstUserCase->Items->Strings[index];
          index = lstStatus->ItemIndex;

          if(index != -1)
          {

              int timeS = RemoteControllerMgr::get()->getUcKeyTime(ucName,index);
              edtKeyTime->Text = timeS;
          }

     }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmAddUcClick(TObject *Sender)
{
      createUserCase();  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDownClick(TObject *Sender)
{
    UserCase* pUc = RemoteControllerMgr::get()->getCurrUserCase();
    if(pUc)
    {
         int idx =lstStatus->ItemIndex ;
         if(idx != -1)
         {
             int to = pUc->moveDown(idx);
             updateUcKeyList(pUc->getName());

             lstStatus->ItemIndex = to;
         }

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnUpClick(TObject *Sender)
{
    UserCase* pUc = RemoteControllerMgr::get()->getCurrUserCase();
    if(pUc)
    {
         int idx =lstStatus->ItemIndex ;
         if(idx != -1)
         {
             int to = pUc->moveUp(idx);
             updateUcKeyList(pUc->getName());
             lstStatus->ItemIndex = to;
             //lstStatus->ItemIndex++;
         }

    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnSaveClick(TObject *Sender)
{
     if(RemoteControllerMgr::get()->SaveRecordToUserCase(""))
     {
         ShowMessage("保存成功");
     }
     else
     {
         ShowMessage("保存失败");
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDelKeyClick(TObject *Sender)
{
       int idx =lstStatus->ItemIndex ;
       if(idx != -1)
       {
            RemoteControllerMgr::get()->deleteUcKey(idx);
            updateUcKeyList("");
       }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnModifyKeyClick(TObject *Sender)
{
    UserCase* pUc = RemoteControllerMgr::get()->getCurrUserCase();
    if(pUc)
    {
         int idx =lstStatus->ItemIndex ;
         if(idx != -1)
         {
             UserCaseKey* pKey = pUc->getKey(idx);
             pKey->time = edtKeyTime->Text.ToInt();
             updateUcKeyList(pUc->getName());
             lstStatus->ItemIndex = idx;
         }

    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::lstStatusMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(Button == mbRight && bRecord)
     {
           if(lstStatus->ItemIndex != -1) //选中了才弹出菜单
           {
              TPoint pt(X,Y);
              TPoint pt2 = lstStatus->ClientToScreen(pt);
              pm4->Popup(pt2.x,pt2.y);
           }

     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
    UserCase* pUc = RemoteControllerMgr::get()->getCurrUserCase();
    if(pUc)
    {
         int idx =lstStatus->ItemIndex ;
         if(idx != -1)
         {
             pUc->deleteKey(idx);
             updateUcKeyList(pUc->getName());
             lstStatus->ItemIndex = idx;
         }

    }
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{

    UserCase* pUc = RemoteControllerMgr::get()->getCurrUserCase();
    if(pUc)
    {
         int idx =lstStatus->ItemIndex ;
         if(idx != -1)
         {
             pUc->clearKeyList();
             updateUcKeyList(pUc->getName());
         }

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
     RemoteControllerMgr::get()->setKeyState(KEY_MODIFY,lstStatus->ItemIndex );

     lstStatus->Items->Strings[lstStatus->ItemIndex] = lstStatus->Items->Strings[lstStatus->ItemIndex] + "     **待修改";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
     RemoteControllerMgr::get()->setKeyState(KEY_INSERT,lstStatus->ItemIndex );
     lstStatus->Items->Strings[lstStatus->ItemIndex] = lstStatus->Items->Strings[lstStatus->ItemIndex] + "     **待插入"; 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
     int idx =lstUserCase->ItemIndex ;
     if(idx != -1)
     {
         frmRemoteDev->Caption = "修改用例名称";
         frmRemoteDev->ShowModal();
         if(frmRemoteDev->isOk)
         {
             AnsiString ucName = lstUserCase->Items->Strings[idx];
             if(RemoteControllerMgr::get()->existUserCase(ucName))
             {
                 if(RemoteControllerMgr::get()->updateUcName(ucName,frmRemoteDev->devName))
                 {
                     updateUserCaseList();
                 }
             }


         }
           //RemoteControllerMgr::get()->updateUcName()
     }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::tmr2Timer(TObject *Sender)
{
    bool nowSt = RemoteControllerMgr::get()->portStatus();

    if(nowSt == bPortStatus)   return;
    if(nowSt)
    {
          bylog("红外发射模块通讯正常");
          updateIdraStatus(true);
          disableWork(false);
    }
    else
    {
          bylog("红外发射模块通讯异常，请插入");
          updateIdraStatus(false);
          disableWork(true);
    }
    bPortStatus = nowSt;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
     if(RemoteControllerMgr::get()->SaveRecordToUserCase(""))
     {
         //ShowMessage("保存成功");
     }
     else
     {
         //ShowMessage("保存失败");
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
    //
     int idx =lstUserCase->ItemIndex ;
     if(idx != -1)
     {
         AnsiString ucName = lstUserCase->Items->Strings[idx];
         AnsiString InputString = InputBox("修改用例" + ucName, "按键间隔时间(s):   ", "5");

         int time;
         if(!TryStrToInt(InputString, time))
         {
               ShowMessage("输入时间不正确");
               return;

         }
         else
         {

         }
     }


}
//---------------------------------------------------------------------------

