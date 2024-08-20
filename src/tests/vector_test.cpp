#include "../vector/s21_vector.h"
#include "test.h"

#define s21_EPS 1e-7

using MyTypes = testing::Types<int, double, std::vector<int>, std::string>;

template <typename T>
class vectorTest : public testing::Test {
 protected:
  s21::vector<T> vec;
  std::vector<T> std_vec;
};

TEST(Testvector, DefaultConstructor) {
  s21::vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Testvector, ParamZeroConstructor) {
  size_t size = 0U;
  s21::vector<int> vec(size);
  std::vector<int> std_vec(size);

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Testvector, ParamSmallConstructor) {
  size_t size = 2U;
  s21::vector<int> vec(size);
  std::vector<int> std_vec(size);

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Testvector, ParamBigConstructor) {
  size_t size = 100U;
  s21::vector<int> vec(size);
  std::vector<int> std_vec(size);

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Listvector, Intvector) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_EQ(vec.size(), std_vec.size());
  // EXPECT_EQ(vec.max_size(), std_vec.max_size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Listvector, Doublevector) {
  s21::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  EXPECT_EQ(vec.size(), std_vec.size());
  // EXPECT_EQ(vec.max_size(), std_vec.max_size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Listvector, Stringvector) {
  s21::vector<std::string> vec{"1", "2", "3", "4", "5"};
  std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  EXPECT_EQ(vec.size(), std_vec.size());
  // EXPECT_EQ(vec.max_size(), std_vec.max_size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Testvector, CopyConstructor) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector vec(origin);

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, ordata);
  EXPECT_EQ(vec.size(), origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], ordata[i]);
  }
}

TEST(Testvector, MoveConstructor) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector vec(std::move(origin));

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(4U, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, data[i]);
  }
}

TEST(Testvector, CopyAssignment) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector<unsigned> vec(15);

  vec = origin;

  EXPECT_EQ(4U, vec.size());
  EXPECT_EQ(4U, origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(origin[i], vec[i]);
  }
}

TEST(Testvector, MoveAssignment) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector<unsigned> vec(15);

  vec = std::move(origin);

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(4U, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, data[i]);
  }
}

TEST(Testvector, MoveAssign) {
  s21::vector<int> original(5);
  s21::vector<int> moved(6);
  original = std::move(moved);

  std::vector<int> std_vec(5);
  std::vector<int> std_moved(6);
  std_vec = std::move(std_moved);

  EXPECT_EQ(moved.size(), 0U);
  EXPECT_EQ(moved.capacity(), 0U);
  EXPECT_EQ(original.size(), 6U);
  EXPECT_EQ(original.capacity(), 6U);

  EXPECT_EQ(std_moved.size(), 0U);
  EXPECT_EQ(std_moved.capacity(), 0U);
  EXPECT_EQ(std_vec.size(), 6U);
  EXPECT_EQ(std_vec.capacity(), 6U);
}

// TEST(vectorTest, MoveSelfAssign) {
//   // по сути это уб
//   s21::vector<int> original(5);
//   original = std::move(original);

//   std::vector<int> std_vec(5);
//   std_vec = std::move(std_vec);

//   EXPECT_EQ(original.size(), 0U);
//   EXPECT_EQ(original.capacity(), 0U);

//   EXPECT_EQ(std_vec.size(), 0U);
//   EXPECT_EQ(std_vec.capacity(), 0U);
// }

// AT, [], front, back, empty
TEST(vector, Intvector) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  vec.at(1) = 10;
  std_vec.at(1) = 10;

  EXPECT_EQ(vec.at(1), 10);
  EXPECT_EQ(std_vec.at(1), 10);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  vec[2] = 20;
  std_vec[2] = 20;

  EXPECT_EQ(vec[2], 20);
  EXPECT_EQ(std_vec[2], 20);

  vec.front() = 30;
  std_vec.front() = 30;

  EXPECT_EQ(vec.front(), 30);
  EXPECT_EQ(std_vec.front(), 30);

  vec.back() = 40;
  std_vec.back() = 40;

  EXPECT_EQ(vec.back(), 40);
  EXPECT_EQ(std_vec.back(), 40);
}

