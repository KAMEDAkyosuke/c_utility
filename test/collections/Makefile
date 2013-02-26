CC         = clang
CFLAGS    += --std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -pedantic
LDFLAGS   += 
LDLIBS    += 
OBJS       = 
TARGETS    = main

SUBDIRS   += ../../collections

.PHONY: all test_socket $(SUBDIRS)

test_socketlist: test_socketlist.c ../../collections/socketlist.o
	$(CC) $(CFLAGS) -o test_socketlist test_socketlist.c ../../collections/socketlist.o

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
