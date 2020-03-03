#ifndef NODE_H
#define NODE_H


template<class T>
class Node{
public:
    Node<T>();
    Node<T>(T value, Node<T>* nxt = nullptr, Node<T>* prev = nullptr);
    Node<T>* next();
    Node<T>* prev();
    void setNext(Node*);
    void setPrev(Node*);
    T value();
    void setValue(T);

private:
    Node<T>* _next;
    Node<T>* _prev;
    T _value;
};

template <class T>
Node<T>::Node(){
    this->next() = nullptr;
    this->prev() = nullptr;
    this->_value = 0;
}

template <class T>
Node<T>::Node( T value, Node<T>* nxt, Node<T>* prv){
    this->_next = nxt;
    this->_prev = prv;
    this->_value = value;
}

template<class T>
Node<T>* Node<T>::next(){
    return this->_next;
}

template<class T>
Node<T>* Node<T>::prev(){
    return this->_prev;
}

template<class T>
void Node<T>::setNext(Node* nxt){
    this->_next = nxt;
}

template<class T>
void Node<T>::setPrev(Node* prv){
    this->_prev = prv;
}

template<class T>
T Node<T>::value(){
    return this->_value;
}

template<class T>
void Node<T>::setValue(T val){
    this->_value = val;
}


#endif // NODE_H
