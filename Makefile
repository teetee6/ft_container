SRCS = main.cpp	\
	algorithm_std.cpp	\
	algorithm.cpp \
	insert_std.cpp \
	insert.cpp \
	insert2_std.cpp \
	insert2.cpp \
	iterator_std.cpp \
	iterator.cpp \
	type_traits.cpp \
	utility_std.cpp \
	utility.cpp \
	vector_std.cpp \
	vector.cpp \
	wrap_iterator_std.cpp \
	wrap_iterator.cpp 

INCS = algorithm.hpp \
	function_base.hpp \
	iterator.hpp \
	map.hpp \
	rbtree.hpp \
	set.hpp \
	stack.hpp \
	type_traits.hpp \
	utility.hpp \
	vector.hpp \
	wrap_iterator.hpp 

CXX = c++
NAME = a.out

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
