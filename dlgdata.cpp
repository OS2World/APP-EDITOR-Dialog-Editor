/* 


	dlgdata.cpp (emx+gcc) 

	1994,95 Giovanni Iachello
	This is freeware software. You can use or modify it as you wish,
	provided that the part of code that I wrote remains freeware.
	Freeware means that the source code must be available on request 
	to anyone.
	You must also include this notice in all files derived from this
	file.


*/
#include "dlgedit.h"


ULONG winflvalues[26]={
	FCF_TITLEBAR, FCF_SYSMENU, FCF_MENU, FCF_SIZEBORDER, FCF_MINBUTTON,
	FCF_MAXBUTTON, FCF_VERTSCROLL, FCF_HORZSCROLL, FCF_DLGBORDER,
	FCF_BORDER, FCF_SHELLPOSITION, FCF_TASKLIST, FCF_NOBYTEALIGN,
	FCF_NOMOVEWITHOWNER, FCF_ICON, FCF_ACCELTABLE, FCF_SYSMODAL,
	FCF_SCREENALIGN, FCF_MOUSEALIGN, FCF_PALETTE_NORMAL, FCF_PALETTE_HELP,
	FCF_PALETTE_POPUPODD, FCF_PALETTE_POPUPEVEN, FCF_HIDEBUTTON,
	FCF_HIDEMAX, FCF_AUTOICON
};

PCHAR winflnames[26]={
	"FCF_TITLEBAR", "FCF_SYSMENU", "FCF_MENU", "FCF_SIZEBORDER", "FCF_MINBUTTON",
	"FCF_MAXBUTTON", "FCF_VERTSCROLL", "FCF_HORZSCROLL", "FCF_DLGBORDER",
	"FCF_BORDER", "FCF_SHELLPOSITION", "FCF_TASKLIST", "FCF_NOBYTEALIGN",
	"FCF_NOMOVEWITHOWNER", "FCF_ICON", "FCF_ACCELTABLE", "FCF_SYSMODAL",
	"FCF_SCREENALIGN", "FCF_MOUSEALIGN", "FCF_PALETTE_NORMAL", "FCF_PALETTE_HELP",
	"FCF_PALETTE_POPUPODD", "FCF_PALETTE_POPUPEVEN", "FCF_HIDEBUTTON",
	"FCF_HIDEMAX", "FCF_AUTOICON"
};

PCHAR apchClassNames[] = {
	" ",
	"WC_FRAME",
	"WC_COMBOBOX",
	"WC_BUTTON",
	"WC_MENU",
	"WC_STATIC",
	"WC_ENTRYFIELD",
	"WC_LISTBOX",
	"WC_SCROLLBAR",
	"WC_TITLEBAR",
	"WC_MLE",
	"WC_APPSTAT",
	"WC_KBDSTAT",
	"WC_PECIC",
	"WC_DBE_KKPOPUP",
	"WC_SPINBUTTON",
	"WC_CONTAINER",
	"WC_SLIDER",
	"WC_VALUESET",
	"WC_NOTEBOOK",
	"WC_PENFIRST",
	"WC_PENLAST",
	"WC_MMPMFIRST",
	"WC_MMPMLAST",
	"WC_BUTTON",
	"WC_BUTTON",
	"WC_BUTTON",
	"WC_STATIC"
};

PCHAR apchDialogControlRCNames[] = {
	NULL,
	NULL,
	NULL,
	"PUSHBUTTON",
	NULL,
	"TEXT",
	"ENTRYFIELD",
	"LISTBOX",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"SPINBUTTON",
	NULL,
	"SLIDER",
	"VALUESET",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"AUTOCHECKBOX",
	"AUTORADIOBUTTON",
	"AUTO3STATE",
	"GROUPBOX"
};

_style* apsStyles[] = {
	aWindowStyles,
	aFrameStyles,
	aComboBoxStyles,
	aButtonStyles,
	NULL,
	aStaticStyles,
	aEntryStyles,
	aListBoxStyles,
	aScrollBarStyles,
	NULL,
	aMLEStyles,
	NULL,NULL,NULL,NULL,
	aSPBStyles,
	aContainerStyles,
	aSliderStyles,
	aValueSetStyles,
	aBookStyles,
	NULL,NULL,NULL,NULL,
	aButtonStyles,
	aButtonStyles,
	aButtonStyles,
	aStaticStyles
};

