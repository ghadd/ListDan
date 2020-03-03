#ifndef LIST_H
#define LIST_H

#include <QDebug>
#include "node.h"

template<class T>
class List
{
public:
    List<T>();
    List<T>(const List<T>&);
    List<T>(size_t size, T val = 0);
    ~List<T>();

    Node<T> *begin(); //
    Node<T> *end(); //
    size_t size(); //
    T front(); //
    T back(); //
    T at(size_t pos);
    void set_at(T value, size_t pos);
    void push_back(T val);
    void push_front(T val);
    void insert(T val, size_t pos);
    void pop_back();
    void pop_front();
    void erase(size_t pos);
    void clear();
    void swap(size_t first, size_t second);
    bool empty();

    void insertionSort(); // desc // typenames only
    void bubbleSort(); // asc  // typenames only

    double avg(); // typenames only
    void reverse();

    void operator+(T elToPushFront);
    void operator+=(T elToPushBack);
    void operator--(); //prefix
    void operator--(int); //postfix
    T operator[](size_t pos);

private:
    bool sorted(char dir); // typenames only

private:
    Node<T>* _head;
    Node<T>* _tail;
    size_t _size;
};

template<class T>
List<T>::List()
{
    this->_head = nullptr;
    this->_tail = nullptr;
    this->_size = 0;
}

template<class T>
List<T>::List(const List<T> &other)
{
    this->_size = other._size;
    for (Node<T>* it = other._head; it != nullptr; it = it->next()){
        push_back(it->value());
    }
}


template<class T>
List<T>::List(size_t size, T val)
{
    this->_size = size;
    for (unsigned i = 0; i < size; i++){
        push_back(val);
    }
}

template<class T>
List<T>::~List()
{
    for (Node<T>* it = this->end(); it != nullptr; ){
        Node <T>* nxt = it->prev();
        delete it;
        it = nxt;
    }
}

template<class T>
Node<T> *List<T>::begin()
{
    return this->_head;
}

template<class T>
Node<T> *List<T>::end()
{
    return this->_tail;
}

template<class T>
size_t List<T>::size()
{
   return this->_size;
}

template<class T>
T List<T>::front()
{
    return this->begin()->getValue();
}

template<class T>
T List<T>::back()
{
    return this->end()->getValue();
}

template<class T>
T List<T>::at(size_t pos)
{
    Node<T>* it = this->_head;
    for (unsigned i = 0; i < pos; i++){
        it = it->next();
    }
    return it->value();
}

template<class T>
void List<T>::set_at(T value, size_t pos)
{
    Node<T>* it = this->_head;
    for (unsigned i = 0; i < pos; i++){
        it = it->next();
    }
    it->setValue(value);
}

template<class T>
void List<T>::push_back(T val)
{
    insert(val, this->_size);
}

template <class T>
void List<T>::push_front(T val)
{
    insert(val, 0);
}

template<class T>
void List<T>::insert(T val, size_t pos)
{
    if (this->empty()){
        Node<T>* new_init_node = new Node<T>(val);
        this->_head = new_init_node;
        this->_tail = new_init_node;
        this->_size++;
    }
    else if (pos < 0 || pos > this->_size){
        throw(std::out_of_range("Out of list range."));
        return;
    }
    else if (pos == 0){
        Node<T>* new_head_node = new Node<T>(val, this->_head, nullptr);
        this->_head->setPrev(new_head_node);
        this->_head = new_head_node;
        this->_size++;
    }
    else if (pos == this->_size){
        Node<T>* new_tail_node = new Node<T>(val, nullptr, this->_tail);
        this->_tail->setNext(new_tail_node);
        this->_tail = new_tail_node;
        this->_size++;
    }
    else{
        Node<T>* it = this->_head;
        for (unsigned i = 0; i < pos; i++){
            it = it->next();
        }
        Node<T>* new_inf_node = new Node<T>(val, it, it->prev());
        it->prev()->setNext(new_inf_node);
        it->setPrev(new_inf_node);
        this->_size++;
    }
}

template<class T>
void List<T>::pop_back()
{
    erase(this->_size -1);
}

template<class T>
void List<T>::pop_front()
{
    erase(0);
}

template<class T>
void List<T>::erase(size_t pos)
{
    if (this->empty() || pos < 0 || pos >= this->_size){
        throw(std::out_of_range("Out of list range"));
        return;
    }
    else if (this->_size == 1){
        delete this->_head;
        this->_head = nullptr;
        this->_tail = nullptr;
        this->_size--;
    }
    else if (pos == 0){
        this->_head = this->_head->next();
        delete this->_head->prev();
        this->_head->setPrev(nullptr);
        this->_size--;
    }
    else if (pos == this->_size-1){
        this->_tail = this->_tail->prev();
        delete this->_tail->next();
        this->_tail->setNext(nullptr);
        this->_size--;
    }
    else{
        Node<T>* it = this->begin();
        for (unsigned i = 0; i < pos; i++){
            it = it->next();
        }
        it->prev()->setNext(it->next());
        it->next()->setPrev(it->prev());
        delete it;
        this->_size--;
    }
}

