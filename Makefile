LIBNAME		=	ftstl
FILENAME	=	lib$(LIBNAME).a

SRCS				=	$(SRCS_UTILS)
SRCS_UTILS	=	is_integral.cpp\
							remove_cv.cpp

OBJS_DIR	=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
INCS			= -Isrcs/utils \
						-Isrcs/utils/is_integral

TESTS			=	is_integral.test
TEST_DIR	=	test

VPATH			=	$(shell ls -R)
RM				=	rm -rf

all: $(FILENAME)

$(OBJS_DIR)/%.o : %.cpp
	$(CXX) -c $< -o $@

$(FILENAME): $(OBJS_DIR) $(OBJS)
	ar rcs $@ $(filter-out $<, $^)

$(OBJS_DIR):
	mkdir $@

fclean:
	$(RM) $(FILENAME)
	$(RM) $(TESTS)

clean:
	$(RM) $(OBJS_DIR)

test: $(FILENAME) $(TESTS)

%.test: $(TEST_DIR)/%_main.cpp
	$(CXX) $< -L. -l$(LIBNAME) $(INCS) -o $@


