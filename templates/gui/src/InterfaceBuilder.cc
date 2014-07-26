// name: InterfaceBuilder.cc
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

#include "InterfaceBuilder.hh"
#include "InterfaceEnumerators.hh"
#include "SignalHandler.hh"


InterfaceBuilder::InterfaceBuilder()
  : MainFrameX(500), MainFrameY(500), 
    CanvasX(450), CanvasY(400)
{
  TheHandler = new SignalHandler(this);

  // Create the widgets
  FillMainFrame();

  // Connect the main frame window close button
  Connect("CloseWindow()", "SignalHandler", TheHandler, "HandleTerminate()");  
  
  // Set the window name
  SetWindowName("A template for ROOT-based GUI projects");

  // Set the main frame window size
  Resize(MainFrameX, MainFrameY);

  // Create the graphical windows
  MapWindow();
  MapSubwindows();
}


InterfaceBuilder::~InterfaceBuilder()
{ delete TheHandler; }


void InterfaceBuilder::FillMainFrame()
{
  TGVerticalFrame *Frame0_VF = new TGVerticalFrame(this);
  AddFrame(Frame0_VF, new TGLayoutHints(kLHintsCenterX, 5,5,5,5));
  
  Frame0_VF->AddFrame(TheCanvas_EC = new TRootEmbeddedCanvas("TheCanvas_EC", Frame0_VF, CanvasX, CanvasY),
  		      new TGLayoutHints(kLHintsCenterX, 5,5,5,5));
  

  TGHorizontalFrame *Frame1_HF = new TGHorizontalFrame(Frame0_VF);
  Frame0_VF->AddFrame(Frame1_HF, new TGLayoutHints(kLHintsCenterX, 5,5,5,5));

  Frame1_HF->AddFrame(Plot_TB = new TGTextButton(Frame1_HF, "Plot", Plot_TB_ID),
		      new TGLayoutHints(kLHintsExpandX, 5,5,5,5));
  Plot_TB->Resize(150,50);
  Plot_TB->ChangeOptions(Plot_TB->GetOptions() | kFixedSize);
  Plot_TB->Connect("Clicked()", "SignalHandler", TheHandler, "HandleTextButtons()");

  Frame1_HF->AddFrame(Exit_TB = new TGTextButton(Frame1_HF, "Exit", Exit_TB_ID),
		      new TGLayoutHints(kLHintsExpandX, 5,5,5,5));
  Exit_TB->Resize(150,50);
  Exit_TB->ChangeOptions(Exit_TB->GetOptions() | kFixedSize);
  Exit_TB->Connect("Clicked()", "SignalHandler", TheHandler, "HandleTextButtons()");
}
