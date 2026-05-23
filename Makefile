# cwm - Claude's Window Manager - Makefile

VERSION = 1.0

PREFIX   = /usr/local
MANPREFIX = $(PREFIX)/share/man

# Xinerama サポート (マルチモニター)
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

INCS = -I/usr/X11R6/include -I/usr/include/X11
LIBS = -L/usr/X11R6/lib -lc -lX11 $(XINERAMALIBS)

CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L \
           -DVERSION=\"$(VERSION)\" $(XINERAMAFLAGS)
CFLAGS   = -std=c99 -pedantic -Wall -Wextra -Wno-deprecated-declarations \
           -Os $(INCS) $(CPPFLAGS)
LDFLAGS  = $(LIBS)

CC = cc

SRC = cwm.c
OBJ = $(SRC:.c=.o)

all: cwm

.c.o:
	$(CC) -c $(CFLAGS) $<

$(OBJ): config.h

cwm: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f cwm $(OBJ)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f cwm $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/cwm
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f cwm.1 $(DESTDIR)$(MANPREFIX)/man1/cwm.1 2>/dev/null || true
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/cwm.1 2>/dev/null || true

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/cwm \
	      $(DESTDIR)$(MANPREFIX)/man1/cwm.1

.PHONY: all clean install uninstall
