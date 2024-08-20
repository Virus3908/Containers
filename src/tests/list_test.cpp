#include "test.h"

TEST(LIST, case1) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(LIST, case2) {
  s21::list<int> s21_list_int(5);
  s21::list<double> s21_list_double(5);
  s21::list<std::string> s21_list_string(5);

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_string.size(), 5U);
}

TEST(LIST, case3) {
  EXPECT_THROW(s21::list<int> s21_list_int(0), std::out_of_range);
  EXPECT_THROW(s21::list<double> s21_list_double(0), std::out_of_range);
  EXPECT_THROW(s21::list<std::string> s21_list_string(0), std::out_of_range);
}

TEST(LIST, case4) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_int.front(), 1);

  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_double.front(), 1.4);

  EXPECT_EQ(s21_list_string.size(), 4U);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(LIST, case5) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int(s21_list_ref_int);

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double(s21_list_ref_double);

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string(s21_list_ref_string);

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case6) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int = s21_list_ref_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double = s21_list_ref_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string = s21_list_ref_string;

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case7) {
  s21::list<int> s21_list_ref_int;
  s21::list<int> s21_list_res_int = s21_list_ref_int;

  s21::list<double> s21_list_ref_double;
  s21::list<double> s21_list_res_double = s21_list_ref_double;

  s21::list<std::string> s21_list_ref_string;
  s21::list<std::string> s21_list_res_string = s21_list_ref_string;

  EXPECT_EQ(s21_list_res_int.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 0U);
}

TEST(LIST, case8) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int = std::move(s21_list_ref_int);
  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double = std::move(s21_list_ref_double);
  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string = std::move(s21_list_ref_string);
  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case9) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;
  s21_list_res_int = std::move(s21_list_ref_int);

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;
  s21_list_res_double = std::move(s21_list_ref_double);

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;
  s21_list_res_string = std::move(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case10) {
  s21::list<int> a = {43, 43, 43, 5};
  s21::list<int> b = {1};
  a = std::move(b);
  EXPECT_EQ(a.back(), 1);
}

TEST(LIST, case11) {
  size_t n = 1e4;
  s21::list<int> lst(n);
  EXPECT_EQ(lst.size(), n);
  EXPECT_TRUE(lst.max_size() != 0);
  lst.pop_back();
  lst.pop_front();
  EXPECT_EQ(lst.size(), (n - 2));
  int back = lst.back();
  int front = lst.front();
  EXPECT_EQ(back, 0);
  EXPECT_EQ(front, 0);
}

TEST(LIST, case12) {
  s21::list<double> lst = {1.032, 2.320,    3.0,   4.0,   5.0,
                           6.0,   7.000043, 8.324, 9.343, 10.0};
  EXPECT_EQ(lst.size(), 10U);
  double front = lst.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  lst.pop_front();
  double new_front = lst.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  lst.pop_back();
  double back = lst.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(lst.size(), 8U);
  lst.clear();
  EXPECT_EQ(lst.size(), 0U);
}

TEST(LIST, case13) {
  s21::list<double> lst = {1.032, 2.32,     3.0,   4.0,   5.0,
                           6.0,   7.000043, 8.324, 9.343, 10.0};
  s21::list<double> lst_cpy(lst);
  EXPECT_EQ(lst_cpy.size(), 10U);
  double front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  lst_cpy.pop_front();
  double new_front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  double back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 10.0);
  lst_cpy.pop_back();
  back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(lst_cpy.size(), 8U);
}

TEST(LIST, case14) {
  s21::list<double> lst = {1.032, 2.32,     3.0,   4.0,   5.0,
                           6.0,   7.000043, 8.324, 9.343, 10.0};
  s21::list<double> lst_cpy(std::move(lst));
  EXPECT_EQ(lst_cpy.size(), 10U);
  double front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  lst_cpy.pop_front();
  double new_front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  double back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 10.0);
  lst_cpy.pop_back();
  back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(lst_cpy.size(), 8U);
  EXPECT_EQ(lst.size(), 0U);
}

TEST(LIST, case15) {
  std::list<int> orig_list = {};
  s21::list<int> lst = {};
  auto orig_itr_end = orig_list.end();
  auto itr_end = lst.end();
  EXPECT_EQ(*orig_itr_end, *itr_end);
}

TEST(LIST, case16) {
  std::list<int> orig_list;
  s21::list<int> lst;
  auto orig_itr = orig_list.end();
  auto itr = lst.end();
  EXPECT_EQ(*orig_itr, *itr);
}

