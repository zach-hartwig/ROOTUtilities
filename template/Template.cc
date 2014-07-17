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

#include "TemplateClass.hh"


int main(int argc, char *argv[])
{
  TApplication *TheApplication = new TApplication("TheApplication", &argc, argv);

  ///////////////////////////
  // Source code goes here //
  ///////////////////////////

  TheApplication->Run();

  return 0;
}
