#include <iostream>
#include <string>
#include "csv2root_example.h"

using namespace std;

void exampleMain(const string& input_file, const string& file_id){
  /*
    Should only need to create new instance of
    converter class and call conver method
  */
  
  Example e(input_file, file_id);
  e.convert();
  return;
}

int main(int argc, char** argv){
  /*
    Get arguments, return 1 if argc != 3
  */
  
  if(argc != 3){
    cout << "Usage: \n\n";
    cout << "./exe [input-file] [file-id]" << endl;
    return 1;
  }else {
    exampleMain(argv[1],argv[2]);
    return 0;
  } 
}
