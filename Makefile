SRCS				=	$(SRCS_UTILS)
SRCS_UTILS	=	is_integral.cpp\
							remove_cv.cpp

OBJS_DIR	=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
INCS			= -Isrcs/utils \
						-Isrcs/utils/is_integral\
						-Isrcs/utils/enable_if

TESTS			=	is_integral.test enable_if.test
TEST_DIR	=	test

VPATH			=	$(shell ls -R)
RM				=	rm -rf

all: $(TESTS)

$(OBJS_DIR)/%.o : %.cpp
	$(CXX) -c $< -o $@

$(OBJS_DIR):
	mkdir $@

fclean:
	$(RM) $(TESTS)

clean:
	$(RM) $(OBJS_DIR)

test: $(TESTS)

%.test: $(TEST_DIR)/%_main.cpp
	$(CXX) $< $(INCS) -o $@