LONG lClassesDefStyles[] = {
	0,
	0,
	BS_PUSHBUTTON,
	0,
	0,
	SS_TEXT,
	ES_MARGIN,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	BS_CHECKBOX,
	BS_RADIOBUTTON,
	BS_3STATE,
	SS_GROUPBOX
};

PSZ apszClasses[] = {
	NULL,
	WC_FRAME,
	WC_COMBOBOX,
	WC_BUTTON,
	WC_MENU,
	WC_STATIC,
	WC_ENTRYFIELD,
	WC_LISTBOX,
	WC_SCROLLBAR,
	WC_TITLEBAR,
	WC_MLE,
	WC_APPSTAT,
	WC_KBDSTAT,
	WC_PECIC,
	WC_DBE_KKPOPUP,
	WC_SPINBUTTON,
	WC_CONTAINER,
	WC_SLIDER,
	WC_VALUESET,
	WC_NOTEBOOK,
	WC_PENFIRST,
	WC_PENLAST,
	WC_MMPMFIRST,
	WC_MMPMLAST,
	WC_BUTTON,
	WC_BUTTON,
	WC_BUTTON,
	WC_STATIC
};


int menu2classindex[] = {
	0,0,0,0,0,0,0,0,0,0,0,5,6,7,2,3,15,17,18,24,25,26,27
};

_style aWindowStyles[] = {
    { "WS_VISIBLE", WS_VISIBLE, 0, 0 },
    { "WS_DISABLED", WS_DISABLED, 0, 0 },
    { "WS_CLIPCHILDREN", WS_CLIPCHILDREN, 0, 0 },
    { "WS_CLIPSIBLINGS", WS_CLIPSIBLINGS, 0, 0 },
    { "WS_PARENTCLIP", WS_PARENTCLIP, 0, 0 },
    { "WS_SAVEBITS", WS_SAVEBITS, 0, 0 },
    { "WS_SYNCPAINT", WS_SYNCPAINT, 0, 0 },
    { "WS_MINIMIZED", WS_MINIMIZED, 0, 0 },
    { "WS_MAXIMIZED", WS_MAXIMIZED, 0, 0 },
    { "WS_ANIMATE", WS_ANIMATE, 0, 0 },
    { "WS_GROUP", WS_GROUP, 0, 0 },
    { "WS_TABSTOP", WS_TABSTOP, 0, 0 },
    { "WS_MULTISELECT", WS_MULTISELECT, 0, 0 },
    { NULL, 0 }
};

_style aFrameStyles[] = {
    { "FS_ICON", FS_ICON },
    { "FS_ACCELTABLE", FS_ACCELTABLE },
    { "FS_SHELLPOSITION", FS_SHELLPOSITION },
    { "FS_TASKLIST", FS_TASKLIST },
    { "FS_NOBYTEALIGN", FS_NOBYTEALIGN },
    { "FS_NOMOVEWITHOWNER", FS_NOMOVEWITHOWNER },
    { "FS_SYSMODAL", FS_SYSMODAL },
    { "FS_DLGBORDER", FS_DLGBORDER },
    { "FS_BORDER", FS_BORDER },
    { "FS_SCREENALIGN", FS_SCREENALIGN },
    { "FS_MOUSEALIGN", FS_MOUSEALIGN },
    { "FS_SIZEBORDER", FS_SIZEBORDER },
    { "FS_AUTOICON", FS_AUTOICON },
    { "FS_STANDARD", FS_STANDARD },
    { NULL, 0 }
};

