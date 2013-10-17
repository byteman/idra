object frmRemoteDev: TfrmRemoteDev
  Left = 523
  Top = 314
  Width = 348
  Height = 207
  Caption = #26032#24314#36965#25511#22120
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object grp1: TGroupBox
    Left = 0
    Top = 0
    Width = 340
    Height = 113
    Align = alTop
    TabOrder = 0
    object lblEdtName: TLabeledEdit
      Left = 104
      Top = 48
      Width = 137
      Height = 21
      EditLabel.Width = 36
      EditLabel.Height = 13
      EditLabel.Caption = #21517#31216#65306
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
    end
  end
  object btnOk: TBitBtn
    Left = 72
    Top = 128
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TBitBtn
    Left = 176
    Top = 128
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 2
    OnClick = btnCancelClick
  end
end
