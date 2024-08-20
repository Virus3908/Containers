#include "s21_list_iterator.h"

namespace s21 {

template <typename T>
ListConstIterator<T>::ListConstIterator() {
  curr_pos = nullptr;
}

template <typename T>
ListConstIterator<T>::ListConstIterator(Node *pos) {
  curr_pos = pos;
}

template <typename T>
ListConstIterator<T>::ListConstIterator(const ListConstIterator &other) {
  *this = other;
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator=(
    const ListConstIterator &other) {
  curr_pos = other.curr_pos;
  return *this;
}

template <typename T>
bool ListConstIterator<T>::operator==(const ListConstIterator &other) {
  return (curr_pos == other.curr_pos);
}

template <typename T>
bool ListConstIterator<T>::operator!=(const ListConstIterator &other) {
  return (curr_pos != other.curr_pos);
}

template <typename T>
typename ListConstIterator<T>::const_reference
ListConstIterator<T>::operator*() {
  return curr_pos->val;
}

template <typename T>
typename ListConstIterator<T>::value_type *ListConstIterator<T>::operator->() {
  return curr_pos;
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator++() {
  curr_pos = curr_pos->next;
  return *this;
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator--() {
  curr_pos = curr_pos->prev;
  return *this;
}

template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator++(int) {
  ListConstIterator tmp(*this);
  ++(*this);
  return tmp;
}

template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator--(int) {
  ListConstIterator tmp(*this);
  --(*this);
  return tmp;
}

template <typename T>
typename ListConstIterator<T>::Node *ListConstIterator<T>::GetNode() {
  return curr_pos;
}

template <typename T>
ListIterator<T>::ListIterator() : ListIterator::ListConstIterator() {}

template <typename T>
ListIterator<T>::ListIterator(Node *pos)
    : ListIterator::ListConstIterator(pos) {}

template <typename T>
ListIterator<T>::ListIterator(ListIterator &other)
    : ListIterator::ListConstIterator(other) {}

template <typename T>
ListIterator<T>::ListIterator(ListConstIterator<T> &other) {
  this->curr_pos = other.GetNode();
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator=(const ListIterator &other) {
  if (this != &other) {
    ListConstIterator<T>::operator=(other);
  }
  return *this;
}

template <typename T>
typename ListIterator<T>::reference ListIterator<T>::operator*() {
  return this->GetNode()->val;
}
}  // namespace s21