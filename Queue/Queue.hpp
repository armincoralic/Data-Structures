#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Queue {
public:
  Queue();
  Queue(const Queue &);
  Queue(Queue &&);
  Queue &operator=(const Queue &);
  Queue &operator=(Queue &&);
  ~Queue();
  // Add new element at the end of the queue
  template <typename U> Queue &push(U && element){
  if(empty()){
    front_=0;
    back_=0;
  }
  if(size_==capacity_){
      capacity_*=2;
      T* tmp=new T[capacity_];
      int j=0;
      for(int i=front_; i<size_; i++){
        arr_[j++]=tmp[i];
      }
      delete[] tmp;
      size_=size_-front_;
      front_=0;
    }
      arr_[back_]=std::forward<U>(element);
      back_=(back_+1)%capacity_;
      ++size_;
      return *this;
    
  };
  // Pop an element from the begin
  T pop();
  T &front();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  void clear();

private:
  void realoc(){
    if(size_==capacity_){
      capacity_*=2;
      T* tmp=new T[capacity_];
      int j=0;
      for(int i=front_; i<size_; i++){
        arr_[j++]=tmp[i];
      }
      delete[] tmp;
      size_=size_-front_;
      front_=0;

    };
  }
  void copyQueue(const Queue& red){
    capacity_=red.capacity_;
    size_=red.size_;
    back_=red.back_;
    front_=red.front_;
    arr_=new T[capacity_];
    for(size_t i=front_; i<red.size_; i++){
      arr_[(front_+i)%capacity_]=red.arr_[(i+front_)%capacity_];
    }
  };
  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
  // Index sa koje strane se dodaje
  size_t back_{0};
  // Index sa koje strane se uklanja
  size_t front_{0};
};
// Vas kod ovdje


template<typename T>
Queue<T>::Queue():capacity_{10}, size_{0}, arr_{new T[capacity_]}, back_{0}, front_{0}{};

template<typename T>
Queue<T>::Queue(const Queue& red){
  capacity_=red.capacity_;
  size_=red.size_;
  back_=red.back_;
  front_=red.front_;
  arr_=new T[capacity_];
  for(size_t i=front_; i<red.size_; i++){
    arr_[(front_+i)%capacity_]=red.arr_[(i+front_)%capacity_];
  }
}

template<typename T>
bool Queue<T>::empty() const{return size_==0;};

template<typename T>
size_t Queue<T>::capacity() const{return capacity_;};

template<typename T>
size_t Queue<T>::size() const{return size_;};

template<typename T>
Queue<T>::~Queue(){
  delete[] arr_;
  capacity_=0;
  size_=0;
  back_=0;
  front_=0;
}

template<typename T>
T Queue<T>::pop(){
  if(size_==0){
    front_=size_=0;
    throw std::out_of_range("prazan red");
  }
  size_--;
  front_++;
  return arr_[front_-1];
};

template<typename T>
T& Queue<T>::front(){
  if(size_==0){throw std::out_of_range("prazan red");}
  return arr_[front_];
};

template<typename T>
Queue<T>::Queue(Queue&& red){
  capacity_=red.capacity_;
  size_=red.size_;
  front_=red.front_;
  back_=red.back_;
  arr_=red.arr_;

  red.arr_=nullptr;
  red.size_=0;
  red.capacity_=0;
  red.front_=0;
  red.back_=0;
  /*for(int i=front_; i<red.size_; i++){
    arr_[(front_+i)%capacity_]=std::move(red.arr_[(i+front_)%capacity_]);
  }
  delete[] red.arr_;*/
};

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& red){
  if(this!=&red){
    copyQueue(red);
  }
  return *this;
};

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& red){
  if(this!=&red){
     capacity_=red.capacity_;
  size_=red.size_;
  front_=red.front_;
  back_=red.back_;
  arr_=red.arr_;

  red.arr_=nullptr;
  red.size_=0;
  red.capacity_=0;
  red.front_=0;
  red.back_=0;
  }

  return *this;
};

template<typename T>
void Queue<T>::clear(){
  size_=0;
};

template <typename T>
bool Queue<T>::full() const{
  return size_==capacity_;
};


