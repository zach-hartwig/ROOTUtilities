// name: TemplateClass.hh
// date: 17 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: Template C++ class implementation file for ROOT-based
//       projects. It should be copied/adapted to suite the user's
//       needs. Note that a user's custom C++ class should be
//       inherited from the ROOT master TObject class so that a ROOT
//       dictionary can be generated for the class to ensure
//       compatibility with the ROOT environment

#ifndef __TemplateClass_hh__
#define __TemplateClass_hh__ 1

#include <TObject.h>

class TemplateClass  : public TObject
{
public:
  TemplateClass();
  ~TemplateClass();

  // Register the class with ROOT
  ClassDef(TemplateClass, 0);

private:

};

#endif
