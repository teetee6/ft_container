#include "vector.hpp"
/*
single element (1)
	iterator insert (iterator position, const value_type& val);

fill (2)
    void insert (iterator position, size_type n, const value_type& val);

range (3)
	template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);
*/

#define TESTED_TYPE int

int		main(void)
{
	ft::vector<TESTED_TYPE> vct(10);
	ft::vector<TESTED_TYPE> vct2;
	ft::vector<TESTED_TYPE> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	std::cout << vct.size() << ", " << vct.capacity() << std::endl;	// 10 10

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl; // 3,3

	vct2.insert(vct2.end() - 2, 42);
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl; // 4,6

	vct2.insert(vct2.end(), 2, 84);
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl; // 6,6

	vct2.resize(4);
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl;	// 4, 6

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());	// 14, 14
	vct.clear();
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl;

	std::cout << vct.size() << ", " << vct.capacity() << std::endl;

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	std::cout << vct3.size() << ", " << vct3.capacity() << std::endl;

	return (0);
}
