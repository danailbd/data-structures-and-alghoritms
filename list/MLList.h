#pragma once

#include <iostream>


/**
 * A minimalistic linked list implementation
 */
template <class T>
class MLList
{
    private:
        template <class L>
        struct Node 
        {
            L data;
            Node<T>* link;

            Node(L _data): data(_data), link(nullptr) {}
        };

    private:
        Node<T>* m_head;      // O(1)
        Node<T>* tailNode();  // O(n)

        void del();           // O(n)
        void copy(MLList<T> const& list);

        Node<T>* getNodeAt(unsigned idx);

    public:
        MLList();
        ~MLList();
        MLList(MLList<T> const& list);
        MLList& operator=(MLList<T> const& list);

        T tail();          // Peek last element; undefined behaviour if empty
        void push(T data); // Add element at last position
        T pop();           // Remove last element; undefined behaviour if empty

        unsigned size() const;       // Number of elements in the list
        unsigned find(T data) const; // Get the index of first occurrence, else -1

        T head() const;       // peek first element
        T shift();            // remove element at first position
        void unshift(T data); // add element at first position
        
        bool insertAt(T data, unsigned position); // inserts node at position; indexed from 0
        bool removeAt(unsigned position);         // remove node at position;  indexed from 0

        T getAt(unsigned position);                   // Gets the value of the n-th element (from 0)
        bool updateAt(T new_data, unsigned position); // Updates the value of the n-th element
};

template <class T>
void printLList(MLList<T> list) {         // O(2n)
    for (int i = list.size(); i > 0; i--)
        std::cout << list.pop() << " ";
}

template <class T>
MLList<T>::MLList(): m_head(nullptr) {}


template <class T>
void MLList<T>::copy(MLList<T> const& list) {
    Node<T>* iterator = list.m_head;
    while(iterator) { // O(n^2) with current implementation
        push(iterator->data); // O(n)
        iterator = iterator->link;
    }
}

template <class T>
MLList<T>::MLList(MLList<T> const& list) {
    copy(list);
}


template <class T>
void MLList<T>::del() {
    Node<T>* iterator;
    while (m_head) {
        iterator = m_head;
        m_head = m_head->link;
        delete iterator;
    }
}

template <class T>
MLList<T>::~MLList() {
    del();
}

template <class T>
MLList<T>::Node<T>* MLList<T>::tailNode() {
    if (!m_head)
        return nullptr;

    Node<T>* iterator = m_head;
    while (iterator->link)
        iterator = iterator->link; 
    return iterator;
}

template <class T>
void MLList<T>::push(T data) {
    Node<T> *last_elem = tailNode(),
            *newElem  = new Node<T>(data);
    
    if (last_elem)
        last_elem->link = newElem;
    else
        m_head = newElem;
}

template <class T>
T MLList<T>::tail() {
    T result = tailNode()->data;
    return result;
}

/**
 * N.B.! Undefined behavior for empty list
 *
 * We want to get the previous of the last item
 * in order to leave the pointers in proper state after the
 * deletetion of the element.
 */
template <class T>
T MLList<T>::pop() {
    // XXX much prettier with ** pointer
    Node<T>* iterator = m_head;
    T result;

    if (!m_head->link) { // single item in the list
        result = m_head->data;
        delete m_head;
        m_head = nullptr;
    } else {
        while (iterator->link->link)
            iterator = iterator->link;

        result = iterator->link->data;
        delete iterator->link;
        iterator->link = nullptr;
    }

    return result; 
}


template <class T>
unsigned MLList<T>::size() const {
    int result = 0;
    Node<T>* iterator = m_head;

    while(iterator) {
        result++;
        iterator = iterator->link;
    }
    return result;
}


template <class T>
unsigned MLList<T>::find(T data) const {
    Node<T>* iterator = m_head;
    int idx = 0;

    while (iterator && iterator->data != data) {
        idx++;
        iterator = iterator->link;
    }

    return iterator ? idx: -1;
}


/**
 * N.B.! undefined behaviour for empty list
 */
template <class T>
T MLList<T>::shift() {
    T result;
    Node<T>* temp = m_head;

    result = m_head->data;
    m_head = m_head->link;
    delete temp;

    return result;
}


template <class T>
void MLList<T>::unshift(T data) {
    Node<T>* new_node = new Node<T>(data);
    new_node->link = m_head; // `m_head` might be NULL

    m_head = new_node;
}

template <class T>
T MLList<T>::head() const {
    return m_head->data;
}

template <class T>
MLList<T>::Node<T>* MLList<T>::getNodeAt(unsigned idx) {
    Node<T>* iterator = m_head;
    while(idx > 0 && iterator) {
        iterator = iterator->link;
        idx--;
    }
    return iterator;
}

/**
 * N.B.! Undefined behavior if index is out of list bounds
 */
template <class T>
T MLList<T>::getAt(unsigned position) {
    return getNodeAt(position)->data;
}


template <class T>
bool MLList<T>::updateAt(T new_data, unsigned position) {
    Node<T> *update_node = getNodeAt(position);
    if (update_node) {
        update_node->data = new_data;
    }

    // ensure boolean is returned
    return !!update_node;
}

template <class T>
bool MLList<T>::insertAt(T data, unsigned position) {
    bool success = false; // a flag
    if (position == 0) {
        unshift(data);
        success = true;
    } else {
        Node<T>* new_node = new Node<T>(data);
        // find where it should be inserted
        Node<T>* prev_node = getNodeAt(position-1);

        if (prev_node) {
            new_node->link = prev_node->link;
            prev_node->link = new_node;

            success = true;
        } 
    }

    // Not enough elements in the list
    return success;
}

template <class T>
bool MLList<T>::removeAt(unsigned position) {
    if (position == 0) {
        // handle undefined behaviour of `shift`
        if (m_head) {
            // list has at least one element
            // could use `size` if it wasn't O(n) in complexity
            shift();
            return true;
        }
        return false;
    }

    // find where it should be removed after
    Node<T>* prev_node = getNodeAt(position-1);
    Node<T>* tmp_node;

    if (prev_node && prev_node->link) {
            tmp_node = prev_node->link->link;
            delete prev_node->link;
            prev_node->link = tmp_node;
        
        return true;
    } 

    // Idx out of list bounds
    return false;
}
