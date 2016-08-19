# -------------------------------------TARGET AND TESTARGS-----------------------------------

TARGET = juliaset

TESTARGS  = -cr -1.05 -ci 0.25 -imgx 1920 -imgy 1080 -zoom 2 -cmap shadownight

FRONTIMAGE = -cr -1.05 -ci 0.25 -imgx 1920 -imgy 1080 -zoom 2 -cmap greenlight
TESTMBROT = -mbrot -imgx 1920 -imgy 1080 -cmap ink -save mimage.jpg
TESTCMAP  = -cmaps

# ----------------------------------------MAKE CONFIG----------------------------------------

SHELL = /bin/bash -O globstar
CC = g++

COMPILE = $(CC) -c
LINK = $(CC)

CFLAGS = -Wall
LFLAGS = -Wall -lpthread -lX11
INCLUD = -Iinclude
LIBRAR = -Llib

# ----------------------------------------DIRECTORIES----------------------------------------

INCDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSDIR = /usr/bin

# ----------------------------------------MAKE RULES-----------------------------------------

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

fimage: $(BINARY)
	@echo Running with $(FRONTIMAGE)
	@echo -------------------------------
	@$(BINARY) $(FRONTIMAGE)
	@echo -------------------------------

cmaps: $(BINARY)
	@echo Running with $(TESTCMAP)
	@echo -------------------------------
	@$(BINARY) $(TESTCMAP)
	@echo -------------------------------

mbrot: $(BINARY)
	@echo Running with $(TESTMBROT)
	@echo -------------------------------
	@$(BINARY) $(TESTMBROT)
	@echo -------------------------------