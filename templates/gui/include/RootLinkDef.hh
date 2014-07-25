// name: RootLinkDef.hh
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: Mandatory header file for ROOT dictionary generation of
//       custom classes. This file is used by the 'rootcint' compiler.

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// Create dictionaries for the custom classes
#pragma link C++ class SignalsHandler+;
#pragma link C++ class InterfaceBuilder+;


#endif
