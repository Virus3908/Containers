CXX=g++
CFLAGS=-std=c++17 -Wall -Werror -Wextra
LIBFLAGS=-lgtest -lgtest_main
GCOV_FLAG= --coverage
CLANG_FORMAT = ../materials/linters/.clang-format


OS = $(shell uname)

ifeq ("$(OS)","Linux")
	LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=yes --log-file=1.txt
else
	LEAKS_RUN_TEST = leaks -atExit -- 
endif

# OBJ = s21_containers.o
TEST_CPP = $(wildcard tests/*.cpp)
TEST_OBJ = $(TEST_CPP:.cpp=.o)

all: test

rebuild: clean all

# s21_containers.a: $(OBJ)
# 	mkdir -p obj	
# 	ar -rcs $(@F) obj/$(<F)
# 	ranlib $(@F)

%.o: %.cpp
	mkdir -p obj
	$(CXX) $(CFLAGS) -c $< -o obj/$(@F)

# %.o: %.h
# 	mkdir -p obj
# 	$(CXX) $(CFLAGS) -c $< -o obj/$(@F)

test.exe: $(TEST_OBJ)
	$(CXX) $(CFLAGS) $(addprefix obj/,$(^F)) -o test $(LIBFLAGS)

test: all test.exe
	./test

gcov_obj/%.o: %.cpp
	mkdir -p gcov_obj
	$(CXX) $(CFLAGS) $(GCOV_FLAG) -c $< -o gcov_obj/$(@F)

leak_test: all test.exe
	$(LEAKS_RUN_TEST) ./test

gcov_report: clean $(addprefix gcov_obj/,$(TEST_OBJ))
	$(CXX) $(CFLAGS) $(TEST_OBJ:tests/%=gcov_obj/%) -o test $(LIBFLAGS) $(GCOV_FLAG)
	./test
	mkdir report
	gcovr -r . --html --html-details -o ./report/index.html
	open report/index.html

clean:
	rm -rf obj/ *.o *.a *.out test report test.* gcov_obj *.gcda *.gcno

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i *.h ./*/*.tpp ./*/*.cpp ./*/*.h ./*/*/*.tpp ./*/*/*.h
	clang-format --style=file:$(CLANG_FORMAT) -n *.h ./*/*.tpp ./*/*.cpp ./*/*.h ./*/*/*.tpp ./*/*/*.h

.PHONY: all clean test s21_containers.a gcov_report rebuild

# g++ -std=c++17 -lgtest -lgtest_main *.cpp