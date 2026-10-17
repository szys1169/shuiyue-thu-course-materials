#pragma once

template <typename K, typename V> Entry<K, V>* Hashtable<K, V>::get( K k )
   { return ht[probe4Hit( k )]; }
