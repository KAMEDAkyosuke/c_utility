CC         = clang
CFLAGS    += --std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -pedantic
LDFLAGS   += 
INCLUDES  +=
LDLIBS    += 
SRCS       = socketlist.c
OBJS       = $(SRCS:.c=.o)

SUBDIRS   += 

.PHONY: all
all: $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *.o $(TARGETS)
	@for dir in $(SUBDIRS) ; do \
		(cd $$dir && $(MAKE) clean) ; \
	done

.PHONY: check-syntax
check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
