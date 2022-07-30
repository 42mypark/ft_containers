SRCS				=	$(SRCS_UTILS)
SRCS_UTILS	=	is_integral.cpp\
							remove_cv.cpp

OBJS_DIR	=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
INCS			= -Isrcs/utils \
						-Isrcs/utils/is_integral \
						-Isrcs/vector\
						-Isrcs/map


TESTS			=	is_integral.test enable_if.test vector.test lexicographical_compare.test pair.test rbtree.test #reverse_iterator.test
TEST_DIR	=	test
CXXFLAGS	= -fsanitize=address -g
ifeq ($(shell uname), Darwin)
	CXXFLAGS += -std=c++98
endif
ifeq ($(shell uname), Linux)
	CXXFLAGS += -std=c++11
endif

VPATH			=	$(shell ls -R)
RM				=	rm -rf

all: $(TESTS)

$(OBJS_DIR)/%.o : %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJS_DIR):
	mkdir $@

re: fclean all

fclean: clean
	$(RM) $(TESTS)
	$(RM) *.dSYM
	$(RM) *.out
	$(RM) *.test

clean:
	$(RM) $(OBJS_DIR)

test: $(TESTS)

%.test: $(TEST_DIR)/%_main.cpp
	$(CXX) $< $(INCS) -o $@ $(CXXFLAGS)


