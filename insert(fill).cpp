#include "vector.hpp"
#include <vector>



int main() {
    int _ratio = 10000;
    
    std::vector<int> vector;
    // ft::vector<int> vector;  //ft::vector키면 swap에서 에러남
    std::vector<int> v;
    vector.assign(1100 * _ratio, 11);
    std::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
        { std::cout << vector.size() << ", " << vector.capacity() << std::endl;}
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
        { std::cout << vector.size() << ", " << vector.capacity() << std::endl;}
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.swap(tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp4);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    return 0;
}