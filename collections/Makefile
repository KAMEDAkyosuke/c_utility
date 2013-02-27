CC         = clang
CFLAGS    += --std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -pedantic
LDFLAGS   += 
INCLUDES  +=
LDLIBS    += 
SRCS       = socketlist.c bufferlist.c
OBJS       = $(SRCS:.c=.o)

SUBDIRS   += 

all:
	@for src in $(SRCS) ; do \
		($(CC) $(CFLAGS) -c $$src) ; \
	done


.PHONY: clean
clean:
	$(RM) *.o $(TARGETS)
	@for dir in $(SUBDIRS) ; do \
		(cd $$dir && $(MAKE) clean) ; \
	done

.PHONY: check-syntax
check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)
