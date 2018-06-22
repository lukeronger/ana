/*
  This is where auxiliary functions for 
  analysis go. Any custom TSelector class
  functions that have been prototyped in 
  the class.cxx file should be implemented
  here.
 
*/

// Some examples

// method
Int_t mySELECTOR::addtwo(Int_t x){
  return x + 2;
}

// function 
Float_t f(Float_t x){
  return std::pow(x,2) + (4*x) - 8;
}
