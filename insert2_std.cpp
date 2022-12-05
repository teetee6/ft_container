#include <vector>
#include <iostream>

#define TESTED_TYPE int

int		main(void)
{
	std::vector<TESTED_TYPE> vct(5);
	std::vector<TESTED_TYPE> vct2;
	const int cut = 3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 7;
	std::cout << vct.size() << ", " << vct.capacity() << std::endl;	// 5, 5

	vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);	
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl;	// 3, 3
	vct2.insert(vct2.begin(), vct.begin() + cut, vct.end());
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl;
	vct2.insert(vct2.end(), vct.begin(), vct.begin() + cut);
	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl;

	std::cout << "insert return:" << std::endl;

	std::cout << *vct2.insert(vct2.end(), 42) << std::endl;
	std::cout << *vct2.insert(vct2.begin() + 5, 84) << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	std::cout << vct2.size() << ", " << vct2.capacity() << std::endl;
	return (0);
}
