PROJECT = libFireBird

DIRS = av compression debug elf EPG ExtAttribs Firmware flash FontManager hdd ini InstructionSequences LogoManager main rec shutdown string StringDB tap tapcom time TMSOSDKeyboard TMSOSDMenu TMSOSDMenu/fonts TMSOSDMenu/graphic tmsvfd

export SRC_DIR = $(shell pwd)

BASE = $(shell cd /tapapi/TMS; pwd)
include ${BASE}/include/tool.mk

# normal library version and debugging control by TAP
CFLAGS = -DFB_CALL_TRACE
#CFLAGS = -DFB_DEBUG      for a special debugging version
#CFLAGS = -DFB_DEBUG_FULL for a special debugging version incl. trace support

export CFLAGS

all: lib devutils

.PHONY: readme devutils

lib:
	@for i in $(DIRS); \
	do \
	  $(MAKE) -C $$i all; \
	done
	-$(RM) $(PROJECT).a
	@for i in $(DIRS); \
	do \
	  $(AR) -r $(PROJECT).a $$i/*.o; \
	done
	@$(RANLIB) $(PROJECT).a

devutils:
	cd $@; \
	$(MAKE) all;

docs:
	rm -rf $@
	doxygen

readme:
	markdown README.md >README.html

clean:
	@for i in $(DIRS); do make -C $$i clean; done
	cd devutils; make clean; cd ..;
	rm -rf $(PROJECT).a HTMLDOCS README.html
