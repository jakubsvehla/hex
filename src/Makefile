CC=g++
LD=g++
CFLAGS=-Wall -pedantic
LDFLAGS=-Wall -pedantic
LIBS=-lncurses

BIN=hex
OBJECTS=main.o editor.o cli.o file.o window.o view.o file_view.o cmd_line_view.o mode.o normal_mode.o cmd_mode.o insert_mode.o subject.o config.o

PREFIX?=/usr/local
INSTALL_BIN=$(PREFIX)/bin
INSTALL=cp -pf

all: $(BIN)

.PHONY: all

dep:
	$(CC) -MM *.cpp > Makefile.dep

.PHONY: dep

-include Makefile.dep

$(BIN): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	mkdir -p $(INSTALL_BIN)
	$(INSTALL) $(BIN) $(INSTALL_BIN)

.PHONY: install

clean:
	rm -f $(BIN) $(OBJECTS)

.PHONY: clean
