//---------------------------------------------------------------------------

#ifndef FormKeyH
#define FormKeyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *grp1;
        TButton *btnAdd;
        TButton *btnCancel;
        TLabeledEdit *edtName;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
        AnsiString keyName;
        bool       ret;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
