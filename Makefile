#
# 'make'        builds the executable 'main' (or 'main.exe' on Windows)
# 'make clean'  removes all object and executable files
#

# -----------------------------#
#         CONFIGURATION        #
# -----------------------------#

CXX       := g++
RC        := windres
CXXFLAGS  := -std=c++20 -Wall -Wextra -g

OUTPUT    := output
SRC       := src
INCLUDE   := include
ICON      := $(INCLUDE)/icon.ico
RES       := $(SRC)/resource.rc
RES_OBJ   := $(OUTPUT)/resource.o

UNAME_S   := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    IS_WINDOWS := 1
else
    IS_WINDOWS := 0
endif

ifeq ($(WINDOWS),)
    MAIN      := main
    RM        := rm -f
    MD        := mkdir -p
else
    MAIN      := main.exe
    RM        := rm -f
    MD        := mkdir -p
endif

OUTPUTMAIN := $(OUTPUT)/$(MAIN)

# -----------------------------#
#      FILES & DIRECTORIES     #
# -----------------------------#

SOURCEDIRS  := $(shell find $(SRC) -type d)
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
INCLUDES    := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
SOURCES     := $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
OBJECTS     := $(patsubst $(SRC)/%.cpp,$(OUTPUT)/%.o,$(SOURCES))

ifeq ($(IS_WINDOWS),1)
    OBJECTS += $(RES_OBJ)
endif

# -----------------------------#
#            TARGETS           #
# -----------------------------#

all: $(OUTPUT) $(OUTPUTMAIN)
	@echo Build complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(OUTPUTMAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJECTS)

# Compile C++ files to object files
$(OUTPUT)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile resource file to object file (Windows only)
$(RES_OBJ): $(RES) $(ICON)
ifeq ($(IS_WINDOWS),1)
	$(RC) $(INCLUDES) $< -o $@
endif

# -----------------------------#
#        CLEAN & RUN           #
# -----------------------------#

.PHONY: clean run

clean:
	$(RM) $(OUTPUT)/$(MAIN) $(OBJECTS)
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)