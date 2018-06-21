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
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TSelector.h>
#include <TH2.h>
#include <TH1.h>
#include <string.h>
#include <string>
#include <math.h>
#include <TVirtualIndex.h>
#include <iostream>             // std::cout, std::endl
#include <fstream>              // std::ifstream
#include <sstream>   
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <cstdlib>
#include <map>
// Header file for the classes stored in the TTree if any.
#include <vector>
