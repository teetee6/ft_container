#include "type_traits.hpp"

struct Obj {};

int main()
{
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << ft::is_integral<bool>::value << std::endl;
    std::cout << ft::is_integral<char>::value << std::endl;
    std::cout << ft::is_integral<signed char>::value << std::endl;
    std::cout << ft::is_integral<unsigned char>::value << std::endl;
    std::cout << ft::is_integral<wchar_t>::value << std::endl;
    std::cout << ft::is_integral<short>::value << std::endl;
    std::cout << ft::is_integral<unsigned short>::value << std::endl;
    std::cout << ft::is_integral<int>::value << std::endl;
    std::cout << ft::is_integral<unsigned int>::value << std::endl;
    std::cout << ft::is_integral<unsigned long long>::value << std::endl;
    std::cout << ft::is_integral<__int128_t>::value << std::endl;
    std::cout << ft::is_integral<__uint128_t>::value << std::endl;
    std::cout << ft::is_integral<Obj>::value << std::endl;
    std::cout << std::endl;

    int a = 5, b;
    b = ft::integral_constant<int, 5>();
    std::cout << b << std::endl;

    ft::integral_constant<int, 5> good;
    std::cout << good() << ",\t" << typeid(good()).name() << std::endl;

    std::cout << "----------------------------------------------------------------" << std::endl;
    ft::enable_if<true>::type();
    std::cout << typeid(ft::enable_if<true, int>::type).name() << std::endl;
    
    ft::enable_if<true, int>::type kkk = 5;
    std::cout << kkk << std::endl;
    // ft::enable_if<false>::type();
    // ft::enable_if<false, int>::type;
}