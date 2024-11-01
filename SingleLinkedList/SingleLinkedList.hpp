#pragma once

#include <iostream>
#include <stdexcept>
#include <functional>

template <typename T>
struct Node
{
    T data;
    Node* next;
    Node(const T& element)
        : data{element}
        , next{nullptr}
    {
    }
};

template <typename T>
class SingleLinkedList
{
public:
    class Iterator{
      public:
      Iterator(){ptr_=nullptr;};
      Iterator(Node<T>* ptr){ptr_=ptr;};
      Iterator(Node<T>& reff):ptr_{&reff}{};
      Node<T>* node() {return ptr_;};
      T& operator*() const{return ptr_->data;};
      Iterator& operator++(){
        ptr_=ptr_->next;
        return *this;
      };
      Iterator operator++(int){
        Iterator temp=*this;
        ++(*this);
        return temp;
      }
      T* operator->() const{
        return &(ptr_->data);
      }

      Iterator(const Iterator& other):ptr_{other.ptr_}{};
      Iterator& operator=(const Iterator& other){
        if(this!=&other){
          ptr_=other.ptr_;
        }
        return *this;
      }
      Iterator(Iterator&& other):ptr_(other.ptr_){
       other.ptr_=nullptr; 
      };
      bool operator==(const Iterator& other) const{
        return ptr_==other.ptr_;
      }
      bool operator!=(const Iterator& other) const{
        return !(*this==other);
      }
      ~Iterator(){ptr_=nullptr;};

      
      private:
        Node<T>* ptr_;
    };
    SingleLinkedList(); //
    SingleLinkedList(const SingleLinkedList&); //
    SingleLinkedList(SingleLinkedList&&); //
    SingleLinkedList& operator=(const SingleLinkedList&);
    SingleLinkedList& operator=(SingleLinkedList&&);
    ~SingleLinkedList();//
    SingleLinkedList& push_back(const T&); //
    SingleLinkedList& push_front(const T&);//
    SingleLinkedList& pop_front();
    SingleLinkedList& pop_back();
    bool empty() const; //
    size_t size() const; //
    SingleLinkedList& extend(const SingleLinkedList&);
    Iterator find(const T& element) const;
    Iterator insert(Iterator pos, const T& element);
    Iterator erase(Iterator pos);
    Iterator begin() const;
    Iterator end() const;
    const Iterator cbegin() const;
    const Iterator cend() const;
    const Iterator rcbegin() const;
    Iterator rbegin() const;
    Node<T>* head() const;//
    Node<T>* tail() const;//
   T& back() const;
     T& front() const;
    Iterator erase(Iterator beginIt, Iterator endIt);
    void clear();
    void remove_if(std::function<bool(const T&)>&& p);
    void reverse();

private:
    void copyList(const SingleLinkedList& lista){
    clear();
    Node<T>* tmp=lista.head();
    while(tmp!=nullptr){
      push_back(tmp->data);
      tmp=tmp->next;
      }
    };

    void dealoc();
    Node<T>* head_{nullptr};
    Node<T>* tail_{nullptr};
    size_t size_{0};
};


template<typename T>
SingleLinkedList<T>::SingleLinkedList():size_{0}, head_{nullptr}, tail_{nullptr}{};

template<typename T>
void SingleLinkedList<T>::clear(){
  while(head_){
    Node<T>* tmp=head_;
    head_=head_->next;
    delete tmp;
  }
  size_=0;
  tail_=nullptr;

};

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::push_back(const T& element){
  Node<T>* novi=new Node<T>{element};
  novi->next=nullptr;
  novi->data=element;
  if(size_==0){
    head_=tail_=novi;
  }
  else{
    tail_->next=novi;
    tail_=tail_->next;
  }
  ++size_;
  return *this;
}

/*template<typename T>
void SingleLinkedList<T>::copyList(const SingleLinkedList lista){
  clear();
  Node<T>* tmp=lista.head();
  while(tmp!=nullptr){
    push_back(tmp->data);
  }
}*/
template<typename T>
size_t SingleLinkedList<T>::size() const{return size_;};

