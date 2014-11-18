/* 


	dlguser.cpp (emx+gcc) 

	1995 Giovanni Iachello
	This is freeware software. You can use or modify it as you wish,
	provided that the part of code that I wrote remains freeware.
	Freeware means that the source code must be available on request 
	to anyone.
	You must also include this notice in all files derived from this
	file.


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INCL_WIN
#include "pmwin.h"
#include "pmdlg.h"
#include "pmgpi.h"
#include "pmstdres.h"
#include "dlgedit.h"
#include "dlgdata.h"

/////////////////////////////////////////////////////////////////////////////

ControlWin::ControlWin(PMWin* iowner, PCSZ pszClass, PCSZ pszName,
    ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy, 
   	HWND hwndInsertBehind, ULONG id, PVOID pCtlData, PVOID pPresParams) :

	PMSubclassWin(iowner->getHwnd(),pszClass,pszName,flStyle,x,y,cx,cy,
		iowner->getHwnd(),hwndInsertBehind,id,pCtlData,pPresParams) 
{
	owner=iowner;
}

BOOL ControlWin::destroyWin() 
{
	return WinDestroyWindow(hwnd);
}

BOOL ControlWin::other(PMEvent &event)
{
	switch (event.msg) {
		case WM_CONTEXTMENU:
			owner->postMsg(WM_CTRLMENU,(MPARAM)this,event.mp1);
			event.ret=(MRESULT)TRUE;
			return TRUE;
		default:
			return FALSE;		
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////


BOOL CtrlFlagsDialog::createWin()
{
	int i;
	_style *p;
	p=aWindowStyles; // ricava dalla struttura i flags
	i=0;
	while (p->label!=NULL) {
		if (dc->flags&p->value) dlgflags.fl[i]=1; 
		else dlgflags.fl[i]=0;
		p++;
		i++;
	}
	p=apsStyles[dc->classidx]; // ricava dalla struttura i flags
	i=13;
	while (p->label!=NULL) {
		if (p->type) {
			if ((dc->flags&p->bits)==p->value) dlgflags.fl[i]=1; 
			else dlgflags.fl[i]=0;
		} else {
			if (dc->flags&p->value) dlgflags.fl[i]=1; 
			else dlgflags.fl[i]=0;
		}
		p++;
		i++;
	}
	int ret=PMModalDialog::createWin();
	if (ret) {
		dc->flags=0;
		p=aWindowStyles; // ricava dalla struttura i flags
		i=0;
		while (p->label!=NULL) {
			if (dlgflags.fl[i])
				dc->flags|=p->value;				
			p++;
			i++;
		}
		p=apsStyles[dc->classidx]; // ricava dalla struttura i flags
		i=13;
		while (p->label!=NULL) {
			if (p->type) {
				if (dlgflags.fl[i]) 
					dc->flags=(dc->flags&(~p->bits))|p->value;
			} else {
				if (dlgflags.fl[i])
					dc->flags|=p->value;
			}
			p++;
			i++;
		}
	}								
	return ret;
}

BOOL CtrlFlagsDialog::initdlg()
{
	_style *p=apsStyles[dc->classidx]; // scrivi nei checkbox i nomi dei flags
	int cbid=DCF_1;
	while (p->label!=NULL) {
		PMControl *c=controlFromID(cbid);
		assert(c);
		c->setWindowText(p->label);
		cbid++;
		p++;
	}
	while (cbid<=DCF_F) {
		controlFromID(cbid)->setPos(getHwnd(),0,0,0,0,SWP_HIDE );
		cbid++;
	}
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////

CtrlListDialog::CtrlListDialog(HWND parent,HWND owner,WorkWindow *iww,PMWin* ieditor) :
	PMModelessDialog(parent,owner,DLG_CTRLLIST,ctrlmap,&dlginfo) 
{
	ww=iww;
	editor=ieditor;
}


BOOL CtrlListDialog::initdlg() 
{
	char buf[128];
	PMListBox* lb=(PMListBox*)controlFromID(DCTRLLIST_LB_CTRLLIST);
	if (ww) {
		_dlgcontrol* p=ww->dlginfo->dlgctrl;
	
		while (p!=NULL) {
			strcpy(buf,apchClassNames[p->classidx]);
			strcat(buf," - ");
			strcat(buf,p->idc);
			lb->insertItem(LIT_END,buf);
			p=p->next;
		}
	}
	
	return TRUE;
}		

BOOL CtrlListDialog::command(USHORT id,USHORT cmddev) 
{
	// find pointer to control information structure
	switch (id) {
	case DCTRLLIST_PB_PROP:
	case DCTRLLIST_PB_DELETE:
	case DCTRLLIST_PB_FLAGS:
		_dlgcontrol* p=ww->dlginfo->dlgctrl;
		PMListBox* lb=(PMListBox*)controlFromID(DCTRLLIST_LB_CTRLLIST);
		int ctrlnum=lb->querySelection();
		if (ctrlnum<0) return PMModalDialog::command(id,cmddev); // non era selezionato nessun controllo
		while (p!=NULL && ctrlnum>0) {
			p=p->next;
			ctrlnum--;
		}								  
		ww->edctrl=p;
	case DID_OK:
		editor->postMsg(WM_CLOSECTRLLIST);
	}
	// le workwindow do the work!!
	switch (id) {
	case DCTRLLIST_PB_PROP:
		ww->command(IDM_PU_PROP,cmddev);
		break;
	case DCTRLLIST_PB_DELETE:
		ww->command(IDM_PU_DELETE,cmddev);
		break;
	case DCTRLLIST_PB_FLAGS:
		ww->command(IDM_PU_FLAGS,cmddev);
		break;
	}
	// refresh the control listbox
	switch (id) {
	case DCTRLLIST_PB_PROP:
	case DCTRLLIST_PB_DELETE:
		PMListBox* lb=(PMListBox*)controlFromID(DCTRLLIST_LB_CTRLLIST);
		assert(lb);
		lb->deleteAll(); // delete all items
		initdlg();
	}
	return PMModalDialog::command(id,cmddev);
}		 

BOOL CtrlListDialog::other(PMEvent& evt) 
{
	if (evt.msg == WM_REFRESH) {
		PMListBox* lb=(PMListBox*)controlFromID(DCTRLLIST_LB_CTRLLIST);
		assert(lb);
		lb->deleteAll(); // delete all items
		initdlg();
	}
	return FALSE;
}

