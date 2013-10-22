//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormIdraSet.h"
#include "Sysconfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmIdraSet *frmIdraSet;
//---------------------------------------------------------------------------
__fastcall TfrmIdraSet::TfrmIdraSet(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmIdraSet::btnSaveIdraClick(TObject *Sender)
{
     //
     SystemConfig config;
     config.port = edtCom->Text.ToInt();
     config.bps  = edtBps->Text.ToInt();
     config.save();
     this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmIdraSet::FormShow(TObject *Sender)
{
      SystemConfig config;
      edtCom->Text = config.port;
      edtBps->Text = config.bps;
}
//---------------------------------------------------------------------------

void __fastcall TfrmIdraSet::btnCancelClick(TObject *Sender)
{
     this->Close();
}
//---------------------------------------------------------------------------

