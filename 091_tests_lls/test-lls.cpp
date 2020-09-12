#include <cstdio>
#include <iostream>

#include "il.h"

void err(std::string errm) {
  std::cerr << errm << std::endl;
  exit(EXIT_FAILURE);
}

void testList(void) {
  IntList::Node x;
  if (x.data != 0 || x.next != NULL || x.prev != NULL) {
    err("wrong node");
  }

  IntList::Node y(1000000000);
  if (y.data != 1000000000 || y.next != NULL || y.prev != NULL) {
    err("wrong node");
  }

  IntList list1;
  if (list1.getSize() != 0 || list1.head != NULL || list1.tail != NULL ||
      list1.head != list1.tail) {
    err("error initialize");
  }

  for (int i = 0; i < 6; i++) {
    list1.addFront(i);
    if (list1.getSize() != i + 1 || list1.size != i + 1) {
      err("addFront size error");
    }
  }

  IntList::Node * next2 = list1.head->next;
  if (next2->prev != list1.head) {
    err("addfront not connect");
  }

  for (int i = 0; i < 6; i++) {
    if (list1[i] != 5 - i) {
      err("addFront location error");
    }
  }
  if (list1.head->data != 5 || list1.tail->data != 0) {
    err("addFront head/tail error");
  }
  if (list1.head->prev != NULL || list1.tail->next != NULL) {
    err("wrong begin/end");
  }

  IntList list2(list1);
  for (int i = 0; i < 6; i++) {
    if (list2[i] != 5 - i) {
      err("list assign error");
    }
  }
  if (list2.getSize() != 6 || list2.size != 6) {
    err("list assign size error");
  }
  if (list2.head == list1.head || list2.tail == list1.tail) {
    err("wrong assign");
  }
  if (list2.head->prev != NULL || list2.tail->next != NULL) {
    err("wrong begin/end");
  }
  if (list2.head->next->data != 4 || list2.tail->prev->data != 1) {
    err("copy connect error");
  }

  IntList list3;
  list3 = list1;
  if (list3.getSize() != 6 || list3.size != 6) {
    err("list copy size error");
  }
  for (int i = 0; i < 6; i++) {
    if (list3[i] != 5 - i) {
      err("list copy error");
    }
  }
  if (list3.head == list1.head || list3.tail == list1.tail) {
    err("wrong copy");
  }
  if (list3.head->prev != NULL || list3.tail->next != NULL) {
    err("wrong begin/end");
  }
  if (list3.head->next->data != 4 || list3.tail->prev->data != 1) {
    err("copy connect error");
  }

  IntList list6, list7;
  list6 = list7 = list1;
  if (list6.getSize() != 6 || list6.size != 6) {
    err("list copy size error");
  }
  for (int i = 0; i < 6; i++) {
    if (list6[i] != 5 - i) {
      err("list copy error");
    }
  }
  if (list6.head == list1.head || list6.tail == list1.tail) {
    err("wrong copy");
  }
  if (list6.head->prev != NULL || list6.tail->next != NULL) {
    err("wrong begin/end");
  }
  if (list6.head->next->data != 4 || list6.tail->prev->data != 1) {
    err("copy connect error");
  }

  list3.remove(4);
  IntList::Node * next1 = list3.head->next;
  IntList::Node * prev1 = next1->prev;
  if (next1->data != 3 || prev1->data != 5) {
    err("remove not connect");
  }

  list6 = list3;
  if (list6.getSize() != 5 || list6.size != 5) {
    err("list copy size error");
  }
  if (list6.head->prev != NULL || list6.tail->next != NULL) {
    err("wrong begin/end");
  }
  if (list6.head->next->data != 3 || list6.tail->prev->data != 1) {
    err("copy connect error");
  }

  IntList list4;
  for (int i = 0; i < 6; i++) {
    list4.addBack(i);
    if (list4.getSize() != i + 1 || list4.size != i + 1) {
      err("addBack size error");
    }
  }
  for (int i = 0; i < 6; i++) {
    if (list4[i] != i) {
      err("addBack location error");
    }
  }

  IntList::Node * prev2 = list4.tail->prev;
  if (prev2->next != list4.tail) {
    err("addback not connect");
  }

  if (list4.head->data != 0 || list4.tail->data != 5) {
    err("addBack head/tail error");
  }
  if (list4.head->prev != NULL || list4.tail->next != NULL) {
    err("wrong begin/end");
  }

  if (list4.remove(6) != false || list4.remove(5) != true) {
    err("remove target error");
  }
  list4.remove(0);
  if (list4.getSize() != 4) {
    err("remove size error");
  }
  if (list4.tail->data != 4 || list4.head->data != 1) {
    err("remove tail/head error");
  }
  if (list4.tail->next != NULL || list4.head->prev != NULL) {
    err("remove connect error");
  }

  if (list4.find(0) != -1 || list4.find(1) != 0 || list4.find(2) != 1) {
    err("find error");
  }
  if (list4.head->prev != NULL || list4.tail->next != NULL) {
    err("wrong begin/end");
  }
}

int main() {
  testList();
  return EXIT_SUCCESS;
}
