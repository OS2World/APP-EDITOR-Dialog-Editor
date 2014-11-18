/* 


	dlgedit.cpp (emx+gcc) 

	1994,95 Giovanni Iachello
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
#define INCL_DOSFILEMGR
#include "pmwin.h"
#include "pmdlg.h"
#include "pmgpi.h"
#include "pmstdres.h"
#include "dlgedit.h"
#include "dlgdata.h"

PMApp* App;

LONG aveCharX,aveCharY;



/////////////////////////////////////////////////////////////////////////////


WorkWindow::WorkWindow(HAB ab,_dlginfo* idlginfo,PMWin* ieditor) : PMWin("temporaryDLGEDITworkwindow",ab) {
	dlginfo=idlginfo;
	editor=ieditor;
	
	createArgs->hwndParent=editor->getHwnd();
	dlginfo->makeflags();
    createArgs->flCreateFlags=dlginfo->flags | FCF_SHELLPOSITION;
    createArgs->pszTitle=dlginfo->title;

	mouseCaptured=FALSE;
	ptr1= new PMPointer(PMPTR_1);
	newControl=0;
}

WorkWindow::~WorkWindow() 
{
	_dlgcontrol* p=dlginfo->dlgctrl;
	while (p!=NULL) { // elimina i controlli
		p->win->destroyWin();
		p=p->next;
	}
	delete popup;
	delete ptr1;
}

BOOL WorkWindow::createWin()
{
	PMWin::createWin();
	setFramePos(editor->getHwnd(),10,10,d2rx(dlginfo->sx),d2ry(dlginfo->sy),SWP_SIZE|SWP_MOVE);

	_dlgcontrol* p=dlginfo->dlgctrl;
	while (p!=NULL) { // ricrea le finestre
		p->win=new ControlWin(this,apszClasses[p->classidx],
				p->text, p->flags, d2rx(p->x), d2ry(p->y), d2rx(p->cx), d2ry(p->cy),
					HWND_BOTTOM, p->idl);
		p->win->createWin();
		p=p->next;
	}
	popup = new PMPopupMenu(this,IDM_POPUPMENU);
	return hwnd;
}

BOOL WorkWindow::paint()
{
	PMWindowPresSpace ps(this);
	PMRect rcl;
	rcl=this;
	ps.fillRect(&rcl,CLR_PALEGRAY);
	return TRUE;
}

void WorkWindow::drawOutline()
{
	PMMicroCachedPresSpace ps(this);
	ps.setMix(FM_INVERT);
	ps.move(&start);
	ps.box(DRO_OUTLINE,&end);
}

void WorkWindow::addControl()
{
	_dlgcontrol* p; 
	p=new _dlgcontrol;
	p->text[0]=0;
	p->x=r2dx(min(start.x,end.x));
	p->y=r2dy(min(start.y,end.y));
	p->cx=r2dx(abs(end.x-start.x));
	p->cy=r2dy(abs(end.y-start.y));
	p->idc[0]=0;
	if (dlginfo->dlgctrl) p->idl=dlginfo->dlgctrl->idl+1; else p->idl=0;
	p->classidx=menu2classindex[newControl];
	p->flags=WS_VISIBLE|lClassesDefStyles[p->classidx];
		
	p->win=new ControlWin(this,apszClasses[p->classidx],
				p->text, p->flags, d2rx(p->x), d2ry(p->y), d2rx(p->cx), d2ry(p->cy),
				HWND_BOTTOM, p->idl);
	p->win->createWin();

	p->next=dlginfo->dlgctrl;
	dlginfo->dlgctrl=p;
	editor->postMsg(WM_MODIFIED);			
}

BOOL WorkWindow::mouse(PMEvent &event)
{
	if (newControl)
	switch (event.msg) {
		case WM_BUTTON1DOWN:
		    TRACKINFO track;
 
		    track.cxBorder = 1;
		    track.cyBorder = 1;
		    track.cxGrid = 1;
		    track.cyGrid = 1;   
	    	track.cxKeyboard = 4;
	    	track.cyKeyboard = 4; 
 
		    WinSetRect(ab, &track.rclTrack, event.mousemsg->x,event.mousemsg->y,event.mousemsg->x,event.mousemsg->y);   /* starting point */
 
		    WinSetRect(ab, &track.rclBoundary, 0, 0, 640, 480); /* bounding rectangle */
 
		    track.ptlMinTrackSize.x = 2;
		    track.ptlMinTrackSize.y = 2;  
		    track.ptlMaxTrackSize.x = 640;
		    track.ptlMaxTrackSize.y = 480; 
 
		    track.fs = TF_RIGHT | TF_BOTTOM;
 
		    if (!WinTrackRect(hwnd, NULLHANDLE, &track) ) {
				ptr1->reset();
				return(FALSE);
		    }
			ptr1->reset();
			start.PMPoint(track.rclTrack.xLeft,track.rclTrack.yBottom);
			end.PMPoint(track.rclTrack.xRight,track.rclTrack.yTop);
			addControl();
			newControl=0;
		case WM_MOUSEMOVE:
			ptr1->set();
			event.ret=(MRESULT)TRUE;
			return TRUE;
	}
	return FALSE;
}	

