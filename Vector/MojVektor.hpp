#pragma once
#include<utility>
#include <initializer_list>
#include <iterator>
#include<cstddef>

template <typename T>
class MojVektor {
  public:
  class Iterator{
    public:
    Iterator();
    Iterator(T*);
    Iterator(const Iterator&);

    Iterator& operator=(const Iterator& other) {
      ptr_ = other.ptr_;
      return *this;
    }

    Iterator(Iterator&&);

    Iterator& operator=(Iterator&& other) {
      ptr_ = std::move(other.ptr_);
      other.ptr_ = nullptr;
      return *this;
    }

    Iterator& operator++() { return *this = ++ptr_; }
    T* operator->();
    T& operator*();
    T* operator[](size_t);
    T* operator+(size_t);
    T* operator-(size_t);
    size_t operator-(const Iterator&);
    bool operator<(const Iterator&);
    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);
  
    private:
      T* ptr_;
  };
  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;
  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;
  bool empty() const;
  size_t capacity() const;
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;
  MojVektor subvector(Iterator begin, Iterator end);
  Iterator begin() const{return Iterator(arr_); };
  Iterator end() const{return Iterator(arr_ + size_); };
  Iterator find(const T& value) const{
    for (size_t i = 0; i < size_; ++i) {
      if (arr_[i] == value) return Iterator(&arr_[i]);
    }
    return Iterator(end());
  };
  Iterator erase(Iterator pos){
    if (pos != end()) {
      for (MojVektor<T>::Iterator it = pos; it != end() - 1; ++it)
        *it = *(it + 1);
      --size_;
    }
    return Iterator(pos);
  };
  Iterator insert(Iterator pos, const T& value){
    if (pos != end()) {
      size_t index = pos - begin();
      if (full()) realoc();
      for (size_t i = size_; i > index; --i) arr_[i] = arr_[i - 1];
      arr_[index] = value;
      ++size_;
      return Iterator(begin() + pos);
    } else
      throw std::out_of_range("Out of range");
  };
  Iterator insert(Iterator pos, T&& value){
    if (pos != end()) {
      size_t index = pos - begin();
      if (full()) realoc();
      for (size_t i = size_; i > index; --i) arr_[i] = arr_[i - 1];
      arr_[index] = std::move(value);
      ++size_;
      return Iterator(begin() + index);
    } else
      throw std::out_of_range("Out of range");
  };
  Iterator rbegin() const{return Iterator(end() - 1); };
  Iterator rend() const{return Iterator(begin() - 1);};
  Iterator erase(Iterator beginIt, Iterator endIt){
    size_t size = endIt - beginIt;
    for (MojVektor<T>::Iterator it = endIt; it != end(); ++it)
      *(it - size) = *it;
    size_ -= size;
    return Iterator(beginIt);
  };
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);
  T* data();
  


  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

template <typename T>
MojVektor<T>::MojVektor():capacity_{10}, size_{0}, arr_{new T[capacity_]}{};
template<typename T> 
MojVektor<T>::MojVektor(const std::initializer_list<T>& inlist):capacity_{inlist.size()}, size_{inlist.size()}, arr_{new T[capacity_]}{
  std::copy(inlist.begin(), inlist.end(), arr_);
};
template<typename T>
MojVektor<T>::MojVektor(const MojVektor& vec){
  capacity_=vec.capacity_;
  size_=vec.size_;
  arr_=new T[capacity_];
  for(int i=0; i<vec.size_; i++){
    arr_[i]=vec.arr_[i];
  }
};
template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& vec){
  if(this!=&vec){
    delete[] arr_;
    capacity_=vec.capacity_;
    size_=vec.size_;
    arr_=new T[capacity_];
    for(int i=0; i<size_; i++){
      arr_[i]=vec.arr_[i];
    }
  }
  return *this;
};
template<typename T>
MojVektor<T>::MojVektor(MojVektor&& vec){
  capacity_=vec.capacity_;
  size_=vec.size_;
  arr_=vec.arr_;

  vec.capacity_=0;
  vec.size_=0;
  vec.arr_=nullptr;
};
template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& vec){
  if(this!=&vec){
    delete[] arr_;
    capacity_=vec.capacity_;
    size_=vec.capacity_;
    arr_=vec.arr_;

    vec.capacity_=0;
    vec.size_=0;
    vec.arr_=nullptr;
  }
  return *this;
};
template<typename T>
MojVektor<T>::~MojVektor(){
  delete[] arr_;
  capacity_=0;
  size_=0;
  arr_=nullptr;
};
template <typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& element){
   if(capacity_==size_){
    capacity_*=2;
    T* newArr = new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=arr_[i];
    }
    delete[] arr_;
    arr_ = newArr;
  }
  arr_[size_]=element;
  ++size_;
  return *this;
};