template<class T>
void List<T>::clear()
{
    while (this->_head != nullptr || this->_tail != nullptr){
        pop_back();
    }
}

template<class T>
void List<T>::swap(size_t first_index, size_t second_index)
{
    if (first_index < 0 || first_index >= size() || second_index < 0 || second_index >= size()){
        throw(std::out_of_range("Out of list range"));
        return;
    }
    Node<T>* _first;
    Node<T>* _second;
    Node<T>* it = this->_head;

    for (unsigned i = 0; i <= (first_index > second_index ? first_index : second_index); i++){
        if (i == first_index) _first = it;
        if (i == second_index) _second = it;
        it = it->next();
    }

    Node<T>** swapper = new Node<T>*[4];
    swapper[0] = _first->prev();
    swapper[1] = _second->prev();
    swapper[2] = _first->next();
    swapper[3] = _second->next();

    if ((_first->next() == _second && _second->prev() == _first) ||
            (_second->next() == _first && _first->prev() == _second)){
        _first->setPrev(_second);
        _first->setNext(swapper[3]);
        _second->setPrev(swapper[0]);
        _second->setNext(_first);
        if (swapper[0]) swapper[0]->setNext(_second);
        if (swapper[3]) swapper[3]->setPrev(_first);
    }
    else{
        _first->setPrev(swapper[1]);
        _first->setNext(swapper[3]);
        _second->setPrev(swapper[0]);
        _second->setNext(swapper[2]);
        if (swapper[0]) swapper[0]->setNext(_second);
        if (swapper[1]) swapper[1]->setNext(_first);
        if (swapper[2]) swapper[2]->setPrev(_second);
        if (swapper[3]) swapper[3]->setPrev(_first);
    }

    if ((this->_head == _first && this->_tail == _second) ||
            (this->_head == _second && this->_tail == _first)){
        Node<T>* tmp = this->_head;
        this->_head = this->_tail;
        this->_tail = tmp;
        return;
    }

    if (this->_head == _first) this->_head = _second;
    else if (this->_head == _second) this->_head = _first;
    if (this->_tail == _first) this->_tail = _second;
    else if (this->_tail == _second) this->_tail = _first;
}

template<class T>
bool List<T>::empty()
{
    return this->_head == nullptr && this->_tail == nullptr;
}

template<typename T>
void List<T>::insertionSort()
{
    int curr_ind = 0;
    List<T> copy;
    for (Node<T>* it = this->begin(); it != nullptr; it = it->next()){
        copy.push_back(it->value());
    }

    while (!copy.empty()){
        int max_ind = 0;
        for (unsigned i = 0; i < copy.size(); i++){
            if (copy[i] > copy[max_ind]){
                max_ind = i;
            }
        }
        this->set_at(copy[max_ind], curr_ind);
        curr_ind++;
        copy.erase(max_ind);
    }
}

template<typename T>
void List<T>::bubbleSort()
{
    while (!sorted('a')){
        for (unsigned i = 0; i < this->size() - 1; i++){
            if ((*this)[i] > (*this)[i + 1]){
                this->swap(i, i + 1);
            }
        }
    }
}

template<typename T>
double List<T>::avg(){
    if (this->size() == 0) throw(std::exception());
    T sum = 0;
    for (unsigned i = 0; i < this->size(); i++){
        sum += (*this)[i];
    }
    return (double)sum / this->size();
}

template<class T>
void List<T>::reverse()
{
    Node<T>* tmp;
    for (auto it = this->begin(); it != nullptr; it = it->prev()){
        tmp = it->next();
        it->setNext(it->prev());
        it->setPrev(tmp);
    }
    tmp = this->_head;
    this->_head = this->_tail;
    this->_tail = tmp;
}

template<class T>
void List<T>::operator+(T elToPushFront)
{
    push_front(elToPushFront);
}

template<class T>
void List<T>::operator+=(T elToPushBack)
{
    push_back(elToPushBack);
}

template<class T>
void List<T>::operator--()
{
    pop_front();
}

template<class T>
void List<T>::operator--(int)
{
    pop_back();
}

// a for ascending, d for descending
template<typename T>
bool List<T>::sorted(char dir)
{
    if (this->_head == this->_tail) return true;
    for (Node<T>* it = this->_head; it != this->_tail; it = it->next()){
        if (dir == 'a' && it->value() > it->next()->value()) return false;
        if (dir == 'd' && it->value() < it->next()->value()) return false;
    }
    return true;
}

template<class T>
T List<T>::operator[](size_t pos)
{
    return at(pos);
}


#endif // LIST_H
