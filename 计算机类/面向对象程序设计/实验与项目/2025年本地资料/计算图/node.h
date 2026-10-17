#pragma once
#include "leaf_node.h"
#include "abstract_node.h"
#include <memory>
using namespace std;

class Node: public AbstractNode {
    // node 指向真正的计算节点，可能是叶子节点，也可能是运算节点。
    std::shared_ptr<AbstractNode> node;
public:
    Node():node(0){};
    Node(float value):node(std::make_shared<LeafNode>(value)){};
    //Node(LeafNode& leaf) : node(&leaf, [](AbstractNode*){}) {}
    // LeafNode 的生命周期由外部管理，这里使用空删除器避免 shared_ptr 释放外部对象。
    Node(const LeafNode& leaf) : node(const_cast<LeafNode*>(&leaf), [](AbstractNode*){}) {}    
    Node(std::shared_ptr<AbstractNode> _ptr):node(_ptr){};
    ~Node(){}
    float get_val() override {return node->get_val();}
    void backward(float _grad) override{node->backward(_grad);}
    friend Node operator + (const Node &x, const Node &y);
    friend Node operator - (const Node &x, const Node &y);
    friend Node operator * (const Node &x, const Node &y);
    friend Node operator / (const Node &x, const Node &y);
};

class OpNode: public AbstractNode
{
    Node x;
    Node y;
    // 用一个字符保存运算类型，代替原来的 addNode/subNode/mulNode/chuNode 四个类。
    char op;
    // 前向计算结果缓存下来，后续 get_val() 直接返回该值。
    float val;
public:
    OpNode(const Node &x1, const Node &y1, char _op):x(x1),y(y1),op(_op)
    {
        // 构造运算节点时完成前向计算。
        switch (op)
        {
            case '+':
                val = x.get_val() + y.get_val();
                break;
            case '-':
                val = x.get_val() - y.get_val();
                break;
            case '*':
                val = x.get_val() * y.get_val();
                break;
            case '/':
                val = x.get_val() / y.get_val();
                break;
            default:
                val = 0;
                break;
        }
    }
    ~OpNode(){};
    float get_val() override
    {
        return val;
    }
    void backward(float _grad) override
    {
        // 根据不同运算符，把当前节点收到的梯度继续传给左右操作数。
        switch (op)
        {
            case '+':
                x.backward(_grad);
                y.backward(_grad);
                break;
            case '-':
                x.backward(_grad);
                y.backward(-_grad);
                break;
            case '*':
                x.backward(_grad * y.get_val());
                y.backward(_grad * x.get_val());
                break;
            case '/':
                x.backward(_grad / y.get_val());
                y.backward(-_grad * x.get_val() / (y.get_val() * y.get_val()));
                break;
        }
    }
};

/*
原来的实现：每一种二元运算都单独定义一个节点类。

class addNode:public AbstractNode
{
    Node x;
    Node y;
    float val;
    public:
    addNode(const Node &x1, const Node &y1):x(x1),y(y1)
    {
        val=x.get_val()+y.get_val();
    }
    ~addNode(){};
    float get_val() override
    {
        return val;
    }
    void backward(float _grad) override
    {
        x.backward(_grad);
        y.backward(_grad);
    }
};

class subNode:public AbstractNode
{
    Node x;
    Node y;
    float val;
    public:
    subNode(const Node &x1, const Node &y1):x(x1),y(y1)
    {
        val=x.get_val()-y.get_val();
    }
    ~subNode(){};
    float get_val() override
    {
        return val;
    }
    void backward(float _grad) override
    {
        x.backward(_grad);
        y.backward(-_grad);
    }
};

class mulNode:public AbstractNode
{
    Node x;
    Node y;
    float val;
    public:
    mulNode(const Node &x1, const Node &y1):x(x1),y(y1)
    {
        val=x.get_val()*y.get_val();
    }
    ~mulNode(){};
    float get_val() override
    {
        return val;
    }
    void backward(float _grad) override
    {
        x.backward(_grad*y.get_val());
        y.backward(_grad*x.get_val());
    }
};

class chuNode:public AbstractNode
{
    Node x;
    Node y;
    float val;
    public:
    chuNode(const Node &x1, const Node &y1):x(x1),y(y1)
    {
        val=x.get_val()/y.get_val();
    }
    ~chuNode(){};
    float get_val() override
    {
        return val;
    }
    void backward(float _grad) override
    {
        x.backward(_grad/y.get_val());
        y.backward(-_grad*x.get_val()/(y.get_val()*y.get_val()));
    }
};
*/

inline Node operator+(const Node& x, const Node& y) {
    // LeafNode 可以通过 Node(const LeafNode&) 自动转换成 Node，两类运算统一走这里。
    return Node(std::make_shared<OpNode>(x, y, '+'));
}

inline Node operator-(const Node& x, const Node& y) {
    return Node(std::make_shared<OpNode>(x, y, '-'));
}

inline Node operator*(const Node& x, const Node& y) {
    return Node(std::make_shared<OpNode>(x, y, '*'));
}

inline Node operator/(const Node& x, const Node& y) {
    return Node(std::make_shared<OpNode>(x, y, '/'));
}
