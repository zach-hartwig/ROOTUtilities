// name: Template.cc
// date: 17 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: Template C++ main implementation file for ROOT-based
//        projects. Note that the use of TApplication will start a
//        continually running ROOT-session to display graphical
//        objects. It is not necessary if you are only using ROOT
//        classes for computation and cmd line output


#include <TApplication.h>


#include "InterfaceBuilder.hh"

int main(int argc, char *argv[])
{
  // Create a ROOT application
  TApplication *TheApplication = new TApplication("TheROOTSession", &argc, argv);

  // Create the graphical user interface (GUI)
  InterfaceBuilder *TheInterface = new InterfaceBuilder;

  // Run the application
  TheApplication->Run();
  
  // Delete objects after the application has finished;
  delete TheInterface;
  delete TheApplication;

  return 0;
}
