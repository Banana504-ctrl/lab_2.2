#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "errors.h"

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& data, Node* prev = nullptr, Node* next = nullptr);
    };
    
    Node* head;
    Node* tail;
    int length;
    
    Node* GetNode(int index) const;

public:
    LinkedList();
    LinkedList(T* items, int count);
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();
    
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    int GetLength() const;
    
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, int index);
    void Set(int index, T value);
    
    LinkedList<T> Concat(LinkedList<T>* list) const;
    
    LinkedList<T>& operator=(const LinkedList<T>& other);
};

#include "LinkedList.cpp"
#endif