BOOL WorkWindow::other(PMEvent& evt) 
{
	switch (evt.msg) {
		case WM_NEWCTRL:
			ptr1->set();
			newControl=(int)evt.mp1;
			return TRUE;
		case WM_CTRLMENU: {
			_dlgcontrol* p=dlginfo->dlgctrl;
			while (p!=NULL) {
				if (p->win==(ControlWin*)evt.mp1) {
					PMPoint pt(SHORT1FROMMP(evt.mp2)+d2rx(p->x),SHORT2FROMMP(evt.mp2)+d2ry(p->y));
					edctrl=p;
					popup->popup(pt,IDM_PU_PROP);
					break;
				}
				p=p->next;
			}				
			return TRUE;
		}
		default:
			return FALSE;
	}
	return FALSE;
}

BOOL WorkWindow::command(USHORT id,USHORT cmddev)
{
	switch (id) {
		case IDM_PU_DELETE: {
			_dlgcontrol *p=dlginfo->dlgctrl,**pp=&dlginfo->dlgctrl;
			while (p!=NULL) {
				if (p==edctrl) {
					_dlgcontrol *old=p;
					*pp=p->next;
					old->win->destroyWin();
					delete old;
					break;
				}
				p=p->next;
				pp=&((*pp)->next);
			}				
			editor->postMsg(WM_MODIFIED);			
			invalidate(TRUE);
			return TRUE;
		}
		case IDM_PU_FLAGS: {
			CtrlFlagsDialog cfd(hwnd,edctrl);
			cfd.createWin();
			edctrl->win->destroyWin();
			edctrl->win=new ControlWin(this,apszClasses[edctrl->classidx],
				edctrl->text, edctrl->flags, d2rx(edctrl->x), d2ry(edctrl->y), d2rx(edctrl->cx), d2ry(edctrl->cy),
				HWND_BOTTOM, edctrl->idl);
			edctrl->win->createWin();
			editor->postMsg(WM_MODIFIED);			
			invalidate(TRUE);
			return TRUE;
		}
		case IDM_PU_PROP: {
			struct _cp {
				char cx[10];
				char cy[10];
				char x[10];
				char y[10];
				char text[80];
				char label[80];
			} cp;
			static PMControlMap ctrlmap[]={
				cmEntryField(DCP_EF_CX,_cp,cx)
				cmEntryField(DCP_EF_CY,_cp,cy)
				cmEntryField(DCP_EF_X,_cp,x)
				cmEntryField(DCP_EF_Y,_cp,y)
				cmEntryField(DCP_EF_TEXT,_cp,text)
				cmEntryField(DCP_EF_LABEL,_cp,label)
				cmEnd(DCP_EF_X)
			};
			sprintf(cp.cx,"%ld",edctrl->cx);
			sprintf(cp.cy,"%ld",edctrl->cy);
			sprintf(cp.x,"%ld",edctrl->x);
			sprintf(cp.y,"%ld",edctrl->y);
			strcpy(cp.text,edctrl->text);
			strcpy(cp.label,edctrl->idc);
			PMModalDialog propdlg(HWND_DESKTOP,hwnd,DLG_CTRLPROP,ctrlmap,&cp);
			int ret=propdlg.createWin();
			if (ret) {
				edctrl->x=atoi(cp.x);
				edctrl->y=atoi(cp.y);
				edctrl->cx=atoi(cp.cx);
				edctrl->cy=atoi(cp.cy);
				strcpy(edctrl->text,cp.text);
				strcpy(edctrl->idc,cp.label);
				edctrl->win->setWindowText(cp.text);
				edctrl->win->setPos(getHwnd(), d2rx(edctrl->x), d2ry(edctrl->y), d2rx(edctrl->cx), d2ry(edctrl->cy),SWP_SIZE|SWP_MOVE );
				editor->postMsg(WM_MODIFIED);			
			}
			return TRUE;
		}
	}
	return PMWin::command(id,cmddev);
}

