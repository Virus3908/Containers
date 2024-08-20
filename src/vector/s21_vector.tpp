#include "s21_vector.h"

namespace s21 {

template <typename T>
vector<T>::vector() : arr_(nullptr) {}

template <typename T>
vector<T>::vector(size_type n)
    : arr_(n ? new value_type[n] : nullptr), size_(n), capacity_(n) {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) : vector() {
  for (auto it : items) {
    push_back(it);
  }
  shrink_to_fit();
}

template <typename T>
vector<T>::vector(const vector &other) : vector() {
  *this = other;
}

template <typename T>
vector<T>::vector(vector &&other) : vector() {
  *this = std::move(other);
}

template <typename T>
vector<T>::~vector() {
  clear();
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &other) {
  if (this != &other) {
    clear();
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = new value_type[capacity_]();
    for (size_type i = 0; i < other.size_; ++i){
      arr_[i] = other.arr_[i];
    }
  }
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&other) {
  if (this != &other) {
    clear();
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = other.arr_;
    other.size_ = 0U;
    other.capacity_ = 0U;
    other.arr_ = nullptr;
  }
  return *this;
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Out of range");
  }
  return arr_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return arr_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  return const_cast<reference>(static_cast<const vector &>(*this).at(pos));
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return const_cast<reference>(
      static_cast<const vector &>(*this).operator[](pos));
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("Out of range");
  }
  return *arr_;
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("Out of range");
  }
  return *(arr_ + size_ - 1);
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
  return const_cast<reference>(static_cast<const vector &>(*this).front());
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return const_cast<reference>(static_cast<const vector &>(*this).back());
}

template <typename T>
const typename vector<T>::value_type *vector<T>::data() const {
  return arr_;
}

template <typename T>
typename vector<T>::value_type *vector<T>::data() {
  return const_cast<value_type *>(static_cast<const vector &>(*this).data());
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(arr_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return const_iterator(arr_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(arr_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return const_iterator(arr_ + size_);
}

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0U;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<value_type>::max();
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size >= capacity()) {
    capacity_ = size;
    value_type *tmp = new value_type[capacity_]();
    size_type i = 0;
    for (auto it = begin(); it != end(); ++it, ++i){
      tmp[i] = *it;
    }
    delete[] arr_;
    arr_ = tmp;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  capacity_ = size_;
  reserve(size_);
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (index > size_) {
    throw std::out_of_range("Out of range");
  }
  if (size_ >= capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }
  for (size_type it = size_; it > index; --it) {
    *(arr_ + it) = *(arr_ + it - 1);
  }
  *(arr_ + index) = value;
  ++size_;
  return arr_ + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - begin();
  if (index > size_) {
    throw std::out_of_range("Out of range");
  }
  std::copy(data(), data() + index, arr_);
  std::copy(data() + index + 1, data()+size_, arr_ + index);
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
void vector<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0U;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args... args) {
  for (const auto &arg : {args...}) {
    pos = insert(pos, arg);
    ++pos;
  }
  return pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args... args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

}  // namespace s21