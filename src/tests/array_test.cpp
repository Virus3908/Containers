#include "test.h"

TEST(S21arrayTest, DefaultConstructor) {
  s21::array<double, 5> arr2;
  EXPECT_EQ(arr2.size(), 5.0);
}

TEST(S21arrayTest, testzero) {
  s21::array<double, 0> arr;
  EXPECT_EQ(arr.size(), 0.0);
}

TEST(s21array, initial) {
  s21::array<int, 7> arr;
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(arrayInitializationTest, InitializerListTest) {
  s21::array<int, 3> arr5 = {10, 20, 30};
  EXPECT_EQ(arr5[0], 10);
  EXPECT_EQ(arr5[1], 20);
  EXPECT_EQ(arr5[2], 30);
}

TEST(S21arrayTest, copyconstructor) {
  s21::array<int, 10> array;

  for (size_t i = 0; i < array.size(); ++i) {
    array[i] = i;
  }
  s21::array<int, 10> copy_array(array);

  for (size_t i = 0; i < array.size(); ++i) {
    EXPECT_EQ(array[i], copy_array[i]);
  }
}

TEST(S21arrayTest1, Hellow) {
  s21::array<std::string, 2> hellow;
  hellow[0] = "Hellow";
  hellow[1] = "World!";

  for (size_t i = 0; i < hellow.size(); ++i) {
    EXPECT_EQ(hellow[i], hellow[i]);
  }
}

TEST(S21arrayTest2, FloatTest) {
  s21::array<double, 100> colec_float;
  for (size_t i = 0; i < colec_float.size(); ++i) {
    colec_float[i] = i;
  }
  for (size_t i = 0; i < colec_float.size(); ++i) {
    EXPECT_EQ(colec_float[i], i);
  }
}

TEST(S21array_copy, copy_int_float_string) {
  s21::array<std::string, 2> hellow;
  hellow[0] = "Hellow";
  hellow[1] = "World!";
  s21::array<std::string, 2> dest_hellow = hellow;
  s21::array<double, 100> colec_float;
  for (size_t i = 0; i < colec_float.size(); ++i) {
    colec_float[i] = i;
  }
  s21::array<double, 100> dest_float = colec_float;
  s21::array<int, 100> colec_int;
  for (size_t i = 0; i < colec_int.size(); ++i) {
    colec_int[i] = i;
  }
  s21::array<int, 100> dest_int = colec_int;

  EXPECT_EQ(dest_hellow[0], hellow[0]);
  EXPECT_EQ(dest_hellow[1], hellow[1]);

  for (size_t i = 0; i < dest_float.size(); ++i) {
    EXPECT_EQ(dest_float[i], colec_float[i]);
  }

  for (size_t i = 0; i < dest_int.size(); ++i) {
    EXPECT_EQ(dest_int[i], colec_int[i]);
  }
}

TEST(S21arraySize, Size_double) {
  s21::array<double, 3> arr;

  for (size_t i = 0; i < arr.size(); ++i) {
    arr[i] = i * 1.5;
  }

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_DOUBLE_EQ(arr[i], i * 1.5);
  }
}

TEST(S21arraySize, Size_char) {
  s21::array<char, 10> arr;

  EXPECT_EQ(static_cast<int>(arr.size()), 10);

  s21::array<std::string, 1> arr2;
  EXPECT_EQ(arr2.size(), static_cast<size_t>(1));
}

TEST(S21arrayAt, int_test) {
  s21::array<int, 10> arrayint;
  for (size_t i = 0; i > arrayint.size(); ++i) {
    arrayint[i] = i + 15;
  }

  EXPECT_THROW(arrayint.at(11), std::out_of_range);
}
TEST(S21arrayAt, TestFloat) {
  s21::array<float, 10> arrayfloat;
  for (size_t i = 0; i > arrayfloat.size(); ++i) {
    arrayfloat[i] = 0.0;
  }
  EXPECT_THROW(arrayfloat.at(-11), std::out_of_range);
}

TEST(Arryoperatoreq, testoperator) {
  s21::array<int, 50> eqarray;
  for (size_t i = 0; i < eqarray.size(); i++) {
    eqarray[i] = i + 2;
  }
  s21::array<int, 50> &destarray = eqarray;

  for (size_t i = 0; i < eqarray.size(); i++) {
    EXPECT_EQ(destarray[i], eqarray[i]);
  }
}
TEST(S21array, testchar) {
  s21::array<char, 50> eqarray;
  for (size_t i = 0; i < eqarray.size(); ++i) {
    eqarray[i] = i;
  }
  s21::array<char, 50> &destarray = eqarray;
  for (size_t i = 0; i < eqarray.size(); i++) {
    EXPECT_EQ(destarray[i], eqarray[i]);
  }
}

TEST(S21array, constfloat) {
  s21::array<float, 5> array;
  for (size_t i = 0; i < array.size(); ++i) {
    array[i] = 0.0;
  }
  const s21::array<float, 5> &const_array = array;
  for (size_t i = 0; i < const_array.size(); ++i) {
    EXPECT_EQ(array[i], const_array[i]);
  }
}

TEST(S21array, conststr) {
  s21::array<std::string, 100> arraystr;
  for (size_t i = 0; i < arraystr.size(); ++i) {
    arraystr[i] = "0";
  }
  const s21::array<std::string, 100> &const_array = arraystr;
  for (size_t i = 0; i < const_array.size(); ++i) {
    EXPECT_EQ(arraystr[i], const_array[i]);
  }
}

TEST(S21array, constchar) {
  s21::array<char, 10> arraychar;
  for (size_t i = 0; i < arraychar.size(); ++i) {
    arraychar[i] = '0';
  }
  const s21::array<char, 10> &const_array = arraychar;
  for (size_t i = 0; i < const_array.size(); ++i) {
    EXPECT_EQ(arraychar[i], const_array[i]);
  }
}

