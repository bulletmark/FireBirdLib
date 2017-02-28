program FontCombine;

uses
  Vcl.Forms,
  FontCombineUnit1 in 'FontCombineUnit1.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
