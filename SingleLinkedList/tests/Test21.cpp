#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../SingleLinkedList.hpp"

TEST_CASE("Move constructor moves pointer and sets source to nullptr") {
  SingleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3);
  SingleLinkedList<int>::Iterator it1 = list.begin();
  SingleLinkedList<int>::Iterator it2(std::move(it1));
  REQUIRE(it1.node() == nullptr);
  REQUIRE(it2.node() == list.head());
}
