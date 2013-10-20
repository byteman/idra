object OKBottomDlg: TOKBottomDlg
  Left = 473
  Top = 264
  BorderStyle = bsDialog
  Caption = #26159#21542#20445#23384#29992#20363#65311#65311
  ClientHeight = 214
  ClientWidth = 313
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 297
    Height = 161
    Shape = bsFrame
  end
  object OKBtn: TButton
    Left = 79
    Top = 180
    Width = 75
    Height = 25
    Caption = #20445#23384
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 159
    Top = 180
    Width = 75
    Height = 25
    Cancel = True
    Caption = #21462#28040
    ModalResult = 2
    TabOrder = 1
    OnClick = CancelBtnClick
  end
  object lbledtUCname: TLabeledEdit
    Left = 96
    Top = 72
    Width = 161
    Height = 33
    EditLabel.Width = 60
    EditLabel.Height = 13
    EditLabel.Caption = #29992#20363#21517#31216#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    LabelPosition = lpLeft
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 2
  end
end
