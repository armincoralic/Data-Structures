#pragma once

#include <iostream>
template <typename T>
struct Node {
  Node* left{nullptr};
  Node* right{nullptr};
  T data;
  Node(T& element) : data{element} {}
  Node(T&& element) : data{std::move(element)} {}
};

template <typename T>
class BST {
  public:
  BST() = default;
  /*Node<T>* copyTree(Node<T>* node){
    if(!node){
      return nullptr;
    }
    Node<T>* newNode=new Node<T>{node->data};
    newNode->left=copyTree(node->left);
    newNode->right=copyTree(node->right);
    return newNode;
  };*/

  BST(const BST& bst){
    root_=copyTree(bst.root_);
  };
  
  void destroyTree(Node<T>* node){
    if(node){
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }
  BST(BST&& bst){
    root_=bst.root_;
    bst.root_=nullptr;
  };
  BST& operator=(BST&& bst){
    if(this!=&bst){
      destroyTree();
      root_=bst.root_;
      bst.root_=nullptr;
    } 
    return *this;
  };
  BST& operator=(const BST& bst){
    if(this!=&bst){
      destroyTree();
      root_=copyTree(bst.root_);
    }
    return *this;

  } ;
  ~BST(){
    destroyTree(root_);
  };

  template <typename U>
  BST& add(U&& element) {
    return add(element, root_);
  }

  void preorder() const {
    std::cout << "[";
    preorder(root_);
    std::cout << "]" << std::endl;
  }
  void inorder() const {
    std::cout << "[";
    inorder(root_);
    std::cout << "]" << std::endl;
  }
  void postorder() const {
    std::cout << "[";
    postorder(root_);
    std::cout << "]" << std::endl;
  }
  Node<T>* search(const T& element) { return (search(root_, element)); }
  // TODO: Implementirati koristenjem petlje
  Node<T>* loopSearch(const T& element){
    Node<T>* current=root_;
    while(current){
      if(current->data == element){
        return current;
      }
      else if(current->data > element){
        current=current->left;
      }
      else{
        current=current->right;
      }
    }
    return nullptr;
  };
  // TODO: Implementirati metod koji uklanja cvor koji ima vrijednost element
  BST& remove(const T& element){
    Node<T>** current = &root_;
    while (*current != nullptr) {
        if ((*current)->data == element) {
            Node<T>* temp = *current;
            if ((*current)->left == nullptr) {
                *current = (*current)->right;
            } else if ((*current)->right == nullptr) {
                *current = (*current)->left;
            } else {
                Node<T>** parent = &(*current)->right;
                while ((*parent)->left != nullptr) {
                    parent = &(*parent)->left;
                }
                temp = *parent;
                *parent = (*parent)->right;
                temp->left = (*current)->left;
                temp->right = (*current)->right;
                *current = temp;
            }
            delete temp;
            break;
        } else if ((*current)->data > element) {
            current = &((*current)->left);
        } else {
            current = &((*current)->right);
        }
    }
    return *this;  
  };

  // Metod koji mijenja vrijednost node na element
  void replace(Node<T>* node, const T& element){
    if(node){
      node->data=element;
    }
    else
    {
      throw std::out_of_range("node is null");
    }
  };

  private:
  template <typename U>
  BST& add(U&& element, Node<T>*& root) {
    auto* node = new Node<T>(std::forward<U>(element));
    if (root == nullptr) {
      root = node;
    } else {
      if (root->data > element) {
        add(element, root->left);
        // Left
      } else {
        add(element, root->right);
        // Right
      }
    }
    return *this;
  }

  Node<T>* copyTree(Node<T>* node){
    if(!node){
      return nullptr;
    }
    Node<T>* newNode=new Node<T>{node->data};
    newNode->left=copyTree(node->left);
    newNode->right=copyTree(node->right);
    return newNode;
  };

  Node<T>* search(Node<T>* node, const T& element) {
    if (!node) return nullptr;
    if (node->data == element) return node;
    if (node->data > element) {
      return search(node->left, element);
    } else {
      return search(node->right, element);
    }
  }
  void preorder(const Node<T>* const current) const {
    if (!current) return;
    std::cout << current->data << ", ";
    preorder(current->left);
    preorder(current->right);
  }
  void inorder(const Node<T>* const current) const {
    if (!current) return;
    inorder(current->left);
    std::cout << current->data << ", ";
    inorder(current->right);
  }
  void postorder(const Node<T>* const current) const {
    if (!current) return;
    postorder(current->left);
    postorder(current->right);
    std::cout << current->data << ", ";
  }

  Node<T>* root_{nullptr};
};