_style aButtonStyles[] = {
    { "BS_PUSHBUTTON", BS_PUSHBUTTON, 1, 0xf }, // default non serve
//    { "BS_CHECKBOX", BS_CHECKBOX, 1, 0xf },
    { "BS_AUTOCHECKBOX", BS_AUTOCHECKBOX, 1, 0xf },
//    { "BS_RADIOBUTTON", BS_RADIOBUTTON, 1, 0xf },
    { "BS_AUTORADIOBUTTON", BS_AUTORADIOBUTTON, 1, 0xf },
//    { "BS_3STATE", BS_3STATE, 1, 0xf },
    { "BS_AUTO3STATE", BS_AUTO3STATE, 1, 0xf },
    { "BS_USERBUTTON", BS_USERBUTTON, 1, 0xf },
//    { "BS_PRIMARYSTYLES", BS_PRIMARYSTYLES },
//    { "Automatic", 1, 2, 0 },
    { "BS_BITMAP", BS_BITMAP, 0, 0 },
    { "BS_ICON", BS_ICON, 0, 0 },
    { "BS_HELP", BS_HELP, 0, 0 },
    { "BS_SYSCOMMAND", BS_SYSCOMMAND, 0, 0 },
    { "BS_DEFAULT", BS_DEFAULT, 0, 0 },
    { "BS_NOPOINTERFOCUS", BS_NOPOINTERFOCUS, 0, 0 },
    { "BS_NOBORDER", BS_NOBORDER, 0, 0 },
    { "BS_NOCURSORSELECT", BS_NOCURSORSELECT, 0, 0 },
    { "BS_AUTOSIZE", BS_AUTOSIZE, 0, 0 },
    { NULL, 0 }
};

_style aComboBoxStyles[] = {
    { "CBS_SIMPLE", CBS_SIMPLE },
    { "CBS_DROPDOWN", CBS_DROPDOWN },
    { "CBS_DROPDOWNLIST", CBS_DROPDOWNLIST },
    { "CBS_COMPATIBLE", CBS_COMPATIBLE },
    { NULL, 0 }
};

_style aEntryStyles[] = {
    { "ES_LEFT", ES_LEFT },
    { "ES_CENTER", ES_CENTER },
    { "ES_RIGHT", ES_RIGHT },
    { "ES_AUTOSCROLL", ES_AUTOSCROLL },
    { "ES_MARGIN", ES_MARGIN },
    { "ES_AUTOTAB", ES_AUTOTAB },
    { "ES_READONLY", ES_READONLY },
    { "ES_COMMAND", ES_COMMAND },
    { "ES_UNREADABLE", ES_UNREADABLE },
    { "ES_AUTOSIZE", ES_AUTOSIZE },
    { NULL, 0 }
};

_style aListBoxStyles[] = {
    { "LS_MULTIPLESEL", LS_MULTIPLESEL },
    { "LS_OWNERDRAW", LS_OWNERDRAW },
    { "LS_NOADJUSTPOS", LS_NOADJUSTPOS },
    { "LS_HORZSCROLL", LS_HORZSCROLL },
    { "LS_EXTENDEDSEL", LS_EXTENDEDSEL },
    { NULL, 0 }
};

_style aScrollBarStyles[] = {
    { "SBS_HORZ", SBS_HORZ },
    { "SBS_VERT", SBS_VERT },
    { "SBS_THUMBSIZE", SBS_THUMBSIZE },
    { "SBS_AUTOTRACK", SBS_AUTOTRACK },
    { "SBS_AUTOSIZE", SBS_AUTOSIZE },
    { NULL, 0 }
};

_style aStaticStyles[] = {
    { "SS_TEXT", SS_TEXT, 1, 0xf },
    { "SS_GROUPBOX", SS_GROUPBOX, 1, 0xf },
    { "SS_ICON", SS_ICON, 1, 0xf },
    { "SS_BITMAP", SS_BITMAP, 1, 0xf },
    { "SS_FGNDRECT", SS_FGNDRECT, 1, 0xf },
    { "SS_HALFTONERECT", SS_HALFTONERECT, 1, 0xf },
    { "SS_BKGNDRECT", SS_BKGNDRECT, 1, 0xf },
    { "SS_FGNDFRAME", SS_FGNDFRAME, 1, 0xf },
    { "SS_HALFTONEFRAME", SS_HALFTONEFRAME, 1, 0xf },
    { "SS_BKGNDFRAME", SS_BKGNDFRAME, 1, 0xf },
    { "SS_SYSICON", SS_SYSICON, 1, 0xf },
    { "SS_AUTOSIZE", SS_AUTOSIZE, 0, 0 },
    { NULL, 0 }
};

