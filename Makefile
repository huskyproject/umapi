# include Husky-Makefile-Config
include ../huskymak.cfg

UMAPIVER=0.1
UMAPIVERHI=0
UMAPIVERLO=1

# program settings

ifeq ($(DEBUG), 1)
  COPT = $(WARNFLAGS) $(DEBCFLAGS) -I.
  LFLAGS = $(DEBLFLAGS)
else
  COPT = $(WARNFLAGS) $(OPTCFLAGS) -I.
  LFLAGS = $(OPTLFLAGS)
endif

CDEFS = -D$(OSTYPE) $(ADDCDEFS)

LOPTCL = -L. -lumapicl
LOPTSRV = -L. -lumapisrv

ifeq ($(SHORTNAME), 1)
  LIBUMAPICL = umapicl
  LIBUMAPISRV = umapisrv
else
  LIBUMAPICL = libumapicl
  LIBUMAPISRV = libumapisrv
endif

default: all

ifeq ($(DYNLIBS), 1)
  all: $(LIBUMAPICL)$(LIB) $(LIBUMAPICL).so.$(UMAPIVER) $(LIBUMAPISRV)$(LIB)
else
  all: $(LIBUMAPICL)$(LIB) $(LIBUMAPISRV)$(LIB)
endif

clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) *.bak

distclean: clean
	-$(RM) $(LIBUMAPICL).so.$(UMAPIVER)
	-$(RM) $(LIBUMAPICL)$(LIB)
	-$(RM) $(LIBUMAPISRV)$(LIB)
	-$(RM) umapid$(EXE)
	-$(RM) test$(EXE)

UMAPIHDRS = umapi.h umapisq.h umapisdm.h umdate.h typesize.h
UMAPIOBJS = umapi$(OBJ) umapisq$(OBJ) umapisdm$(OBJ) \
            umdate$(OBJ) umaddr$(OBJ)
UMAPICLOBJS = $(UMAPIOBJS) umapicl$(OBJ)
UMAPISRVOBJS = $(UMAPIOBJS) umapisrv$(OBJ)

$(LIBUMAPICL)$(LIB): $(UMAPICLOBJS) $(UMAPIHDRS)
	$(AR) $(AR_R) $(LIBUMAPICL)$(LIB) $(UMAPICLOBJS)

$(LIBUMAPISRV)$(LIB): $(UMAPISRVOBJS) $(UMAPIHDRS)
	$(AR) $(AR_R) $(LIBUMAPISRV)$(LIB) $(UMAPISRVOBJS)

$(LIBUMAPICL).so.$(UMAPIVER): $(UMAPICLOBJS) $(UMAPIHDRS)
	$(CC) -shared -Wl,-soname,$(LIBUMAPICL).so.$(UMAPIVERHI) \
	  -o $(LIBUMAPICL).so.$(UMAPIVER) $(UMAPICLOBJS)

test$(EXE): all test$(OBJ)
	$(CC) $(LFLAGS) -o test$(EXE) test$(OBJ) $(LOPTCL)

umapid$(EXE): $(LIBUMAPISRV)$(LIB) umapid$(OBJ)
	$(CC) $(LFLAGS) -o umapid$(EXE) umapid$(OBJ) $(LOPTSRV)

%.o: %.c
	$(CC) $(CDEFS) $(COPT) $*.c

ifeq ($(DYNLIBS), 1)
instdyn: $(LIBUMAPICL).so.$(UMAPIVER)
	$(INSTALL) $(ILOPT) $(LIBUMAPICL).so.$(UMAPIVER) $(LIBDIR)
	$(LN) $(LNOPT) $(LIBDIR)/$(LIBUMAPICL).so.$(UMAPIVER) \
	  $(LIBDIR)/$(LIBUMAPICL).so.$(UMAPIVERHI)
	$(LN) $(LNOPT) $(LIBDIR)/$(LIBUMAPICL).so.$(UMAPIVERHI) \
	  $(LIBDIR)/$(LIBUMAPICL).so
	$(LDCONFIG)

else
instdyn:
	@echo
endif

install: $(LIBUMAPICL)$(LIB) instdyn
	-$(MKDIR) $(MKDIROPT) $(INCDIR)/$(UMAPI)
	$(INSTALL) $(ILOPT) $(LIBUMAPICL)$(LIB) $(LIBDIR)

uninstall:
	-$(RM) $(LIBDIR)$(DIRSEP)$(LIBUMAPICL)$(LIB)
	-$(RM) $(LIBDIR)$(DIRSEP)$(LIBUMAPICL).so.$(UMAPIVER)
	-$(RM) $(LIBDIR)$(DIRSEP)$(LIBUMAPICL).so.$(UMAPIVERHI)
	-$(RM) $(LIBDIR)$(DIRSEP)$(LIBUMAPICL).so

