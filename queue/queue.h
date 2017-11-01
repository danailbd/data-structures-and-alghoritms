#pragma once

// something power of 2
const unsigned DEFAULT_SIZE = 16; 

template <typename T>
// circular queue
class CQueue {
    private:
        T* m_container;
        int m_front, m_back;
        unsigned m_size;

        void copy(CQueue<T> const &Cqueue);
        void del();

    public:
        CQueue(unsigned size=DEFAULT_SIZE);
        ~CQueue();
        CQueue(CQueue<T> const &Cqueue);
        CQueue<T> operator=(CQueue<T> const &Cqueue);

        void pop(T& result);
        void head(T& result) const;
        void push(T const &data);
        bool empty() const;
        bool full() const;

        // number of items currently in the CQueue
        unsigned length() const;
        unsigned size() const;
};


template class CQueue<int>;