TEST(LIST_PUSH_FRONT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.push_front(33);
  s21_list_double.push_front(33.0);
  s21_list_string.push_front("33");

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_int.front(), 33);

  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_double.front(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 5U);
  EXPECT_EQ(s21_list_string.front(), "33");
}

TEST(LIST_PUSH_FRONT, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  s21_list_int.push_front(33);
  s21_list_double.push_front(33.0);
  s21_list_string.push_front("33");

  EXPECT_EQ(s21_list_int.size(), 1U);
  EXPECT_EQ(s21_list_int.front(), 33);

  EXPECT_EQ(s21_list_double.size(), 1U);
  EXPECT_EQ(s21_list_double.front(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 1U);
  EXPECT_EQ(s21_list_string.front(), "33");
}

TEST(LIST_PUSH_FRONT, case3) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.push_front(33);
  s21_list_double.push_front(33.0);
  s21_list_string.push_front("33");

  EXPECT_EQ(s21_list_int.size(), 2U);
  EXPECT_EQ(s21_list_int.front(), 33);

  EXPECT_EQ(s21_list_double.size(), 2U);
  EXPECT_EQ(s21_list_double.front(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 2U);
  EXPECT_EQ(s21_list_string.front(), "33");
}

TEST(LIST_PUSH_FRONT, case4) {
  s21::list<int> li = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> li_orig = {1, 2, 10, 3, 4, 6, 43};
  li.push_front(21);
  li_orig.push_front(21);
  auto itr_orig = li_orig.begin();
  for (auto itr = li.begin(); itr != li.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }

  s21::list<int> li1;
  std::list<int> li_orig1;
  li1.push_front(21);
  li_orig1.push_front(21);
  auto itr_orig1 = li_orig1.begin();
  for (auto itr1 = li1.begin(); itr1 != li1.end(); itr1++) {
    EXPECT_EQ(*itr1, *itr_orig1);
    itr_orig1++;
  }
}

TEST(LIST_PUSH_BACK, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.push_back(33);
  s21_list_double.push_back(33.0);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_double.back(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 5U);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(LIST_PUSH_BACK, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  s21_list_int.push_back(33);
  s21_list_double.push_back(33.0);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 1U);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_double.size(), 1U);
  EXPECT_EQ(s21_list_double.back(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 1U);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(LIST_PUSH_BACK, case3) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.push_back(33);
  s21_list_double.push_back(33.0);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 2U);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_double.size(), 2U);
  EXPECT_EQ(s21_list_double.back(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 2U);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(LIST_POP_FRONT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.pop_front();
  s21_list_double.pop_front();
  s21_list_string.pop_front();

  EXPECT_EQ(s21_list_int.size(), 3U);
  EXPECT_EQ(s21_list_int.front(), 4);

  EXPECT_EQ(s21_list_double.size(), 3U);
  EXPECT_EQ(s21_list_double.front(), 4.8);

  EXPECT_EQ(s21_list_string.size(), 3U);
  EXPECT_EQ(s21_list_string.front(), ",");
}

TEST(LIST_POP_FRONT, case2) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.pop_front();
  s21_list_double.pop_front();
  s21_list_string.pop_front();

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(LIST_POP_FRONT, case3) {
  s21::list<int> li = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> li_orig = {1, 2, 10, 3, 4, 6, 43};
  li.pop_front();
  li_orig.pop_front();
  auto itr_orig = li_orig.begin();
  for (auto itr = li.begin(); itr != li.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }
}

TEST(LIST_POP_BACK, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.pop_back();
  s21_list_double.pop_back();
  s21_list_string.pop_back();

  EXPECT_EQ(s21_list_int.size(), 3U);
  EXPECT_EQ(s21_list_int.back(), 8);

  EXPECT_EQ(s21_list_double.size(), 3U);
  EXPECT_EQ(s21_list_double.back(), 8.9);

  EXPECT_EQ(s21_list_string.size(), 3U);
  EXPECT_EQ(s21_list_string.back(), "world");
}

TEST(LIST_POP_BACK, case2) {
  s21::list<int> s21_list_int{1, 2};
  s21::list<double> s21_list_double{1.0, 2.0};
  s21::list<std::string> s21_list_string{"1", "2"};

  s21_list_int.pop_back();
  s21_list_double.pop_back();
  s21_list_string.pop_back();

  EXPECT_EQ(s21_list_int.size(), 1U);
  EXPECT_EQ(s21_list_double.size(), 1U);
  EXPECT_EQ(s21_list_string.size(), 1U);
}

TEST(LIST_FRONT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(LIST_FRONT, case2) {
  s21::list<char> li = {'l', 'o', 'l'};
  std::list<char> li_orig = {'l', 'o', 'l'};
  EXPECT_EQ(li.front(), li_orig.front());
}

TEST(back, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.back(), 9);
  EXPECT_EQ(s21_list_double.back(), 9.1);
  EXPECT_EQ(s21_list_string.back(), "!");
}

TEST(swap, case1) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int{12, 13};

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double{11.0, 12.0, 13.0};

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string{"12", "13", "14", "15"};

  s21_list_ref_int.swap(s21_list_res_int);
  s21_list_ref_double.swap(s21_list_res_double);
  s21_list_ref_string.swap(s21_list_res_string);

  EXPECT_EQ(s21_list_ref_int.size(), 2U);
  EXPECT_EQ(s21_list_ref_int.front(), 12);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 3U);
  EXPECT_EQ(s21_list_ref_double.front(), 11.0);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 4U);
  EXPECT_EQ(s21_list_ref_string.front(), "12");
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(swap, case2) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;

  s21_list_ref_int.swap(s21_list_res_int);
  s21_list_ref_double.swap(s21_list_res_double);
  s21_list_ref_string.swap(s21_list_res_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(sort, case1) {
  s21::list<int> s21_list_int{8, 1, 4, 9};
  s21::list<double> s21_list_double{9.1, 1.4, 4.8, 8.9};
  s21::list<std::string> s21_list_string{"hello", "there", "21", "school"};

  s21_list_int.sort();
  s21_list_double.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "21");
}

