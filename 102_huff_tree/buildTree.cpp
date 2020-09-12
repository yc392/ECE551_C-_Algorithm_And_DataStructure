#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t ans;
  for (int i = 0; i <= 256; i++) {
    if (counts[i] > 0) {
      ans.push(new Node(i, counts[i]));
    }
  }
  while (ans.size() > 1) {
    Node * left = ans.top();
    ans.pop();
    Node * right = ans.top();
    ans.pop();
    ans.push(new Node(left, right));
  }
  return ans.top();
}
