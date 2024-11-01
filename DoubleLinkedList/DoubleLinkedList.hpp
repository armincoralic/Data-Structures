#pragma once

#include <cstddef>
#include <functional>

template <typename T> struct Node {
  Node *prev{nullptr};
  Node *next{nullptr};
  T data;
  Node(const T &element) : data{element}, next{nullptr}, prev{nullptr} {}
  Node():prev{nullptr}, next{nullptr}, data{0}{};
};

template <typename T> class DoubleLinkedList {
public:
  class Iterator;
  DoubleLinkedList();
  DoubleLinkedList(const DoubleLinkedList &);
  DoubleLinkedList(DoubleLinkedList &&);
  DoubleLinkedList &operator=(const DoubleLinkedList &);
  DoubleLinkedList &operator=(DoubleLinkedList &&);
  ~DoubleLinkedList();

  DoubleLinkedList &push_back(const T &);
  DoubleLinkedList &push_front(const T &);
  DoubleLinkedList &push_back(T &&);
  DoubleLinkedList &push_front(T &&);
  DoubleLinkedList &pop_front();
  DoubleLinkedList &pop_back();
  bool empty() const;
  size_t size() const;
  T &front();
  T &back();
  Iterator begin() const;
  Iterator end() const;
  const Iterator cbegin() const;
  const Iterator cend() const;
  Iterator rbegin() const;
  Iterator rend() const;
  const Iterator rcbegin() const;
  const Iterator rcend() const;
  void clear();
  Iterator insert(Iterator pos, const T &element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);
  void remove_if(std::function<bool(const T &)> &&p);
  void reverse();
  Iterator find(const T &element) const;

private:
  void dealoc();
  Node<T> *head_{nullptr};
  Node<T> *tail_{nullptr};
  size_t size_{0};
};
template <typename T>
class DoubleLinkedList<T>::Iterator:public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
  Iterator():ptr_{nullptr}{};
  Iterator(Node<T>* node):ptr_{node}{};
  Iterator(const Iterator& it){
    ptr_=it.ptr_;
  };
  Iterator& operator=(const Iterator& it){
    if(this!=&it){ptr_=it.ptr_;}
    return *this;
  };
  Iterator(Iterator&& it){
    ptr_=it.ptr_;
    it.ptr_=nullptr;
  };
  Iterator& operator=(Iterator&& it){
    ptr_=it.ptr_;
    it.ptr_=nullptr;
    return *this;
  };
  Iterator& operator++(){
    if(ptr_){ptr_=ptr_->next;};
    return *this;
  };
  Iterator operator++(int){
    Iterator tmp(*this);
    ++(*this);
    return tmp;
  };
  Iterator& operator--(){
    ptr_=ptr_->prev;
    return *this;
  };
  Iterator operator--(int){
    Iterator tmp(*this);
    --(*this);
    return tmp;
  };
  bool operator==(const Iterator& it) const{
    return ptr_==it.ptr_;
  };
  bool operator!=(const Iterator& it) const{
    return ptr_!=it.ptr_;
  };
  T* operator->() const{
    return &(ptr_->data);
  };
  T& operator*() const{
    return ptr_->data;
  };
  Node<T>* node() const{return ptr_;};

private:
  Node<T>* ptr_;
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList():head_{nullptr}, tail_{nullptr}, size_{0}{};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& lst){
  Node<T>* temp=lst.head_;
  while(temp){
    push_back(temp->data);
    temp=temp->next;
  }
};
template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& lista){
  Node<T>* temp=lista.head_;
  while(temp){
    push_back(temp->data);
    temp=temp->next;
  }
  lista.head_=nullptr;
  lista.tail_=nullptr;
  lista.size_=0;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& lista){
  if(this!=&lista){
    clear();
    Node<T>* temp=lista.head_;
    while(temp){
      push_back(temp->data);
      temp=temp->next;
    }
  }
  return *this;
};
  
template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& lista){
  if(this!=&lista){
    clear();
    Node<T>* temp=lista.head_;
    while(temp){
      push_back(temp->data);
      temp=temp->next;
    }
  }
  lista.head_=nullptr;
  lista.tail_=nullptr;
  lista.size_=0;
  return *this;
};

template<typename T>  
DoubleLinkedList<T>::~DoubleLinkedList(){
  Node<T>* tmp=head_;
  while(tmp!=nullptr){
    Node<T>* tmp2=tmp->next;
    delete tmp;
    tmp=tmp2;
  }
  head_=nullptr;
  tail_=nullptr;
  size_=0;
};

template<typename T>
bool DoubleLinkedList<T>::empty() const{return size_==0;};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(const T &el){
  Node<T>* novi=new Node<T>{el};
  if(empty()){
    head_=tail_=novi;
  }
  else{
  tail_->next=novi;
  novi->next=nullptr;
  novi->prev=tail_;
  tail_=novi;}
  size_++;
  return *this;
};
//  DoubleLinkedList &push_front(const T &);
// template<typename T>
template<typename T> 
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(T && el){
  Node<T>* novi=new Node<T>{el};
  if(empty()){
    head_=tail_=novi;
  }
  else{
  tail_->next=novi;
  novi->next=nullptr;
  novi->prev=tail_;
  tail_=novi;}

  size_++;
  return *this;
};

template<typename T>
T& DoubleLinkedList<T>::front(){
  if(empty()){
    throw std::out_of_range("prazna lista");
  }
  return head_->data;
}

template<typename T>
T& DoubleLinkedList<T>::back(){
  if(empty()){
    throw std::out_of_range("prazna lista");
  }
  return tail_->data;
  }

