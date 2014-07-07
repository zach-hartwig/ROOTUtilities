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

// C++
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
using namespace std;

// Boost (Must be protected from ROOT's CINT interpreter)
#ifndef __CINT__          
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
using namespace boost;
#endif

#include "ZHistManager.h"


// Constructor 0 : After calling, the user is responsible for opening
// a file, loading the data, and creating the TH1D histogram object
// before attempting to fill the histogram with data.
ZHistManager::ZHistManager()
  : FileName(""), Separator(" "), NumColumns(0), NumLines(0),
    NumBins(100), Min(-5.), Max(5.),
    Hist_H(new TH1D), HistExists(false)
{;}


// Constructor 1 (Preferred) : The user specifies constructor
// arguments to streamline data loading. The arguments are:
//
//  FN (mandatory) = Path to file name (relative or absolute)
//  NB (mandatory) = Number of bins in the histogram
//   m (mandatory) = Minimum bin center value of the histogram
//   M (mandatory) = Maximum bin center value of the histogram
//   S (optional)  = Data delimiter. The default is " "
ZHistManager::ZHistManager(string FN, int NB, double m, double M, string S)
  : FileName(FN), Separator(S), NumColumns(0), NumLines(0),
    NumBins(NB), Min(m), Max(M),
    Hist_H(new TH1D), HistExists(false)
{
  OpenFile();
  LoadData();
  CreateHistogram();
}


ZHistManager::~ZHistManager()
{
  if(Input.is_open())
    Input.close();

  if(HistExists)
    delete Hist_H;
}


void ZHistManager::OpenFile()
{
  Input.open(FileName.c_str());
  if(!Input.good()){
    cout << "\nError! The file '" << FileName << "' could not be opened!\n" 
	 << "         use ZHistManager::SetFileName() to try again.\n" 
	 << endl;

    Input.close();
  }
}


void ZHistManager::CloseFile()
{
  if(Input.is_open())
    Input.close();
}


void ZHistManager::LoadData()
{
  if(!Input.is_open()){
    cout << "\nError! There is no file presently open for reading!\n"
	 << endl;
    
    return;
  }

  // Ensure Input is pointing to the top of the file
  Input.clear();
  Input.seekg(0, ios::beg);

  string Line;
  
  // Create the separator to use with Boost::Tokenizer
  char_separator<char> Sep(Separator.c_str());

  // Create typedef for utility
  typedef tokenizer<char_separator<char> > TokSep;

  // Get the first line and use it to determine number of columns
  getline(Input, Line);
  TokSep Tokenize0(Line, Sep);
  NumColumns = distance(Tokenize0.begin(), Tokenize0.end());

  // Initialize a vector of vectors with the right number of columns
  vector<double> Init;
  for(int i=0; i<NumColumns; i++)
    Data.push_back(Init);

  // Return Input to the top of the file
  Input.clear();
  Input.seekg(0, ios::beg);

  NumLines = 0;

  while(Input.good()){

    getline(Input, Line);

    if(Input.eof())
      break;

    // Use Boost::Tokenize to separate the line with the specified
    // data delimeter and then iterate over the tokens, pushing them
    // into the vector of vectors that holds columnar data.

    TokSep Tokenize1(Line, Sep);
    
    TokSep::iterator it = Tokenize1.begin();

    int Idx = 0;
    for(; it!=Tokenize1.end(); it++){
      Data[Idx].push_back( atof((*it).c_str()) );
      Idx++;
    }

    NumLines++;
  }
}


TH1D *ZHistManager::FillHistogram(int Column)
{
  if(CheckColumnNumber(Column)){
    if(HistExists)
      CreateHistogram();
    
    vector<double>::iterator it = Data[Column].begin();
    for(; it!=Data[Column].end(); it++)
      Hist_H->Fill((*it));

    return Hist_H;
  }
  else
    return 0;
}


TH1D *ZHistManager::FillHistogramWithCondition(int FColumn, 
					       int CColumn,
					       double CValue)
{
  if(CheckColumnNumber(FColumn) and CheckColumnNumber(CColumn)){
    if(HistExists)
      CreateHistogram();
    
    vector<double>::iterator it = Data[FColumn].begin();
    for(; it!=Data[FColumn].end(); it++)
      if(Data[CColumn][it - Data[FColumn].begin()] == CValue)
	Hist_H->Fill((*it));
    
    return Hist_H;
  }
  else
    return 0;
}


TH1D *ZHistManager::FillHistogramWithRange(int FColumn, 
					   int RColumn,
					   double RMin,
					   double RMax)
{
  if(CheckColumnNumber(FColumn) and CheckColumnNumber(RColumn)){
    if(HistExists)
      CreateHistogram();
    
    vector<double>::iterator it = Data[FColumn].begin();
    for(; it!=Data[FColumn].end(); it++){
      int Idx = it - Data[FColumn].begin();
      
      if((Data[RColumn][Idx] < RMax) and (Data[RColumn][Idx] > RMin))
	Hist_H->Fill((*it));
    }
    return Hist_H;
  }
  else
    return 0;
}


void ZHistManager::SetHistBinning(int NB, double m, double M)
{
  NumBins = NB;
  Min = m;
  Max = M;

  CreateHistogram();
}


void ZHistManager::GetHistBinning(int &NB, double &m, double &M)
{
  NB = NumBins;
  m = Min;
  M = Max;
}


bool ZHistManager::CheckColumnNumber(int ColumnNumber)
{
  if(ColumnNumber+1 > NumColumns){
    cout << "\nError! Specified column is greater than total columns in file!\n"
	 <<   "       Try again, remembering that column number starts at 0\n"
	 << endl;

    return false;
  }
  else
    return true;
}


void ZHistManager::CreateHistogram()
{
  if(HistExists)
    delete Hist_H;
  
  Hist_H = new TH1D("Hist_H", "Hist_H", NumBins, Min, Max);

  HistExists = true;
}