/////////////////////////////////////////////////////////////////////////////


class DlgEditor : public PMMainWin {
	_dlginfo dlginfo;
	WorkWindow *ww;
	char* tempfile;
	SHORT activatemenus;
	CtrlListDialog *ctrllistdlg;
protected:
//	void getcurdir(char* buf)
//	{
//		ULONG drive,pathlen=CCHMAXPATH-8;
//		DosQueryCurrentDisk(&drive,NULL);
//		buf[0]='A'+drive;
//		buf[1]=':';	buf[2]='\\';
//		DosQueryCurrentDir(drive,buf+3,&pathlen);
//	}
public:
	DlgEditor(HAB ab,char* file) : PMMainWin("dialogeditor",ab) {
		createArgs->flCreateFlags|=FCF_MENU|FCF_ICON|FCF_ACCELTABLE;
		createArgs->idResources=ID_DLGEDIT;
		createArgs->pszTitle="Dialog Editor - (none)";
		caption="Dialog Editor";
//		fnFilter=new char[CCHMAXPATH];
//		getcurdir(fnFilter);
//		strcat(fnFilter,"*.DL");
//		ErrBox(fnFilter);
		fnFilter="*.DL";
		fileFlags=PMMWFF_UNTITLED;
		flCaption="Open Dialog File";
		fsCaption="Save Dialog File";
		dlginfo._dlginfo();
		ww=NULL;
		tempfile=file;
		activatemenus=FALSE;
		ctrllistdlg=NULL;
	};
	BOOL createWin() 
	{
		PMMainWin::createWin();
		return TRUE;
	}	
	void setmenus(PMMenu* menu,BOOL st)
	{
		menu->enableItem(IDM_SIZE,st);
		menu->enableItem(IDM_TEXT,st);
		menu->enableItem(IDM_FLAGS,st);
		menu->enableItem(IDM_CTRLLIST,st);
		menu->enableItem(IDM_STATICTEXT,st);
		menu->enableItem(IDM_ENTRYFIELD,st);
		menu->enableItem(IDM_LISTBOX,st);
		menu->enableItem(IDM_COMBOBOX,st);
		menu->enableItem(IDM_BUTTON,st);
		menu->enableItem(IDM_SPINBUTTON,st);
		menu->enableItem(IDM_SLIDER,st);
		menu->enableItem(IDM_VALUESET,st);
		menu->enableItem(IDM_CHECKBOX,st);
		menu->enableItem(IDM_RADIOBUTTON,st);
		menu->enableItem(IDM_3STATE,st);
		menu->enableItem(IDM_GROUPBOX,st);
	}
	BOOL initmenu(SHORT id,PMMenu* menu)
	{
		if (id==IDM_PREF || id==IDM_NEWCTRL) {
			setmenus(menu,activatemenus);
		}
		if (ctrllistdlg) menu->enableItem(IDM_CTRLLIST,FALSE);
		return TRUE;
	}
	BOOL destroyWin()
	{
		if (ctrllistdlg) ctrllistdlg->destroyWin();
		if (ww) ww->destroyWin();
		return PMMainWin::destroyWin();
	}							 
	~DlgEditor() {
//		delete fnFilter;
	}
	BOOL paint(PMPresSpace& ps)
	{
		PMRect rcl;
		rcl=this;
		ps.fillRect(&rcl,CLR_PALEGRAY);
		if (!aveCharX) {
			PMDeviceContext dc(ab,ps.queryDevice());
			LONG d,e;
			dc.queryCaps(CAPS_GRAPHICS_CHAR_WIDTH,1,&d);
			dc.queryCaps(CAPS_GRAPHICS_CHAR_HEIGHT,1,&e);
			dc.queryCaps(CAPS_CHAR_WIDTH,1,&aveCharX);
			dc.queryCaps(CAPS_CHAR_HEIGHT,1,&aveCharY);
			SIZEF cb;
			ps.queryCharBox(&cb);
//			msgBox("Result","%ld %ld %ld %ld %f %f",aveCharX,aveCharY,d,e,((float)cb.cx) / 0x10000,((float)cb.cy) / 0x10000);
		}
		if (tempfile)
			if (fileOpen(tempfile)) {
				strcpy(filename,tempfile);
				fileFlags=PMMWFF_FILE;
				setTitleCaption();
				tempfile=NULL;
			}
		if (ww) ww->setFramePos(getHwnd(),10,10,d2rx(dlginfo.sx),d2ry(dlginfo.sy),SWP_SIZE|SWP_MOVE|SWP_SHOW|SWP_ACTIVATE);
		return TRUE;
	}
	BOOL mouse(PMEvent& event)
	{
		return FALSE;
	}
	BOOL command(USHORT id,USHORT cmddev)
	{
		switch (id) {
			case IDM_STATICTEXT: 
			case IDM_LISTBOX: 
			case IDM_ENTRYFIELD: 
			case IDM_COMBOBOX:
			case IDM_BUTTON:
			case IDM_SPINBUTTON:
			case IDM_SLIDER:
			case IDM_VALUESET:
			case IDM_CHECKBOX:
			case IDM_RADIOBUTTON:
			case IDM_3STATE:
			case IDM_GROUPBOX:
				if (ww) ww->postMsg(WM_NEWCTRL,(MPARAM)id);
				setModified(TRUE);
				return TRUE;
    	    case IDM_COMPILE:	
				compile(filename,&dlginfo);
    	    	return TRUE;
    	    case IDM_FONTS:	{
/*				FONTMETRICS fm;
				char buf[200];
				PMWindowPresSpace ps(this);
				ps.queryFontMetrics(&fm);
				PMFontDialog fd(HWND_DESKTOP,hwnd, &fm,"Titolo","Preview");
				int ret=fd.createWin();
				assert(ret);
				FONTDLG fi=fd;
				sprintf(buf,"%d %s %ld %hd %hd %hd %hd",ret,fi.pszFamilyname,fi.fxPointSize,fi.usWeight,fi.usWidth,fi.x,fi.y);
				msgBox("Result",buf); */
				return TRUE;
			}
    	    case IDM_SIZE:	{
				struct _dlgsize {
					char sx[10];
					char sy[10];
				} dlgsize;
				static PMControlMap ctrlmap[]={
					cmEntryField(DSIZE_EF_SX,_dlgsize,sx)
					cmEntryField(DSIZE_EF_SY,_dlgsize,sy)
					cmEnd(DSIZE_EF_SX)
				};
				sprintf(dlgsize.sx,"%d",dlginfo.sx);
				sprintf(dlgsize.sy,"%d",dlginfo.sy);
				PMModalDialog sizedlg(HWND_DESKTOP,hwnd,DLG_SIZE,ctrlmap,&dlgsize);
				int ret=sizedlg.createWin();
				if (ret) {
					dlginfo.sx=atoi(dlgsize.sx);
					dlginfo.sy=atoi(dlgsize.sy);
					if (ww) ww->setFramePos(getHwnd(),10,10,d2rx(dlginfo.sx),d2ry(dlginfo.sy),SWP_SIZE|SWP_MOVE);
					else {
						ww=new WorkWindow(ab,&dlginfo,this);
						ww->createWin();
					}
					setModified(TRUE);
				}
				return TRUE;
			}
    	    case IDM_TEXT:	{
				struct _dlgtext {
					char lb[100];
					char ti[100];
				} dlgtext;
				static PMControlMap ctrlmap[]={
					cmEntryField(DTEXT_EF_LB,_dlgtext,lb)
					cmEntryField(DTEXT_EF_TI,_dlgtext,ti)
					cmEnd(DTEXT_EF_TI)
				};
				strcpy(dlgtext.ti,dlginfo.title);
				strcpy(dlgtext.lb,dlginfo.label);
				PMModalDialog textdlg(HWND_DESKTOP,hwnd,DLG_TEXT,ctrlmap,&dlgtext);
				int ret=textdlg.createWin();
				if (ret) {
					strcpy(dlginfo.title,dlgtext.ti);
					strcpy(dlginfo.label,dlgtext.lb);
					if (ww) ww->setFrameWindowText(dlginfo.title);
					else {
						ww=new WorkWindow(ab,&dlginfo,this);
						ww->createWin();
					}
					setModified(TRUE);
				}
				return TRUE;
			}
    	    case IDM_FLAGS:	{
				int i;
				_windowflags windowflags;
				for (i=0; i<26; i++) windowflags.fl[i]=dlginfo.fl[i];
				PMModalDialog flagsdlg(HWND_DESKTOP,hwnd,DLG_FLAGS,windowflagsctrlmap,&windowflags);
				int ret=flagsdlg.createWin();
				if (ret) {
					for (i=0; i<26; i++) dlginfo.fl[i]=windowflags.fl[i];
					if (ww) ww->destroyWin();
					ww=new WorkWindow(ab,&dlginfo,this);
					ww->createWin();
					setModified(TRUE);
				}
				return TRUE;
			}
    	    case IDM_CTRLLIST: {
				if (!ctrllistdlg)
					ctrllistdlg=new CtrlListDialog(HWND_DESKTOP,hwnd,ww,this);

				ctrllistdlg->createWin();
				return TRUE;
			}
		}		
		return PMMainWin::command(id,cmddev);
	}
	BOOL fileNew() {
		if (ww)	ww->destroyWin();
		
		_dlgcontrol* p=dlginfo.dlgctrl;
		while (p!=NULL) { // cancella i controlli
			_dlgcontrol* old=p;
			p=p->next;
			delete old;			
		}
		dlginfo._dlginfo();
		ww=new WorkWindow(ab,&dlginfo,this);
		ww->createWin();
		setFrameWindowText("Dialog Editor - (untitled)");
		activatemenus=TRUE;
		return TRUE;
	}
	BOOL fileOpen(PCSZ filename) {
		if (ww)	ww->destroyWin();
		
		_dlgcontrol* p=dlginfo.dlgctrl;
		while (p!=NULL) { // cancella i controlli
			_dlgcontrol* old=p;
			p=p->next;
			delete old;			
		}
		dlginfo._dlginfo();

		if (loaddl(filename,&dlginfo)) {
			ww=new WorkWindow(ab,&dlginfo,this);
			ww->createWin();
			activatemenus=TRUE;
			return TRUE;
		}

		ErrBox("Error Loading file %s",filename);

		return FALSE;
	};
	BOOL fileSave(PCSZ filename) {
		savedl(filename,&dlginfo);
		invalidate(TRUE);
		return TRUE;
	};
	BOOL other(PMEvent& evt) 
	{
		if (evt.msg==WM_MODIFIED) {
			if (ctrllistdlg) ctrllistdlg->postMsg(WM_REFRESH);			
			setModified(TRUE);
			return TRUE;
		}
		if (evt.msg==WM_CLOSECTRLLIST) {
			ctrllistdlg=NULL;
			return TRUE;
		}
		return FALSE;
	}
};


int main (int argc,char* argv[])
{
	char* file=NULL;
	if (argc>1) {
		// ci sono switch
		if (argv[1][0]=='-')
			if (argv[1][1]=='c') { 
				compile(argv[2],NULL);
				return 0;
			}
		file=argv[1];
	}

	PMAnchorBlock ab;
	PMMessageQueue mq;
	ab.init();
	mq.create(ab);
	
	App=new PMApp(ab,mq,argc,argv);

	DlgEditor * de=new DlgEditor(ab,file); // dagli anche il nome di un'eventuale file
	de->createWin();
	
	App->run();

	de->destroyWin();

	mq.destroy();
	ab.uninit();

	return (0);
}


