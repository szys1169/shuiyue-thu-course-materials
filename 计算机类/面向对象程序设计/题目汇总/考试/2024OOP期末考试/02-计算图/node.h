#pragma once

#include "abstract_node.h"

class Node: public AbstractNode {
public:
    float get_val() override;
    void backward(float _grad) override;

    friend Node operator + (const Node &x, const Node &y);
    friend Node operator - (const Node &x, const Node &y);
    friend Node operator * (const Node &x, const Node &y);
    friend Node operator / (const Node &x, const Node &y);
};

Node operator + (const Node &x, const Node &y);
Node operator - (const Node &x, const Node &y);
Node operator * (const Node &x, const Node &y);
Node operator / (const Node &x, const Node &y);
