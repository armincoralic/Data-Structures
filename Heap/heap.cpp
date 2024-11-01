#include<iostream>
#include<stdexcept>

template <typename T>
class MaxHeap{
  public:
    MaxHeap():heap_{nullptr}, size_{0}, capacity_{10}{};
    /*MaxHeap(int maxN){
      heap_=new T[maxN];
      size_=0;
    }
    void insert(T const& value){
      if(size_==capacity_){
        doubleCapacity();
      }
      heap_[size_++]=value;
      int i=size_-1;
      while()
    }

    void update(int k){
      while(k>1 && ptr_[k/2] < ptr_[k]){
        std::swap(ptr_[k], ptr_[k/2]);
        k=k/2;
      }
    }*/

    void insert(T const& value){
      if(size_==capacity_){
        realoc();
      }
      heap_[size_++]=value;
      int i = size_-1;
      while(i != 0  && heap_[parent(i)] < heap_[i]){
        std::swap(&heap_[parent(i)], &heap_[i]);
        i = parent(i);
      }
    }

    T& removeMax(){
      if(size_==0){
        throw std::out_of_range("prazan heap");
      }
      T* temp = heap_[0];
      heap_[0]=heap_[size_--];
      updateMax(0);
      return temp;
    }

    void updateMax(int index){
      T left = leftChild(index);
      T right = rightChild(index);

      T largest = index;

      if((left <= size_) && (heap_[left] > heap_[largest])){
        largest = left;
      }
      if((right<=size_) && (heap_[right] > heap_[largest])){
        largest = right;
      }

      if(largest != index){
        T temp = heap_[index];
        heap_[index] = heap_[largest];
        heap_[largest] = temp;
        updateMax(largest);
      }
    }

    friend std::ostream& operator<<(std::ostream& os, const MaxHeap<T>& heap){
      heap.preorderPrint(os, 0);
      return os;
    }

  void preorderPrint(std::ostream& os, int index) const {
    if (index >= size_) {
        return;
    }
    os << heap_[index] << " ";
    preorderPrint(os, 2 * index + 1);
    preorderPrint(os, 2 * index + 2);
  }


    void print(){
      if(size_==0){
        throw std::out_of_range("prazan heap");
      }
      for(int i = 0; i < size_; i++){
        std::cout<<heap_[i]<<" "; 
      }
    }
    T& max(){
      if(size_==0){
        throw std::out_of_range("prazan heap");
      }
      return heap_[0];
    }
    void realoc(){
      capacity_*=2;
      T* temp=new T[capacity_];
      std::copy(heap_, heap_+capacity_, temp);
      delete[] heap_;
      heap_=temp;
    };

    void swap(T* a, T* b){
      T temp=*a;
      *a=*b;
      *b=temp;
    };

    int parent(int index) const{
      return (index-1)/2;
    }
    int leftChild(int index) const{
      return 2*index+1;
    }
    int rightChild(int index) const{
      return 2*index+2;
    }

  private:
    T* heap_;
    int size_;
    int capacity_;
};





