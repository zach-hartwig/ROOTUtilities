// name: InterfaceEnumerators.hh
// date: 25 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: This header provides global enumerators that are used to
//       uniquely assign/identify widgets. This is a clean way to
//       ensure that signals generated by widgets are caught by the
//       corresponding slot, which must be a one-to-one relationship.
#ifndef __InterfaceEnumerators_hh__
#define __InterfaceEnumerators_hh__ 1

enum{
  Plot_TB_ID,
  Exit_TB_ID
};

#endif