/*template<typename T>  
MojVektor<T>& MojVektor<T>::push_front(const T& element){
    if(capacity_==size_){
    capacity_*=2;
    T* newArr = new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=arr_[i];
    }
    delete[] arr_;
    arr_ = newArr;
  }
  for(int i=0; i<size_; i++){
    arr_[i+1]=arr_[i];
  }
  arr_[0]=element;
  ++size_;
  return *this;
  
};
*/
template <typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& element) {
  if (arr_ == nullptr)
    *this = MojVektor<T>();
  else {
    T* arr = nullptr;
    if (full())
      arr = new T[capacity_ *= 2];
    else
      arr = new T[capacity_];
    std::copy(arr_, arr_ + size_, arr + 1);
    delete[] arr_;
    arr_ = arr;
  }
  arr_[0] = element;
  ++size_;
  return *this;
}


template <typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& element){
  if(capacity_==size_){
    capacity_*=2;
    T* newArr = new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=arr_[i];
    }
    delete[] arr_;
    arr_ = newArr;
  }
  arr_[size_]=std::move(element);
  ++size_;
  return *this;
};

/*template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element){
    if(capacity_==size_){
    capacity_*=2;
    T* newArr = new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=std::move(arr_[i]);
    }
    delete[] arr_;
    arr_ = newArr;
  }
  for(int i=0; i<size_; i++){
    arr_[i+1]=arr_[i];
  }
  arr_[0]=std::move(element);
  ++size_;
  return *this;
  };
*/
template <typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element) {
  if (arr_ == nullptr)
    *this = MojVektor<T>();
  else {
    T* arr = nullptr;
    if (full())
      arr = new T[capacity_ *= 2];
    else
      arr = new T[capacity_];
    std::copy(arr_, arr_ + size_, arr + 1);
    delete[] arr_;
    arr_ = arr;
  }
  arr_[0] = std::move(element);
  ++size_;
  return *this;
}



template<typename T>
size_t MojVektor<T>::size() const{
  return size_;
};
template <typename T>
T& MojVektor<T>::at(size_t indeks) const{
  if(indeks>=size_){
    throw std::out_of_range("nevalidan indeks");
  }
  return arr_[indeks];
};

template<typename T>
T& MojVektor<T>::operator[](size_t indeks) const{
  return arr_[indeks]; 
};
template<typename T>
void MojVektor<T>::clear(){
  delete[] arr_;
  arr_=nullptr;
  size_=0;
  capacity_=0;
};

template <typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value){
  if(newSize<size_){
    size_=newSize;
  }
  else if(newSize>capacity_){
    T* newArr=new T[newSize];
    for(int i=0; i<size_; i++){
      newArr[i]=arr_[i];
    }

    for(int i=size_; i<newSize; i++){
      newArr[i]=difference_value;
    }
    delete[] arr_;
    arr_=newArr;
    size_=newSize;
    capacity_=newSize;
  }
};

template <typename T>
MojVektor<T>& MojVektor<T>::pop_back(){
  if(size_==0){
    throw std::out_of_range("kontejner je prazan");
  }
  size_--;
  return *this;
};
template <typename T>
MojVektor<T>& MojVektor<T>::pop_front(){
  if(size_==0){throw std::out_of_range("kontejner je prazan");}
  for(size_t i=1; i<size_; i++){
    arr_[i-1]=arr_[i];
  }
  size_--;
  return *this;
};
template <typename T>
T& MojVektor<T>::back() const{
  if(size_==0){throw std::out_of_range("prazan kontejner");}
  return arr_[size_-1];
};
template <typename T>
T& MojVektor<T>::front() const{
  if(size_==0){throw std::out_of_range("prazan kontejner");}
  return arr_[0];
};
template <typename T>
bool MojVektor<T>::empty() const{
  return size_==0;
};
template <typename T>
size_t MojVektor<T>::capacity() const{
  return capacity_;
};

