#include <iostream>
#include <string>
#include "csv2root_example.h"

using namespace std;

void exampleMain(const string& input_file){
  /*
    Should only need to create new instance of
    converter class and call conver method
  */
  
  Example e(input_file);
  e.convert();
  return;
}

int main(int argc, char** argv){
  /*
    Get arguments, return 1 if argc != 3
  */
  
  if(argc != 2){
    cout << "Usage: \n\n";
    cout << "./exe [input-file]" << endl;
    return 1;
  }else {
    exampleMain(argv[1]);
    return 0;
  } 
}
