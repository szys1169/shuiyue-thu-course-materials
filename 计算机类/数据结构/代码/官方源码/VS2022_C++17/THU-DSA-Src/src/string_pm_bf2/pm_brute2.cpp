/*DSA*/#include <cstdio>
#include <cstring>
/*DSA*/void showProgress( char*, char*, int, int );

/******************************************************************************************
 * Text     :  0   1   2   .   .   .   i   i+1 .   .   .   i+j .   .   n-1
 *             ------------------------|-------------------|------------
 * Pattern  :                          0   1   .   .   .   j   .   .
 *                                     |-------------------|
 ******************************************************************************************/
int match( char* P, char* T ) { //串匹配算法（Brute-Force-2）
   int n = strlen( T ), i = 0;
   int m = strlen( P ), j = 0;
   while ( (j < m) && (i <= n-m) ) //自左向右逐个比对字符
      /*DSA*/{showProgress( T, P, i, j );
      if (T[i + j] == P[j]) //若匹配
         j++; //则转到下一对字符
      else //否则
         { i++; j = 0; } //文本串回退、模式串复位
      /*DSA*/}
   /*DSA*/if (i > n-m) showProgress( T, P, i, j ); //last failure
   return i; //如何通过返回值，判断匹配结果？
}