TEST(S21arrayTest, Test) {
  s21::array<int, 5> arr;
  const s21::array<int, 5> &const_arr = arr;

  for (size_t i = 0; i < const_arr.size(); ++i) {
    EXPECT_EQ(const_arr[i], arr[i]);
  }
}

TEST(S21array, data) {
  s21::array<int, 3> datarray;
  datarray[0] = 1;
  EXPECT_EQ(datarray.data(), &datarray[0]);
}

TEST(S21array, end) {
  s21::array<int, 4> endarray;

  auto Ptr4 = &endarray[4];

  EXPECT_EQ(endarray.end(), Ptr4);
}

TEST(S21array, testint) {
  s21::array<int, 10> valint;
  auto Ptr = valint[0];
  auto Ptr2 = valint.front();
  EXPECT_EQ(Ptr, Ptr2);
}

TEST(S21array_char, testchar) {
  s21::array<char, 6> valchar;
  for (auto i = 0; i < 6; ++i) {
    valchar[i] = 'a' + i;
  }
  auto Ptr = valchar[0];
  auto Ptr2 = valchar.front();
  EXPECT_EQ(Ptr, Ptr2);
}
TEST(S21array_string, test_string) {
  s21::array<std::string, 2> valstring;
  s21::array<std::string, 2> word;
  word[0] = "Hello schcool 21";
  valstring[0] = "Hello schcool 21";
  EXPECT_EQ(valstring.front(), word.front());
}

TEST(S21array_back, test_char) {
  s21::array<char, 6> letters;
  for (auto i = 0; i < 6; ++i) {
    letters[i] = 'a' + i;
  }

  EXPECT_EQ(letters.back(), letters[5]);
}
TEST(S21array_back, test_int) {
  s21::array<int, 6> intvalue;
  for (auto i = 0; i < 6; ++i) {
    intvalue[i] = i;
  }
  EXPECT_EQ(intvalue.back(), intvalue[5]);
}

TEST(s21array_back, test_float) {
  s21::array<float, 10> floatvalue;
  for (auto i = 0; i < 10; ++i) {
    floatvalue[i] = i;
  }
  EXPECT_EQ(floatvalue.back(), floatvalue[9]);
}

TEST(S21array, empty_zero) {
  s21::array<float, 0> zero;
  ASSERT_TRUE(zero.empty());
}
TEST(S21array, empty_full) {
  s21::array<int, 3> full;
  for (size_t i = 0; i < full.size(); ++i) {
    full[i] = i;
  }
  EXPECT_FALSE(full.empty());
}

TEST(S21array, swap) {
  s21::array<int, 3> origin = {1, 2, 3};
  s21::array<int, 3> coppy = {0, 0, 0};
  s21::array<int, 3> zero = {0, 0, 0};
  s21::array<int, 3> num = {1, 2, 3};
  origin.swap(coppy);
  for (size_t i = 0; i < origin.size(); ++i) {
    EXPECT_EQ(zero[i], origin[i]);
    EXPECT_EQ(num[i], coppy[i]);
  }
}

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  // Check that the size is correct
  EXPECT_EQ(arr.size(), 5U);

  // Check that all elements are initialized to their default value (0 for int)
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayTest, InitListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  // Check that the size is correct
  EXPECT_EQ(arr.size(), 5U);

  // Check that each element is initialized correctly
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrCopy(arr);

  // Check that the size is correct
  EXPECT_EQ(arrCopy.size(), 5U);

  // Check that the elements are copied correctly
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrMoved(std::move(arr));

  // Check that the size is correct
  EXPECT_EQ(arrMoved.size(), 5U);

  // Check that the elements are moved correctly
  for (size_t i = 0; i < arrMoved.size(); ++i) {
    EXPECT_EQ(arrMoved[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, Begin) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  // Modify the data through the iterator and check if the array is updated
  *it = 10;
  EXPECT_EQ(arr[0], 10);
}

TEST(ArrayTest, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.end();
  // end() iterator should not be dereferenced; comparing it to another iterator
  // should work
  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(ArrayTest, At_ValidIndex) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(ArrayTest, At_OutOfBounds) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  // Attempting to access an out-of-bounds index using at() should throw an
  // exception
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(ArrayTest, ConstAt_ValidIndex) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(ArrayTest, ConstAt_OutOfBounds) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  // Attempting to access an out-of-bounds index using const at() should throw
  // an exception
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(ArrayTest, Front) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(ArrayTest, Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(ArrayTest, ConstFront) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(ArrayTest, ConstBack) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(ArrayTest, Empty_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, Empty_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, Size_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5U);
}

TEST(ArrayTest, Size_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.size(), 0U);
}

// TEST(ArrayTest, MaxSize) {
//   s21::array<int, 5> arr;
//   // The max size of an array with a specified size is the same as its
//   declared
//   // size
//   EXPECT_EQ(arr.max_size(), std::numeric_limits<int>::max());
// }

TEST(ArrayTest, Swap) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1.swap(arr2);

  // Check that the elements of arr1 are now from arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }

  // Check that the elements of arr2 are now from arr1
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(10);

  // Check that all elements are filled with the specified value
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 10);
  }
}

TEST(ArrayTest, CopyAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = arr2;

  // Check that arr1 now contains the same elements as arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = std::move(arr2);

  // Check that arr1 now contains the same elements as arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
}

TEST(ArrayTest, OperatorBracket) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  // Check that elements can be accessed using the [] operator
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }

  // Modify an element using the [] operator and check if the array is updated
  arr[2] = 10;
  EXPECT_EQ(arr[2], 10);
}