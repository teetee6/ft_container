#include "vector.hpp"
#include <iostream>

int main() {

	std::cout << "----------------------------------------" << std::endl;
	{
		std::vector<int> vec;
		vec.push_back(3);
		vec.push_back(7);
		std::cout << vec[0] << std::endl;
		try {
			std::cout << vec.at(3) << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << vec.at(1) << std::endl;
		std::cout << std::endl;

		std::cout << "(normal iter test)" << std::endl;
		std::vector<int>::iterator it = vec.begin();
		*it = 8;
		std::cout << *it++ << std::endl;
		std::cout << *it << std::endl;

		std::cout << "(const iter test)" << std::endl;
		std::vector<int>::const_iterator cit = vec.begin();
		// *cit = 7777;
		std::cout << *cit++ << std::endl;
		std::cout << *cit << std::endl;

		std::cout << "(reverse iter test)" << std::endl;
		std::vector<int>::reverse_iterator rit = vec.rbegin();
		for(; rit != vec.rend(); ++rit) {
			*rit += 100;
			std::cout << *rit << std::endl;
		}

		std::cout << "(const reverse iter test)" << std::endl;
		std::vector<int>::const_reverse_iterator crit = vec.rbegin();
		for(; crit != vec.rend(); ++crit) {
			// *crit += 7777;
			std::cout << *crit << std::endl;
		}
	}

	int arr[] = {0, 11111, 22222, 33333, 44444, 55555};
	std::vector< int > ft_default;
	std::vector< int > ft_fill(4, 77777);
	std::vector< int > ft_range(arr, arr + (sizeof(arr) / sizeof(int)));
	std::vector< int > ft_copy(ft_range);
	std::cout << "----------------------------------------" << std::endl;
	{
		std::vector<int>::iterator ft_fill_begin = ft_fill.begin();
		std::vector<int>::iterator ft_fill_end = ft_fill.end();
		std::cout << ft_fill.size() << ", " << ft_fill.capacity() << std::endl;
		for(std::vector<int>::iterator iter = ft_fill_begin; iter != ft_fill_end; ++iter) {
			std::cout << *iter << " ";
		}
		std::cout << std::endl;	
	}
	{
		std::vector<int>::iterator ft_range_begin = ft_range.begin();
		std::vector<int>::iterator ft_range_end = ft_range.end();
		std::cout << ft_range.size() << ", " << ft_range.capacity() << std::endl;
		for(std::vector<int>::iterator iter = ft_range_begin; iter != ft_range_end; ++iter) {
			std::cout << *iter << " ";
		}
		std::cout << std::endl;	
		{
			std::vector<int>::iterator ft_copy_begin = ft_copy.begin();
			std::vector<int>::iterator ft_copy_end = ft_copy.end();
			std::cout << ft_copy.size() << ", " << ft_copy.capacity() << std::endl;
			for(std::vector<int>::iterator iter = ft_copy_begin; iter != ft_copy_end; ++iter) {
				std::cout << *iter << " ";
			}
			std::cout << std::endl;	
		}
	}
	std::cout << "----------------------------------------" << std::endl;
	{
		std::vector<int> vec;
		for(int i=0; i<100; )
			vec.push_back(i++);
		std::cout << vec.size() << ", " << vec.capacity() << std::endl;
		vec.push_back(100);
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 100
		std::cout << std::endl;
		
		std::cout << "\tErase test" << std::endl;
		vec.erase(vec.begin() + 10, vec.begin() + 20);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 20 21 ... 100
		std::cout << std::endl;

		vec.erase(vec.begin());
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 1 2 ... 9 20 21 ... 100
		std::cout << std::endl;

		std::cout << "\tInsert test" << std::endl;
		vec.insert(vec.begin() + 9, 10, 99999);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 1 2 ... 9 99999 ... 99999 20 21 ... 100
		std::cout << std::endl;

		vec.insert(vec.begin(), 0);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 100
		std::cout << std::endl;

		vec.insert(vec.begin() + vec.size(), vec.begin(), vec.begin() + 30); // realloc
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 100 0 1 2 ... 29
		std::cout << std::endl;

		std::cout << "\tAssign test" << std::endl;
		vec.assign(vec.begin(), vec.begin() + 100);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 99
		std::cout << std::endl;

		std::vector<int> vec2 = vec;
		vec2.assign(22, 1);
		for(std::vector<int>::iterator it = vec2.begin(); it != vec2.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec2.size() << ", " << vec2.capacity() << std::endl; // 1 1 1 ... 1
		std::cout << std::endl;

		std::cout << "\tResize test" << std::endl;
		vec.resize(50);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 49
		std::cout << std::endl;

		vec.resize(70, 88888);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 49 88888 ... 88888
		std::cout << std::endl;

		std::cout << "\tReserve test" << std::endl;
		vec.reserve(10);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 49 88888 ... 88888
		std::cout << std::endl;

		vec.reserve(200);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 49 88888 ... 88888
		std::cout << std::endl;

		std::cout << "\tSwap test" << std::endl;
		vec.swap(vec2);
		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec.size() << ", " << vec.capacity() << std::endl; // 1 1 1 ... 1 
		std::cout << std::endl;

		for(std::vector<int>::iterator it = vec2.begin(); it != vec2.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << vec2.size() << ", " << vec2.capacity() << std::endl; // 0 1 2 ... 9 99999 ... 99999 20 21 ... 49 88888 ... 88888
		std::cout << std::endl;

		std::cout << "\tOperator test" << std::endl;
		std::cout << (vec < vec2) << (vec <= vec2) << (vec > vec2) << (vec >= vec2) << (vec == vec2) << (vec != vec2) << std::endl;
		std::cout << std::endl;

		std::cout << "\tEmpty test" << std::endl;
		std::vector<int> emp_vec;
		std::cout << vec.empty() << std::endl;
		std::cout << emp_vec.empty() << std::endl;
	}

}