template<typename T>
size_t DoubleLinkedList<T>::size() const{
  return size_;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(const T & element){
  Node<T>* novi=new Node<T>{element};
  if(empty()){
    head_=tail_=novi;
  }
  else{
    head_->prev=novi;
    novi->next=head_;
    novi->prev=nullptr;
    head_=novi;
  }
  size_++;
  return *this;
};
template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(T&& element){
  Node<T>* novi=new Node<T>{element};
  if(empty()){
    head_=tail_=novi;
  }
  else{
    head_->prev=novi;
    novi->next=head_;
    novi->prev=nullptr;
    head_=novi;
  }
  size_++;
  return *this;
};
template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front(){
  if(empty()){
    throw std::out_of_range("prazna lista");
  }
  Node<T>* tmp=head_;
  head_=head_->next;
  if(head_){
    head_->prev=nullptr;
  }
  else{
    tail_=nullptr;
  }
  delete tmp;
  size_--;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back(){
  if(empty()){
    throw std::out_of_range("lista prazna");
  }
  Node<T>* temp=tail_;
  tail_=tail_->prev;
  if(tail_){
    tail_->next=nullptr;
  }
  else{
    head_=nullptr;
  }
  delete temp;
  size_--;
  return *this;
}

template<typename T>
void DoubleLinkedList<T>::clear(){
  while(head_){
    Node<T>* temp=head_;
    head_=head_->next;
    delete temp;
  }
  size_=0;
  tail_=nullptr;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const{ 
  return Iterator{head_};
};
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const{ 
  return Iterator{nullptr};
};

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cbegin() const{
  return Iterator{head_};
};

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cend() const{
  return Iterator{nullptr};
};
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rbegin() const{
  return Iterator{tail_};
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rend() const{
  return Iterator{nullptr};
};

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcbegin() const{
  return Iterator{tail_};
};

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcend() const{
  return Iterator{nullptr};
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(Iterator pos, const T &element){
  Node<T>* novi=new Node<T>{element};
  if(empty()){
    push_back(element);
    return Iterator(tail_);
  }
  Node<T>* current=pos.node();
  Node<T>* prv=current->prev;

  novi->next=current;
  novi->prev=prv;

  if(prv!=nullptr){
    prv->next=novi;
  }
  else{
    head_=novi;
  }
  current->prev=novi;
  size_++;
  return Iterator(novi);
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator pos){
  if(pos==end()){
    throw std::out_of_range("end iterator ne moze bit obrisan");
  }
  Node<T>* current=pos.node();
  
  if(current==nullptr){
    throw std::out_of_range("ne mozes obrsat null iterator");
  }

  if(current==head_){
    pop_front();
    return begin();
  }

  if(current==tail_){
    pop_back();
    return end();
  }

  Node<T>* prev=current->prev;
  Node<T>* next=current->next;

  prev->next=next;
  next->prev=prev;

  delete current;
  size_--;
  return Iterator(next);
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator beginIt, Iterator endIt){
  if(empty()){
    throw std::out_of_range("prazna lista");
  }

  if(beginIt==begin() && endIt==end()){
    clear();
    return nullptr;
  }

  Node<T>* beginNode=beginIt.node();
  Node<T>* endNode=endIt.node();

  if(beginNode==nullptr || endNode==nullptr){return nullptr;}
  
  Node<T>* prevNode=beginNode->prev;
  Node<T>* nextNode=endNode;

  if(prevNode!=nullptr){
    prevNode->next=nextNode;
  }
  else{
    head_=nextNode;
  }

  if(nextNode!=nullptr){
    nextNode->prev=prevNode;
  }
  else{
    tail_=prevNode;
  }

  while(beginNode!=endNode){
    Node<T>* temp=beginNode;
    beginNode=beginNode->next;
    delete temp;
    size_--;
  }
  if (beginIt == begin()) {
        return Iterator(head_);
    } else if (endIt == end()) {
        return Iterator(tail_);
    } else {
        return Iterator(nextNode);
    }
};


template<typename T>
void DoubleLinkedList<T>::remove_if(std::function<bool(const T &)> &&p){
  if(empty()){
    throw std::out_of_range("prazna lista");
  }
  Node<T>* temp=head_;
  while(temp){
    if(p(temp->data)){
      Node<T>* temp2=temp;
      temp=temp->next;
      erase(Iterator(temp2));
    }
    else{
      temp=temp->next;
    }
  }
};


template <typename T>
void DoubleLinkedList<T>::reverse(){
  if (size() <= 1) {
        return;
    }

    Node<T>* current = head_;
    Node<T>* previous = nullptr;
    Node<T>* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    head_ = previous;
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(const T& element) const{
  for(auto it=begin(); it!=end(); it++){
    if(*it==element){
      return it;
    }
  }
  return end();
}
 // void reverse();
 // Iterator find(const T &element) const;

/*
DoubleLinkedList &push_front(const T &);
  DoubleLinkedList &push_front(T &&);
  DoubleLinkedList &pop_front();
  DoubleLinkedList &pop_back();
  bool empty() const;
  size_t size() const;
  T &front();
  T &back();
  Iterator begin() const;
  Iterator end() const;
  const Iterator cbegin() const;
  const Iterator cend() const;
  Iterator rbegin() const;
  Iterator rend() const;
  const Iterator rcbegin() const;
  const Iterator rcend() const;
  void clear();
  Iterator insert(Iterator pos, const T &element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);
  void remove_if(std::function<bool(const T &)> &&p);
  void reverse();
  Iterator find(const T &element) const;
*/

