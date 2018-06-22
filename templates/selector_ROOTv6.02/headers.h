/*
  This is the only file where headers needed
  in any of the hackable analysis files are
  to be includes. It is crucial this standard
  is followed. Also globals should be defined here.
  It is of note that these headers are included
  in the TSelector header file, not the C file.

  Note the default headers are:
  #include <TROOT.h>
  #include <TChain.h>
  #include <TFile.h>
  #include <TSelector.h>
  #include <TTreeReader.h>
  #include <TTreeReaderValue.h>
  #include <TTreeReaderArray.h>
  #include "Rtypes.h" 
*/

// Examples

// Headers
#include "TH2.h"
#include <iostream>
#include <stack>
#include <math.h>

// Globals
Int_t total;
