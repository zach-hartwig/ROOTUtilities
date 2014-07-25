// name: SignalsHandler.hh
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: 
#ifndef __SignalsHandler_hh__
#define __SignalsHandler_hh__ 1

#include <TObject.h>

class SignalsHandler : public TObject
{
public:
  SignalsHandler();
  ~SignalsHandler();
  
  // Register the class with ROOT
  ClassDef(SignalsHandler, 0);
  
private:
};

#endif
