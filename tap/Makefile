BASE = $(shell cd /tapapi/TMS; pwd)
CUR_DIR = $(shell pwd)
BLOCK = tap

# include default settings
include ${BASE}/include/tool.mk

# Folders
INCLUDE_DIRS = ${SRC_DIR} ${BASE}/include

#compile options
CFLAGS += -DLINUX -MD -W -Wall -O2 -mips32 -fPIC
CFLAGS += $(addprefix -I, $(INCLUDE_DIRS))
CFLAGS += $(addprefix -I, /opt/crosstool/include)
ifeq (${DEBUG},y)
CFLAGS += -g -DDEBUG
endif


#TAP_LIBS =  ${BASE}/tapinit.o ${BASE}/libtap.so -lc
TAP_OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
TAP_HEAD = ${SRC_DIR}/libFireBird.h FBLib_$(BLOCK).h $(CUR_DIR)/Makefile

all: ${TAP_OBJS}
	@$(Q_)-${RM} *.d

%.o: %.c ${TAP_HEAD}
	@$(CC) $(CFLAGS) $(TAP_FLAGS) -c $< -o $@

clean:
	@echo "[Clean all objs...]"
	@$(Q_)-${RM} $(BLOCK).a *.d *.o
