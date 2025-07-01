#
# 'make'        builds executable 'main' (or 'main.exe' on Windows)
# 'make clean'  removes all object and executable files
#

CXX = g++
RC = windres

CXXFLAGS := -std=c++20 -Wall -Wextra -g

OUTPUT   := output
SRC      := src
INCLUDE  := include
UNAME_S  := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    MAIN    := main
    RM      := rm -f
    MD      := mkdir -p
    FIXPATH = $1
else ifeq ($(UNAME_S),Darwin)
    MAIN    := main
    RM      := rm -f
    MD      := mkdir -p
    FIXPATH = $1
else ifneq (,$(findstring MINGW,$(UNAME_S)))
    MAIN    := main.exe
    RM      := rm -f
    MD      := mkdir -p
    FIXPATH = $1
else ifneq (,$(findstring MSYS,$(UNAME_S)))
    MAIN    := main.exe
    RM      := rm -f
    MD      := mkdir -p
    FIXPATH = $1
else
    $(error Unsupported OS: $(UNAME_S))
endif

ICON       := $(INCLUDE)/icon.ico
RES        := $(SRC)/resource.rc
RES_OBJ    := $(OUTPUT)/resource.o

SOURCEDIRS     := $(shell find $(SRC) -type d)
INCLUDEDIRS    := $(shell find $(INCLUDE) -type d)
INCLUDES       := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
SOURCES        := $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
OBJECTS        := $(patsubst $(SRC)/%.cpp,$(OUTPUT)/%.o,$(SOURCES))

# Append resource.o only on Windows
ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
    OBJECTS += $(RES_OBJ)
else ifeq ($(findstring MSYS,$(UNAME_S)),MSYS)
    OBJECTS += $(RES_OBJ)
endif

OUTPUTMAIN := $(call FIXPATH,$(OUTPUT)/$(MAIN))

# Resource compilation only on Windows
ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
$(RES_OBJ): $(RES) $(ICON)
	$(RC) -I$(INCLUDE) $< -o $@
else ifeq ($(findstring MSYS,$(UNAME_S)),MSYS)
$(RES_OBJ): $(RES) $(ICON)
	$(RC) -I$(INCLUDE) $< -o $@
endif

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS)

# Compile .cpp to .o into output folder
$(OUTPUT)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUT)/main.exe $(OUTPUT)/main
	$(RM) $(OUTPUT)/*.o
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!
