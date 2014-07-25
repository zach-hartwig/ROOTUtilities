// name: Template.cc
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: Template C++ main implementation file for ROOT-based
//        projects. Note that the use of TApplication will start a
//        continually running ROOT-session to display graphical
//        objects. It is not necessary if you are only using ROOT
//        classes for computation and cmd line output

#include <TRint.h>

#include "TemplateClass.hh"


int main(int argc, char *argv[])
{
  TRint *TheROOTSession = new TRint("TheROOTSession", &argc, argv);

  ///////////////////////////
  // Source code goes here //
  ///////////////////////////

  // Drop user to ROOT cmd line after code execution
  TheROOTSession->Run();

  return 0;
}
