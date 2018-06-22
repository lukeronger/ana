# Analysis

An analysis directory consists of the following six files. 

```
aux.cxx
begin.cxx
class.cxx
headers.h
process.cxx
terminate.cxx
```

This is the directory where Ana searches to create a TSelector for a project and outputs files after analysis. Its full path should be provided to Ana in its specified argument position.

Simply follow the templates (in the ```templates/``` directory) and ROOT online documentation to get rolling. It should be noted that ```mySELECTOR``` is a keyword that gets updated specific to each project and should not be changed when adding class methods. Moreover anything not labeled an example in the general selector template should not be deleted.

