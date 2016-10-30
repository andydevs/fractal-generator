# -------------------------------------TARGET AND ARGS-----------------------------------

TARGET = juliaset

ARGS  = -cr -0.4 -ci 0.6 -imgx 1920 -imgy 1080 -zoom 2 -cmap flower -save fimage.jpg
XML   = -xml juliaset.xml
CMAP  = -test -cmap flower -save colormaptest.jpg
CMAPS = -cmaps
MANDELBROT = -mbrot -imgx 1920 -imgy 1080 -zoom 2 -offx -0.5 -cmap ink -save mimage.jpg
WALLPAPER  = -cr -0.19 -ci -0.67 -imgx 1920 -imgy 1080 -rot -30 -zoom 2 -offx -0.8 -offy 0.5 -save wimage.jpg -cmap saree

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

CMAPS = juliaset_colormaps.xml

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
	@cp $(CMAPS) $(INSDIR)

uninstall:
	@rm $(INSDIR)/$(TARGET)
	@rm $(INSDIR)/$(CMAPS)

run: $(BINARY)
	@echo Running with $(ARGS)
	@echo -------------------------------
	@$(BINARY) $(ARGS)
	@echo -------------------------------

xml: $(BINARY)
	@echo Running with $(XML)
	@echo -------------------------------
	@$(BINARY) $(XML)
	@echo -------------------------------

wimage: $(BINARY)
	@echo Running with $(WALLPAPER)
	@echo -------------------------------
	@$(BINARY) $(WALLPAPER)
	@echo -------------------------------

mimage: $(BINARY)
	@echo Running with $(MANDELBROT)
	@echo -------------------------------
	@$(BINARY) $(MANDELBROT)
	@echo -------------------------------

cmaps: $(BINARY)
	@echo Running with $(CMAPS)
	@echo -------------------------------
	@$(BINARY) $(CMAPS)
	@echo -------------------------------

testcmap: $(BINARY)
	@echo Running with $(CMAP)
	@echo -------------------------------
	@$(BINARY) $(CMAP)
	@echo -------------------------------