TEST(sort, case2) {
  s21::list<int> s21_list_int{8};
  s21::list<double> s21_list_double{9.1};
  s21::list<std::string> s21_list_string{"hello"};

  s21_list_int.sort();
  s21_list_double.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 8);
  EXPECT_EQ(s21_list_double.front(), 9.1);
  EXPECT_EQ(s21_list_string.front(), "hello");
}

TEST(merge, case1) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int{12, 13};
  std::list<int> std_list_ref_int{1, 4, 8, 9};
  std::list<int> std_list_res_int{12, 13};

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double{11.0, 12.0, 13.0};
  std::list<double> std_list_ref_double{1.4, 4.8, 8.9, 9.1};
  std::list<double> std_list_res_double{11.0, 12.0, 13.0};

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string{"12", "13", "14", "15"};
  std::list<std::string> std_list_ref_string{"Hello", ",", "world", "!"};
  std::list<std::string> std_list_res_string{"12", "13", "14", "15"};

  s21_list_res_int.merge(s21_list_ref_int);
  s21_list_res_double.merge(s21_list_ref_double);
  s21_list_res_string.merge(s21_list_ref_string);
  std_list_res_int.merge(std_list_ref_int);
  std_list_res_double.merge(std_list_ref_double);
  std_list_res_string.merge(std_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), std_list_ref_int.size());
  EXPECT_EQ(s21_list_res_int.size(), std_list_res_int.size());
  EXPECT_EQ(s21_list_res_int.front(), std_list_res_int.front());

  EXPECT_EQ(s21_list_ref_double.size(), std_list_ref_double.size());
  EXPECT_EQ(s21_list_res_double.size(), std_list_res_double.size());
  EXPECT_EQ(s21_list_res_double.front(), std_list_res_double.front());

  EXPECT_EQ(s21_list_ref_string.size(), std_list_ref_string.size());
  EXPECT_EQ(s21_list_res_string.size(), std_list_res_string.size());
  EXPECT_EQ(s21_list_res_string.front(), std_list_res_string.front());
}

TEST(merge, case2) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;

  s21_list_res_int.merge(s21_list_ref_int);
  s21_list_res_double.merge(s21_list_ref_double);
  s21_list_res_string.merge(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(merge, case3) {
  s21::list<int> li = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> li_orig = {1, 2, 10, 3, 4, 6, 43};
  s21::list<int> list_merge = {2, 5, 7, 9};
  std::list<int> list_merge_orig = {2, 5, 7, 9};
  li.sort();
  li_orig.sort();
  li.merge(list_merge);
  li_orig.merge(list_merge_orig);
  auto itr_orig = li_orig.begin();
  for (auto itr = li.begin(); itr != li.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }
}

TEST(reverse, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.reverse();
  s21_list_double.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 9);
  EXPECT_EQ(s21_list_double.front(), 9.1);
  EXPECT_EQ(s21_list_string.front(), "!");
}

