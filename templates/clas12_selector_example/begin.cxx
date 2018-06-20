mySELECTOR::begin(){
  /*
    This is where the begin function
    for the generated TSelector would 
    go. Read the ROOT documentation 
    for more information.
  */

  TString Option = GetOption();
  outfile = new TFile("clas12_neff.root", "RECREATE");

  AddBranches();
  AddMCBranches();

  firstCall = kTRUE;

  Pmass = 0.938272;
  Nmass = 0.93957;
  Dmass = 1.8756;
  LightSpeed = 29.9792458;
  Ebeam = 10.6;
  ElectronBeam.SetXYZT(0,0,Ebeam,Ebeam);
  Target_Vec.SetXYZT(0,0,0,Dmass); 
  PTarget_Vec.SetXYZT(0,0,0,Pmass); 
  NTarget_Vec.SetXYZT(0,0,0,Nmass); 
  
  firstCall = kFALSE;
}
