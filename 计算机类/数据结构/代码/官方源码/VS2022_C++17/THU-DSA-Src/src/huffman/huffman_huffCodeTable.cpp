/*DSA*/#include "Huffman_PQ.h"

void huffCT( Stack<char>& theseus, HuffTable& table, BNP<HuffChar> v ) {
   if ( IsLeaf( v ) ) { //每遇到一个叶节点，便导出对应的编码串，并添加到编码表中
      Rank n = theseus.size() - 1; Stack<char> sueseht;
      for ( Rank k = 0; k < n; k++ ) sueseht.push( theseus.pop() );
      char* code = new char[n+1]; code[n] = '\0';
      for ( Rank k = 0; k < n; k++ ) theseus.push( code[k] = sueseht.pop() );
      table.put( v->data.ch, code );  /*DSA*/printf( "%c : %s\n", v->data.ch, code );
   } else { //否则，继续递归地遍历
      if ( v->lc ) { theseus.push( '0' ); huffCT( theseus, table, v->lc ); }
      if ( v->rc ) { theseus.push( '1' ); huffCT( theseus, table, v->rc ); }
   } //else
   theseus.pop();
} // huffCT

HuffTable huffCodeTable( HuffTree& tree ) { //由编码树，导出编码表
   HuffTable table; Stack<char> theseus; theseus.push('x');
   huffCT( theseus, table, tree.root() );
   return table;
} //huffCodeTable
