DESTDIR   ?=
PREFIX    ?= /usr/local
MANPREFIX ?= $(PREFIX)/man

CFLAGS += -Wall -Wextra

all: cycle

clean:
	rm -f cycle

check: cycle
	echo test | ./cycle | head >/dev/null

install: cycle
	install -d $(DESTDIR)$(PREFIX)/bin
	install -d $(DESTDIR)$(MANPREFIX)/man1
	install -m755 cycle   $(DESTDIR)$(PREFIX)/bin/
	install -m644 cycle.1 $(DESTDIR)$(MANPREFIX)/man1/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/cycle
	rm -f $(DESTDIR)$(MANPREFIX)/man1/cycle.1

.PHONY: all clean install uninstall