TEST(vector, Doublevector) {
  s21::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  vec.at(1) = 10.0;
  std_vec.at(1) = 10.0;

  EXPECT_TRUE(vec.at(1) - 10 < s21_EPS);
  EXPECT_TRUE(std_vec.at(1) - 10 < s21_EPS);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  vec[2] = 20.0;
  std_vec[2] = 20.0;

  EXPECT_TRUE(vec[2] - 20.0 < s21_EPS);
  EXPECT_TRUE(std_vec[2] - 20.0 < s21_EPS);

  vec.front() = 30.0;
  std_vec.front() = 30.0;

  EXPECT_TRUE(vec.front() - 30 < s21_EPS);
  EXPECT_TRUE(std_vec.front() - 30 < s21_EPS);

  vec.back() = 40.0;
  std_vec.back() = 40.0;

  EXPECT_TRUE(vec.back() - 40 < s21_EPS);
  EXPECT_TRUE(std_vec.back() - 40 < s21_EPS);
}

TEST(vector, Stringvector) {
  s21::vector<std::string> vec{"1", "2", "3", "4", "5"};
  std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  vec.at(1) = "10";
  std_vec.at(1) = "10";

  EXPECT_EQ(vec.at(1), "10");
  EXPECT_EQ(std_vec.at(1), "10");

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  vec[2] = "20";
  std_vec[2] = "20";

  EXPECT_EQ(vec[2], "20");
  EXPECT_EQ(std_vec[2], "20");

  vec.front() = "30";
  std_vec.front() = "30";

  EXPECT_EQ(vec.front(), "30");
  EXPECT_EQ(std_vec.front(), "30");

  vec.back() = "40";
  std_vec.back() = "40";

  EXPECT_EQ(vec.back(), "40");
  EXPECT_EQ(std_vec.back(), "40");
}
// CONST!!!
TEST(vector, ConstIntvector) {
  const s21::vector<int> vec{1, 2, 3, 4, 5};
  const std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(std_vec.at(1), 2);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(std_vec[2], 3);

  EXPECT_EQ(vec.front(), 1);
  EXPECT_EQ(std_vec.front(), 1);

  EXPECT_EQ(vec.back(), 5);
  EXPECT_EQ(std_vec.back(), 5);
}

TEST(vector, ConstDoublevector) {
  const s21::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  const std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  EXPECT_TRUE(vec.at(1) - 2.0 < s21_EPS);
  EXPECT_TRUE(std_vec.at(1) - 2.0 < s21_EPS);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  EXPECT_TRUE(vec[2] - 3.0 < s21_EPS);
  EXPECT_TRUE(std_vec[2] - 3.0 < s21_EPS);

  EXPECT_TRUE(vec.front() - 1.0 < s21_EPS);
  EXPECT_TRUE(std_vec.front() - 1.0 < s21_EPS);

  EXPECT_TRUE(vec.back() - 5.0 < s21_EPS);
  EXPECT_TRUE(std_vec.back() - 5.0 < s21_EPS);
}

TEST(vector, ConstStringvector) {
  const s21::vector<std::string> vec{"1", "2", "3", "4", "5"};
  const std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  EXPECT_EQ(vec.at(1), "2");
  EXPECT_EQ(std_vec.at(1), "2");

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  EXPECT_EQ(vec[2], "3");
  EXPECT_EQ(std_vec[2], "3");

  EXPECT_EQ(vec.front(), "1");
  EXPECT_EQ(std_vec.front(), "1");

  EXPECT_EQ(vec.back(), "5");
  EXPECT_EQ(std_vec.back(), "5");
}

// iterators: data, begin, end + reserve

void check_int_iterator(const int* p, std::size_t size) {
  int entry = 0;
  for (std::size_t i = 0; i < size; ++i) {
    EXPECT_EQ(p[i], ++entry);
  }
}

template <typename Iterator>
void check_begin_end_int_iterator(Iterator begin, Iterator end) {
  int entry = 0;
  for (auto it = begin; it != end; ++it) {
    EXPECT_EQ(*it, ++entry);
  }
}

TEST(vectorIterator, IntIterator) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  check_int_iterator(vec.data(), vec.size());
  check_int_iterator(std_vec.data(), vec.size());

  vec.reserve(10);
  std_vec.reserve(10);

  check_begin_end_int_iterator(vec.begin(), vec.end());
  check_begin_end_int_iterator(std_vec.begin(), std_vec.end());
}

void check_double_iterator(const double* p, std::size_t size) {
  double entry = 1.0;
  for (std::size_t i = 0; i < size; ++i) {
    EXPECT_TRUE(std::abs(p[i] - entry) < s21_EPS);
    entry += 1.0;
  }
}

