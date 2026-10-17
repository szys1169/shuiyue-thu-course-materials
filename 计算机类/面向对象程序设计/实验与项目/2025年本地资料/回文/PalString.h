#ifndef PALSTRING_H
#define PALSTRING_H
#include <iostream>
#include <cstring>
class PalString 
{
public:
   char* data_;    //A character array that stores strings

   //TODO [Optional] : define other useful variables

   //TODO: finish the constructor
   PalString(const char* pStr) 
   {
      int len=strlen(pStr);
      data_=new char[2*len+1];
      for(int i=0;i<len;i++)
      {
         data_[i]=pStr[i];
         data_[2*len-i-1]=pStr[i];
      }
      data_[2*len]='\0';
   }

   //TODO: finish the destructor
   ~PalString()
   {
      delete data_;
   }

 	//TODO: finish the function getString
   char * getString()
   {
      int len=strlen(data_);
      char* data2=new char[len+1]; 
      for(int i=0;i<len;i++)
      {
         data2[i]=data_[i];
      }
      data2[len]='\0';
      return data2;
   }

 	//TODO: finish the function changeString
   void changeString(const char* pStr)
   {
      delete data_;
      int len=strlen(pStr);
      data_=new char[2*len+1];
      for(int i=0;i<len;i++)
      {
         data_[i]=pStr[i];
         data_[2*len-i-1]=pStr[i];
      }
      data_[2*len]='\0';
   }
 
 	//TODO: finish the copy constructor
	PalString(const PalString& rhs)
   {
      int len=strlen(rhs.data_);
      data_=new char[len+1];
      for(int i=0;i<len;i++)
      {
         data_[i]=rhs.data_[i];
      }
      data_[len]='\0';
	}

 	//TODO: override the operator <<
   friend std::ostream& operator<<(std::ostream& out,const PalString& a)
   {
      out<<a.data_;
      return out;
   }
};

#endif // #ifndef PALSTRING_H