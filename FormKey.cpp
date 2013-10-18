//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormKey.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
    ret = false;
    keyName = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
    //
    ret = false;
    keyName = "";
    edtName->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::btnAddClick(TObject *Sender)
{
      ret = true;
      keyName = edtName->Text;
      Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::btnCancelClick(TObject *Sender)
{
      ret = false;
      keyName = "";
      Close();
}
//---------------------------------------------------------------------------

