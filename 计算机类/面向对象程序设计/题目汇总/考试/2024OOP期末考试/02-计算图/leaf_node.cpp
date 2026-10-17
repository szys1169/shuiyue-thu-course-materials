#include "leaf_node.h"

LeafNode::LeafNode(float _val): val(_val), grad(0) {}
LeafNode::~LeafNode() {}
float LeafNode::get_val() {
    return this->val;
}
void LeafNode::set_val(float _val) {
    this->val = _val;
}
float LeafNode::get_grad() {
    return this->grad;
}
void LeafNode::backward(float _grad) {
    this->grad = this->grad + _grad;
}
void LeafNode::clear_grad() {
    this->grad = 0;
}