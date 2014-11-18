/* 


	dlgedit.h (emx+gcc) 

	1994,95 Giovanni Iachello
	This is freeware software. You can use or modify it as you wish,
	provided that the part of code that I wrote remains freeware.
	Freeware means that the source code must be available on request 
	to anyone.
	You must also include this notice in all files derived from this
	file.


*/
#ifndef _DLGEDIT_H_
#define _DLGEDIT_H_


#define PMPTR_1         10
#define IDM_POPUPMENU	40
#define IDM_PU_PROP		41
#define IDM_PU_FLAGS	42
#define IDM_PU_DELETE	43


#define ID_DLGEDIT 		1

#define IDM_NEWCTRL     10
#define IDM_STATICTEXT  11
#define IDM_ENTRYFIELD  12
#define IDM_LISTBOX     13
#define IDM_COMBOBOX    14
#define IDM_BUTTON      15
#define IDM_SPINBUTTON  16
#define IDM_SLIDER      17
#define IDM_VALUESET 	18
#define IDM_CHECKBOX    19
#define IDM_RADIOBUTTON 20
#define IDM_3STATE  	21
#define IDM_GROUPBOX	22

#define IDM_PREF       	30
#define IDM_FONTS       31
#define IDM_SIZE        32
#define IDM_FLAGS       34
#define IDM_TEXT        33
#define IDM_CTRLLIST	35

#define IDM_COMPILE 	50

#define DLG_SIZE		2
#define DSIZE_EF_SX		200
#define DSIZE_EF_SY		201

#define DLG_TEXT		6
#define DTEXT_EF_LB		600
#define DTEXT_EF_TI		601

#define DLG_FLAGS					3
#define DFLAGS_CB_FCF_TITLEBAR		300
#define DFLAGS_CB_FCF_SYSMENU		301
#define DFLAGS_CB_FCF_MENU			302	
#define DFLAGS_CB_FCF_SIZEBORDER	303
#define DFLAGS_CB_FCF_MINBUTTON		304
#define DFLAGS_CB_FCF_MAXBUTTON		305
#define DFLAGS_CB_FCF_VERTSCROLL	306	
#define DFLAGS_CB_FCF_HORZSCROLL	307	
#define DFLAGS_CB_FCF_DLGBORDER		308
#define DFLAGS_CB_FCF_BORDER		309
#define DFLAGS_CB_FCF_SHELLPOSITION	310
#define DFLAGS_CB_FCF_TASKLIST		311
#define DFLAGS_CB_FCF_NOBYTEALIGN	312	
#define DFLAGS_CB_FCF_NOMOVEWITHOWNER 	313	
#define DFLAGS_CB_FCF_ICON			314
#define DFLAGS_CB_FCF_ACCELTABLE	315	
#define DFLAGS_CB_FCF_SYSMODAL		316
#define DFLAGS_CB_FCF_SCREENALIGN	317	
#define DFLAGS_CB_FCF_MOUSEALIGN	318	
#define DFLAGS_CB_FCF_PALETTE_NORMAL 319	
#define DFLAGS_CB_FCF_PALETTE_HELP	320
#define DFLAGS_CB_FCF_PALETTE_POPUPODD	321
#define DFLAGS_CB_FCF_PALETTE_POPUPEVEN	322
#define DFLAGS_CB_FCF_HIDEBUTTON	323
#define DFLAGS_CB_FCF_HIDEMAX		324
#define DFLAGS_CB_FCF_AUTOICON		325

#define DLG_CTRLPROP	4
#define DCP_EF_X		400
#define DCP_EF_Y		401
#define DCP_EF_CX		402
#define DCP_EF_CY		403
#define DCP_EF_TEXT		404
#define DCP_EF_LABEL	405

#define DLG_CTRLFLAGS				5
#define DCF_WS_VISIBLE				500
#define DCF_WS_DISABLED				501
#define DCF_WS_CLIPCHILDREN			502	
#define DCF_WS_CLIPSIBLINGS      	503
#define DCF_WS_PARENTCLIP      		504
#define DCF_WS_SAVEBITS        		505
#define DCF_WS_SYNCPAINT        	506	
#define DCF_WS_MINIMIZED        	507	
#define DCF_WS_MAXIMIZED       		508
#define DCF_WS_ANIMATE      		509
#define DCF_WS_GROUP               	510
#define DCF_WS_TABSTOP        		511
#define DCF_WS_MULTISELECT       	512	
#define DCF_1 	513	
#define DCF_2	514
#define DCF_3	515	
#define DCF_4	516
#define DCF_5	517	
#define DCF_6	518	
#define DCF_7 	519	
#define DCF_8	520
#define DCF_9	521
#define DCF_A	522
#define DCF_B	523
#define DCF_C	524
#define DCF_D	525
#define DCF_E	526
#define DCF_F	527


#define DLG_CTRLLIST 7
#define DCTRLLIST_LB_CTRLLIST 700
#define DCTRLLIST_PB_DELETE 701
#define DCTRLLIST_PB_FLAGS  702
#define DCTRLLIST_PB_PROP 703

