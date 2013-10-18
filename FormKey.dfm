object Form2: TForm2
  Left = 432
  Top = 383
  Width = 313
  Height = 212
  Caption = #28155#21152#33258#23450#20041#25353#38190
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
    Width = 305
    Height = 121
    Align = alTop
    TabOrder = 0
    object edtName: TLabeledEdit
      Left = 88
      Top = 56
      Width = 137
      Height = 28
      EditLabel.Width = 60
      EditLabel.Height = 13
      EditLabel.Caption = #25353#38190#21517#31216#65306
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      LabelPosition = lpLeft
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 0
    end
  end
  object btnAdd: TButton
    Left = 49
    Top = 139
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 1
    OnClick = btnAddClick
  end
  object btnCancel: TButton
    Left = 168
    Top = 139
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 2
    OnClick = btnCancelClick
  end
end
