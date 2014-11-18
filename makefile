#
#
# dlgedit.exe makefile
# version 0.0 3-10-1995
# to be used with dmake & gcc/emx 0.9a patchlevel 3
#
CFLAGS=-Zmtd -Zcrtdll -g -v -Wall -Id:\emx\os2class -m486
CC=gcc $(CFLAGS)
B=/emx/bin/
I=/emx/include/
IP=/emx/include.cpp/
L=/emx/lib/
OS2CLASS=/emx/os2class/
LIBS=$(L)crt0.o $(L)mt/c.a $(L)gcc.a
LIBP=$(L)iostream.a
LIBOS2=$(L)os2.a
LIBBSD=$(L)bsd.a

.SUFFIXES: .o .c .cc .cpp .s .exe .obj

.c.o: 
			$(CC) -c $<

.cc.o:
			$(CC) -c $< 

.cpp.o:
			$(CC) -c $< 

.c.s:
			$(CC) -S $< 

.o.exe:
			$(CC) -o $*.exe $< 


default:        dlgedit.exe

all:            dlgedit.exe

clean:
			-del *.o $(DELOPT)
			-del *.exe $(DELOPT)
			-del *.dll $(DELOPT)
			-del *.obj $(DELOPT)
			-del *.map $(DELOPT)
			-del *.msg $(DELOPT)
			-del *.lib $(DELOPT)

#############################################################################        

dlgdata.o:		 dlgdata.cpp dlgedit.h dlgdata.h $(OS2CLASS)pmdlg.h $(OS2CLASS)pmwin.h $(OS2CLASS)pmgpi.h $(OS2CLASS)pmsys.h
		$(CC) -c dlgdata.cpp

dlgcomr.o:		 dlgcomr.cpp dlgedit.h dlgdata.h $(OS2CLASS)pmdlg.h $(OS2CLASS)pmwin.h $(OS2CLASS)pmgpi.h $(OS2CLASS)pmsys.h
		$(CC) -c dlgcomr.cpp

dlgedit.o:       dlgedit.cpp dlgedit.h $(OS2CLASS)pmwin.h $(OS2CLASS)pmdlg.h $(OS2CLASS)pmgpi.h $(OS2CLASS)pmsys.h $(I)stdio.h $(I)os2emx.h
		$(CC) -c dlgedit.cpp

dlguser.o:       dlguser.cpp dlgedit.h $(OS2CLASS)pmwin.h $(OS2CLASS)pmdlg.h $(OS2CLASS)pmgpi.h $(OS2CLASS)pmsys.h $(I)stdio.h $(I)os2emx.h
		$(CC) -c dlguser.cpp

dlgedit.res:     dlgedit.rc dlgedit.h
		rc -r -i $(I) -i $(OS2CLASS) dlgedit.rc 

dlgedit:         dlgedit.o dlguser.o dlgdata.o dlgcomr.o $(OS2CLASS)pmpp.a dlgedit.def $(LIBS) $(LIBOS2)
		$(CC) -o dlgedit dlgedit.o dlguser.o dlgdata.o dlgcomr.o $(OS2CLASS)pmpp.a dlgedit.def
        
dlgedit.exe:     dlgedit dlgedit.res
		emxbind -bpq -rdlgedit.res $(B)emxl dlgedit
        