template <typename T>
bool MojVektor<T>::operator==(const MojVektor& vec) const{
  if(size_!=vec.size_){return false;}
  for(int i=0; i<size_; i++){
    if(arr_[i]!=vec.arr_[i]){
      return false;
    }
  }
  return true;
};
template<typename T>
bool MojVektor<T>::operator!=(const MojVektor& vec) const{
   if(size_!=vec.size_){return true;}
  for(int i=0; i<size_; i++){
    if(arr_[i]!=vec.arr_[i]){
      return true;
    }
  }
  return false;

};
template<typename T>
bool MojVektor<T>::full() const{
  return size_==capacity_;
};

template <typename T>
T* MojVektor<T>::data(){
  return arr_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MojVektor<T>& vec){
  //if(vec.size_==0){throw std::out_of_range("vec prazan");}
  os<<"{";
  if(!vec.empty()){
    for(size_t i=0; i<vec.size()-1; i++){ os<<vec[i]<<", ";
      os<<vec[vec.size()-1];
    }
  }
  os<<"}";
  return os;
};


template <typename T>
void MojVektor<T>::realoc() {
  T* newArr = new T[capacity_ *= 2];
  std::copy(arr_, arr_ + size_, newArr);
  delete[] arr_;
  arr_ = newArr;
}

//ITERATOOOOOOOOOOOOOOOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRRRRRRRRR
/*template<typename T>
class MojVektor<T>::Iterator{
public:
    Iterator();
    Iterator(T*);
    Iterator(const Iterator&);

    Iterator& operator=(const Iterator& other) {
      ptr_ = other.ptr_;
      return *this;
    }

    Iterator(Iterator&&);

    Iterator& operator=(Iterator&& other) {
      ptr_ = std::move(other.ptr_);
      other.ptr_ = nullptr;
      return *this;
    }

    Iterator& operator++() { return *this = ++ptr_; }
    T* operator->();
    T& operator*();
    T* operator[](size_t);
    T* operator+(size_t);
    T* operator-(size_t);
    size_t operator-(const Iterator&);
    bool operator<(const Iterator&);
    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);
  private:
    T* ptr;
};*/
template<typename T>
MojVektor<T>::Iterator::Iterator():ptr_(nullptr){}

template <typename T>
MojVektor<T>::Iterator::Iterator(T* ptr) : ptr_{ptr} {}

template <typename T>
MojVektor<T>::Iterator::Iterator(const Iterator& other) : ptr_{other.ptr_} {}

template <typename T>
MojVektor<T>::Iterator::Iterator(Iterator&& other)
    : ptr_{std::move(other.ptr_)} {
  other.ptr_ = nullptr;
}


template <typename T>
T* MojVektor<T>::Iterator::operator->() {
  return ptr_;
}

template <typename T>
T& MojVektor<T>::Iterator::operator*() {
  return *ptr_;
}

template <typename T>
T* MojVektor<T>::Iterator::operator[](size_t index) {
  return ptr_ + index;
}
template <typename T>
T* MojVektor<T>::Iterator::operator+(size_t n) {
  return ptr_ + n;
}

template <typename T>
T* MojVektor<T>::Iterator::operator-(size_t n) {
  return ptr_ - n;
}

template <typename T>
size_t MojVektor<T>::Iterator::operator-(const Iterator& other) {
  return ptr_ - other.ptr_;
}

template <typename T>
bool MojVektor<T>::Iterator::operator<(const Iterator& other) {
  return ptr_ < other.ptr_;
}

template <typename T>
bool MojVektor<T>::Iterator::operator==(const Iterator& other) {
  return ptr_ == other.ptr_;
}

template <typename T>
bool MojVektor<T>::Iterator::operator!=(const Iterator& other) {
  return ptr_ != other.ptr_;
};

