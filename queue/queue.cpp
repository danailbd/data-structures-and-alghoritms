#include <iostream>
#include "queue.hpp"
using namespace std;


template<typename T>
void CQueue<T>::del() 
{
    delete [] m_container;
}

template<typename T>
void CQueue<T>::head(T &result) const
{
    result = m_container[m_front + 1];
}

template<typename T>
void CQueue<T>::copy(CQueue<T> const &Cqueue)
{
    m_size = Cqueue.m_size;
    m_front = Cqueue.m_front;
    m_back = Cqueue.m_back;

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
CQueue<T>::CQueue(unsigned size):
{
    // TODO
}

template<typename T>
bool CQueue<T>::empty() const
{
    // TODO
    return false;
}

template<typename T>
void CQueue<T>::push(T const &data)
{
    // TODO
}


template<typename T>
unsigned CQueue<T>::length() const
{
    // TODO
    return 0;
}

template<typename T>
void CQueue<T>::pop(T &result)
{
    // TODO
}

template<typename T>
bool CQueue<T>::full() const
{
    // TODO
    return false;
}
