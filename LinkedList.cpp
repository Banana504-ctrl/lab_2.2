#include "LinkedList.h"

template <class T>
LinkedList<T>::Node::Node(const T& data, Node* prev, Node* next)
    : data(data), prev(prev), next(next) {}

template <class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template <class T>
LinkedList<T>::LinkedList(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    head = nullptr;
    tail = nullptr;
    length = 0;
    
    for (int i = 0; i < count; ++i) {
        Append(items[i]);
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) 
    : head(nullptr), tail(nullptr), length(0) {
    Node* current = other.head;
    while (current != nullptr) {
        Append(current->data);
        current = current->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template <class T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int index) const {
    if (index < 0 || index >= length) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    if (index < length / 2) {
        Node* current = head;
        for (int i = 0; i < index; ++i) current = current->next;
        return current;
    } else {
        Node* current = tail;
        for (int i = length - 1; i > index; --i) current = current->prev;
        return current;
    }
}

template <class T>
T LinkedList<T>::GetFirst() const {
    if (length == 0) throw ErrorCode::EMPTY_CONTAINER;
    return head->data;
}

template <class T>
T LinkedList<T>::GetLast() const {
    if (length == 0) throw ErrorCode::EMPTY_CONTAINER;
    return tail->data;
}

template <class T>
T LinkedList<T>::Get(int index) const {
    return GetNode(index)->data;
}

template <class T>
int LinkedList<T>::GetLength() const {
    return length;
}

template <class T>
void LinkedList<T>::Append(T item) {
    Node* newNode = new Node(item, tail, nullptr);
    
    if (length == 0) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++length;
}

template <class T>
void LinkedList<T>::Prepend(T item) {
    Node* newNode = new Node(item, nullptr, head);
    
    if (length == 0) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        head = newNode;
    }
    ++length;
}

template <class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > length) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    if (index == 0) {
        Prepend(item);
        return;
    }
    
    if (index == length) {
        Append(item);
        return;
    }
    
    Node* nextNode = GetNode(index);
    Node* prevNode = nextNode->prev;
    Node* newNode = new Node(item, prevNode, nextNode);
    
    prevNode->next = newNode;
    nextNode->prev = newNode;
    ++length;
}

template <class T>
LinkedList<T> LinkedList<T>::Concat(LinkedList<T>* list) const {
    if (list == nullptr) throw ErrorCode::CONCAT_NULL_POINTER;
    
    LinkedList<T> result;
    
    Node* current = head;
    while (current != nullptr) {
        result.Append(current->data);
        current = current->next;
    }
    
    current = list->head;
    while (current != nullptr) {
        result.Append(current->data);
        current = current->next;
    }
    
    return result;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this == &other) return *this;
    
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    
    head = tail = nullptr;
    length = 0;
    
    current = other.head;
    while (current != nullptr) {
        Append(current->data);
        current = current->next;
    }
    
    return *this;
}

template <class T>
void LinkedList<T>::Set(int index, T value) {
    GetNode(index)->data = value;
}