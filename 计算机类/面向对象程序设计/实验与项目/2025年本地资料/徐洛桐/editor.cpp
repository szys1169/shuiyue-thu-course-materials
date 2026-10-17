#include"editor.h"
#include<iostream>
#include<algorithm>
#include<utility>
#include<cstring>
using namespace std;


void TextEditor::move(Position dest){
  maxrow=data.size()-1;
  for(auto t=0;t<data.size();t++){
  int a=data[t].length();
  maxcol=max(maxcol,a);
  }
  pt.first=max(maxrow,dest.first);
  pt.second=max(maxcol,dest.second);
}


void TextEditor::write(const std::string &str){
    data[pt.first].insert(pt.second,str);
    pt.second+=str.size();
    version++;
    li.push_back(data);
}

void TextEditor::newline(){
    string b="";string a="";
    string example=data[pt.first];
    for(int i=0;i<pt.second;i++){
        a.push_back(example[i]);
    }
    for(int i=pt.second;i<example.length();i++){
        b.push_back(example[i]);
    }
    data.insert(data.begin()+pt.first,b);
    data[pt.first]=a;
    pt.first+=1;
    pt.second=0;
    version++;
    li.push_back(data);
}

void TextEditor::del(){
    if(pt.second==0){
        if(pt.first==0){
            version++;
            li.push_back(data);
            return;}
        int a=data[pt.first-1].length();
        data[pt.first-1]+=data[pt.first];
        data.erase(data.begin()+pt.first);
        pt.first-=1;
        pt.second=a-1;
        version++;
       li.push_back(data);
        return;
    }
    string a=data[pt.first];
    string b="";
    for(int i=0;i<pt.second;i++){
        b+=a[i];
    }
     for(int i=pt.second;i<a.length();i++){
        b+=a[i];
    }
    data[pt.first]=b;
    pt.second--;
    version++;
    li.push_back(data);
}

void TextEditor::screenshot(){
cout<<"### SCREENSHOT BEGIN ###"<<endl;
int row=0;
int col=0;
for(auto i=data.begin();i<data.end();i++){
   
  if(row==pt.first){
    string a=data[pt.first];
    a.insert(a.begin()+pt.second,'*');
    cout<<a<<endl; 
    row++;
    continue;
  }
  else{
    cout<<data[row]<<endl;
    row++;
  }
}
cout<<"### SCREENSHOT END ###"<<endl;

}

 
void TextEditor::undo(){
    auto it=prev(li.end(),2);
    data=*it;
     version++;
    li.push_back(data);
 }
 

