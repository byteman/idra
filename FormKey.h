//---------------------------------------------------------------------------

#ifndef FormKeyH
#define FormKeyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *grp1;
        TListBox *lst1;
        TListBox *lst2;
        TButton *btn1;
        TButton *btn2;
        TButton *btnSaveKey;
        TButton *btnCancelKey;
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
