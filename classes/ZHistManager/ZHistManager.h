//******************************************************************************
// name: ZHistManager.cc
// date: 06 Jul 14
// auth: Zach Hartwig
// mail: hartwig@psfc.mit.edu
//
// desc: The ZHistManager class is a custom class derived from TObject
//       that provides (at present) an extremely easy way to histogram
//       columnar data in 1D TH1D objets in ROOT. Valid file formats
//       are ASCII data with space/tab separated (the default), CSV
//       separated, or any other with any arbitrary data
//       delimeter. Arbitrary number of columns are supported. The
//       user can define a histogram condition (i.e. only histogram
//       from column X if the value in Column Y of the same line
//       equals some user-specified value) or range (i.e. only
//       histogram from Column X if the value in Column Y of the same
//       line falls within a user specified range). No graphical
//       actions are presently supported; the user can take the
//       returned TH1D and do whatever he/she wants with it
//******************************************************************************

#ifndef __ZHistManager_h__
#define __ZHistManager_h__ 1

#include <TObject.h>
#include <TH1D.h>

#include <string>
#include <fstream>
using namespace std;


class ZHistManager : public TObject
{
public:
  ////////////////////////////////
  // Constructors / destructors //
  ////////////////////////////////

  ZHistManager();
  ZHistManager(string FN, int, double, double, string S=" ");
  ~ZHistManager();


  //////////////////////////////////
  // User-intended action methods //
  //////////////////////////////////

  void OpenFile();
  void CloseFile();
  void LoadData();

  TH1D *FillHistogram(int);
  TH1D *FillHistogramWithCondition(int, int, double);
  TH1D *FillHistogramWithRange(int, int, double, double);


  /////////////////////
  // Set/Get methods //
  /////////////////////

  void SetFileName(string FN) {FileName = FN; OpenFile();}
  string GetFileName() {return FileName;}

  void SetHistBinning(int, double, double);
  void GetHistBinning(int &, double &, double &);

  void SetSeparator(string S) {Separator = S; LoadData();}
  string GetSeparator() {return Separator;}

  TH1D *GetHistogram() {return Hist_H;}
  int GetNumColumns() {return NumColumns;}
  int GetNumLines() {return NumLines;}
	       
  ClassDef(ZHistManager,0);

protected:
  void CreateHistogram();
  bool CheckColumnNumber(int);

	       
private:
  ifstream Input;

  string FileName;
  string Separator;
  int NumColumns, NumLines;

  int NumBins;
  double Min, Max;
  TH1D *Hist_H;
  bool HistExists;

  vector<vector<double> > Data;
};

#endif
