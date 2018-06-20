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
#include "TStyle.h"  
#include "TH1.h"
#include "TH2.h"  
#include "TH3.h"
#include "TTree.h"
#include "TString.h"
#include "TVirtualIndex.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <cstdlib>
