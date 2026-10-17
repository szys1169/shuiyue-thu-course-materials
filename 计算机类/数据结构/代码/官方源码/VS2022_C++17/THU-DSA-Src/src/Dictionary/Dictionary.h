#pragma once

template <typename K, typename V> struct Dictionary { //词典Dictionary模板类
   virtual Rank size() const = 0; //当前词条总数
   virtual Entry<K, V>* get( K ) = 0; //读取词条
   virtual Entry<K, V>* put( K, V ) = 0; //插入词条
   virtual bool remove( K ) = 0; //删除词条
};
