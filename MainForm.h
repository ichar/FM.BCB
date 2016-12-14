//---------------------------------------------------------------------------
#ifndef FM_MAIN_H
#define FM_MAIN_H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#pragma hdrstop

#include "utils.h"
//---------------------------------------------------------------------------

class TMainForm : public TForm
{
static const int MIN_WIDTH = 500;
static const int MIN_HEIGHT = 380;

__published:	// IDE-managed Components
        TMainMenu *MainMenu;

        TMenuItem *MenuFileItem;
        TMenuItem *MenuFileNewItem;
        TMenuItem *MenuFileOpenItem;
        TMenuItem *MenuFileSaveItem;
        TMenuItem *MenuFileSaveAsItem;
        TMenuItem *MenuFilePrintItem;
        TMenuItem *MenuFilePrintSetupItem;
        TMenuItem *MenuFileExitItem;

        TMenuItem *MenuEditItem;
        TMenuItem *MenuEditObjectItem;
        TMenuItem *MenuEditLinksItem;
        TMenuItem *MenuEditGoToItem;
        TMenuItem *MenuEditReplaceItem;
        TMenuItem *MenuEditFindItem;
        TMenuItem *MenuEditPasteItem;
        TMenuItem *MenuEditPasteSpecialItem;
        TMenuItem *MenuEditCopyItem;
        TMenuItem *MenuEditCutItem;
        TMenuItem *MenuEditRepeatcommandItem;
        TMenuItem *MenuEditUndoItem;

        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;

        TMenuItem *MenuWindowItem;
        TMenuItem *MenuWindowShowItem;
        TMenuItem *MenuWindowHideItem;
        TMenuItem *MenuWindowArrangeAllItem;
        TMenuItem *MenuWindowCascadeItem;
        TMenuItem *MenuWindowTileItem;
        TMenuItem *MenuWindowNewWindowItem;

        TMenuItem *MenuHelpItem;
        TMenuItem *MenuHelpAboutItem;
        TMenuItem *MenuHelpHowtoUseHelpItem;
        TMenuItem *MenuHelpTutorialItem;
        TMenuItem *MenuHelpIndexItem;
        TMenuItem *MenuHelpContentsItem;

        TGroupBox *gbActions;

        TPanel *pnlProps;
        TLabel *lblFormProps;
        TEdit *edFormProps;

        TPanel *pnlFileName;
        TLabel *lblFileName;
        TEdit *edFileName;

        TGroupBox *gbFileContent;
        TPanel *pnlFileContent;
        TRichEdit *reFileContent;

        TOpenDialog *dlgMainOpen;
        TSaveDialog *dlgMainSave;
        TFontDialog *dlgFont;
        TFindDialog *dlgFind;
        TReplaceDialog *dlgReplace;

        TPopupMenu *PopupMenu;
        TMenuItem *pmFont;
        TMenuItem *pmAlign;

        TImageList *imagesListMainMenu;

        void __fastcall FormResize(TObject *Sender);

        void __fastcall MenuFileOpenItemClick(TObject *Sender);
        void __fastcall MenuFileSaveItemClick(TObject *Sender);
        void __fastcall MenuFileSaveAsItemClick(TObject *Sender);
        void __fastcall MenuFileExitItemClick(TObject *Sender);

        void __fastcall MenuEditCutItemClick(TObject *Sender);
        void __fastcall MenuEditCopyItemClick(TObject *Sender);
        void __fastcall MenuEditPasteItemClick(TObject *Sender);
        void __fastcall MenuEditFindItemClick(TObject *Sender);
        void __fastcall MenuEditUndoItemClick(TObject *Sender);

        void __fastcall pmFontClick(TObject *Sender);
        void __fastcall pmAlignLeftClick(TObject *Sender);
        void __fastcall pmAlignRightClick(TObject *Sender);
        void __fastcall pmAlignCenterClick(TObject *Sender);

        void __fastcall dlgFindFind(TObject *Sender);
        void __fastcall dlgReplaceReplace(TObject *Sender);

private:	// User declarations
        AnsiString filename;
        int width, height;
        stmap loc;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        loadLocale(char* file);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
