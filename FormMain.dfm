object Form1: TForm1
  Left = 115
  Top = 188
  Width = 1025
  Height = 708
  Caption = #36965#25511#22120#27169#25311#22120'V1.0'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mm1
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object grp2: TGroupBox
    Left = 614
    Top = 0
    Width = 395
    Height = 631
    Align = alClient
    Caption = #29992#20363#27979#35797#65306
    TabOrder = 0
    object grp3: TGroupBox
      Left = 2
      Top = 15
      Width = 391
      Height = 105
      Align = alTop
      TabOrder = 0
      object btnPlay: TBitBtn
        Left = 24
        Top = 32
        Width = 75
        Height = 25
        Caption = #36816#34892#29992#20363
        TabOrder = 0
        OnClick = btnPlayClick
      end
      object btnPause: TBitBtn
        Left = 110
        Top = 32
        Width = 75
        Height = 25
        Caption = #26242#20572
        Enabled = False
        TabOrder = 1
        OnClick = btnPauseClick
      end
      object btnRecord: TBitBtn
        Left = 200
        Top = 32
        Width = 75
        Height = 25
        Caption = #24320#22987#24405#21046
        TabOrder = 2
        OnClick = btnRecordClick
      end
    end
    object grp4: TGroupBox
      Left = 2
      Top = 120
      Width = 391
      Height = 289
      Align = alTop
      Caption = #29992#20363#25191#34892#27493#39588#65306
      TabOrder = 1
      object lstStatus: TListBox
        Left = 2
        Top = 15
        Width = 294
        Height = 272
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
        OnClick = lstStatusClick
        OnMouseUp = lstStatusMouseUp
      end
      object pnl1: TPanel
        Left = 296
        Top = 15
        Width = 93
        Height = 272
        Align = alRight
        TabOrder = 1
        object btnUp: TBitBtn
          Left = 8
          Top = 80
          Width = 81
          Height = 33
          Caption = #19978#31227
          TabOrder = 0
          OnClick = btnUpClick
        end
        object btnDown: TBitBtn
          Left = 8
          Top = 117
          Width = 81
          Height = 33
          Caption = #19979#31227
          TabOrder = 1
          OnClick = btnDownClick
        end
        object btnDelKey: TBitBtn
          Left = 8
          Top = 154
          Width = 81
          Height = 33
          Caption = #21024#38500
          TabOrder = 2
          OnClick = btnDelKeyClick
        end
        object btnModifyKey: TBitBtn
          Left = 48
          Top = 21
          Width = 40
          Height = 25
          Caption = #20462#25913
          TabOrder = 3
          OnClick = btnModifyKeyClick
        end
        object edtKeyTime: TLabeledEdit
          Left = 8
          Top = 24
          Width = 33
          Height = 21
          EditLabel.Width = 81
          EditLabel.Height = 13
          EditLabel.Caption = #38388#38548#26102#38388'('#31186')'#65306' '
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 4
        end
        object btnSave: TButton
          Left = 8
          Top = 194
          Width = 81
          Height = 33
          Caption = #20445#23384
          TabOrder = 5
          OnClick = btnSaveClick
        end
      end
    end
    object grp5: TGroupBox
      Left = 2
      Top = 409
      Width = 391
      Height = 220
      Align = alClient
      Caption = #24037#20316#35760#24405#65306
      TabOrder = 2
      object mmoInfo: TMemo
        Left = 2
        Top = 15
        Width = 387
        Height = 203
        Align = alClient
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
  object grp1: TGroupBox
    Left = 0
    Top = 0
    Width = 249
    Height = 631
    Align = alLeft
    Caption = #29992#20363#21015#34920
    TabOrder = 1
    object lstUserCase: TListBox
      Left = 2
      Top = 15
      Width = 245
      Height = 614
      Align = alClient
      ItemHeight = 13
      ScrollWidth = 1
      TabOrder = 0
      OnClick = lstUserCaseClick
      OnMouseUp = lstUserCaseMouseUp
    end
  end
  object rzstsbr1: TRzStatusBar
    Left = 0
    Top = 631
    Width = 1009
    Height = 19
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
    BorderWidth = 0
    TabOrder = 2
    object statusName: TRzStatusPane
      Left = 0
      Top = 0
      Width = 249
      Height = 19
      Align = alLeft
      Caption = #24403#21069#36965#25511#22120#65306'ZCX100'
    end
    object statusUC: TRzStatusPane
      Left = 249
      Top = 0
      Width = 368
      Height = 19
      Align = alLeft
      Caption = #24403#21069#29992#20363#65306'UserCase1'
    end
    object rzstspn3: TRzStatusPane
      Left = 617
      Top = 0
      Width = 376
      Height = 19
      Align = alLeft
      Caption = #25191#34892#32467#26524':'
    end
  end
  object grpRemoter: TGroupBox
    Left = 249
    Top = 0
    Width = 365
    Height = 631
    Align = alLeft
    Caption = #36965#25511#22120#21517#31216#65306
    TabOrder = 3
    object lbl1: TLabel
      Left = 16
      Top = 43
      Width = 84
      Height = 13
      Caption = #36873#25321#36965#25511#22120':       '
    end
    object shpIdra: TShape
      Left = 296
      Top = 40
      Width = 33
      Height = 25
      Brush.Color = clRed
      Shape = stCircle
    end
    object grpStandKey: TGroupBox
      Left = 2
      Top = 109
      Width = 361
      Height = 336
      Align = alBottom
      Caption = #26631#20934#25353#38190#65306
      TabOrder = 0
    end
    object grpUserKey: TGroupBox
      Left = 2
      Top = 445
      Width = 361
      Height = 184
      Align = alBottom
      Caption = #33258#23450#20041#25353#38190#65288#40736#26631#21491#38190#21487#28155#21152#65289#65306
      TabOrder = 1
      OnMouseUp = grpUserKeyMouseUp
    end
    object cbbDevice: TComboBox
      Left = 104
      Top = 40
      Width = 169
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      OnChange = cbbDeviceChange
    end
    object btnNew: TBitBtn
      Left = 24
      Top = 88
      Width = 75
      Height = 25
      Caption = #26032#24314#36965#25511#22120
      TabOrder = 3
      OnClick = btnNewClick
    end
    object btnDel: TBitBtn
      Left = 112
      Top = 88
      Width = 75
      Height = 25
      Caption = #21024#38500#36965#25511#22120
      TabOrder = 4
      OnClick = btnDelClick
    end
    object btnModify: TBitBtn
      Left = 192
      Top = 88
      Width = 75
      Height = 25
      Caption = #20462#25913
      TabOrder = 5
      OnClick = btnModifyClick
    end
  end
  object btnLearn: TBitBtn
    Left = 528
    Top = 88
    Width = 75
    Height = 25
    Caption = #24320#22987#23398#20064
    TabOrder = 4
    OnClick = btnLearnClick
  end
  object com1: TYbCommDevice
    PortNo = 2
    Baud = br115200
    ByteSize = 8
    InBufSize = 8192
    OutBufSize = 8192
    HwInSize = 1200
    HwOutSize = 1200
    QueueSize = 16
    PackageSize = 4096
    Left = 880
    Top = 80
  end
  object mm1: TMainMenu
    Left = 968
    Top = 80
    object mmCtrl: TMenuItem
      AutoHotkeys = maManual
      Caption = #36965#25511#22120#31649#29702
      object mmAddDev: TMenuItem
        AutoHotkeys = maManual
        Caption = #28155#21152#36965#25511#22120
        ShortCut = 16462
        OnClick = mmAddDevClick
      end
      object mmDelDev: TMenuItem
        AutoHotkeys = maManual
        Caption = #21024#38500#36965#25511#22120
        ShortCut = 16452
        OnClick = mmDelDevClick
      end
      object mmMDev: TMenuItem
        AutoHotkeys = maManual
        Caption = #20462#25913#36965#25511#22120
        ShortCut = 16461
        OnClick = mmMDevClick
      end
      object mmLearnKey: TMenuItem
        AutoHotkeys = maManual
        Caption = #23398#20064#25353#38190
        ShortCut = 16460
        OnClick = mmLearnKeyClick
      end
      object N1: TMenuItem
        AutoHotkeys = maManual
        Caption = #28155#21152#33258#23450#20041#25353#38190
        ShortCut = 16449
        OnClick = N1Click
      end
    end
    object N2: TMenuItem
      AutoHotkeys = maManual
      Caption = #29992#20363#31649#29702
      object mmAddUc: TMenuItem
        Caption = #26032#24314#29992#20363
        ShortCut = 49230
        OnClick = mmAddUcClick
      end
    end
    object mmLog: TMenuItem
      AutoHotkeys = maManual
      Caption = #28165#31354#26085#24535
      ShortCut = 16466
    end
  end
  object pm1: TPopupMenu
    Left = 936
    Top = 80
    object mmKeyAdd: TMenuItem
      Caption = #28155#21152#33258#23450#38190
      OnClick = mmKeyAddClick
    end
  end
  object pm2: TPopupMenu
    Left = 832
    Top = 80
    object mmKeyAdd2: TMenuItem
      Caption = #28155#21152#25353#38190
      OnClick = mmKeyAdd2Click
    end
    object mmKeyDel: TMenuItem
      Caption = #21024#38500#25353#38190
      OnClick = mmKeyDelClick
    end
  end
  object pm3: TPopupMenu
    Left = 768
    Top = 80
    object N7: TMenuItem
      Caption = #20462#25913#29992#20363#21517
      OnClick = N7Click
    end
    object mmUCDel: TMenuItem
      Caption = #21024#38500#24403#21069#29992#20363
      OnClick = mmUCDelClick
    end
    object mmUCDelAll: TMenuItem
      Caption = #28165#31354#25152#26377#29992#20363
    end
  end
  object tmr1: TTimer
    Enabled = False
    OnTimer = tmr1Timer
    Left = 520
    Top = 16
  end
  object pm4: TPopupMenu
    Left = 680
    Top = 80
    object N3: TMenuItem
      Caption = #21024#38500#25353#38190
      OnClick = N3Click
    end
    object N4: TMenuItem
      Caption = #20462#25913#25353#38190
      OnClick = N4Click
    end
    object N6: TMenuItem
      Caption = #25554#20837#25353#38190
      OnClick = N6Click
    end
    object N5: TMenuItem
      Caption = #28165#38500#20840#37096
      OnClick = N5Click
    end
  end
  object tmr2: TTimer
    Interval = 2000
    OnTimer = tmr2Timer
    Left = 552
    Top = 16
  end
end
