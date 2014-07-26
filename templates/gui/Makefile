# name: Makefile
# date: 25 Jul 14
# auth: Zach Hartwig
# mail: hartwig@psfc.mit.edu
# desc: GNU makefile for compiling ROOT-based projects for the
#       graphical interface template with elegant directory structure


####################
# Define variables #
####################

# Include the required ROOT makefiles and variables
RC:=root-config
ROOTSYS:=$(shell $(RC) --prefix)
ROOTMAKE:=$(ROOTSYS)/etc/Makefile.arch
include $(ROOTMAKE)

# Specify the directory structure. Note that the absolute path to the
# 'include' directory is required to ensure that the generated includes
# in the ROOT dictionary objects can find the header files
BUILDDIR = build
SRCDIR = src
INCLDIR = $(PWD)/include

# Automatically specify object files from source files
TMP0 = $(wildcard src/*.cc) 
TMP1 = $(patsubst %.cc,%.o,$(TMP0))
OBJS = $(subst $(SRCDIR),$(BUILDDIR),$(TMP1))

# Add required ROOT dictionary object file
OBJS += $(BUILDDIR)/GUITemplateDict.o

# Specify directories for header files and libraries
INCL = -I$(INCLDIR)/
LIB = 

# Specify compiler choice and flags
CXX = clang++
CXXFLAGS +=

# Specify the final binary name
TARGET = GUITemplate

# Specify general purpose dependencies
DEPS = $(wildcard $(INCLDIR)/*.hh)


###############
# Build rules #
###############

# Rule to build and link the executable
$(TARGET) : $(OBJS)
	@echo -e "\nGenerating $@ ..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(ROOTLIB) $(ROOTGLIBS)
	@echo -e "\n$@ build is complete!\n"

# Rule to automatically generate object files from source files
$(BUILDDIR)/%.o : $(SRCDIR)/%.cc $(DEPS)
	@echo -e "\nGenerating object file $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

# Rule to generate ROOT dictionaries for custom classes
$(BUILDDIR)/GUITemplateDict.cc : $(DEPS) $(INCLDIR)/RootLinkDef.hh
	@echo -e "\nGenerating ROOT dictionary $@ ..."
	rootcint -f $@ -c $(INCL) $^

# Clean up the transient files and executable
.PHONY:
clean:
	@echo -e "\nCleaing up the build files ..."
	@rm -f $(BUILDDIR)/* $(TARGET)
	@echo -e ""

# Useful notes for the uninitiated:
#
# target : dependency list
#  --TAB-- rule
#
# "$@" == subst. the word to the left of the ":"
# "$^" == subst. the words to the right of ":"
# "$<" == subst. first item in dependency list