TEST(reverse, case2) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.4};
  s21::list<std::string> s21_list_string{"Hello"};

  s21_list_int.reverse();
  s21_list_double.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(unique, case1) {
  s21::list<int> s21_list_int{1, 1, 4, 4, 8, 8, 8, 9, 9, 9, 9, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 1.4, 4.8, 8.9, 9.1,
                                    1.4, 4.8, 8.9, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",",     "Hello", ",",
                                         "world", ",",     "world", "!",
                                         "!",     "world", "!"};

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 10U);
  EXPECT_EQ(s21_list_string.size(), 10U);
}

TEST(unique, case2) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_string.size(), 4U);
}

TEST(unique, case3) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(size, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_string.size(), 4U);
}

TEST(size, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(max_size, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  std::list<int> std_list_int{1, 4, 8, 9};

  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  std::list<double> std_list_double{1.4, 4.8, 8.9, 9.1};

  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};
  std::list<std::string> std_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.max_size(), std_list_int.max_size());
  EXPECT_EQ(s21_list_double.max_size(), std_list_double.max_size());
  EXPECT_EQ(s21_list_string.max_size(), std_list_string.max_size());
}

TEST(LIST_EMPTY, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.empty(), 0);
  EXPECT_EQ(s21_list_double.empty(), 0);
  EXPECT_EQ(s21_list_double.empty(), 0);
}

TEST(LIST_EMPTY, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.empty(), 1);
  EXPECT_EQ(s21_list_double.empty(), 1);
  EXPECT_EQ(s21_list_double.empty(), 1);
}

TEST(LIST_EMPTY, case3) {
  s21::list<int> li;
  std::list<int> li_orig;
  EXPECT_EQ(li.front(), li_orig.front());
}

TEST(LIST_EMPTY, case4) {
  s21::list<int> li;
  std::list<int> li_orig;
  EXPECT_EQ(li.back(), li_orig.back());
}

