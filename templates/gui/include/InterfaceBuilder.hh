// name: InterfaceBuilder.hh
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: The InterfaceBuilder class handles the creation of the ROOT
//       GUI widgets. The widgets provide the interface for the user
//       to perform actions, i.e. to generate signals based on a
//       graphical trigger. The generated "signals" are received by
//       the "slots", where the code for specific actions is
//       executed. To modularize the code the "slots" are handled by
//       the SignalHandler class.
#ifndef __InterfaceBuilder_hh__
#define __InterfaceBuilder_hh__ 1

#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <TGButton.h>
#include <TColor.h>

class SignalHandler;


class InterfaceBuilder  : public TGMainFrame
{
  friend class SignalHandler;
  
public:
  InterfaceBuilder();
  ~InterfaceBuilder();

  void FillMainFrame();

  // Register the class with ROOT
  ClassDef(InterfaceBuilder, 0);

private:
  int MainFrameX, MainFrameY;
  int CanvasX, CanvasY;

  TRootEmbeddedCanvas *TheCanvas_EC;
  TGTextButton *Plot_TB, *Exit_TB;

  SignalHandler *TheHandler;
};

#endif
