// name: InterfaceBuilder.cc
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc:

#include "InterfaceBuilder.hh"
#include "SignalsHandler.hh"


InterfaceBuilder::InterfaceBuilder()
  : MainFrameX(1000), MainFrameY(700), 
    CanvasX(950), CanvasY(600)
{
  TheHandler = new SignalsHandler;

  CreateMainFrame();
}


InterfaceBuilder::~InterfaceBuilder()
{
  delete TheHandler;
}


void InterfaceBuilder::CreateMainFrame()
{
  TGVerticalFrame *Frame0_VF = new TGVerticalFrame(this);
  AddFrame(Frame0_VF, new TGLayoutHints(kLHintsCenterX, 5,5,5,5));
  
  Frame0_VF->AddFrame(TheCanvas_EC = new TRootEmbeddedCanvas("TheCanvas_EC", Frame0_VF, CanvasX, CanvasY),
  		      new TGLayoutHints(kLHintsCenterX, 5,5,5,5));
  

  TGHorizontalFrame *Frame1_HF = new TGHorizontalFrame(Frame0_VF);
  Frame0_VF->AddFrame(Frame1_HF, new TGLayoutHints(kLHintsCenterX, 5,5,5,5));

  Frame1_HF->AddFrame(Plot_TB = new TGTextButton(Frame1_HF, "Plot", -1),
		      new TGLayoutHints(kLHintsExpandX, 5,5,5,5));
  Plot_TB->Resize(300,50);
  Plot_TB->ChangeOptions(Plot_TB->GetOptions() | kFixedSize);
  Plot_TB->Connect("Clicked()", "SignalsHandler", TheHandler, "HandleTextButtons()");

  Frame1_HF->AddFrame(Exit_TB = new TGTextButton(Frame1_HF, "Exit", -1),
		      new TGLayoutHints(kLHintsExpandX, 5,5,5,5));
  Exit_TB->Resize(300,50);
  Exit_TB->ChangeOptions(Exit_TB->GetOptions() | kFixedSize);
  Exit_TB->Connect("Clicked()", "SignalsHandler", TheHandler, "HandleTextButtons()");

  SetWindowName("TheMainFrame");
  MapSubwindows();
  Resize(MainFrameX, MainFrameY);
  MapWindow();
}
