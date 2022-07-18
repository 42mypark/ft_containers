LIBNAME		=	ftstl
FILENAME	=	lib$(LIBNAME).a

SRCS			=	test_dependency.cpp
OBJS_DIR	=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
INCS			= -Isrcs

TESTS			=	test1.test test2.test
TEST_DIR	=	test

VPATH			=	$(shell ls -R)
RM				=	rm -rf
# DEP		:=	$(OBJS:.o=.d)

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


