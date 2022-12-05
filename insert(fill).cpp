#include "vector.hpp"
#include <vector>
#include <iostream>


int main() {
    int _ratio = 10000;
    
    // STD
    // std::vector<int> vector;
    // // ft::vector<int> vector;  //ft::vector키면 swap에서 에러남
    // vector.assign(1100 * _ratio, 11);
    // std::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    // std::cout << vector[2] << std::endl;
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;
    //     { std::cout << vector.size() << ", " << vector.capacity() << std::endl;}
    // long *adr1 = reinterpret_cast<long *>(&vector);
    // long *adr2 = reinterpret_cast<long *>(&tmp);
    // vector.swap(tmp);
    //     { std::cout << vector.size() << ", " << vector.capacity() << std::endl;}
    // if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    // 	std::cout << 1 << std::endl;
    // std::cout << vector[2] << std::endl;
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;
    // vector.swap(tmp3);
    // std::cout << vector[2] << std::endl;
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;
    // std::swap(vector, tmp2);
    // std::cout << vector[2] << std::endl;
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;
    // std::swap(vector, tmp4);
    // std::cout << vector[2] << std::endl;
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;


    // FT
    ft::vector<int> vector;  //ft::vector키면 swap에서 에러남
    std::vector<int> v;
    // 1100만개(11)
    vector.assign(1100 * _ratio, 11); 
    // 500만(5), 1000만(10), 1500만(15), 3000만개(30)
    ft::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30); 
    std::cout << vector[2] << std::endl;    //11
    std::cout << vector.size() << std::endl;    // 1100,0000
    std::cout << vector.capacity() << std::endl;    // 1100,0000
        { std::cout << vector.size() << ", " << vector.capacity() << std::endl;}    // 1100,0000 , 1100,0000
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
        { std::cout << vector.size() << ", " << vector.capacity() << std::endl;}    // 5000000, 5000000
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	std::cout << 1 << std::endl;    // 1
    std::cout << vector[2] << std::endl;    // 5
    std::cout << vector.size() << std::endl;    // 5000000
    std::cout << vector.capacity() << std::endl;    // 5000000
    vector.swap(tmp3);
    std::cout << vector[2] << std::endl;    // 15
    std::cout << vector.size() << std::endl;    // 15000000
    std::cout << vector.capacity() << std::endl;    // 15000000
    ft::swap(vector, tmp2);
    std::cout << vector[2] << std::endl;    // 10
    std::cout << vector.size() << std::endl;    // 10000000
    std::cout << vector.capacity() << std::endl;    // 10000000 (15000000 나와버림)
    ft::swap(vector, tmp4);
    std::cout << vector[2] << std::endl;
    std::cout << vector.size() << std::endl;
    std::cout << vector.capacity() << std::endl;
    return 0;
}