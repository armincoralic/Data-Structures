#include "BST.hpp"

int main(int argc, char* argv[]) {
  BST<int> bst;
  bst.add(1).add(-5).add(10).add(-20).add(50).add(5).add(100);
  bst.preorder();
  bst.inorder();
  bst.postorder();
  auto* node = bst.search(50);
  if (node) {
    std::cout << "Element je pronadjen: " << node->data << std::endl;
  } else {
    std::cout << "Element ne postoji" << std::endl;
  }
  return 0;
}
