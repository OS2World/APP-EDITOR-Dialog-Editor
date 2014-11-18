#include "dlgedit.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

char filebanner[]="DL Binary Dialog File version 0.0\x1a";
char resbanner[]="/*\n * Resource file created by dlgedit version 0.0\n * Giovanni Iachello 1995\n * ";

/* */

void writecontrol(FILE* f,_dlgcontrol* ctrl);

BOOL compile(const char* file,_dlginfo* pdi)
{
	int i;
	time_t compiletime;
	char fn[300];
	_dlginfo* p;

	time(&compiletime);

	strcpy(fn,file);
	strcat(fn,"G");
	if (pdi) p=pdi; else { p=new _dlginfo; loaddl(file,p); }

	FILE* f=fopen(fn,"wt");
	fputs(resbanner,f);
	fprintf(f,"%s compiled on %s */\n",fn,ctime(&compiletime));
	fprintf(f,"DLGTEMPLATE %s \n{\n\tDIALOG \"%s\", %s , %d, %d, %d, %d,\n",
		p->label,p->title,p->label,10,10,p->sx,p->sy);
	fprintf(f,"\t\tWS_VISIBLE, ");
	int notfirst=FALSE;
	for (i=0; i<26; i++) {
		if (p->fl[i]) {
			if (notfirst) fputs("| ",f);
			fprintf(f,"%s ",winflnames[i]);
			notfirst=TRUE;
		}
	}		
	fputs("\n\t{\n",f);
	_dlgcontrol* ctrl=p->dlgctrl;
	while ( ctrl != NULL ) {
		writecontrol(f,ctrl);
		ctrl=ctrl->next;
	}

	fputs("\n\t}\n}\n",f);
	fclose(f);
	
	if (p!=pdi) delete p;
	return TRUE;
}

void writecontrol(FILE* f,_dlgcontrol* ctrl)
{
	if (apchDialogControlRCNames[ctrl->classidx]) {
		fprintf(f,"\t\t%s \"%s\", %s, %ld, %ld, %ld, %ld",
			apchDialogControlRCNames[ctrl->classidx],
			ctrl->text,
			(ctrl->idc[0] ? ctrl->idc : "-1"),
			ctrl->x,
			ctrl->y,
			ctrl->cx,
			ctrl->cy);
	} else {
		fprintf(f,"\t\tCONTROL \"%s\", %s, %ld, %ld, %ld, %ld, %s",
			ctrl->text,
			(ctrl->idc[0] ? ctrl->idc : "-1"),
			ctrl->x,
			ctrl->y,
			ctrl->cx,
			ctrl->cy,
			apchClassNames[ctrl->classidx]);
	}
	if (ctrl->flags) { // mettici i flags, prima quelli della finestra
		int first=1;
		fputs(", ",f);
		_style *ws=aWindowStyles;
		while (ws->label!=NULL) {
			if (ws->value & ctrl->flags) {
				if (first) first=0; else fputs("| ",f);
				fprintf(f,"%s ",ws->label);
			}
			ws++;
		}
		ws=apsStyles[ctrl->classidx];
		if (ws) {
			while (ws->label!=NULL) { // poi quelli specifici
				if (ws->type==1) { // valore preciso 
					if ( ws->value == ( ctrl->flags & ws->bits ) ) {
						if (first) first=0; else fputs("| ",f);
						fprintf(f,"%s ",ws->label);
					}
				} else { // semplice bit
					if ( ws->value & ctrl->flags ) {
						if (first) first=0; else fputs("| ",f);
						fprintf(f,"%s ",ws->label);
					}
				}
				ws++;
			}
		}
	}	
	fputs("\n",f);
}


BOOL savedl(const char* file,_dlginfo* pdi)
{
	FILE* f=fopen(file,"wb");
	fwrite(filebanner,strlen(filebanner)+1,1,f);
	fwrite(pdi,sizeof(*pdi),1,f);
	_dlgcontrol* pdc=pdi->dlgctrl;
	while (pdc!=NULL) {
		fwrite(pdc,sizeof(*pdc),1,f);
		pdc=pdc->next;
	}
	fclose(f);
	return TRUE;
}

BOOL loaddl(const char* file,_dlginfo* pdi)
{
	FILE* f=fopen(file,"rb");
	if (!f) return FALSE;
	fseek(f,strlen(filebanner)+1,SEEK_CUR);

	fread(pdi,sizeof(*pdi),1,f);

	_dlgcontrol** pdc=&(pdi->dlgctrl);
	while (!feof(f)) {
		*pdc= new _dlgcontrol;
		fread(*pdc,sizeof(**pdc),1,f);
		if (feof(f)) { delete *pdc; break; }
		pdc=&((*pdc)->next);
	}
	*pdc=NULL;
	fclose(f);
	return TRUE;
}

