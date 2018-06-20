#include <stdio.h>
#include <string>
#include <TTree.h>
#include <TFile.h>

using namespace std;

void create_TSelector(const string& project_name,
		      const string& head_of_chain,
		      const string& tree_name){
  TFile f(head_of_chain.c_str());
  TTree *t; f.GetObject(tree_name.c_str(),t);
  string selector = project_name + "Selector";
  t->MakeSelector(selector.c_str());
}

int main(int argc, char** argv){
  if(argc != 4) return -1;
  create_TSelector(argv[1],argv[2],argv[3]);
  return 1;
}
