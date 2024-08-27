#include "s21_RBTree.h"

namespace s21 {

template <typename T, typename Comparator>
RBTree<T, Comparator>::RBTree() : root_(nullptr), size_(0U) {
  InitFake();
}

template <typename T, typename Comparator>
RBTree<T, Comparator>::RBTree(const RBTree &other) : RBTree() {
  *this = other;
}

template <typename T, typename Comparator>
RBTree<T, Comparator>::RBTree(RBTree &&other) : RBTree() {
  swap(other);
}

template <typename T, typename Comparator>
RBTree<T, Comparator>::~RBTree() {
  // PrintTree();
  clear();
  delete nil_;
}

template <typename T, typename Comparator>
RBTree<T, Comparator> &RBTree<T, Comparator>::operator=(RBTree &&other) {
  swap(other);
  return *this;
}

template <typename T, typename Comparator>
RBTree<T, Comparator> &RBTree<T, Comparator>::operator=(const RBTree &other) {
  if (this != &other) {
    clear();
    root_ = CopyTree(other.root_, other.nil_);
  }
  return *this;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::begin() {
  iterator res;
  if (root_) {
    res = iterator(GetMin(root_), nil_);
  } else {
    res = end();
  }
  return res;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::end() {
  return iterator(nil_, nil_);
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::const_iterator RBTree<T, Comparator>::begin()
    const {
  const_iterator res;
  if (root_) {
    res = const_iterator(GetMin(root_), nil_);
  } else {
    res = end();
  }
  return res;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::const_iterator RBTree<T, Comparator>::end()
    const {
  return const_iterator(nil_, nil_);
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::size_type RBTree<T, Comparator>::size() const {
  return size_;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::size_type RBTree<T, Comparator>::max_size()
    const {
#if defined(__linux__)
  return (std::numeric_limits<std::ptrdiff_t>::max()) / sizeof(Node);
#else
  return std::numeric_limits<std::ptrdiff_t>::max() / (sizeof(Node) / 2U);
#endif
}

template <typename T, typename Comparator>
bool RBTree<T, Comparator>::empty() const {
  return size_ == 0U;
}

template <typename T, typename Comparator>
std::pair<typename RBTree<T, Comparator>::iterator, bool>
RBTree<T, Comparator>::insert(const value_type &value) {
  std::pair<iterator, bool> res;
  if (!root_) {
    root_ = new Node(value, nil_, nil_, nil_);
    root_->color_ = BLACK;
    res.first = iterator(root_, nil_);
    res.second = true;
  } else {
    res = insert(root_, value);
  }
  if (res.second) {
    ++size_;
  }
  BalanceInsert(res.first.GetNode());
  UpdateFake();
  return res;
}

template <typename T, typename Comparator>
std::pair<typename RBTree<T, Comparator>::iterator, bool>
RBTree<T, Comparator>::insertUnique(const value_type &value) {
  std::pair<iterator, bool> res;
  iterator it = Find(value);
  if (it == end()) {
    res = insert(value);
  } else {
    res.first = it;
    res.second = false;
  }
  return res;
}

template <typename T, typename Comparator>
std::pair<typename RBTree<T, Comparator>::iterator, bool>
RBTree<T, Comparator>::insert(Node *node, const value_type &value) {
  std::pair<iterator, bool> res{iterator{}, false};
  while (!res.second) {
    if (comp_(value, node->val_)) {
      if (node->left_ == nil_) {
        node->left_ = new Node(value, node, nil_, nil_);
        node->left_->color_ = RED;
        res.first = iterator(node->left_, nil_);
        res.second = true;
      } else {
        node = node->left_;
      }
    } else {
      if (node->right_ == nil_) {
        node->right_ = new Node(value, node, nil_, nil_);
        node->right_->color_ = RED;
        res.first = iterator(node->right_, nil_);
        res.second = true;
      } else {
        node = node->right_;
      }
    }
  }
  return res;
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::UpdateFake() {
  nil_->color_ = BLACK;
  nil_->parent_ = GetMax(root_);
  nil_->right_ = GetMin(root_);
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::Node *RBTree<T, Comparator>::GetMin(
    Node *node) const {
  while (node && node->left_ != nil_) {
    node = node->left_;
  }
  return node;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::Node *RBTree<T, Comparator>::GetMax(
    Node *node) const {
  while (node && node->right_ != nil_) {
    node = node->right_;
  }
  return node;
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::clear() {
  Destroy(root_);
  root_ = nullptr;
  size_ = 0U;
  UpdateFake();
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::Destroy(Node *node) {
  if (node && node != nil_) {
    Destroy(node->left_);
    Destroy(node->right_);
    delete node;
  }
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::InitFake() {
  nil_ = new Node{};
  nil_->left_ = nil_;
  nil_->right_ = nil_;
  nil_->parent_ = nil_;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::Find(
    const_reference key) {
  iterator res = lower_bound(key);
  if (res != end() && (comp_(*res, key) || comp_(key, *res))) {
    res = end();
  }
  return res;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::lower_bound(
    const_reference key) {
  Node *res = nil_;
  Node *cur_node = root_;
  while (cur_node && cur_node != nil_) {
    if (!comp_(cur_node->val_, key)) {
      res = cur_node;
      cur_node = cur_node->left_;
    } else {
      cur_node = cur_node->right_;
    }
  }
  return iterator(res, nil_);
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::upper_bound(
    const_reference key) {
  Node *res = nil_;
  Node *cur_node = root_;
  while (cur_node && cur_node != nil_) {
    if (comp_(key, cur_node->val_)) {
      res = cur_node;
      cur_node = cur_node->left_;
    } else {
      cur_node = cur_node->right_;
    }
  }
  return iterator(res, nil_);
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::LeftRotate(Node *node) {
  Node *right_node = node->right_;
  if (node == root_) {
    root_ = node->right_;
  } else if (node->parent_->left_ == node) {
    node->parent_->left_ = right_node;
  } else {
    node->parent_->right_ = right_node;
  }
  node->right_ = right_node->left_;
  right_node->parent_ = node->parent_;

  if (right_node->left_ != nil_) {
    right_node->left_->parent_ = node;
  }

  node->parent_ = right_node;
  right_node->left_ = node;
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::RightRotate(Node *node) {
  Node *left_node = node->left_;
  if (node == root_) {
    root_ = node->left_;
  } else if (node->parent_->left_ == node) {
    node->parent_->left_ = left_node;
  } else {
    node->parent_->right_ = left_node;
  }
  node->left_ = left_node->right_;
  left_node->parent_ = node->parent_;

  if (left_node->right_ != nil_) {
    left_node->right_->parent_ = node;
  }

  node->parent_ = left_node;
  left_node->right_ = node;
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::BalanceInsert(Node *node) {
  while (node != root_ && node->parent_->color_ == RED) {
    Node *parent = node->parent_;
    Node *grandpa = parent->parent_;
    Node *uncle = (grandpa->left_ == parent ? grandpa->right_ : grandpa->left_);
    if (uncle->color_ == RED) {
      uncle->color_ = BLACK;
      parent->color_ = BLACK;
      grandpa->color_ = RED;
      node = grandpa;
    } else {
      if (grandpa->left_ == parent) {
        if (parent->right_ == node) {
          LeftRotate(parent);
          std::swap(parent, node);
        }
        RightRotate(grandpa);
        parent->color_ = BLACK;
        grandpa->color_ = RED;
      } else {
        if (parent->left_ == node) {
          RightRotate(parent);
          std::swap(parent, node);
        }
        LeftRotate(grandpa);
        parent->color_ = BLACK;
        grandpa->color_ = RED;
      }
    }
  }
  root_->color_ = BLACK;
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::swap(RBTree &other) {
  std::swap(root_, other.root_);
  std::swap(nil_, other.nil_);
  std::swap(size_, other.size_);
  std::swap(comp_, other.comp_);
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::merge(RBTree &other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
    other.clear();
  }
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::mergeUnique(RBTree &other) {
  if (this != &other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insertUnique(*it);
    }
    other.clear();
  }
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::Node *RBTree<T, Comparator>::CopyTree(
    Node *node, Node *nil) {
  Node *new_node = new Node{node->val_};
  new_node->color_ = node->color_;
  if (node->parent_ == nil) {
    new_node->parent_ = nil_;
  }
  if (node->left_ == nil) {
    new_node->left_ = nil_;
  } else {
    new_node->left_ = CopyTree(node->left_, nil);
    new_node->left_->parent_ = new_node;
  }
  if (node->right_ == nil) {
    new_node->right_ = nil_;
  } else {
    new_node->right_ = CopyTree(node->right_, nil);
    new_node->right_->parent_ = new_node;
  }
  ++size_;
  return new_node;
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::SwapNode(Node *firstNode, Node *secondNode) {
  Node *root_tmp = root_;
  if (firstNode == root_tmp) {
    root_ = secondNode;
  } else {
    if (firstNode->parent_->left_ == firstNode) {
      firstNode->parent_->left_ = secondNode;
    } else {
      firstNode->parent_->right_ = secondNode;
    }
  }
  if (secondNode == root_tmp) {
    root_ = firstNode;
  } else {
    if (secondNode->parent_->left_ == secondNode) {
      secondNode->parent_->left_ = firstNode;
    } else {
      secondNode->parent_->right_ = firstNode;
    }
  }

  std::swap(firstNode->parent_, secondNode->parent_);
  std::swap(firstNode->left_, secondNode->left_);
  std::swap(firstNode->right_, secondNode->right_);
  std::swap(firstNode->color_, secondNode->color_);

  if (firstNode->left_ != nil_) {
    firstNode->left_->parent_ = firstNode;
  }
  if (firstNode->right_ != nil_) {
    firstNode->right_->parent_ = firstNode;
  }
  if (secondNode->left_ != nil_) {
    secondNode->left_->parent_ = secondNode;
  }
  if (secondNode->right_ != nil_) {
    secondNode->right_->parent_ = secondNode;
  }
  UpdateFake();
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::erase(iterator pos) {
  Node *deletedNode = pos.GetNode();

  if (deletedNode != nil_) {
    if (deletedNode->left_ != nil_ && deletedNode != nil_) {
      SwapNode(deletedNode, GetMax(deletedNode->left_));
    }
    int count_child = (deletedNode->left_ == nil_ ? 0 : 1) +
                      (deletedNode->right_ == nil_ ? 0 : 1);

    if (count_child == 1) {
      if (deletedNode->left_ != nil_) {
        SwapNode(deletedNode, deletedNode->left_);
      } else {
        SwapNode(deletedNode, deletedNode->right_);
      }
    }

    if (count_child == 0 && deletedNode->color_ == BLACK) {
      BalanceErase(deletedNode);
    }
    root_->color_ = BLACK;
    DeleteNode(deletedNode);
    --size_;
  }
  UpdateFake();
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::DeleteNode(Node *deletedNode) {
  if (deletedNode == root_) {
    root_ = nullptr;
  } else {
    if (deletedNode->parent_->left_ == deletedNode) {
      deletedNode->parent_->left_ = nil_;
    } else {
      deletedNode->parent_->right_ = nil_;
    }
  }
  delete deletedNode;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::Node *RBTree<T, Comparator>::LeftBalanceErase(
    Node *cur_node, Node *parent, bool *is_break) {
  Node *bro = parent->right_;

  if (bro->color_ == BLACK) {
    if (bro->right_->color_ == RED) {
      bro->right_->color_ = BLACK;
      std::swap(bro->color_, parent->color_);
      LeftRotate(parent);
      *is_break = true;
    } else if (bro->left_->color_ == RED) {
      std::swap(bro->color_, bro->left_->color_);
      RightRotate(bro);
    } else {
      bro->color_ = RED;
      if (parent->color_ == RED) {
        parent->color_ = BLACK;
        *is_break = true;
      } else {
        cur_node = parent;
      }
    }
  } else {
    std::swap(bro->color_, parent->color_);
    LeftRotate(parent);
  }
  return cur_node;
}

template <typename T, typename Comparator>
typename RBTree<T, Comparator>::Node *RBTree<T, Comparator>::RightBalanceErase(
    Node *cur_node, Node *parent, bool *is_break) {
  Node *bro = parent->left_;

  if (bro->color_ == BLACK) {
    if (bro->left_->color_ == RED) {
      std::swap(bro->color_, parent->color_);
      bro->left_->color_ = BLACK;
      RightRotate(parent);
      *is_break = true;
    } else if (bro->right_->color_ == RED) {
      std::swap(bro->color_, bro->right_->color_);
      LeftRotate(bro);
    } else {
      bro->color_ = RED;
      if (parent->color_ == RED) {
        parent->color_ = BLACK;
        *is_break = true;
      } else {
        cur_node = parent;
      }
    }
  } else {
    std::swap(bro->color_, parent->color_);
    RightRotate(parent);
  }
  return cur_node;
}

template <typename T, typename Comparator>
void RBTree<T, Comparator>::BalanceErase(Node *node) {
  Node *cur_node = node;
  bool is_break = false;

  while (cur_node->parent_ != nil_ && !is_break) {
    Node *parent = cur_node->parent_;

    if (parent->left_ == cur_node) {
      cur_node = LeftBalanceErase(cur_node, parent, &is_break);
    } else {
      cur_node = RightBalanceErase(cur_node, parent, &is_break);
    }
  }
}

// HELPER

// template <typename T, typename Comparator>
// void RBTree<T, Comparator>::PrintTree() {
//   std::cout << "------------------\n";
//   PrintTree(root_);
//   std::cout << "------------------\n";
// }

// template <typename T, typename Comparator>
// void RBTree<T, Comparator>::PrintTree(Node *node, int indent) {
//   int space = 3;
//   if (node) {
//     if (node->right_ != nil_) {
//       PrintTree(node->right_, indent + space);
//     }
//     if (indent) {
//       std::cout << std::setw(indent) << ' ';
//     }
//     std::cout << indent << ':' << node->color_ << '\n';
//     if (node->left_ != nil_) {
//       PrintTree(node->left_, indent + space);
//     }
//   }
// }

}  // namespace s21