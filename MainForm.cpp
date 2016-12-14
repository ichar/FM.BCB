#include <vcl.h>
//---------------------------------------------------------------------------
#pragma hdrstop

#include "MainForm.h"
#include "utils.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

#define DEBUG 0
//---------------------------------------------------------------------------
char* LOCALE_NAME = "locale.txt";

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    const char *Msg = "Simple RichText Editor";
    SendMessage(Handle, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)Msg);

    width = this->Width;
    height = this->Height;

    int code = loadLocale(LOCALE_NAME);
    if (code != 0)
    {
        ShowMessage("Locale not found! Exit: " + IntToStr(code));
    }

#if DEBUG == 1
    string body = get_filebody(LOCALE_NAME);
    ShowMessage(body.c_str());
#endif

    gbFileContent->Width = width - 36;
    pnlFileContent->Width = width - 70;
    reFileContent->Width = width - 90;

    reFileContent->Clear();

    TMenuItem *pmLeft = new TMenuItem(MainForm->PopupMenu);
    pmLeft->Caption = loc["Left"];
    pmLeft->OnClick = &this->pmAlignLeftClick;
    pmAlign->Insert(0,pmLeft);

    TMenuItem *pmRight = new TMenuItem(MainForm->PopupMenu);
    pmRight->Caption = loc["Right"];
    pmRight->OnClick = &this->pmAlignRightClick;
    pmAlign->Insert(1,pmRight);

    TMenuItem *pmCenter = new TMenuItem(MainForm->PopupMenu);
    pmCenter->Caption = loc["Center"];
    pmCenter->OnClick = &this->pmAlignCenterClick;
    pmAlign->Insert(2,pmCenter);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuFileExitItemClick(TObject *Sender)
{
    exit(0);
}
//---------------------------------------------------------------------------
int TMainForm::loadLocale(char* file)
{
    FILE *fp;
    TStringList* lst = new TStringList();
    char str[80];

    if ((fp = fopen(file, "rb")) == NULL)
    {
        return -1;
    }

    while(!feof(fp))
    {
        fgets(str, 79, fp);
        lst->Clear();
        split(lst, str, ":");

        if (lst->Count == 2)
        {
            loc.insert(stmap::value_type(
                lst->Strings[0].c_str(),
                lst->Strings[1]
            ));
        }
    }

    delete lst;
    lst = NULL;

    fclose(fp);
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuFileOpenItemClick(TObject *Sender)
{
    if (dlgMainOpen->Execute())
    {
        filename = dlgMainOpen->FileName;
        reFileContent->Lines->LoadFromFile(filename);
        reFileContent->Modified = false;
        edFileName->Text = filename;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
    int w = this->Width - width;
    int h = this->Height - height;

    bool isWidthOverflow = false, isHeightOverflow = false;

    if (this->Width >= MIN_WIDTH) {
        gbActions->Width += w;
        pnlProps->Width += w;
        pnlFileName->Width += w;
        edFileName->Width += w;
        gbFileContent->Width += w;
        pnlFileContent->Width += w;
        reFileContent->Width += w;
    } else {
        isWidthOverflow = true;
    }

    if (this->Height >= MIN_HEIGHT) {
        gbFileContent->Height += h;
        pnlFileContent->Height += h;
        reFileContent->Height += h;
    } else {
        isHeightOverflow = true;
    }

    if (isWidthOverflow)
        this->Width = width;
    else
        width = this->Width;

    if (isHeightOverflow)
        this->Height = height;
    else
        height = this->Height;

    string outs = format(
        " = Width: %s[%s,%i] *** Height: %s[%s,%i] = ",
        IntToStr(width),
        IntToStr(w),
        isWidthOverflow ? 1 : 0,
        IntToStr(height),
        IntToStr(h),
        isHeightOverflow ? 1 : 0
    );
    edFormProps->Text = outs.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuFileSaveItemClick(TObject *Sender)
{
    if (filename.Length() == 0)
        return;
    reFileContent->Lines->SaveToFile(filename);
    reFileContent->Modified = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuFileSaveAsItemClick(TObject *Sender)
{
    dlgMainSave->FileName = filename;
    if (dlgMainSave->Execute())
    {
        filename = dlgMainSave->FileName;
        reFileContent->Lines->SaveToFile(filename);
        reFileContent->Modified = false;
        edFileName->Text = filename;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuEditCutItemClick(TObject *Sender)
{
    if (filename.Length() == 0)
        return;
    reFileContent->CutToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuEditCopyItemClick(TObject *Sender)
{
    if (filename.Length() == 0)
        return;
    reFileContent->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuEditPasteItemClick(TObject *Sender)
{
    if (filename.Length() == 0)
        return;
    reFileContent->PasteFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::pmFontClick(TObject *Sender)
{
    dlgFont->Font->Assign(reFileContent->SelAttributes);
    if (dlgFont->Execute())
    {
        reFileContent->SelAttributes->Assign(dlgFont->Font);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::pmAlignLeftClick(TObject *Sender)
{
    reFileContent->Paragraph->Alignment = taLeftJustify;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::pmAlignRightClick(TObject *Sender)
{
    reFileContent->Paragraph->Alignment = taRightJustify;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::pmAlignCenterClick(TObject *Sender)
{
    reFileContent->Paragraph->Alignment = taCenter;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuEditFindItemClick(TObject *Sender)
{
    dlgFind->FindText = reFileContent->SelText;
    dlgFind->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::dlgFindFind(TObject *Sender)
{
    int pos_at, pos_from, pos_to;
    TSearchTypes options;
    TReplaceDialog *dlg = (TReplaceDialog *)Sender;

    pos_from = reFileContent->SelStart;
    if (dlg->Options.Contains(frDown))
    {
        if (reFileContent->SelLength)
            pos_from += reFileContent->SelLength;
        pos_to = reFileContent->Text.Length() - pos_from;
    } 
    else 
    {
        pos_to = 0;
    }

    if (dlg->Options.Contains(frWholeWord))
        options << stWholeWord;
    else
        options >> stWholeWord;

    if (dlg->Options.Contains(frMatchCase))
        options << stMatchCase;
    else
        options >> stMatchCase;

    pos_at = reFileContent->FindText(dlg->FindText, pos_from, pos_to, options);

    if (pos_at != -1)
    {
        reFileContent->SelStart = pos_at;
        reFileContent->SelLength = dlg->FindText.Length();
        if (dlg->Name == "dlgReplace" && dlg->Options.Contains(frReplaceAll))
            dlgReplaceReplace(Sender);
    }
    else
        ShowMessage(AnsiString(format(
            loc["Text not found"].c_str(),
            dlg->FindText
        ).c_str()));

    reFileContent->Perform(EM_SCROLLCARET,0,0);
    reFileContent->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::dlgReplaceReplace(TObject *Sender)
{
    reFileContent->SetFocus();
    if (reFileContent->SelText != "")
    {
        reFileContent->SelText = dlgReplace->ReplaceText;
        if (dlgReplace->Options.Contains(frReplaceAll))
            reFileContent->SelStart += dlgReplace->ReplaceText.Length();
    }
    else if (dlgReplace->Options.Contains(frReplace))
    {
        ShowMessage(AnsiString(format(
            loc["Text not found"].c_str(),
            dlgReplace->FindText
        ).c_str()));
        return;
    }
    if (dlgReplace->Options.Contains(frReplaceAll))
        dlgFindFind(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuEditUndoItemClick(TObject *Sender)
{
    reFileContent->Undo();
}
//---------------------------------------------------------------------------

