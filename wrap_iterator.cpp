#include "wrap_iterator.hpp"
#include "./utility.hpp"
#include <string>
#include <iostream>

int main()
{
    int test = 0;
    std::cout << "-----------------------------["<< ++test <<"]-----------------------------" << std::endl;
    int b[1]; b[0]=3;
    __wrap_iter<int> a(b);
    std::cout << *a << std::endl;
    std::cout << a.operator->() << std::endl;
    
    ft::pair<int, char> tmp(1, 2);
    __wrap_iter<ft::pair<int, char> > c(&tmp);
    std::cout << c->first << std::endl; 
    std::cout << c.operator->()->first << std::endl; 
    std::cout << &(*c) << std::endl; 
    
    std::cout << "-----------------------------["<< ++test <<"]-----------------------------" << std::endl;
    std::string str1("abcde");
    std::string str2("abcde");
    std::string str3("abcdf");
    typedef std::string::iterator sit;
    sit from1(str1.begin()), from2(str2.begin()), from3(str3.begin()), end1(str1.end());
    __wrap_iter<char> ft_from1(from1.base()), ft_from2(from2.base()), ft_from3(from3.base()), ft_end1(end1.base());

    std::cout << (ft_from1 < ft_end1) << (ft_from1 <= ft_end1) << (ft_from1 > ft_end1) << (ft_from1 >= ft_end1) << std::endl;
    std::cout << (ft_from1 == ft_end1) << (ft_from1 != ft_end1) << std::endl;
    std::cout << (ft_from1 == ft_from1) << (ft_from1 == ft_from2) << std::endl;
    std::cout << std::endl;

    std::cout << *ft_from1 << std::endl;
    std::cout << *(ft_from1 +4) << std::endl;
    std::cout << *(ft_from1 += 2) << std::endl;
    std::cout << ft_from1[2] << std::endl;
    std::cout << std::endl;

    std::cout << "-----------------------------["<< ++test <<"]-----------------------------" << std::endl;
    ft_from1 = from1.base();
    std::cout << *ft_from1 << std::endl;
    std::cout << std::endl;

    std::cout << *(ft_end1 -= 1) << std::endl;
    std::cout << *ft_end1-- << std::endl;
    std::cout << *ft_end1 << std::endl;
    std::cout << *--ft_end1 << std::endl; // c
    std::cout << *(ft_end1 - 2) << std::endl;
    std::cout << *(2 + ft_end1) << std::endl;
    std::cout << (((ft_end1 - 2) == ft_from1) ? "true" : "false") << std::endl;
    std::cout << ft_end1 - ft_from1 << std::endl;
}