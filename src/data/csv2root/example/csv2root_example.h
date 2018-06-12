/*//////////////////////////////////////////////////
/                 HEADER GUARDS                    /
//////////////////////////////////////////////////*/
#ifndef EXAMPLE_H
#define EXAMPLE_H

/*//////////////////////////////////////////////////
/                INCLUDE HEADERS                   /
//////////////////////////////////////////////////*/

/*
  Should not need more than this in header file
*/

#include <Rtypes.h>
#include <string>

/*//////////////////////////////////////////////////
/                   DATA STRUCT                    /
//////////////////////////////////////////////////*/

/*
  The struct defined here contains the data defined 
  by the CSV file.

  It reprents one row of data.

  One label per struct member.

  Machine independent types are preferred.
*/

struct example_struct {
  std::string name;
  Int_t rating;
  std::string country;
};

/*//////////////////////////////////////////////////
/               CONVERTER CLASS                    /
//////////////////////////////////////////////////*/
class Example{
 public:
  /*
    Three things are to be defined with public protection.

    1. Class constructor

    2. Class converter

    3. Common Ana convert method 
  */
  Example(std::string input);
  ~Example();
  void convert();
 private:
  /*
    Attributes: 
    
    -input_file: CSV file to convert to .root
   
    add any as necessary (not necessary for most cases)
  */
  std::string input_file;

  /*
    Helper methods:

    add any as necessay (not necessary for most cases)
  */

  // void helper_method();
};

#endif /* EXAMPLE_H */
