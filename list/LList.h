#pragma once

template <class T>
struct Node 
{
    T data;
    Node* next;
};

template <class T>
class LList
{
    private:
        Node<T>* m_head;
        void del();
        void copy(LList<T> const& list);

    public:
        LList();
        ~LList();
        LList(LList<T> const& list);
        LList& operator=(LList<T> const& list);

        T tail() const;    // Peek last element; undefined behaviour if empty
        void push(T data); // Add element at last position
        T pop();           // Remove last element; undefined behaviour if empty

        unsigned size() const;       // Number of elements in the list
        unsigned find(T data) const; // Get the index of first occurrence, else -1

        T head() const; // peek first element
        T shift(); // remove element at first position
        void unshift(T data); // add element at first position
        
        void insertAt(T data, unsigned position);
        T removeAt(unsigned position);

        T getAt(unsigned position) const; // Gets the value of the n-th element (from 0)
        void updateAt(unsigned position); // Updates the value of the n-th element
};
