CC         = clang
CFLAGS    += --std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -pedantic
LDFLAGS   += 
INCLUDES  +=
LDLIBS    += 
SRCS       = net.c
OBJS       = $(SRCS:.c=.o)
TARGETS    = main

SUBDIRS   += 

all: $(OBJS) $(SUBDIRS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: clean
clean:
	$(RM) *.o $(TARGETS)
	@for dir in $(SUBDIRS) ; do \
		(cd $$dir && $(MAKE) clean) ; \
	done

.PHONY: check-syntax
check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