TEST(LIST_INSERT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  ++it_int;
  ++it_int;
  it_int = s21_list_int.insert(it_int, 13);
  it_int = s21_list_int.begin();
  ++it_int;
  ++it_int;
  EXPECT_EQ(s21_list_int.front(), 13);
  EXPECT_EQ(*it_int, 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  ++it_double;
  ++it_double;
  it_double = s21_list_double.insert(it_double, 21.0);
  it_double = s21_list_double.begin();
  ++it_double;
  ++it_double;
  EXPECT_EQ(s21_list_double.front(), 21.0);
  EXPECT_EQ(*it_double, 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  ++it_string;
  ++it_string;
  it_string = s21_list_string.insert(it_string, "HI");
  it_string = s21_list_string.begin();
  ++it_string;
  ++it_string;
  EXPECT_EQ(s21_list_string.front(), "HI");
  EXPECT_EQ(*it_string, "HI");
}

TEST(LIST_INSERT, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  EXPECT_EQ(s21_list_double.front(), 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(LIST_INSERT, case3) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  EXPECT_EQ(s21_list_double.front(), 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(LIST_INSERT, case4) {
  s21::list<int> li;
  std::list<int> li_orig;
  auto itr = li.begin();
  auto itr_orig = li_orig.begin();
  itr = li.insert(itr, 21);
  itr_orig = li_orig.insert(itr_orig, 21);
  EXPECT_EQ(*itr, *itr_orig);

  s21::list<int> li1 = {1, 2, 3, 4, 6, 43};
  std::list<int> li_orig1 = {1, 2, 3, 4, 6, 43};
  auto itr1 = li1.begin();
  auto itr_orig1 = li_orig1.begin();
  itr1 = li1.insert(itr1, 21);
  itr_orig1 = li_orig1.insert(itr_orig1, 21);
  auto end1 = li1.end();
  auto end_orig1 = li_orig1.end();
  while (itr1 != end1 && itr_orig1 != end_orig1) {
    EXPECT_EQ(*itr1, *itr_orig1);
    itr1++;
    itr_orig1++;
  }

  s21::list<int> li2 = {1, 2, 3, 4, 6, 44};
  std::list<int> li_orig2 = {1, 2, 3, 4, 6, 44};
  auto itr2 = li2.end();
  auto itr_orig2 = li_orig2.end();
  itr2 = li2.insert(itr2, 21);
  itr_orig2 = li_orig2.insert(itr_orig2, 21);
  itr2--;
  itr_orig2--;
  while (itr2 != li2.begin() && itr_orig2 != li_orig2.begin()) {
    EXPECT_EQ(*itr2, *itr_orig2);
    itr2--;
    itr_orig2--;
  }
}

TEST(LIST_SPLICE, case1) {
  s21::list<int> s21_list_ref_int{3, 5};
  s21::list<int> s21_list_res_int{1, 4, 8, 9};

  s21::list<double> s21_list_ref_double{5.6, 7.1};
  s21::list<double> s21_list_res_double{1.4, 4.8, 8.9, 9.1};

  s21::list<std::string> s21_list_ref_string{"Hi"};
  s21::list<std::string> s21_list_res_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 3);
  EXPECT_EQ(*(++(s21_list_res_int.begin())), 5);

  auto it_double = s21_list_res_double.begin();
  s21_list_res_double.splice(it_double, s21_list_ref_double);
  EXPECT_EQ(*(s21_list_res_double.begin()), 5.6);
  EXPECT_EQ(*(++(s21_list_res_double.begin())), 7.1);

  auto it_string = s21_list_res_string.begin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hi");
}

TEST(LIST_SPLICE, case2) {
  s21::list<int> s21_list_ref_int;
  s21::list<int> s21_list_res_int{1, 4, 8, 9};

  s21::list<double> s21_list_ref_double;
  s21::list<double> s21_list_res_double{1.4, 4.8, 8.9, 9.1};

  s21::list<std::string> s21_list_ref_string;
  s21::list<std::string> s21_list_res_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 1);

  auto it_double = s21_list_res_double.begin();
  s21_list_res_double.splice(it_double, s21_list_ref_double);
  EXPECT_EQ(*(s21_list_res_double.begin()), 1.4);

  auto it_string = s21_list_res_string.begin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hello");
}

TEST(LIST_SPLICE, case3) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 1);

  auto it_double = s21_list_res_double.begin();
  s21_list_res_double.splice(it_double, s21_list_ref_double);
  EXPECT_EQ(*(s21_list_res_double.begin()), 1.4);

  auto it_string = s21_list_res_string.begin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hello");
}

TEST(LIST_ITERATOR, case1) {
  s21::list<int> li = {1, 2, 3, 4, 6, 43};
  std::list<int> li_orig = {1, 2, 3, 4, 6, 43};
  unsigned int n = li.size();
  unsigned int n_orig = li_orig.size();
  EXPECT_EQ(n, n_orig);
  auto itr = li.begin();
  auto itr_orig = li_orig.begin();
  auto end = li.end();
  auto end_orig = li_orig.end();
  while (itr != end && itr_orig != end_orig) {
    EXPECT_EQ(*itr, *itr_orig);
    itr++;
    itr_orig++;
  }
}

TEST(LIST_ITERATOR, case2) {
  s21::list<int> li = {1, 2, 3, 4, 6, 43};
  std::list<int> li_orig = {1, 2, 3, 4, 6, 43};
  unsigned int n = li.size();
  unsigned int n_orig = li_orig.size();
  EXPECT_EQ(n, n_orig);
  auto itr = li.end();
  auto itr_orig = li_orig.end();
  itr--;
  itr_orig--;
  auto end = li.begin();
  auto end_orig = li_orig.begin();
  while (itr != end && itr_orig != end_orig) {
    EXPECT_EQ(*itr, *itr_orig);
    itr--;
    itr_orig--;
  }
}

TEST(List, Constructor_Default) {
  s21::list<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Constructor_Size) {
  s21::list<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(List, Constructor_List) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Constructor_Copy) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy(our_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(List, Operator_Copy) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy;
  our_copy = our_list;
  std::list<int> std_copy;
  std_copy = std_list;
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(List, Constructor_Move) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Operator_Move) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Size) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(List, Push_Front) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Push_Back) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Pop_Front) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Pop_Back) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Iterator_Begin) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_BeginPlusAndMinus) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_End_Last) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator our_it;
  our_it = our_list.end();
  --our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Insert) {
  s21::list<int> our_list;
  std::list<int> std_list;
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Erase) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Splice) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(List, Merge) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(List, Reverse) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Unique) {
  s21::list<int> our_list = {1, 2, 2, 3, 3};
  std::list<int> std_list = {1, 2, 2, 3, 3};
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.unique();
  std_list.unique();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Sort) {
  s21::list<int> our_list = {2, 4, 1, 3, 5};
  std::list<int> std_list = {2, 4, 1, 3, 5};
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.sort();
  std_list.sort();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Insert_Many) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, Insert_Many_Back) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  our_it = our_list.end();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(List, Insert_Many_Front) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}
// int main() {
//   testing::InitGoogleTest();
//   return RUN_ALL_TESTS();
// }
