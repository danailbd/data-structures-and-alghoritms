#include "queue.h"

#include <iostream>
using namespace std;


template<typename T>
void CQueue<T>::del() 
{
    delete [] m_container;
}

template<typename T>
void CQueue<T>::head(T &result) const
{
    result = m_container[m_front];
}

template<typename T>
void CQueue<T>::copy(CQueue<T> const &Cqueue)
{
    m_size = Cqueue.m_size;
    m_front = Cqueue.m_front;
    m_back = Cqueue.m_back;

    m_container = new T[m_size];

    for (int i = 0; i < m_size; i++)
        m_container[i] = Cqueue.m_container[i];
}

template<typename T>
CQueue<T>::~CQueue()
{
    del();
}

template<typename T>
CQueue<T>::CQueue(CQueue<T> const &Cqueue) 
{
    copy(Cqueue);
}

template<typename T>
CQueue<T> CQueue<T>::operator=(CQueue<T> const &Cqueue)
{
    if (this != &Cqueue)
    {
        del();
        copy(Cqueue);
    }
    return *this;
}

template<typename T>
CQueue<T>::CQueue(unsigned size)
    : m_size(size), m_front(-1), m_back(0)
{
    m_container = new T[m_size];
}

template<typename T>
void CQueue<T>::push(T const &data)
{
    if (full()) {
        cerr << "ERROR: Queue is full";
    } else {
        m_container[m_back] = data;
        m_back = (m_back + 1) % m_size;

        // NOTE: dynamic lenght
        // check whether is in empty state
        if (m_front == -1) 
            m_front = m_back - 1;
    }
}


template<typename T>
unsigned CQueue<T>::length() const
{
    // ugly, only for exercise
    // a better implementation would be to have a counter for the number of items
    // it would be clearer and faster
    if (m_front == -1)
        // empty state
        return 0;
    else if (m_front < m_back)
        return m_back - m_front;
    else
        return m_size - m_front + m_back;
}

template<typename T>
unsigned CQueue<T>::size() const
{
    return m_size;
}

template<typename T>
void CQueue<T>::pop(T &result)
{
    if (empty()) {
        cerr << "ERROR: Queue is empty";
    } else {
        head(result);
        m_front = (m_front + 1) % m_size;

        // dynamic length
        if (m_front == m_back)
            // set in empty
            m_front = -1;
    }
}

template<typename T>
bool CQueue<T>::full() const
{
    return length() == m_size;
}

template<typename T>
bool CQueue<T>::empty() const
{
    return length() == 0;
}

