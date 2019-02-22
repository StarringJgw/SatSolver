#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__

#include <memory>

using namespace std;

template<class T>
class Vector {
public:
    typedef T value_type;
    typedef value_type *iterator;    // vector的迭代器就是原生指针
    typedef value_type *pointer;
    typedef value_type &reference;
    typedef size_t size_type;

public:
    Vector() : start(NULL), finish(NULL), end_of_storage(NULL) {
    }

    Vector(size_type n, const value_type &value) {
        start = alloc.allocate(n);
        end_of_storage = finish = start + n;
        uninitialized_fill_n(start, n, value);
    }

    Vector(size_type n) {
        start = alloc.allocate(n);
        end_of_storage = finish = start + n;
        uninitialized_fill_n(start, n, value_type());
    }

    ~Vector() {
        // 顺序调用元素的析构函数
        for (iterator i = start; i != finish; ++i)
            alloc.destroy(i);

        // 销毁分配的空间
        if (start != NULL)
            alloc.deallocate(start, end_of_storage - start);
    }

    iterator begin() const {
        return start;
    }

    iterator end() const {
        return finish;
    }

    size_type size() const {
        return end() - begin();    // 使用接口函数，包裹性更好
    }

    size_type capacity() const {
        return end_of_storage - begin();    // 使用接口函数，包裹性更好
    }

    bool empty() const {
        return begin() == end();
    }

    // 返回的引用可被修改
    reference front() {
        return *(begin());
    }

    // 返回的引用可被修改
    reference back() {
        return *(end() - 1);
    }

    reference operator[](const size_type n) {
        return *(begin() + n);
    }

    const reference operator[](const size_type n) const {
        return *(begin() + n);
    }

    void push_back(const value_type &value) {
        if (finish == end_of_storage)
            reallocate();    // 存储空间已满，则重新分配内存
        alloc.construct(finish, value);
        ++finish;
    }

    void reallocate();

    void pop_back() {
        --finish;
        alloc.destroy(finish);    // 析构最后一个函数，但不释放空间
    }

    // 清除一个元素
    iterator erase(iterator position) {
        if (position + 1 != finish)
            copy(position + 1, finish, position);
        --finish;
        alloc.destroy(finish);
        return position;
    }

    // 清除一段元素
    iterator erase(iterator first, iterator last) {
        if (first < start || last > finish)
            throw std::invalid_argument("Invalid input.");

        copy(last, finish, first);
        int len = last - first;
        while (len--)
            alloc.destroy(--finish);
        return first;
    }

    void clear() {
        erase(begin(), end());
    }

private:
    iterator start;
    iterator finish;
    iterator end_of_storage;

private:
    static std::allocator<value_type> alloc;    // 空间配置器，采用静态属性节省空间
};

template<class Type>
std::allocator<Type> Vector<Type>::alloc;

template<class Type>
void Vector<Type>::reallocate() {
    size_type oldsize = size();
    size_type newsize = 2 * (oldsize == 0 ? 1 : oldsize);

    // 分配新的内存空间
    iterator newstart = alloc.allocate(newsize);
    uninitialized_copy(start, finish, newstart);

    // 顺序调用每个元素的析构函数
    for (iterator i = start; i != finish; ++i)
        alloc.destroy(i);

    // 销毁分配的空间，销毁之前主要检查是否为NULL
    if (start != NULL)
        alloc.deallocate(start, end_of_storage - start);

    // 更新下标
    start = newstart;
    finish = start + oldsize;
    end_of_storage = start + newsize;
}

#endif