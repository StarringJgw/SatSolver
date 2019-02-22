#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__

#include <memory>

using namespace std;

template<class T>
class myVector {
private:
    T *start, *end, *storageEnd;
    allocator<T> alloc;

    void reallocate() {
        size_t oldSize = end - start;
        size_t newSize = 2 * oldSize;
        if (newSize == 0)
            newSize = 1;
        auto newSpace = alloc.allocate(newSize);
        uninitialized_copy(start, end, newSpace);
        for (auto i = start; i != end; i++) {
            alloc.destroy(i);
        }
        if (start != NULL)
            alloc.deallocate(start, oldSize);
        start = newSpace;
        end = newSpace + oldSize;
        storageEnd = newSpace + newSize;
    }

public:
    typedef T value_type;
    typedef T *iterator;
    typedef T &reference;

//    typedef T* pointer;
    myVector() : start(NULL), end(NULL), storageEnd(NULL) {
    }

    void push_back(const value_type target) {
        if (end == storageEnd) {
            reallocate();
        }
        alloc.construct(end, target);
        end++;
    }

    const iterator erase(iterator target) {
        copy(target + 1, end, target);
        alloc.destroy(end);
        end--;
        return target - 1;

    }

    const iterator Start() {
        return start;
    }

    const iterator End() {
        return end - 1;
    }

    int Size() {
        return end - start;
    }

    reference operator[](const size_t n) {
        return *(start + n);
    }
};

#endif