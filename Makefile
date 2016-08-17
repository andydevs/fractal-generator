TARGET = juliaset

TESTARGS = -1.05 0.25 1920 1080 -cmap ironman

SHELL = /bin/bash -O globstar
CC = g++

COMPILE = $(CC) -c
LINK = $(CC)

CFLAGS = -Wall
LFLAGS = -Wall -lpthread -lX11
INCLUD = -Iinclude
LIBRAR = -Llib

INCDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSDIR = /usr/bin

INCLUDS = $(shell ls $(INCDIR)/**/*.h)
SOURCES = $(shell ls $(SRCDIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
BINARY  = $(BINDIR)/$(TARGET)

$(BINARY): $(OBJECTS)
	@test -d $(@D) || mkdir -p $(@D)
	@echo building $@
	@$(LINK) $^ -o $@ $(LFLAGS) $(LIBRAR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDS)
	@test -d $(@D) || mkdir -p $(@D)
	@echo compiling $<
	@$(COMPILE) $< -o $@ $(CFLAGS) $(INCLUD)

clean:
	@echo Cleaning up...
	@rm -rf $(OBJDIR) $(BINDIR)

install: $(BINARY)
	@cp $(BINARY) $(INSDIR)

uninstall:
	@rm $(INSDIR)/$(TARGET)

run: $(BINARY)
	@echo Running with $(TESTARGS)
	@echo -------------------------------
	@$(BINARY) $(TESTARGS)
	@echo -------------------------------