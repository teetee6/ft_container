FILENAME = 	\
	algorithm_std	\
	algorithm \
	insert_std \
	insert \
	insert2_std \
	insert2 \
	iterator_std \
	iterator \
	type_traits \
	utility_std \
	utility \
	vector_std \
	vector \
	wrap_iterator_std \
	wrap_iterator \
	main \

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(FILENAME)

$(FILENAME):
	$(CXX) $(CXXFLAGS) $@.cpp -o $@

clean:
	rm -f $(FILENAME)

fclean: clean
	rm -f $(FILENAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