template<typename T>
bool SingleLinkedList<T>::empty() const{return size_==0;};

template<typename T>
Node<T>* SingleLinkedList<T>::head() const{return head_;};

template<typename T>
Node<T>* SingleLinkedList<T>::tail() const{return tail_;};

template<typename T>
SingleLinkedList<T>::~SingleLinkedList(){
  clear();
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList& lista){
  copyList(lista);
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList&& lista){
  clear();
  head_=lista.head_;
  tail_=lista.tail_;
  size_=lista.size_;


  lista.head_=nullptr;
  lista.tail_=nullptr;
  lista.size_=0;
};
template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList& lista){
  if(this!=&lista){
    clear();
    Node<T>* tmp=lista.head_;

    while(tmp!=nullptr){
      push_back(tmp->data);
      tmp=tmp->next;
    }
  }
  return *this;
};
template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList&& lista){
  if(this!=&lista){
    head_=lista.head_;
    tail_=lista.tail_;
    size_=lista.size_;

    lista.head_=nullptr;
    lista.tail_=nullptr;
    lista.size_=0;
  }
  return *this;
};

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::push_front(const T& element){
  Node<T>* novi=new Node<T>{element};
  if(size_==0){
    head_=tail_=novi;
  }
  else
  {
    novi->next=head_;
    head_=novi;
  }
  size_++;
  return *this;
};

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::pop_front(){
  if(size_==0){throw std::out_of_range("prazna lista");}
  if(head_){
    Node<T>* oldhead=head_;
    head_=head_->next;
    delete oldhead;
    size_--;
    if(head_==nullptr){
      tail_=nullptr;
    }
  }
  return *this;
};

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::pop_back(){
  if(empty()){throw std::out_of_range("prazna lista");}
  
  if(size_==1){
    delete tail_;
    head_=nullptr;
    tail_=nullptr;
    size_=0;
    return *this;
    }
  Node<T>* predzadnji=head_;
  while(predzadnji->next!=tail_){
    predzadnji=predzadnji->next;
  }
  delete tail_;
  tail_=predzadnji;
  tail_->next=nullptr;
  size_--;
  return *this;
};

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::extend(const SingleLinkedList& lista){
  if(&lista==this){return *this;}
  if(lista.size()==0){return *this;}
  if(size()==0 && lista.size()==0){
    return *this;
  }

  Node<T>* tmp=lista.head_;
  while(tmp){
    push_back(tmp->data);
    tmp=tmp->next;
  }
  return *this;
};

template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::find(const T& element) const{
  Node<T>* tmp=head_;
  while(tmp){
    if(tmp->data==element){
      return Iterator(tmp);
    }
    tmp=tmp->next;
  }
  return end();
};

template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::insert(Iterator pos, const T& element){
  /*if(pos==end()){
    return push_back(element);
  }
  Node<T>* tmp=head_;
  Node<T>* prethodni=nullptr;

  while(tmp && Iterator(tmp)!=pos){
    prethodni=tmp;
    tmp=tmp->next;
  }
  if(!tmp){
    return end();
  }

  Node<T>* newNode=new Node<T>(element);
  newNode->next=tmp;

  if(!prethodni){
    head_=newNode;
  }
  else{
    prethodni->next=newNode;
  }
  if(tmp==tail_){
    tail_=newNode;
  }
  size_++;
  return Iterator(newNode);*/
 
    Node<T>* newNode = new Node<T>(element);

    // Ako lista nije prazna
    if (pos != end()) {
        if (pos == begin()) {
            // Ubacujemo na početak liste
            newNode->next = head_;
            head_ = newNode;
            // Ako je ovo prvo umetanje u listu, ažuriramo i rep
            if (size_ == 0) {
                tail_ = newNode;
            }
        } else {
            // Ubacujemo na sredinu ili kraj liste
            Node<T>* prevNode = head_;
            while (prevNode != nullptr && prevNode->next != pos.node()) {
                prevNode = prevNode->next;
            }
            if (prevNode != nullptr) {
                newNode->next = pos.node();
                prevNode->next = newNode;
            } else {
                // Umetanje na kraj ako nije pronađena odgovarajuća pozicija
                tail_->next = newNode;
                tail_ = newNode;
            }
        }
    } else {
        // Ubacujemo na kraj liste
        if (tail_ != nullptr) {
            tail_->next = newNode;
        } else {
            // Ako je lista prazna, postavljamo i glavu i rep na novi čvor
            head_ = newNode;
        }
        tail_ = newNode;
    }

    size_++;
    return Iterator(newNode);
};

