object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'FontCombine'
  ClientHeight = 479
  ClientWidth = 680
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label_FontPath1: TLabel
    Left = 8
    Top = 39
    Width = 56
    Height = 13
    Caption = 'Font Path 1'
  end
  object Label_FontPath2: TLabel
    Left = 343
    Top = 39
    Width = 56
    Height = 13
    Caption = 'Font Path 2'
  end
  object CheckListBox1: TCheckListBox
    Left = 8
    Top = 72
    Width = 329
    Height = 361
    OnClickCheck = CheckListBox1ClickCheck
    ItemHeight = 13
    TabOrder = 0
  end
  object CheckListBox2: TCheckListBox
    Left = 343
    Top = 72
    Width = 329
    Height = 361
    OnClickCheck = CheckListBox2ClickCheck
    ItemHeight = 13
    TabOrder = 1
  end
  object Button_FontPath1: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Font 1'
    TabOrder = 2
    OnClick = Button_FontPath1Click
  end
  object Button_FontPath2: TButton
    Left = 343
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Font 2'
    TabOrder = 3
    OnClick = Button_FontPath2Click
  end
  object Button_Combine: TButton
    Left = 304
    Top = 448
    Width = 75
    Height = 25
    Caption = 'Combine'
    TabOrder = 4
    OnClick = Button_CombineClick
  end
  object OpenDialog1: TOpenDialog
    Left = 624
    Top = 16
  end
end