_style aMLEStyles[] = {
    { "MLS_WORDWRAP", MLS_WORDWRAP },
    { "MLS_BORDER", MLS_BORDER },
    { "MLS_VSCROLL", MLS_VSCROLL },
    { "MLS_HSCROLL", MLS_HSCROLL },
    { "MLS_READONLY", MLS_READONLY },
    { "MLS_IGNORETAB", MLS_IGNORETAB },
    { "MLS_DISABLEUNDO", MLS_DISABLEUNDO },
    { NULL, 0 }
};

_style aSPBStyles[] = {
    { "SPBS_ALLCHARACTERS", SPBS_ALLCHARACTERS },
    { "SPBS_NUMERICONLY", SPBS_NUMERICONLY },
    { "SPBS_READONLY", SPBS_READONLY },
    { "SPBS_SERVANT", SPBS_SERVANT },
    { "SPBS_MASTER", SPBS_MASTER },
    { "SPBS_JUSTDEFAULT", SPBS_JUSTDEFAULT },
    { "SPBS_JUSTRIGHT", SPBS_JUSTRIGHT },
    { "SPBS_JUSTLEFT", SPBS_JUSTLEFT },
    { "SPBS_JUSTCENTER", SPBS_JUSTCENTER },
    { "SPBS_NOBORDER", SPBS_NOBORDER },
    { "SPBS_PADWITHZEROS", SPBS_PADWITHZEROS },
    { "SPBS_FASTSPIN", SPBS_FASTSPIN },
    { NULL, 0 }
};

_style aSliderStyles[] = {
//    { "SLS_HORIZONTAL", SLS_HORIZONTAL },
    { "SLS_VERTICAL", SLS_VERTICAL },
//    { "SLS_CENTER", SLS_CENTER },
    { "SLS_BOTTOM", SLS_BOTTOM },
    { "SLS_TOP", SLS_TOP },
    { "SLS_LEFT", SLS_LEFT },
    { "SLS_RIGHT", SLS_RIGHT },
    { "SLS_SNAPTOINCREMENT", SLS_SNAPTOINCREMENT },
    { "SLS_BUTTONSBOTTOM", SLS_BUTTONSBOTTOM },
    { "SLS_BUTTONSTOP", SLS_BUTTONSTOP },
    { "SLS_BUTTONSLEFT", SLS_BUTTONSLEFT },
    { "SLS_BUTTONSRIGHT", SLS_BUTTONSRIGHT },
    { "SLS_OWNERDRAW", SLS_OWNERDRAW },
    { "SLS_READONLY", SLS_READONLY },
    { "SLS_RIBBONSTRIP", SLS_RIBBONSTRIP },
//    { "SLS_HOMEBOTTOM", SLS_HOMEBOTTOM },
    { "SLS_HOMETOP", SLS_HOMETOP },
//    { "SLS_HOMELEFT", SLS_HOMELEFT },
    { "SLS_HOMERIGHT", SLS_HOMERIGHT },
//    { "SLS_PRIMARYSCALE1", SLS_PRIMARYSCALE1 },
//    { "SLS_PRIMARYSCALE2", SLS_PRIMARYSCALE2 },
    { NULL, 0 }
};

_style aBookStyles[] = {
    { "BKS_BACKPAGESBR", BKS_BACKPAGESBR },
    { "BKS_BACKPAGESBL", BKS_BACKPAGESBL },
    { "BKS_BACKPAGESTR", BKS_BACKPAGESTR },
    { "BKS_BACKPAGESTL", BKS_BACKPAGESTL },
    { "BKS_MAJORTABRIGHT", BKS_MAJORTABRIGHT },
    { "BKS_MAJORTABLEFT", BKS_MAJORTABLEFT },
    { "BKS_MAJORTABTOP", BKS_MAJORTABTOP },
    { "BKS_MAJORTABBOTTOM", BKS_MAJORTABBOTTOM },
    { "BKS_SQUARETABS", BKS_SQUARETABS },
    { "BKS_ROUNDEDTABS", BKS_ROUNDEDTABS },
    { "BKS_POLYGONTABS", BKS_POLYGONTABS },
    { "BKS_SOLIDBIND", BKS_SOLIDBIND },
    { "BKS_SPIRALBIND", BKS_SPIRALBIND },
    { "BKS_STATUSTEXTLEFT", BKS_STATUSTEXTLEFT },
    { "BKS_STATUSTEXTRIGHT", BKS_STATUSTEXTRIGHT },
    { "BKS_STATUSTEXTCENTER", BKS_STATUSTEXTCENTER },
    { "BKS_TABTEXTLEFT", BKS_TABTEXTLEFT },
    { "BKS_TABTEXTRIGHT", BKS_TABTEXTRIGHT },
    { "BKS_TABTEXTCENTER", BKS_TABTEXTCENTER },
    { NULL, 0 }
};

