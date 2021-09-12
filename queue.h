#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
    public:
    void push(T data){
        this->push_back(data);
    }
    T pop(){
        T elem = this->pop_front();
        return elem;
    }
};