template <typename T>
MojVektor<T> MojVektor<T>::subvector(Iterator begin, Iterator end){
  MojVektor<T> rez;
  for (MojVektor<T>::Iterator it = begin; it != end; ++it) rez.push_back(*it);
  rez.size_ = end - begin;
  return rez;
  /*while(begin!=end){
    rez.push_back(*begin);
    ++begin;
  }*/
};
/*
template<typename T>
class MojVektor<T>::Iterator MojVektor<T>::begin() const{
  return Iterator(begin());
};
template<typename T>  
class MojVektor<T>::Iterator MojVektor<T>::end() const{
  return Iterator(end());
};
template<typename T>
class MojVektor<T>::Iterator MojVektor<T>::find(const T& value) const{
  for(Iterator it=begin(); it!=end(); it++){
      if(*it==value){
        return it;
      }
    }
  return end();
};

template<typename T>
class MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos){
  if(pos==end()){
    return end();
  }
  size_t indeks=pos-begin();

  for(size_t i=indeks; i<size_; i++){
    arr_[i]=arr_[i+1];
  }
  --size_;
  return pos;
};*/
/*template <typename T>
class MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, const T& value){
  if(pos==end()){
     if(size_==capacity_){
    capacity_*=2;
    T* newArr=new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=arr_[i];
    }
    delete[] arr_;
    arr_=newArr;
    }
     arr_[size_]=value;
     ++size_;
     return Iterator(&arr_[size_-1]);
  }

  size_t indeks=pos-begin();
  if(size_==capacity_){
    capacity_*=2;
    T* newArr=new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=arr_[i];
    }
    delete[] arr_;
    arr_=newArr;
  }

  for(size_t i=size_; i>indeks; i--){
    arr_[i]=arr_[i-1];
  }
  arr_[indeks]=value;
  ++size_;
  return pos;
};*/
/*template <typename T>
class MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, T&& value){
  if(pos==end()){
     if(size_==capacity_){
    capacity_*=2;
    T* newArr=new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=std::move(arr_[i]);
    }
    delete[] arr_;
    arr_=newArr;
    }
     arr_[size_]=std::move(value);
     ++size_;
     return Iterator(&arr_[size_-1]);
  }

  size_t indeks=pos-begin();
  if(size_==capacity_){
    capacity_*=2;
    T* newArr=new T[capacity_];
    for(int i=0; i<size_; i++){
      newArr[i]=std::move(arr_[i]);
    }
    delete[] arr_;
    arr_=newArr;
  }

  for(size_t i=size_; i>indeks; i--){
    arr_[i]=arr_[i-1];
  }
  arr_[indeks]=std::move(value);
  ++size_;
  return pos;

};*/
/*template <typename T>
class MojVektor<T>::Iterator MojVektor<T>::rbegin() const{
  if(size_==0){
    return Iterator(end());
  }
  return Iterator(begin()-1);
};
template <typename T>
class MojVektor<T>::Iterator MojVektor<T>::rend() const{
  if(size_==0){
    return end();
  }
  return Iterator(begin()-1);
};*/
/*template <typename T>
class MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt){
  if(beginIt==endIt){
    return beginIt;
  }
  if(endIt==end()){endIt=Iterator(&arr_[size_]);}
  size_t indeks=0;
  for(Iterator it=begin(); it<beginIt; it++){
    arr_[indeks++]=*it;
    }

  size_t indeks2=std::distance(begin(), endIt);
  while(endIt!=end()){
    arr_[indeks]=*endIt[indeks2];
    endIt++;
  }
  };

template<typename T>
class MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt) {
    size_t size = endIt - beginIt;
    for (MojVektor<T>::Iterator it = endIt; it != end(); ++it)
      *(it - size) = *it;
    size_ -= size;
    return Iterator(beginIt);
  }

  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);

  T* data();
*/

template <typename T>
void MojVektor<T>::rotate() {
  if (!empty()) {
    for (size_t i = 0, j = size_ - 1; i < j; ++i, --j)
      std::swap(arr_[i], arr_[j]);
  }
}

template <typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt) {
  if (!empty()) {
    for (MojVektor<T>::Iterator it1 = beginIt, it2 = endIt - 1; it1 < it2;
         ++it1, it2 = it2 - 1)
      std::swap(*it1, *it2);
  }
}