_style aValueSetStyles[] = {
    { "VS_BITMAP", VS_BITMAP },
    { "VS_ICON", VS_ICON },
    { "VS_TEXT", VS_TEXT },
    { "VS_RGB", VS_RGB },
    { "VS_COLORINDEX", VS_COLORINDEX },
    { "VS_BORDER", VS_BORDER },
    { "VS_ITEMBORDER", VS_ITEMBORDER },
    { "VS_SCALEBITMAPS", VS_SCALEBITMAPS },
    { "VS_RIGHTTOLEFT", VS_RIGHTTOLEFT },
    { "VS_OWNERDRAW", VS_OWNERDRAW },
    { NULL, 0 }
};

_style aContainerStyles[] = {
    { "CCS_EXTENDSEL", CCS_EXTENDSEL },
    { "CCS_MULTIPLESEL", CCS_MULTIPLESEL },
    { "CCS_SINGLESEL", CCS_SINGLESEL },
    { "CCS_AUTOPOSITION", CCS_AUTOPOSITION },
    { "CCS_VERIFYPOINTERS", CCS_VERIFYPOINTERS },
    { "CCS_READONLY", CCS_READONLY },
    { "CCS_MINIRECORDCORE", CCS_MINIRECORDCORE },
    { NULL, 0 }
};

///////////////////////////////////////////////////////////////////////////////

PMControlMap windowflagsctrlmap[]={
	cmCheckBox(DFLAGS_CB_FCF_TITLEBAR,_windowflags,fl[0])
	cmCheckBox(DFLAGS_CB_FCF_SYSMENU,_windowflags,fl[1])
	cmCheckBox(DFLAGS_CB_FCF_MENU,_windowflags,fl[2])
	cmCheckBox(DFLAGS_CB_FCF_SIZEBORDER,_windowflags,fl[3])
	cmCheckBox(DFLAGS_CB_FCF_MINBUTTON,_windowflags,fl[4])
	cmCheckBox(DFLAGS_CB_FCF_MAXBUTTON,_windowflags,fl[5])
	cmCheckBox(DFLAGS_CB_FCF_VERTSCROLL,_windowflags,fl[6])
	cmCheckBox(DFLAGS_CB_FCF_HORZSCROLL,_windowflags,fl[7])
	cmCheckBox(DFLAGS_CB_FCF_DLGBORDER,_windowflags,fl[8])
	cmCheckBox(DFLAGS_CB_FCF_BORDER,_windowflags,fl[9])
	cmCheckBox(DFLAGS_CB_FCF_SHELLPOSITION,_windowflags,fl[10])
	cmCheckBox(DFLAGS_CB_FCF_TASKLIST,_windowflags,fl[11])
	cmCheckBox(DFLAGS_CB_FCF_NOBYTEALIGN,_windowflags,fl[12])
	cmCheckBox(DFLAGS_CB_FCF_NOMOVEWITHOWNER,_windowflags,fl[13])
	cmCheckBox(DFLAGS_CB_FCF_ICON,_windowflags,fl[14])
	cmCheckBox(DFLAGS_CB_FCF_ACCELTABLE,_windowflags,fl[15])
	cmCheckBox(DFLAGS_CB_FCF_SYSMODAL,_windowflags,fl[16])
	cmCheckBox(DFLAGS_CB_FCF_SCREENALIGN,_windowflags,fl[17])
	cmCheckBox(DFLAGS_CB_FCF_MOUSEALIGN,_windowflags,fl[18])
	cmCheckBox(DFLAGS_CB_FCF_PALETTE_NORMAL,_windowflags,fl[19])
	cmCheckBox(DFLAGS_CB_FCF_PALETTE_HELP,_windowflags,fl[20])
	cmCheckBox(DFLAGS_CB_FCF_PALETTE_POPUPODD,_windowflags,fl[21])
	cmCheckBox(DFLAGS_CB_FCF_PALETTE_POPUPEVEN,_windowflags,fl[22])
	cmCheckBox(DFLAGS_CB_FCF_HIDEBUTTON,_windowflags,fl[23])
	cmCheckBox(DFLAGS_CB_FCF_HIDEMAX,_windowflags,fl[24])
	cmCheckBox(DFLAGS_CB_FCF_AUTOICON,_windowflags,fl[25])
	cmEnd(DFLAGS_CB_FCF_TITLEBAR)
};

