mySELECTOR::terminate(){
  /*
    This is where the terminate function
    for the generated TSelector would 
    go. Check ROOT documentation for more
    information.
  */
  outfile->cd();
  DVCS_tree->Write();
  MC_tree->Write();
  outfile->Write();
  outfile->Close();
}
