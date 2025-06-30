#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

CXX = g++

CXXFLAGS	:= -std=c++20 -Wall -Wextra -g

OUTPUT	:= output

SRC		:= src

INCLUDE	:= include
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    MAIN        := main
    RM          := rm -f
    MD          := mkdir -p
    FIXPATH     = $1
else ifeq ($(UNAME_S),Darwin)
    MAIN        := main
    RM          := rm -f
    MD          := mkdir -p
    FIXPATH     = $1
else ifneq (,$(findstring MINGW,$(UNAME_S)))
    MAIN        := main.exe
    RM          := rm -f
    MD          := mkdir -p
    FIXPATH     = $1
else ifneq (,$(findstring MSYS,$(UNAME_S)))
    MAIN        := main.exe
    RM          := rm -f
    MD          := mkdir -p
    FIXPATH     = $1
else
    $(error Unsupported OS: $(UNAME_S))
endif


SOURCEDIRS     := $(shell find $(SRC) -type d)
INCLUDEDIRS    := $(shell find $(INCLUDE) -type d)

INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))

OBJECTS := $(patsubst $(SRC)/%.cpp,$(OUTPUT)/%.o,$(SOURCES))

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))


all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS)

# Pattern rule to compile .cpp to .o into output folder
$(OUTPUT)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# this is a suffix replacement rule for building .o's and .d's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# -MMD generates dependency output files same name as the .o file
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OUTPUT)/main.exe
	rm -f $(OBJECTS)
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!
