//
// Created by Jgw on 18/2/19.
//

#ifndef TESTC_MYLIST_H
#define TESTC_MYLIST_H

#include <memory>

using namespace std;

template<class T>
class node {
public:
    T data;
    node<T> *next;
    node<T> *pre;

    node() : next(NULL), pre(NULL) {
        data = *(new T);
    }
};

template<class T>
class myList {
private:
    node<T> *start, *end, *blank;
public:
    typedef T value_Type;
    typedef node<T> *iterator;
    typedef T &reference;

    myList() {
        start = new node<T>;
        end = new node<T>;
        blank = new node<T>;
        start->pre = blank;
        start->next = end;
        end->pre = start;
        end->next = blank;
        blank->pre = end;
        blank->next = start;
    }

    void insert(const iterator position, const value_Type target) {
        node<T> *newNode = new node<T>;
        newNode->data = target;
        newNode->pre = position;
        newNode->next = position->next;
        position->next->pre = newNode;
        position->next = newNode;
    }

    void push_back(const value_Type target) {
        insert(end->pre, target);
    }

    const iterator erase(const iterator position) {
        position->pre->next = position->next;
        position->next->pre = position->pre;
        auto temp = position->pre;
        free(position);
        return temp;
    }

    void Clear() {
        if (start->next != end) {
            for (auto p = start->next; p != end;) {
                auto temp = p->next;
                erase(p);
                p = temp;
            }
        }
    }

    const iterator Start() {
        if (start->next == end)
            return NULL;
        return start->next;
    }

    const iterator End() {
        if (start->next == end)
            return NULL;
        return end->pre;
    }
//    const iterator Front(){
//        if(start==end)
//            return NULL;
//    }

    size_t Size() {
        size_t i = 0;
        for (auto p = start->next; p != end; p = p->next) {
            i++;
        }
        return i;
    }

    reference operator[](size_t x) {
        if (x >= Size())
            x = Size();
        auto p = start->next;
        for (int i = 0; i < x; i++) {
            p = p->next;
        }
        return p->data;
    }
};

#endif //TESTC_MYLIST_H
