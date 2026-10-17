#ifndef PALSTRING_H
#define PALSTRING_H
#include <iostream>
#include <cstring>
class PalString {
public:
    char* data_;    //A character array that stores strings

    //TODO [Optional] : define other useful variables

    //TODO: finish the constructor
    PalString(const char* pStr) {
    }

    //TODO: finish the destructor
    ~PalString(){
    }

 	//TODO: finish the function getString
    char * getString(){
    }

 	//TODO: finish the function changeString
    void changeString(const char* pStr){
    }
 
 	//TODO: finish the copy constructor
	PalString(const PalString& rhs){
	}

 	//TODO: override the operator <<

};

#endif // #ifndef PALSTRING_H