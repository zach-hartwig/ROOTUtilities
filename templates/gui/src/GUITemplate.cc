// name: Template.cc
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: Template C++ main implementation file for ROOT-based projects
//       with a graphical user interface (GUI). The code provide an
//       easy way to rapidly develop GUI projects with all the
//       infrastructure of a mature project (advanced GNU makefile,
//       elegant directory strucutre, etc).

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
