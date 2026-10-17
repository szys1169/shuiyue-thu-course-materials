#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>
#include <stack>

template<class T>
class Data
{
protected:
    int length;
public:
    Data(int _length) : length(_length) {}
    int get_length() const
    {
        return length;
    }
    virtual const T& get(int index) const = 0;
    virtual std::shared_ptr<Data<T>> parent() const = 0;
    enum class OpType { PushBack, Set };
    struct Operation {
        OpType type;
        int index;
        T value;
    };
    virtual Operation get_operation() const = 0;
    virtual ~Data() = default; // 添加虚析构函数
};

template<class T>
class DataEmpty : public Data<T>
{
public:
    DataEmpty() : Data<T>(0) {} // 修正构造函数
    const T& get(int index) const override {
        assert(0 && "Index out of bounds");
        static T dummy; // 必须返回一个有效值，避免未定义行为
        return dummy;
    }
    std::shared_ptr<Data<T>> parent() const override {
        return nullptr;
    }
    typename Data<T>::Operation get_operation() const override {
        return {Data<T>::OpType::PushBack, -1, T()};
    }
};

template<class T>
class DataPushBackDecorator : public Data<T>
{
    std::shared_ptr<Data<T>> parent_data;
    T value;
public:
    DataPushBackDecorator(std::shared_ptr<Data<T>> parent, const T& val)
        : Data<T>(parent->get_length() + 1), parent_data(parent), value(val) {}
    const T& get(int index) const override {
        if (index == parent_data->get_length()) {
            return value;
        }
        return parent_data->get(index);
    }
    std::shared_ptr<Data<T>> parent() const override {
        return parent_data;
    }
    typename Data<T>::Operation get_operation() const override {
        return {Data<T>::OpType::PushBack, parent_data->get_length(), value};
    }
};

template<class T>
class DataSetDecorator : public Data<T>
{
    std::shared_ptr<Data<T>> parent_data;
    int set_index;
    T value;
public:
    DataSetDecorator(std::shared_ptr<Data<T>> parent, int index, const T& val)
        : Data<T>(parent->get_length()), parent_data(parent), set_index(index), value(val) {
        assert(index >= 0 && index < parent->get_length());
    }
    const T& get(int index) const override {
        if (index == set_index) {
            return value;
        }
        return parent_data->get(index);
    }
    std::shared_ptr<Data<T>> parent() const override {
        return parent_data;
    }
    typename Data<T>::Operation get_operation() const override {
        return {Data<T>::OpType::Set, set_index, value};
    }
};


template<class T>
class PVector
{
public:
    std::shared_ptr<Data<T>> data;

    PVector() : data(std::make_shared<DataEmpty<T>>()) {}
    explicit PVector(std::shared_ptr<Data<T>> _data) : data(_data) {}

    PVector<T> push_back(const T &value) const {
        return PVector<T>(std::make_shared<DataPushBackDecorator<T>>(data, value));
    }

    PVector<T> set(int index, const T &value) const {
        return PVector<T>(std::make_shared<DataSetDecorator<T>>(data, index, value));
    }

    PVector<T> undo() const {
        auto parent_data = data->parent();
        if (!parent_data) {
            std::cout << "cannot undo" << std::endl;
            return *this;
        }
        return PVector<T>(parent_data);
    }

    std::vector<typename Data<T>::Operation> get_operations(std::shared_ptr<Data<T>> ancestor) const {
        std::vector<typename Data<T>::Operation> ops;
        auto current = data;
        // 修正循环条件：检查 current 是否为 ancestor，而非仅检查 parent
        while (current != ancestor && current) {
            ops.push_back(current->get_operation());
            current = current->parent(); // 通过 parent() 函数获取父节点
        }
        std::reverse(ops.begin(), ops.end()); // 保证操作顺序正确
        return ops;
    }

    std::shared_ptr<Data<T>> find_common_ancestor(std::shared_ptr<Data<T>> a, std::shared_ptr<Data<T>> b) const {
        std::unordered_set<std::shared_ptr<Data<T>>> ancestors;
        // 收集 a 的所有祖先
        auto curr = a;
        while (curr) {
            ancestors.insert(curr);
            curr = curr->parent();
        }
        // 查找 b 的祖先中第一个存在于集合中的节点
        curr = b;
        while (curr) {
            if (ancestors.count(curr)) {
                return curr;
            }
            curr = curr->parent();
        }
        return nullptr; // 无公共祖先时返回空
    }

    PVector<T> update(const PVector<T>& other) const {
        auto common = find_common_ancestor(data, other.data);
        if (!common) {
            std::cout << "cannot update: no common ancestor found " << std::endl;
            return *this;
        }

        // 获取当前对象和 other 从公共祖先开始的操作
        auto this_ops = get_operations(common);
        auto other_ops = other.get_operations(common);

        bool has_push_this = false, has_push_other = false;
        std::unordered_set<int> this_set, other_set;

        // 分析当前对象的操作
        for (const auto& op : this_ops) {
            if (op.type == Data<T>::OpType::PushBack) {
                has_push_this = true;
            } else if (op.type == Data<T>::OpType::Set) {
                this_set.insert(op.index);
            }
        }

        // 分析 other 的操作
        for (const auto& op : other_ops) {
            if (op.type == Data<T>::OpType::PushBack) {
                has_push_other = true;
            } else if (op.type == Data<T>::OpType::Set) {
                other_set.insert(op.index);
            }
        }

        // 检查冲突：同时有 PushBack 或 Set 操作索引冲突
        if ((has_push_this && has_push_other) || 
            !std::all_of(this_set.begin(), this_set.end(), [&](int idx) {
                return !other_set.count(idx);
            })) {
            std::cout << "cannot update: conflicts found " << std::endl;
            return *this;
        }

        // 从公共祖先开始合并 other 的操作，确保父链正确
        auto merged = common; // 从公共祖先开始应用操作
        for (const auto& op : other_ops) {
            if (op.type == Data<T>::OpType::PushBack) {
                merged = std::make_shared<DataPushBackDecorator<T>>(merged, op.value);
            } else {
                merged = std::make_shared<DataSetDecorator<T>>(merged, op.index, op.value);
            }
        }
        return PVector<T>(merged);
    }

    const T& operator[](int index) const {
        assert(index >= 0 && index < data->get_length());
        return data->get(index);
    }

    friend std::ostream& operator<<(std::ostream& out, const PVector<T>& p) {
        out << "[";
        for (int i = 0; i < p.data->get_length(); ++i) {
            if (i > 0) out << ", ";
            out << p.data->get(i);
        }
        out << "]";
        return out;
    }
};