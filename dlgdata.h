/* dlgdata.h */

#ifndef _DLGDATA_H_
#define _DLGDATA_H_


extern ULONG winflvalues[26];

extern PCHAR winflnames[26];

extern PCHAR apchClassNames[];

extern LONG lClassesDefStyles[];

extern PSZ apszClasses[];

extern PCHAR apchDialogControlRCNames[];

extern int menu2classindex[];

struct _style {
	char *label;
	ULONG value;
	int type; // 0 se bit 1 se valore 2 se da aggiungere
	ULONG bits; // se type e' valore indica quali bits occupa il valore
};

extern _style *apsStyles[];
extern _style aWindowStyles[];
extern _style aFrameStyles[];
extern _style aButtonStyles[];
extern _style aComboBoxStyles[];
extern _style aEntryStyles[];
extern _style aListBoxStyles[];
extern _style aScrollBarStyles[];
extern _style aStaticStyles[];
extern _style aMLEStyles[];
extern _style aSPBStyles[];
extern _style aSliderStyles[];
extern _style aBookStyles[];
extern _style aValueSetStyles[];
extern _style aContainerStyles[];

/////////////////////////////////////////////////////////////////////////////



#endif