template <typename Iterator>
void check_begin_end_double_iterator(Iterator begin, Iterator end) {
  int entry = 1.0;
  for (auto it = begin; it != end; ++it) {
    EXPECT_TRUE(std::abs(*it - entry) < s21_EPS);
    entry += 1.0;
  }
}

TEST(vectorIterator, DoubleIterator) {
  s21::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  check_double_iterator(vec.data(), vec.size());
  check_double_iterator(std_vec.data(), vec.size());

  vec.reserve(10);
  std_vec.reserve(10);

  check_begin_end_double_iterator(vec.begin(), vec.end());
  check_begin_end_double_iterator(std_vec.begin(), std_vec.end());
}

void check_string_iterator(const std::string* p, std::size_t size) {
  int entry = 0;
  for (std::size_t i = 0; i < size; ++i) {
    std::string strNumber = std::to_string(++entry);
    EXPECT_EQ(p[i], strNumber);
  }
}

template <typename Iterator>
void check_begin_end_string_iterator(Iterator begin, Iterator end) {
  int entry = 0;
  for (auto it = begin; it != end; ++it) {
    std::string strNumber = std::to_string(++entry);
    EXPECT_EQ(*it, strNumber);
  }
}

TEST(vectorIterator, StringIterator) {
  s21::vector<std::string> vec{"1", "2", "3", "4", "5"};
  std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  check_string_iterator(vec.data(), vec.size());
  check_string_iterator(std_vec.data(), vec.size());

  vec.reserve(10);
  std_vec.reserve(10);

  check_begin_end_string_iterator(vec.begin(), vec.end());
  check_begin_end_string_iterator(std_vec.begin(), std_vec.end());
}
// CONST!!!
TEST(vectorIterator, ConstIntIterator) {
  const s21::vector<int> vec{1, 2, 3, 4, 5};
  const std::vector<int> std_vec{1, 2, 3, 4, 5};

  check_int_iterator(vec.data(), vec.size());
  check_int_iterator(std_vec.data(), vec.size());

  check_begin_end_int_iterator(vec.begin(), vec.end());
  check_begin_end_int_iterator(std_vec.begin(), std_vec.end());
}

TEST(vectorIterator, ConstDoubleIterator) {
  const s21::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  const std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  check_double_iterator(vec.data(), vec.size());
  check_double_iterator(std_vec.data(), vec.size());

  check_begin_end_double_iterator(vec.begin(), vec.end());
  check_begin_end_double_iterator(std_vec.begin(), std_vec.end());
}

TEST(vectorIterator, ConstStringIterator) {
  const s21::vector<std::string> vec{"1", "2", "3", "4", "5"};
  const std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  check_string_iterator(vec.data(), vec.size());
  check_string_iterator(std_vec.data(), vec.size());

  check_begin_end_string_iterator(vec.begin(), vec.end());
  check_begin_end_string_iterator(std_vec.begin(), std_vec.end());
}

// modifiers: insert, erase, push back, pop back
TEST(Modifiers, IntNotEmptyModifiers) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  vec.insert(vec.begin(), 10);
  vec.insert(vec.begin() + 2, 20);
  vec.insert(vec.end(), 30);
  std_vec.insert(std_vec.begin(), 10);
  std_vec.insert(std_vec.begin() + 2, 20);
  std_vec.insert(std_vec.end(), 30);
  ASSERT_EQ(vec.size(), 8U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }

  vec.erase(vec.begin());
  std_vec.erase(std_vec.begin());
  vec.erase(vec.end() - 1);
  std_vec.erase(std_vec.end() - 1);
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }

  vec.push_back(100);
  std_vec.push_back(100);

  ASSERT_EQ(vec.size(), 7U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }

  vec.pop_back();
  std_vec.pop_back();

  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }
}

TEST(Modifiers, IntEmptyBeginModifiers) {
  s21::vector<int> vec;
  std::vector<int> std_vec;

  vec.insert(vec.begin(), 10);
  std_vec.insert(std_vec.begin(), 10);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, IntEmptyEndModifiers) {
  s21::vector<int> vec;
  std::vector<int> std_vec;

  vec.insert(vec.end(), 10);
  std_vec.insert(std_vec.end(), 10);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, IntEmptyPushModifiers) {
  s21::vector<int> vec;
  std::vector<int> std_vec;

  vec.push_back(10);
  std_vec.push_back(10);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, IntEmptyPushCapacityChangeModifiers) {
  s21::vector<int> vec(5);
  std::vector<int> std_vec(5);

  vec.push_back(10);
  std_vec.push_back(10);
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(5), std_vec.at(5));
}

