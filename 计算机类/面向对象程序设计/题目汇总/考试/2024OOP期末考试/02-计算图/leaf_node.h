#pragma once
#include "abstract_node.h"

class LeafNode: public AbstractNode {
    float val, grad;
public:
    LeafNode(float _val);
    ~LeafNode();
    float get_val();
    void set_val(float _val);
    float get_grad();
    void backward(float _grad);
    void clear_grad();
};
