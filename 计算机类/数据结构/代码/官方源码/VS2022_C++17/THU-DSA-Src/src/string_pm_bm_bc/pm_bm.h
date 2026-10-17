#pragma once

//Boyer-Moore算法
void ShowProgress( String, String,  int,  int );
#define  CARD_CHAR_SET     256   //Cardinality of charactor set
int*     BuildBC( String ); //构造Bad Charactor Shift表
int*     suffixes( String );
int*     BuildGS( String ); //构造Good Suffix Shift表
