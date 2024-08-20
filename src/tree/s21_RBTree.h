#ifndef S21_TREE_H
#define S21_TREE_H

#include <iomanip>
#include <vector>

#include "../Node/s21_node.h"
#include "../iterator/tree_iterator/s21_tree_iterator.h"

namespace s21 {

template <typename T, typename Comparator = std::less<T>>
class RBTree {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = TreeIterator<T>;
  using const_iterator = ConstTreeIterator<T>;
  using size_type = size_t;
  using Node = Node_tree<T>;

  RBTree();
  RBTree(const RBTree &other);
  RBTree(RBTree &&other);
  ~RBTree();

  void clear();

  RBTree &operator=(RBTree &&other);
  RBTree &operator=(const RBTree &RBTree);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  size_type size() const;
  size_type max_size() const;
  bool empty() const;

  iterator Find(const_reference key);
  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insertUnique(const value_type &value);
  void erase(iterator pos);

  void swap(RBTree &other);
  void merge(RBTree &other);
  void mergeUnique(RBTree &other);

  // void PrintTree();
  // void PrintTree(Node *node, int indent = 0);

 protected:
  Node *GetMin(Node *node) const;
  Node *GetMax(Node *node) const;

  void Destroy(Node *node);
  void DeleteNode(Node *deletedNode);

  void InitFake();
  void UpdateFake();

  void LeftRotate(Node *node);
  void RightRotate(Node *node);
  void SwapNode(Node *fNode, Node *sNode);

  void BalanceInsert(Node *node);
  std::pair<iterator, bool> insert(Node *node, const value_type &value);

  void BalanceErase(Node *node);
  Node *LeftBalanceErase(Node *cur_node, Node *parent, bool *is_break);
  Node *RightBalanceErase(Node *cur_node, Node *parent, bool *is_break);

  Node *CopyTree(Node *node, Node *nil);

  Node *root_;
  Node *nil_;
  Comparator comp_;
  size_type size_ = 0U;
};

}  // namespace s21

#include "s21_RBTree.tpp"

#endif