CXX= g++
FLAG= -std=c++17 -Wall -Wextra -g# -Werror
R=\033[0;31m # Red
NC=\033[0m # No Color

TESTFLAG= -lgtest -pthread
TEST_DIR := tests
TESTS_SRC := $(wildcard $(TEST_DIR)/*.cc)
TESTS_RUN := $(patsubst $(TEST_DIR)/%.cc, %, $(TESTS_SRC))

all: install

install:
	-mkdir build
	cmake -S ./ -B build/
	cd build && make
	cp -r build/Maze.app .

uninstall:
	rm -rf build
	rm -rf Maze.app


dvi:
	doxygen doxy_config || true
	open ./html/index.html

dist: clean
	cd .. && tar -czvf  Maze.tar src 

clean: uninstall
	rm -rf *.o *.test || true
	rm -rf report *.gcno *.gcda *.info *.dSYM || true
	rm -rf anna || true
	rm -rf build || true
	# rm -rf dvi/ || true

test: $(TESTS_RUN)

$(TESTS_RUN): %: $(TEST_DIR)/%.cc 
	$(CXX) $(FLAG) model.cc parser.cc painter.cc matrix.cc maze.cc cave.cc $< -o $@ $(TESTFLAG) || echo "${R}CAN'T BUILD $@${NC}"
	$(VALG) ./$@ || true
	rm -rf $@

clang:
	clang-format -i -style=Google *.h *.cc 

