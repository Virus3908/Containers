#ifndef S21_LIST_H
#define S21_LIST_H

#include <limits>

#include "../Node/s21_node.h"
#include "../iterator/list_iterator/s21_list_iterator.h"

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = Node_t<T>;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  list();                                                // done
  list(size_type n);                                     // done
  list(std::initializer_list<value_type> const &items);  // done
  list(const list &list);                                // done
  list(list &&list);                                     // done
  ~list();                                               // done

  list<T> &operator=(list &&list);       // done
  list<T> &operator=(const list &list);  // done

  reference front();              // done
  reference back();               // done
  const_reference front() const;  // done
  const_reference back() const;   // done

  iterator begin();              // done
  iterator end();                // done
  const_iterator begin() const;  // done
  const_iterator end() const;    // done

  bool empty() const;          // done
  size_type size() const;      // done
  size_type max_size() const;  // done

  void clear();                                          // done
  iterator insert(iterator pos, const_reference value);  // done
  void erase(iterator pos);                              // done
  void push_back(const_reference value);                 // done
  void pop_back();                                       // done
  void push_front(const_reference value);                // done
  void pop_front();                                      // done
  void swap(list &other);                                // done
  void merge(list &other);
  void splice(const_iterator pos, list &other);  // done
  void reverse();                                // done
  void unique();                                 // done
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  size_type size_ = 0U;
  Node *end_;

  Node *CreateEnd();
};

};  // namespace s21

#include "s21_list.tpp"

#endif