// name: InterfaceBuilder.hh
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: 

#ifndef __InterfaceBuilder_hh__
#define __InterfaceBuilder_hh__ 1

#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <TGButton.h>
#include <TColor.h>

#include "SignalsHandler.hh"

class InterfaceBuilder  : public TGMainFrame
{
public:
  InterfaceBuilder();
  ~InterfaceBuilder();

  void CreateMainFrame();

  // Register the class with ROOT
  ClassDef(InterfaceBuilder, 0);

private:
  int MainFrameX, MainFrameY;
  int CanvasX, CanvasY;

  TRootEmbeddedCanvas *TheCanvas_EC;
  TGTextButton *Plot_TB, *Exit_TB;

  SignalsHandler *TheHandler;
};

#endif
