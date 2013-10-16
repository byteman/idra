//---------------------------------------------------------------------------

#ifndef FormIdraSetH
#define FormIdraSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmIdraSet : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *edtCom;
        TLabeledEdit *edtBps;
        TBitBtn *btnAutoDectect;
        TBitBtn *btnSaveIdra;
        TBitBtn *btnCancel;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmIdraSet(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmIdraSet *frmIdraSet;
//---------------------------------------------------------------------------
#endif
