#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

template<class T>
void CircularArray<T>::push_front(T data) {
    if (is_full()){
        throw("Queue is full");
    }
    else {
        if (front == -1){
            front = 0;
            back = 0;
        }
        else if (front == 0){
            front = capacity - 1;
        }
        else {
            front = prev(front);
        }
        array[front] = data;
    }
}

template<class T>
void CircularArray<T>::push_back(T data) {
    if (is_full()) {
        T* temp = new T[2 * capacity];

        for (int i = 0; i < capacity; i++) {
            temp[i] = array[i];
        }

        delete[] array;
        capacity *= 2;
        array = temp;
    } else {
        if (front == -1) front = 0;
        back = next(back);
        array[back] = data;
    }
}

template<class T>
void CircularArray<T>::insert(T data, int pos) {
    int n = front;
    for (int i = 0; i < pos; i++)
    {
        n = next(n);
    }
    array[n] = data;
}

template<class T>
T CircularArray<T>::pop_front() {
    if (is_empty()){
        throw("Queue is empty");
    }
    else{
        T del = array[front];
        front = next(front);
        return del;
    } 
}

template<class T>
T CircularArray<T>::pop_back() {
    if (is_empty()){
        throw("Queue is empty");
    }
    else{
        T del = array[back];
        back = prev(back);
        return del;
    }
}

template<class T>
bool CircularArray<T>::is_full() {
    return front == next(back) && !is_empty();
}

template<class T>
bool CircularArray<T>::is_empty() {
    return front == -1;
}

template<class T>
int CircularArray<T>::size() {
    if (back >= front)
        return back - front + 1;
    else
        return capacity - (front - back) + 1;
}

template<class T>
void CircularArray<T>::clear() {
    delete[] array;
}

template<class T>
T &CircularArray<T>::operator[](int index) {
    if (index > capacity - 1 || index < 0){
        throw("No element in this position");
    }
    int pos = front;
    for (int i = 0; i < index; i++){
        pos = next(pos);
    }
    return array[pos];
}

template<class T>
void CircularArray<T>::sort() {
    for(int i = front; i != back - 1; i = next(i)){
        int min_index = i;
        for (int j = next(i); j != next(back); j=next(j))
            if (array[j] < array[min_index])
                min_index = j;
        T temp= array[min_index];
        array[min_index]=array[i];
        array[i]= temp;
    }
}

template<class T>
bool CircularArray<T>::is_sorted() {
    if (is_empty()) {
        throw("Array is empty");
        return false;
    }
    if(back > front){
        for (int i = front; i != back ; ++i) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
    }
    else if (front > back) {
        for (int i = front; i != back ; ++i) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
    }
    return true;
}

template<class T>
void CircularArray<T>::reverse() {
    T temp;
    int begin = front;
    int end = back;
    while(begin != end){
        temp = array[begin];
        array[begin] = array[end];
        array[end] = temp;
        begin = next(begin);
        end = prev(end);
    }
}