PMControlMap CtrlFlagsDialog::ctrlmap[]={
	cmCheckBox(DCF_WS_VISIBLE,CtrlFlagsDialog::_dlgflags,fl[0])
	cmCheckBox(DCF_WS_DISABLED,CtrlFlagsDialog::_dlgflags,fl[1])
	cmCheckBox(DCF_WS_CLIPCHILDREN,CtrlFlagsDialog::_dlgflags,fl[2])
	cmCheckBox(DCF_WS_CLIPSIBLINGS,CtrlFlagsDialog::_dlgflags,fl[3])
	cmCheckBox(DCF_WS_PARENTCLIP,CtrlFlagsDialog::_dlgflags,fl[4])
	cmCheckBox(DCF_WS_SAVEBITS,CtrlFlagsDialog::_dlgflags,fl[5])
	cmCheckBox(DCF_WS_SYNCPAINT,CtrlFlagsDialog::_dlgflags,fl[6])
	cmCheckBox(DCF_WS_MINIMIZED,CtrlFlagsDialog::_dlgflags,fl[7])
	cmCheckBox(DCF_WS_MAXIMIZED,CtrlFlagsDialog::_dlgflags,fl[8])
	cmCheckBox(DCF_WS_ANIMATE,CtrlFlagsDialog::_dlgflags,fl[9])
	cmCheckBox(DCF_WS_GROUP,CtrlFlagsDialog::_dlgflags,fl[10])
	cmCheckBox(DCF_WS_TABSTOP,CtrlFlagsDialog::_dlgflags,fl[11])
	cmCheckBox(DCF_WS_MULTISELECT,CtrlFlagsDialog::_dlgflags,fl[12])
	cmCheckBox(DCF_1,CtrlFlagsDialog::_dlgflags,fl[13])
	cmCheckBox(DCF_2,CtrlFlagsDialog::_dlgflags,fl[14])
	cmCheckBox(DCF_3,CtrlFlagsDialog::_dlgflags,fl[15])
	cmCheckBox(DCF_4,CtrlFlagsDialog::_dlgflags,fl[16])
	cmCheckBox(DCF_5,CtrlFlagsDialog::_dlgflags,fl[17])
	cmCheckBox(DCF_6,CtrlFlagsDialog::_dlgflags,fl[18])
	cmCheckBox(DCF_7,CtrlFlagsDialog::_dlgflags,fl[19])
	cmCheckBox(DCF_8,CtrlFlagsDialog::_dlgflags,fl[20])
	cmCheckBox(DCF_9,CtrlFlagsDialog::_dlgflags,fl[21])
	cmCheckBox(DCF_A,CtrlFlagsDialog::_dlgflags,fl[22])
	cmCheckBox(DCF_B,CtrlFlagsDialog::_dlgflags,fl[23])
	cmCheckBox(DCF_C,CtrlFlagsDialog::_dlgflags,fl[24])
	cmCheckBox(DCF_D,CtrlFlagsDialog::_dlgflags,fl[25])
	cmCheckBox(DCF_E,CtrlFlagsDialog::_dlgflags,fl[26])
	cmCheckBox(DCF_F,CtrlFlagsDialog::_dlgflags,fl[27])
	cmEnd(DCF_WS_VISIBLE)
};

PMControlMap CtrlListDialog::ctrlmap[]={
	cmListBox(DCTRLLIST_LB_CTRLLIST,CtrlListDialog::_dlginfo,selctrl)
	cmEnd(DID_OK)
};

