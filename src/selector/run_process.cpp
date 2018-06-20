#include <stdio.h>
#include <string>
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>

using namespace std;

void run_TSelector(const string& project_name,
		      const string& head_of_chain,
		      const string& tree_name){

  
  string description = project_name + " Chain";
  TChain *ch=new TChain(tree_name.c_str(), description.c_str());
  string chain_name = head_of_chain.substr(0,head_of_chain.find(".root")) + "*.root";
  ch->Add(chain_name.c_str());
  //ch->ls();
  string selector_name = project_name + "Selector.C+";
  ch->Process(selector_name.c_str());
}

int main(int argc, char** argv){
  if(argc != 4) return -1;
  run_TSelector(argv[1],argv[2],argv[3]);
  return 1;
}
