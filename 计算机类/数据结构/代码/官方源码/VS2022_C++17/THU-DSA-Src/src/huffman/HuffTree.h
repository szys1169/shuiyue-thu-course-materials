#pragma once

using HuffTree = BinTree<HuffChar>; //Huffman树：由BinTree派生，节点类型为HuffChar
#define Weight(T) ((T).root()->data.weight) //快捷方式：根节点的频数，即子树的权重
