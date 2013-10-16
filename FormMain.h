//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "YbCommDevice.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "RzPanel.hpp"
#include <Buttons.hpp>
#include "RzStatus.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TYbCommDevice *com1;
        TMainMenu *mm1;
        TMenuItem *mmIdra;
        TMenuItem *mmCtrl;
        TMenuItem *mmUserCase;
        TGroupBox *grp2;
        TGroupBox *grp1;
        TRzStatusBar *rzstsbr1;
        TGroupBox *grpRemoter;
        TGroupBox *grpStandKey;
        TGroupBox *grpUserKey;
        TMenuItem *mmAddDev;
        TListBox *lstUserCase;
        TGroupBox *grp3;
        TBitBtn *btnPlay;
        TBitBtn *btnPause;
        TBitBtn *btnResume;
        TGroupBox *grp4;
        TListBox *lstStatus;
        TGroupBox *grp5;
        TMemo *mmoInfo;
        TRzStatusPane *rzstspn1;
        TRzStatusPane *rzstspn2;
        TRzStatusPane *rzstspn3;
        TBitBtn *btn1;
        TBitBtn *btn2;
        TBitBtn *btn3;
        TBitBtn *btn4;
        TBitBtn *btn5;
        TBitBtn *btn6;
        TBitBtn *btn7;
        TBitBtn *btn8;
        TBitBtn *btn9;
        TBitBtn *btn10;
        TBitBtn *btn11;
        TBitBtn *btn12;
        TBitBtn *btn13;
        TBitBtn *btn14;
        TBitBtn *btn15;
        TBitBtn *btn16;
        TBitBtn *btn17;
        TBitBtn *btn18;
        TBitBtn *btn19;
        TBitBtn *btn20;
        TBitBtn *btn21;
        TBitBtn *btn22;
        TBitBtn *btn26;
        TBitBtn *btn27;
        TBitBtn *btn28;
        TBitBtn *btn29;
        TBitBtn *btn30;
        TPopupMenu *pm1;
        TMenuItem *N1;
        TMenuItem *mmAddUC;
        TBitBtn *btnRecord;
        TLabel *lbl1;
        TComboBox *cbbDevice;
        TBitBtn *btn23;
        TBitBtn *btnNew;
        TBitBtn *btnDel;
        TBitBtn *btnModify;
        TMenuItem *mmAddKey;
        TBitBtn *btnAddKey;
        TBitBtn *btn24;
    void __fastcall FormCreate(TObject *Sender);
        void __fastcall mmIdraClick(TObject *Sender);
        void __fastcall mmAddKeyClick(TObject *Sender);
        void __fastcall btn1Click(TObject *Sender);
        void __fastcall btn24Click(TObject *Sender);
        void __fastcall btnPlayClick(TObject *Sender);
        void __fastcall btn23Click(TObject *Sender);
    void __fastcall btn2Click(TObject *Sender);
    void __fastcall btn6Click(TObject *Sender);
private:	// User declarations
    void __fastcall addKeyButton(AnsiString name,TObject *Sender);
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
