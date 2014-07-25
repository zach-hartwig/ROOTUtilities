# name: Makefile
# date: 25 Jul 14
# auth: Zach Hartwig
# mail: hartwig@psfc.mit.edu
# desc: Template GNU makefile for compiling ROOT-based projects


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
OBJS = $(BUILDDIR)/StandardTemplate.o $(BUILDDIR)/TemplateClass.o $(BUILDDIR)/TemplateClassDict.o

# Specify directories for header files and libraries
INCL = -I$(INCLDIR)/
LIB = 

# Specify compile choice and flags
CXX = clang++
CXXFLAGS +=

# Specifcy the final binary name
TARGET = StandardTemplate


###################
# Write the rules #
###################

# Rules to generate the final binary and object files should be placed here
$(TARGET) : $(OBJS)
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(ROOTLIB) $(ROOTGLIBS)
	@echo -e "\n$@ build is complete!\n"

$(BUILDDIR)/StandardTemplate.o : StandardTemplate.cc
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

$(BUILDDIR)/TemplateClass.o : $(SRCDIR)/TemplateClass.cc $(INCLDIR)/TemplateClass.hh
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

$(BUILDDIR)/TemplateClassDict.o : $(BUILDDIR)/TemplateClassDict.cc
	@echo -e "\nBuilding $@ ..."
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<

# Rule(s) to generate ROOT dictionary should be placed here
$(BUILDDIR)/TemplateClassDict.cc : $(INCLDIR)/TemplateClass.hh $(INCLDIR)/RootLinkDef.hh
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
