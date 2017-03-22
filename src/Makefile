INSTALLDIR=/home/adcastel/opt/GLT/
UNDERA=argobots
UNDERQ=qthreads
UNDERM=massivethreads
UNDERP=pthreads

all:qth mth arg pth

arg:
	make -C argobots

mth:
	make -C massivethreads

qth:
	make -C qthreads

pth:
	make -C pthreads

clean:
	make -C argobots clean
	make -C massivethreads clean
	make -C qthreads clean
	make -C pthreads clean

install:

	mkdir -p $(INSTALLDIR)/$(UNDERA)/lib
	mkdir -p $(INSTALLDIR)/$(UNDERA)/include
	cp $(UNDERA)/libglt.so $(INSTALLDIR)/$(UNDERA)/lib
	cp $(UNDERA)/libgltpthread.so $(INSTALLDIR)/$(UNDERA)/lib
	cp $(UNDERA)/glt.h $(INSTALLDIR)/$(UNDERA)/include
	cp $(UNDERA)/fast_glt.h $(INSTALLDIR)/$(UNDERA)/include
	cp $(UNDERA)/glt_pthreads.h $(INSTALLDIR)/$(UNDERA)/include

	mkdir -p $(INSTALLDIR)/$(UNDERQ)/lib
	mkdir -p $(INSTALLDIR)/$(UNDERQ)/include
	cp $(UNDERQ)/libglt.so $(INSTALLDIR)/$(UNDERQ)/lib
	cp $(UNDERQ)/libgltpthread.so $(INSTALLDIR)/$(UNDERQ)/lib
	cp $(UNDERQ)/glt.h $(INSTALLDIR)/$(UNDERQ)/include
	cp $(UNDERQ)/fast_glt.h $(INSTALLDIR)/$(UNDERQ)/include
	cp $(UNDERQ)/glt_pthreads.h $(INSTALLDIR)/$(UNDERQ)/include
	
	mkdir -p $(INSTALLDIR)/$(UNDERM)/lib
	mkdir -p $(INSTALLDIR)/$(UNDERM)/include
	cp $(UNDERM)/libglt.so $(INSTALLDIR)/$(UNDERM)/lib
	cp $(UNDERM)/libgltpthread.so $(INSTALLDIR)/$(UNDERM)/lib
	cp $(UNDERM)/glt.h $(INSTALLDIR)/$(UNDERM)/include
	cp $(UNDERM)/fast_glt.h $(INSTALLDIR)/$(UNDERM)/include
	cp $(UNDERM)/glt_pthreads.h $(INSTALLDIR)/$(UNDERM)/include

	mkdir -p $(INSTALLDIR)/$(UNDERP)/lib
	mkdir -p $(INSTALLDIR)/$(UNDERP)/include
	cp $(UNDERP)/libglt.so $(INSTALLDIR)/$(UNDERP)/lib
	cp $(UNDERP)/glt.h $(INSTALLDIR)/$(UNDERP)/include
	cp $(UNDERP)/fast_glt.h $(INSTALLDIR)/$(UNDERP)/include
