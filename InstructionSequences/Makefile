BASE = $(shell cd /tapapi/TMS; pwd)
CUR_DIR = $(shell pwd)
BLOCK = InstructionSequences

# include default settings
include ${BASE}/include/tool.mk

# Folders
SRC_DIR = ${CUR_DIR}
INCLUDE_DIRS = ${BASE}/include

#compile options
CFLAGS += -DLINUX -MD -W -Wall -O2 -mips32
CFLAGS += $(addprefix -I, $(INCLUDE_DIRS))
CFLAGS += $(addprefix -I, /opt/crosstool/include)
ifeq (${DEBUG},y)
CFLAGS += -g -DDEBUG
endif


#TAP_LIBS =  ${BASE}/tapinit.o ${BASE}/libtap.so -lc
TAP_OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
TAP_HEAD = ${BASE}/include/libFireBird.h $(CUR_DIR)/Makefile

all: ${TAP_OBJS}
	@$(Q_)-${RM} *.d

%o: %c ${TAP_HEAD}
	@$(CC) $(CFLAGS) $(TAP_FLAGS) -c $< -o $@

clean:
	@echo "[Clean all objs...]"
	@$(Q_)-${RM} $(BLOCK).a *.d *.o
