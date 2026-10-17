#pragma once

template <typename K, typename V> void UniPrint::p( Entry<K, V>& e ) //词条
{  printf( "-<" ); print( e.key ); printf( ":" ); print( e.value ); printf( ">-" );  }
