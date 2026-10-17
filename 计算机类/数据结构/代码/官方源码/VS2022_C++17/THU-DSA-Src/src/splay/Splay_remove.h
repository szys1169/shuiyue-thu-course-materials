#pragma once

template <typename T> bool Splay<T>::remove( const T& e ) {
   search(e); if ( !_root || e != _root->data ) return false; //失败，随即返回（否则，命中节点必已伸展至根）
   BNP<T> L = _root->lc, R = _root->rc; delete _root; _size--; //记下子树L、R后，释放之
   if ( !R ) { if ( _root = L ) _root->parent = nullptr; } //若R空，则L即是余树
   else { //否则
      (_root = R)->parent = nullptr; search( e ); //再次查找必败，但R的最小节点会伸展为_root，且无左孩子
      _root->attachLc( L ); _root->updateHeight(); //故可令L为其左子树
   }       
   return true;
} //remove
