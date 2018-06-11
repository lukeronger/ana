/*//////////////////////////////////////////////////
/                INCLUDE HEADERS                   /
//////////////////////////////////////////////////*/

/*
  Import the necesary header files for your project
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <TFile.h>
#include <TTree.h>

#include "csv2root_example.h"

/*//////////////////////////////////////////////////
/                   CONSTRUCTOR                    /
//////////////////////////////////////////////////*/
Example::Example(std::string input, std::string output_id){
  /* Two standard attributes.
     More should not be necessary,
     but can be added in any case.
  */
  input_file = input;
  id = output_id;
}


/*//////////////////////////////////////////////////
/                   DESTRUCTOR                     /
//////////////////////////////////////////////////*/
Example::~Example(){
  /*
    Optional print statement
  */
  using namespace std;
  cout << "Deleting temporary csv2root object. Converted root file: '" << id << "'" << endl; 
}


/*//////////////////////////////////////////////////
/                      CONVERT                     /
//////////////////////////////////////////////////*/
void Example::convert(){
  /*
    Name output file and create instance of data struct
  */
  std::string output_file = id + ".root";
  example_struct ex;
  
  /*
    Create new TFile and TTree
  */  
  TFile *f = new TFile(output_file.c_str(), "RECREATE");
  TTree *t = new TTree("t", "Generated chess players as an example");

  /*
     Create as many branches as necessary
     
     Refer to the ROOT guide for best practice
     
     In general variables independent from one
     another go on seperate branches, while 
     variables dependent on each other go on 
     the same branch. 
  */
  t->Branch("name", &ex.name); 
  t->Branch("rating", &ex.rating, "rating/I");
  t->Branch("country", &ex.country);
  
  /*
    Variables necesaay for parsing
  */
  std::ifstream ifs;
  std::string ln;
  int lnctr = 0;

  /*
    Open input file
  */
  ifs.open(input_file.c_str());

  /*
    General parsing structure

    Should not need to change until
    the switch statement
  */
  while(getline(ifs, ln)){
    if (lnctr != 0){
      std::stringstream lns;
      lns << ln;
      std::string lb;
      int i = 0;
      while (getline(lns,lb,',')){ // change delimeter if necessary
       
	/*
	  Edit the switch statement to handle filling data
	  
	  Will need one case for each variable
	*/
	switch(i) {
	case 0 :	  
	  ex.name = lb; 
	  break;
	case 1 :
	  ex.rating = std::stoi(lb);
	  break;
	case 2 :
	  ex.country = lb;
	  break;
	}
	i++;
      }
      /*
	Fill branch
      */
      t->Fill();
    }
    lnctr++; // can utilize line counter for other purposes if necessary
  }

  /*
    Print tree
    
    Write out to file
  */
  t->Print();
  f->Write();
}
