#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Stack {
public:
  Stack();
  Stack(const Stack &);
  Stack(Stack &&);
  Stack &operator=(const Stack &);
  Stack &operator=(Stack &&);
  T pop();
  T &top() const;
  // Savrseno proslijedjivane (forward referenca)
  template <typename U> Stack<T> &push(U && element){
    if(capacity_==size_){
      realoc();
    }
    arr_[size_]=std::move(element);
    size_++;
    return *this;
  };
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  ~Stack();
  void clear();
  void resize(size_t newSize);
  bool operator==(const Stack &);
  bool operator!=(const Stack &);

private:
  void realoc(){
    capacity_*=2;
    T* newarr_=new T[capacity_];
    for(size_t i=0; i<size_; i++){
      newarr_[i]=arr_[i];
    }
    delete[] arr_;
    arr_=newarr_;
  };
  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
};

template<typename T>
Stack<T>::Stack():capacity_{10}, size_{0}, arr_{new T[capacity_]}{};

template<typename T>
bool Stack<T>::empty() const{
  return size_==0;
}

template<typename T>
size_t Stack<T>::size() const{
  return size_;
}

template<typename T>
Stack<T>::~Stack(){
  delete[] arr_;
  size_=0;
  capacity_=0;
}

/*template<typename U>
Stack<T>& Stack<T>::push(U&& element){
  arr_[size_-1]=element;
}*/

template<typename T>
Stack<T>::Stack(const Stack& stek){
  capacity_=stek.capacity_;
  size_=stek.size_;
  arr_=new T[stek.capacity_];
  for(size_t i=0; i<stek.size(); i++){
    arr_[i]=stek.arr_[i];
  }
}
template<typename T>
bool Stack<T>::operator==(const Stack& stek){
  if(size_!=stek.size_){return false;}
  for(size_t i=0; i<stek.size(); i++){
    if(arr_[i]!=stek.arr_[i]){return false;}
  }
  return true;
}
template<typename T>
bool Stack<T>::operator!=(const Stack& stek){
  if(size_!=stek.size_){return true;}
  for(size_t i=0; i<stek.size(); i++){
    if(arr_[i]!=stek.arr_[i]){return true;}
  }
  return false;
}

template<typename T>
T Stack<T>::pop(){
  if(size_==0){throw std::out_of_range("prazan stek");}
  size_--;
  return arr_[size_];
};

template<typename T>
T& Stack<T>::top() const{
  if(size_==0){
    throw std::out_of_range("stek prazan");
  }
  return arr_[size_-1];
};

template<typename T>
Stack<T>::Stack(Stack&& stek){
  capacity_=stek.capacity_;
  size_=stek.size_;
  arr_=new T[stek.capacity_];
  for(size_t i=0; i<stek.size_; i++){
    arr_[i]=std::move(stek.arr_[i]);
  }
  stek.size_=0;
  stek.capacity_=0;
  delete[] stek.arr_;
};

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack &stek){
  capacity_=stek.capacity_;
  size_=stek.size_;
  arr_=new T[capacity_];
  for(size_t i=0; i<stek.size_; i++){
    arr_[i]=stek.arr_[i];
  }
  return *this;
};

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& stek){
  if(this!=&stek){
    capacity_=stek.capacity_;
    size_=stek.size_;
    arr_=new T[capacity_];
    for(size_t i=0; i<stek.size_; i++){
      arr_[i]=std::move(stek.arr_[i]);
    }
    stek.size_=0;
    stek.capacity_=0;
    delete[] stek.arr_;
  }
  return *this;

};

template<typename T>
size_t Stack<T>::capacity() const{return capacity_;};

template<typename T>
bool Stack<T>::full() const{return size_==capacity_;};


template<typename T>
void Stack<T>::clear(){
  delete[] arr_;
  size_=0;
};

template<typename T>
void Stack<T>::resize(size_t newSize){
  size_=newSize;
};

