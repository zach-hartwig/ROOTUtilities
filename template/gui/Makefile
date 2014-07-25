# name: Makefile
# date: 25 Jul 14
# auth: Zach Hartwig
# mail: hartwig@psfc.mit.edu
# desc: Template GNU makefile for compiling ROOT-based projects with
#       a graphical interface template and code-layout setup


####################
# Define variables #
####################

# Include the required ROOT makefiles and variables
RC:=root-config
ROOTSYS:=$(shell $(RC) --prefix)
ROOTMAKE:=$(ROOTSYS)/etc/Makefile.arch
include $(ROOTMAKE)

# Specify the directory structure
SRCDIR = src
INCLDIR = $(PWD)/include
BUILDDIR = $(PWD)/build

# Specify the object files
OBJS = $(BUILDDIR)/GUITemplate.o $(BUILDDIR)/InterfaceBuilder.o $(BUILDDIR)/SignalsHandler.o $(BUILDDIR)/GUITemplateDict.o

# Specify directories for header files and libraries
INCL = -I$(INCLDIR)/
LIB = 

# Specify compile choice and flags
CXX = clang++
CXXFLAGS +=

# Specifcy the final binary name
TARGET = GUITemplate


###################
# Write the rules #
###################

# Rules to generate the final binary and object files should be placed here
$(TARGET) : $(OBJS)
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(ROOTLIB) $(ROOTGLIBS)
	@echo -e "\n$@ build is complete!\n"

$(BUILDDIR)/GUITemplate.o : GUITemplate.cc
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

$(BUILDDIR)/InterfaceBuilder.o : $(SRCDIR)/InterfaceBuilder.cc $(INCLDIR)/InterfaceBuilder.hh
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

$(BUILDDIR)/SignalsHandler.o : $(SRCDIR)/SignalsHandler.cc $(INCLDIR)/SignalsHandler.hh
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

$(BUILDDIR)/GUITemplateDict.o : $(BUILDDIR)/GUITemplateDict.cc
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

# Rule(s) to generate ROOT dictionary should be placed here
$(BUILDDIR)/GUITemplateDict.cc : $(INCLDIR)/InterfaceBuilder.hh $(INCLDIR)/SignalsHandler.hh $(INCLDIR)/RootLinkDef.hh
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