template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::erase(Iterator pos){
  Node<T>* tmp=head_;
  Node<T>* prethodni=nullptr;
  while(tmp && Iterator(tmp)!=pos){
    prethodni=tmp;
    tmp=tmp->next;
  }
  if(!tmp){
    return end();
  }

  if(!prethodni){
    head_=tmp->next;
  }
  else
  {
    prethodni->next=tmp->next;
  }

  if(tmp==tail_){
    tail_=prethodni;
  }
  Iterator next_iter(tmp->next);
  delete tmp;
  size_--;
  return next_iter;
};

template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::begin() const{return Iterator(head_);};

template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::end() const{return Iterator(tail_);};

template<typename T>
const typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::cbegin() const {
    return Iterator(head_);
}
template<typename T>
const typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::cend() const{
  return Iterator(nullptr);
};

template<typename T>
const typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::rcbegin() const{
  return Iterator(tail_);
};
template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::rbegin() const{
  return Iterator(tail_);
};
template <typename T>
T& SingleLinkedList<T>::back() const{
  if(tail_==nullptr){
    throw std::out_of_range("prazna lista");
  }
  return tail_->data;
};

template <typename T>
T& SingleLinkedList<T>::front() const{
  if(head_==nullptr){throw std::out_of_range("prazna lista");}
  return head_->data;
};
template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::erase(Iterator beginIt, Iterator endIt){
    if (beginIt == endIt) {
        return endIt;
    }
  if(beginIt==begin() && endIt==end()){
    size_=0;
    return end();
  }
    Node<T>* prevNode = nullptr;
    Node<T>* currentNode = head_;
    while (currentNode != nullptr && currentNode != beginIt.node()) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    while (currentNode != nullptr && currentNode != endIt.node()) {
        Node<T>* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
        size_--;
    }
    if (prevNode != nullptr) {
        prevNode->next = currentNode;
    } else {
        head_ = currentNode;
    }
    if (currentNode == nullptr) {
        tail_ = prevNode;
    }
    if (head_ == nullptr) {
        tail_ = nullptr;
    }
    if (currentNode == nullptr && prevNode != nullptr) {
        tail_ = prevNode;
    }

    return Iterator(currentNode); 
};

template<typename T>
void SingleLinkedList<T>::remove_if(std::function<bool(const T&)>&& p) {
    Node<T>* currentNode = head_;
    Node<T>* prevNode = nullptr;

    while (currentNode != nullptr) {
      if (p(currentNode->data)) {
        Node<T>* nextNode = currentNode->next;
          if (prevNode == nullptr) {
                head_ = nextNode;
            } else {
                prevNode->next = nextNode;
            }
            if (nextNode == nullptr) {
                tail_ = prevNode;
            }
            delete currentNode;
            currentNode = nextNode;
            size_--;
        } 
        else {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
    }
}

template<typename T>
void SingleLinkedList<T>::reverse() {
    if (head_ == nullptr || head_ == tail_) {
        return;
    }
    Node<T>* prevNode = nullptr;
    Node<T>* currentNode = head_;
    Node<T>* nextNode = nullptr;
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    tail_ = head_;
    head_ = prevNode;
}
/*
template<typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::begin() const{
  
};
    Iterator end() const;
    const Iterator cbegin() const;
    const Iterator cend() const;
    const Iterator rcbegin() const;
    Iterator rbegin() const;
    Node<T>* head() const;//
    Node<T>* tail() const;//
    const T& back() const;
    const T& front() const;
    Iterator erase(Iterator beginIt, Iterator endIt);
    void clear();
    void remove_if(std::function<bool(const T&)>&& p);
    void reverse();
*/
