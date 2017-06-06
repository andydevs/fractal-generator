# -------------------------------------TARGET AND ARGS-----------------------------------

TARGET = fractal

# Error arguments
ERRREAD = -xml foobar.xml
ERRXML  = -xml err.xml
ERRCMAP = -cmap foobar

# Fractal Images
FIMAGE = -cr -0.4 -ci 0.6 -imgx 1920 -imgy 1080 -zoom 2 -cmap flower -save fimage.jpg
MIMAGE = -mbrot -imgx 1920 -imgy 1080 -zoom 2 -offx -0.5 -cmap ink -save mimage.jpg
WIMAGE = -cr -0.19 -ci -0.67 -imgx 1920 -imgy 1080 -rot -30 -zoom 2 -offx -0.8 -offy 0.5 -save wimage.jpg -cmap saree

# Other tests
HELP   = -help
XML    = -xml fractal.xml
XMLID  = -xml fractal.xml -id front
TCMAP  = -test -cmap flower -save colormaptest.jpg
LCMAPS = -cmaps

# ----------------------------------------MAKE CONFIG----------------------------------------

SHELL = /bin/bash -O globstar
CC    = g++

COMPILE = $(CC) -c
LINK    = $(CC)

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

# ----------------------------------------OTHER FILES----------------------------------------

PRESET = fractal_colormaps.xml

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
	@cp $(PRESET) $(INSDIR)

uninstall:
	@rm $(INSDIR)/$(TARGET)
	@rm $(INSDIR)/$(PRESET)

# ------------------------------------------TESTS-------------------------------------------

errcmap: $(BINARY)
	@echo Running with $(ERRCMAP)
	@echo -------------------------------
	@$(BINARY) $(ERRCMAP)
	@echo -------------------------------

errxml: $(BINARY)
	@echo Running with $(ERRXML)
	@echo -------------------------------
	@$(BINARY) $(ERRXML)
	@echo -------------------------------

errread: $(BINARY)
	@echo Running with $(ERRREAD)
	@echo -------------------------------
	@$(BINARY) $(ERRREAD)
	@echo -------------------------------

fimage: $(BINARY)
	@echo Running with $(FIMAGE)
	@echo -------------------------------
	@$(BINARY) $(FIMAGE)
	@echo -------------------------------

wimage: $(BINARY)
	@echo Running with $(WIMAGE)
	@echo -------------------------------
	@$(BINARY) $(WIMAGE)
	@echo -------------------------------

mimage: $(BINARY)
	@echo Running with $(MIMAGE)
	@echo -------------------------------
	@$(BINARY) $(MIMAGE)
	@echo -------------------------------

help: $(BINARY)
	@echo Running with $(HELP)
	@echo -------------------------------
	@$(BINARY) $(HELP)
	@echo -------------------------------

xml: $(BINARY)
	@echo Running with $(XML)
	@echo -------------------------------
	@$(BINARY) $(XML)
	@echo -------------------------------

xmlid: $(BINARY)
	@echo Running with $(XMLID)
	@echo -------------------------------
	@$(BINARY) $(XMLID)
	@echo -------------------------------

listcmaps: $(BINARY)
	@echo Running with $(LCMAPS)
	@echo -------------------------------
	@$(BINARY) $(LCMAPS)
	@echo -------------------------------

testcmap: $(BINARY)
	@echo Running with $(TCMAP)
	@echo -------------------------------
	@$(BINARY) $(TCMAP)
	@echo -------------------------------