TEST(Modifiers, DoubleNotEmptyModifiers) {
  s21::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  vec.insert(vec.begin(), 10.0);
  vec.insert(vec.begin() + 2, 20.0);
  vec.insert(vec.end(), 30.0);
  std_vec.insert(std_vec.begin(), 10.0);
  std_vec.insert(std_vec.begin() + 2, 20.0);
  std_vec.insert(std_vec.end(), 30.0);
  ASSERT_EQ(vec.size(), 8U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }

  vec.erase(vec.begin());
  std_vec.erase(std_vec.begin());
  vec.erase(vec.end() - 1);
  std_vec.erase(std_vec.end() - 1);
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }

  vec.push_back(100.0);
  std_vec.push_back(100.0);
  ASSERT_EQ(vec.size(), 7U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }

  vec.pop_back();
  std_vec.pop_back();
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }
}

TEST(Modifiers, DoubleEmptyBeginModifiers) {
  s21::vector<double> vec;
  std::vector<double> std_vec;

  vec.insert(vec.begin(), 10.0);
  std_vec.insert(std_vec.begin(), 10.0);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  EXPECT_TRUE((vec.at(0) - std_vec.at(0) < s21_EPS));
}

TEST(Modifiers, DoubleEmptyEndModifiers) {
  s21::vector<double> vec;
  std::vector<double> std_vec;

  vec.insert(vec.end(), 10.0);
  std_vec.insert(std_vec.end(), 10.0);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  EXPECT_TRUE((vec.at(0) - std_vec.at(0) < s21_EPS));
}

TEST(Modifiers, DoubleEmptyPushModifiers) {
  s21::vector<double> vec;
  std::vector<double> std_vec;

  vec.push_back(10.0);
  std_vec.push_back(10.0);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  EXPECT_TRUE((vec.at(0) - std_vec.at(0) < s21_EPS));
}

TEST(Modifiers, StringNotEmptyModifiers) {
  s21::vector<std::string> vec{"1.0", "2.0", "3.0", "4.0", "5.0"};
  std::vector<std::string> std_vec{"1.0", "2.0", "3.0", "4.0", "5.0"};

  vec.insert(vec.begin(), "10");
  vec.insert(vec.begin() + 2, "20");
  vec.insert(vec.end(), "30");
  std_vec.insert(std_vec.begin(), "10");
  std_vec.insert(std_vec.begin() + 2, "20");
  std_vec.insert(std_vec.end(), "30");
  ASSERT_EQ(vec.size(), 8U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }
}

TEST(Modifiers, StringEmptyBeginModifiers) {
  s21::vector<std::string> vec;
  std::vector<std::string> std_vec;

  vec.insert(vec.begin(), "10");
  std_vec.insert(std_vec.begin(), "10");
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, StringEmptyEndModifiers) {
  s21::vector<std::string> vec;
  std::vector<std::string> std_vec;

  vec.insert(vec.end(), "10");
  std_vec.insert(std_vec.end(), "10");
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, StringEmptyPushModifiers) {
  s21::vector<std::string> vec;
  std::vector<std::string> std_vec;

  vec.push_back("10");
  std_vec.push_back("10");
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Testvector, EmptyIterator) {
  s21::vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_TRUE(vec.begin() == vec.end());
  EXPECT_TRUE(std_vec.begin() == std_vec.end());
}