#ifndef RC_INVOKED

#include "pmwin.h"
#include "pmdlg.h"
#include "dlgdata.h"

////////////////////////////////////////////////////////////////////////////

#define WM_NEWCTRL ( WM_USER + 0 )			  // mandato da DlgEdit a WorkWindow per creare un nuovo controllo
#define WM_CTRLMENU ( WM_USER + 1 )			  // mandato a WorkWindow per tirare fuori il menu' popup
#define WM_REFRESH ( WM_USER + 2 )			  // mandato da DlgEdit a CtrlListDialog per comandare di rifare la lista dei controlli
#define WM_MODIFIED ( WM_USER + 3 )			  // mandato da Workwindow a DlgEdit per informare che il dialog e' stato modificato
#define WM_CLOSECTRLLIST ( WM_USER + 4 )        // mandato da CtrlList a DlgEdit per informare che ctrllist e' stata chiusa

////////////////////////////////////////////////////////////////////////////

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

// real 2 dialog , servono numeri magici per mantenere il ratio!
#define r2dx(a) ((a)*4*32/aveCharX/25)
#define r2dy(a) ((a)*8*59/aveCharY/75)

// dialog 2 real 
#define d2rx(a) ((a)*25*aveCharX/4/32)
#define d2ry(a) ((a)*75*aveCharY/8/59)

extern PMApp* App;

extern LONG aveCharX,aveCharY;

/////////////////////////////////////////////////////////////////////////////
// strutture che servono anche a dlgcomr.cpp:

class ControlWin : public PMSubclassWin {
	PMWin* owner;
public:
	ControlWin(PMWin* iowner, PCSZ pszClass, PCSZ pszName,
	    ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy, 
    	HWND hwndInsertBehind, ULONG id, PVOID pCtlData=NULL, PVOID pPresParams=NULL) ;
	BOOL other(PMEvent &event);	
	BOOL destroyWin() ;
};


struct _dlgcontrol {
	CHAR text[80];
	ULONG flags;
	ULONG x,y,cx,cy;
	CHAR idc[80];
	ULONG idl;
	int classidx;
	ControlWin *win;
	_dlgcontrol *next;
};

struct _dlginfo {
	_dlginfo() {
		sx=100;
		sy=100;
		title[0]='\0';
		label[0]='\0';
		for (int i=0; i<26; i++) fl[i]=0;
		fl[8]=1; // DLGBORDER
		dlgctrl=NULL;
	}
	int sx;
	int sy;
	int fl[26];
	char title[100];
	char label[100];
	ULONG flags;
	_dlgcontrol* dlgctrl;
	void makeflags() {
		flags=0L;
		for (int i=0; i<26; i++) if (fl[i]) flags|=winflvalues[i];
	}
} ;

/////////////////////////////////////////////////////////////////////////////

extern BOOL compile(const char* file,_dlginfo*);
extern BOOL savedl(const char* file,_dlginfo*);
extern BOOL loaddl(const char* file,_dlginfo*);

/////////////////////////////////////////////////////////////////////////////

class CtrlFlagsDialog : public PMModalDialog {
	struct _dlgflags {
		int fl[32];
	} dlgflags;
	static PMControlMap ctrlmap[];
	_dlgcontrol *dc;
public:
	CtrlFlagsDialog(HWND hwnd,_dlgcontrol *idc) : PMModalDialog(HWND_DESKTOP,hwnd,DLG_CTRLFLAGS,ctrlmap,&dlgflags) 
	{ 
		dc=idc;
	}
	BOOL createWin();
	BOOL initdlg();

};


class WorkWindow : public PMWin {
	_dlginfo* dlginfo;
	PMWin* editor;
	PMPoint start,end;        // per intercettare il posizionamento
	BOOL mouseCaptured;
	int newControl;
	_dlgcontrol* edctrl;
	PMPointer *ptr1; // selezione
	PMPopupMenu *popup;    // popupmenu
public:
	friend class CtrlListDialog;
	WorkWindow(HAB ab,_dlginfo* idlginfo,PMWin* ieditor);
	~WorkWindow();
	BOOL createWin();
	BOOL paint();
	void drawOutline();
	void addControl();
	BOOL mouse(PMEvent &event);
	BOOL other(PMEvent& evt) ;
	BOOL command(USHORT id,USHORT cmddev);
};

class CtrlListDialog : public PMModelessDialog {
	WorkWindow *ww;
	PMWin* editor;
	static PMControlMap ctrlmap[];
	struct _dlginfo {
		int selctrl;
	} dlginfo;	
public:
	CtrlListDialog(HWND parent,HWND owner,WorkWindow *iww,PMWin* ieditor);
	BOOL initdlg() ;
	BOOL command(USHORT id,USHORT cmddev) ;
	BOOL other(PMEvent& evt) ;
};

struct _windowflags {
	int fl[26];
};

extern PMControlMap windowflagsctrlmap[];

#endif

#endif

