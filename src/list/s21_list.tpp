#include "s21_list.h"

namespace s21 {

template <typename T>
list<T>::list() : end_(new Node(value_type())) {}

template <typename T>
list<T>::list(size_type n) : list() {
  if (n <= 0) {
    throw std::out_of_range("Wrong size of list");
  }
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (const auto &i : items) {
    push_back(i);
  }
}

template <typename T>
list<T>::list(const list &other_list) : list() {
  *this = other_list;
}

template <typename T>
list<T>::list(list &&other_list) {
  if (this != &other_list) {
    head_ = other_list.head_;
    tail_ = other_list.tail_;
    size_ = other_list.size_;
    end_ = other_list.end_;
    other_list.size_ = 0;
    other_list.head_ = nullptr;
    other_list.tail_ = nullptr;
    other_list.end_ = new Node(value_type());
  }
}

template <typename T>
list<T>::~list() {
  clear();
  delete end_;
}

template <typename T>
list<T> &list<T>::operator=(const list &other_list) {
  if (this != &other_list) {
    clear();
    for (auto it = other_list.begin(); it != other_list.end(); ++it) {
      push_back(*it);
    }
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list &&other_list) {
  if (this != &other_list) {
    list<T> tmp_lst(std::move(other_list));
    *this = tmp_lst;
  }
  return *this;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  auto new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    head_->next = end_;
    end_->prev = head_;
    tail_ = head_;
  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
    tail_->next = end_;
    end_->prev = tail_;
  }
  ++size_;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  auto new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    head_->next = end_;
    end_->prev = head_;
    tail_ = head_;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (tail_) {
    Node *tail_buff = tail_;
    if (tail_->prev) {
      tail_ = tail_buff->prev;
      tail_->next = end_;
    } else {
      tail_ = nullptr;
      head_ = nullptr;
    }
    end_->prev = tail_;
    delete tail_buff;
    --size_;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (head_) {
    Node *head_buf = head_;
    if (head_->next == end_) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      head_ = head_->next;
    }
    delete head_buf;
    --size_;
  }
}

template <typename T>
void list<T>::clear() {
  while (size_ > 0) {
    pop_front();
  }
}

template <typename T>
bool list<T>::empty() const {
  return (size_ == 0);
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  iterator result = iterator(end_);
  if (!empty()) {
    result = iterator(head_);
  }
  return result;
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(end_);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  iterator result = iterator(end_);
  if (!empty()) {
    result = iterator(head_);
  }
  return (const_iterator)result;
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(end_);
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  reference res = end_->val;
  if (size_ != 0) {
    res = head_->val;
  }
  return (const_reference)res;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  reference res = end_->val;
  if (size_ != 0) {
    res = tail_->val;
  }
  return (const_reference)res;
}

template <typename T>
typename list<T>::reference list<T>::front() {
  return const_cast<reference>(static_cast<const list &>(*this).front());
}

template <typename T>
typename list<T>::reference list<T>::back() {
  return const_cast<reference>(static_cast<const list &>(*this).back());
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
#if defined(__linux__)
  return (std::numeric_limits<std::ptrdiff_t>::max()) / sizeof(Node);
#else
  return std::numeric_limits<std::ptrdiff_t>::max() / (sizeof(Node) / 2U);
#endif
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == begin()) {
    push_front(value);
  } else if (pos == end()) {
    push_back(value);
  } else {
    Node *new_node = new Node(value, pos.GetNode()->prev, pos.GetNode());
    pos.GetNode()->prev->next = new_node;
    pos.GetNode()->prev = new_node;
    ++size_;
    pos = new_node;
  }
  --pos;
  return pos;
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node *del_pos = pos.GetNode();
  if (del_pos == head_) {
    pop_front();
  } else if (del_pos == tail_) {
    pop_back();
  } else if (del_pos != end_) {
    del_pos->prev->next = del_pos->next;
    del_pos->next->prev = del_pos->prev;
    --size_;
    delete del_pos;
  }
}

template <typename T>
void list<T>::swap(list &other) {
  auto temp = std::move(other);
  other = std::move(*this);
  *this = std::move(temp);
}

template <typename T>
void list<T>::reverse() {
  if (!empty()) {
    for (auto i = begin(); i != end();) {
      Node *cur = (i++).GetNode();
      std::swap(cur->next, cur->prev);
    }
    head_->next = end_;
    tail_->prev = nullptr;
    tail_ = head_;
    head_ = end_->prev;
    end_->prev = tail_;
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (this != &other) {
    iterator new_pos(pos.GetNode());
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(new_pos, *it);
    }
    other.clear();
  }
}

template <typename T>
void list<T>::unique() {
  if (size_ > 1) {
    iterator it = begin();
    while (it != end()) {
      iterator current_it = it;
      ++it;
      if (*it == *current_it) {
        erase(it);
        it = current_it;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    list<T> left{};
    list<T> right{};
    auto support = front();
    auto it = begin();
    ++it;
    for (; it != end(); ++it) {
      if (*it < support) {
        left.push_back(*it);
      } else {
        right.push_back(*it);
      }
    }
    left.sort();
    left.push_back(support);
    right.sort();
    left.splice(left.end(), right);
    *this = left;
  }
}

template <typename T>
void list<T>::merge(list &other) {
  if (this != &other) {
    list<T> merged{};
    auto this_it = begin();
    auto other_it = other.begin();
    for (; this_it != end() && other_it != other.end();) {
      if (*this_it < *other_it) {
        merged.push_back(*this_it);
        ++this_it;
      } else {
        merged.push_back(*other_it);
        ++other_it;
      }
    }
    while (this_it != end()) {
      merged.push_back(*this_it);
      ++this_it;
    }
    while (other_it != other.end()) {
      merged.push_back(*other_it);
      ++other_it;
    }
    *this = merged;
    other.clear();
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  for (const auto &arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_front(arg);
  }
}

};  // namespace s21