// reserve
TEST(Testvector, ReserseSmall) {
  size_t size = 2U;
  s21::vector<int> vec(size);
  std::vector<int> std_vec(size);

  vec.reserve(1);
  std_vec.reserve(1);

  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

// reserve, shrink_to_fit
TEST(Testvector, ReserseBig) {
  size_t size = 2U;
  s21::vector<int> vec(size);
  std::vector<int> std_vec(size);

  vec.reserve(5);
  std_vec.reserve(5);

  EXPECT_EQ(vec.capacity(), std_vec.capacity());

  vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(Testvector, Clear) {
  s21::vector<int> vec;
  vec.clear();
  EXPECT_EQ(0U, vec.size());

  s21::vector<char> vec2({'a', 'b', 'c'});
  vec2.clear();
  EXPECT_EQ(0U, vec2.size());
}

TEST(Testvector, Swap) {
  s21::vector<int> vec({1, 2, 3, 4});
  s21::vector copied_vec(vec);
  auto size = vec.size();
  auto capacity = vec.capacity();
  auto data = vec.data();

  s21::vector<int> other_vec({5, 6, 7, 8, 9, 10});
  s21::vector copied_other_vec(other_vec);
  auto other_size = other_vec.size();
  auto other_capacity = other_vec.capacity();
  auto other_data = other_vec.data();

  vec.swap(other_vec);

  EXPECT_EQ(vec.size(), other_size);
  EXPECT_EQ(other_vec.size(), size);

  EXPECT_EQ(copied_other_vec.size(), vec.size());
  EXPECT_EQ(copied_vec.size(), other_vec.size());

  EXPECT_EQ(vec.capacity(), other_capacity);
  EXPECT_EQ(other_vec.capacity(), capacity);

  EXPECT_EQ(vec.data(), other_data);
  EXPECT_EQ(other_vec.data(), data);

  for (size_t i = 0; i < copied_vec.size(); ++i) {
    EXPECT_EQ(copied_vec[i], other_vec[i]);
  }

  for (size_t i = 0; i < copied_other_vec.size(); ++i) {
    EXPECT_EQ(copied_other_vec[i], vec[i]);
  }
}
TEST(Testvector, Empty) {
  s21::vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_TRUE(vec.empty());
  EXPECT_TRUE(std_vec.empty());
}

// [] - получим сег фолт даже по стандартному вектору
TEST(Testvector, AtFromEmpty) {
  s21::vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_THROW(vec.at(0), std::out_of_range);
  EXPECT_THROW(vec.at(1), std::out_of_range);
  EXPECT_THROW(std_vec.at(0), std::out_of_range);
  EXPECT_THROW(std_vec.at(1), std::out_of_range);
}

TEST(VectorTest, DefaultConstructor_EmptyVector) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0U);
}

TEST(VectorTest, SizeConstructor_PositiveSize) {
  const size_t size = 5;
  s21::vector<int> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, SizeConstructor_ZeroSize) {
  const size_t size = 0;
  s21::vector<int> v(size);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(VectorTest, InitializerListConstructor_EmptyList) {
  s21::vector<int> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0U);
}

TEST(VectorTest, InitializerListConstructor_NonEmptyList) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 5U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0U);
}

TEST(VectorTest, CopyConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTest, MoveConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0U);
}

TEST(VectorTest, MoveConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 3U);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, Destructor_EmptyVector) {
  s21::vector<int>* v = new s21::vector<int>();
  delete v;  // Destructor should be called here
  // No specific assertions, but this ensures the destructor is working
}

TEST(VectorTest, Destructor_NonEmptyVector) {
  s21::vector<int>* v = new s21::vector<int>{1, 2, 3};
  delete v;  // Destructor should be called here
  // No specific assertions, but this ensures the destructor is working
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0U);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3U);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToNonEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0U);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3U);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, At_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);
}

TEST(VectorTest, At_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(VectorTest, IndexOperator_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

// TEST(VectorTest, IndexOperator_InvalidIndex) {
//   s21::vector<int> v = {1, 2, 3, 4, 5};
//   EXPECT_ANY_THROW(v[5]);
//   EXPECT_ANY_THROW(v[10]);
// }

TEST(VectorTest, ConstIndexOperator_ValidIndex) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

// TEST(VectorTest, ConstIndexOperator_InvalidIndex) {
//   const s21::vector<int> v = {1, 2, 3, 4, 5};
//   EXPECT_ANY_THROW(v[5]);
//   EXPECT_ANY_THROW(v[10]);
// }

TEST(VectorTest, FrontConst_ValidVector) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, FrontConst_EmptyVector) {
  const s21::vector<int> v;
  EXPECT_THROW(v.front(), std::out_of_range);
}

TEST(VectorTest, BackConst_ValidVector) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);
}

TEST(VectorTest, BackConst_EmptyVector) {
  const s21::vector<int> v;
  EXPECT_THROW(v.back(), std::out_of_range);
}

TEST(VectorTest, Data_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  int* dataPtr = v.data();
  EXPECT_EQ(*dataPtr, 1);
  // Modify the data through the pointer and check if the vector is updated
  *dataPtr = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, Data_EmptyVector) {
  s21::vector<int> v;
  int* dataPtr = v.data();
  // Data pointer of an empty vector can be anything
  EXPECT_EQ(dataPtr, nullptr);
}

