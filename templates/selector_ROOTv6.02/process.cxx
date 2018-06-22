mySELECTOR::process(){
  /*
    This is where the process function
    for the generated TSelector would 
    go. Check ROOT documentation for
    more information.
  */
   fChain->GetTree()->GetEntry(entry);                                                                                                      
   // CODE HERE

   
   return kTRUE;  
}