TEST(VectorTest, Begin_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  // Modify the data through the iterator and check if the vector is updated
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, Begin_EmptyVector) {
  s21::vector<int> v;
  auto it = v.begin();
  // The begin() of an empty vector should be the end() too, so iterator should
  // be equal to end()
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, End_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  // end() iterator should not be dereferenced; comparing it to another iterator
  // should work
  auto beginIt = v.begin();
  EXPECT_NE(it, beginIt);
}

TEST(VectorTest, End_EmptyVector) {
  s21::vector<int> v;
  auto it = v.end();
  // The end() of an empty vector should be the begin() too, so iterator should
  // be equal to begin()
  EXPECT_EQ(it, v.begin());
}

TEST(VectorTest, Empty_EmptyVector) {
  const s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Empty_NonEmptyVector) {
  const s21::vector<int> v = {1, 2, 3};
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size_EmptyVector) {
  const s21::vector<int> v;
  EXPECT_EQ(v.size(), 0U);
}

TEST(VectorTest, Size_NonEmptyVector) {
  const s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.size(), 3U);
}

TEST(VectorTest, MaxSize) {
  const s21::vector<int> v;
  // You can't predict the exact max size, but it should be a very large value
  EXPECT_GT(v.max_size(), 0U);
}

TEST(VectorTest, Reserve_IncreaseCapacity) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, Reserve_DecreaseCapacity) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity - 2;
  v.reserve(newCapacity);
  // Capacity may not decrease immediately, but it shouldn't exceed the
  // requested value
  EXPECT_LE(v.capacity(), initialCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, Capacity_EmptyVector) {
  const s21::vector<int> v;
  // The capacity of an empty vector should be at least 0
  EXPECT_GE(v.capacity(), 0U);
}

TEST(VectorTest, Capacity_NonEmptyVector) {
  const s21::vector<int> v = {1, 2, 3};
  // The capacity of a non-empty vector might vary, but it should be at least
  // the size of the vector
  EXPECT_GE(v.capacity(), v.size());
}

TEST(VectorTest, ShrinkToFit_EmptyVector) {
  s21::vector<int> v;
  v.shrink_to_fit();
  // After shrink_to_fit() on an empty vector, the capacity should still be at
  // least 0
  EXPECT_GE(v.capacity(), 0U);
}

TEST(VectorTest, ShrinkToFit_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  v.pop_back();  // Simulate a reduction in size
  v.shrink_to_fit();
  // After shrink_to_fit(), the capacity should not exceed the new size
  EXPECT_LE(v.capacity(), v.size());
  // The capacity may not necessarily decrease, but it should not be larger than
  // the initial capacity
  EXPECT_LE(v.capacity(), initialCapacity);
}

TEST(VectorTest, Clear_EmptyVector) {
  s21::vector<int> v;
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0U);
  // Clearing an empty vector should not affect capacity
  EXPECT_GE(v.capacity(), 0U);
}

TEST(VectorTest, Clear_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0U);
  // Clearing a vector should not affect capacity immediately
  EXPECT_GE(v.capacity(), 0U);
}

TEST(VectorTest, Insert_Beginning) {
  s21::vector<int> v = {2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, Insert_Middle) {
  s21::vector<int> v = {1, 3, 4};
  auto it = v.insert(v.begin() + 1, 2);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, Insert_End) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.insert(v.end(), 4);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(VectorTest, Erase_Beginning) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin());  // Erase the first element
  EXPECT_EQ(v.size(), 3U);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, Erase_Middle) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 3U);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Erase_End) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.end() - 1);  // Erase the last element
  EXPECT_EQ(v.size(), 3U);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PushBack_EmptyVector) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1U);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, PushBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, PopBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2U);
  EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, PopBack_EmptyVector) {
  s21::vector<int> v;
  // Popping from an empty vector should not cause an error (undefined behavior
  // for some std::vector implementations)
  v.pop_back();
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Swap_NonEmptyVectors) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3U);
  EXPECT_EQ(v2.size(), 3U);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, Swap_EmptyAndNonEmptyVectors) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3U);
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v2.size(), 0U);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> vec = {1, 2, 3, 7, 8};
  s21::vector<int>::const_iterator pos = vec.begin() + 3;

  vec.insert_many(pos, 4, 5, 6);

  // Check the size of the vector after insertion
  EXPECT_EQ(vec.size(), 8U);

  // Check the elements after insertion
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> vec = {1, 2, 3};

  vec.insert_many_back(4, 5, 6);

  // Check the size of the vector after insertion
  EXPECT_EQ(vec.size(), 6U);

  // Check the elements after insertion
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}