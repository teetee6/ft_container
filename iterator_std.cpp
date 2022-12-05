#include "iterator.hpp"

struct triple {
    int a,b,c;
    triple(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {};
};

int main() {
    typedef ft::iterator_traits<int*> traits;
    if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator" << std::endl;
    std::cout << std::endl;

    int arr1[5] = {111,222,333,444,555};
    std::vector<int> vec1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    ft::reverse_iterator< std::vector<int>::iterator > rit;
    ft::reverse_iterator< std::vector<int>::iterator > until(vec1.begin());
    ft::reverse_iterator< std::vector<int>::iterator > from(vec1.end());
    for(rit = from; rit != until; rit++)
    {
       std::cout << *rit << "(my base value:" << *rit.base() << ")" << std::endl; 
    }
    std::cout << "end-->" << *rit << "(my base:" << *rit.base() << ")" << std::endl; 
    std::cout << std::endl;
    
    {
        rit = from + 3;
        std::cout << "rbegin() + 3 -->\t";
        std::cout << *rit << "(my base:" << *rit.base() << ")"<< std::endl;
        
        std::vector<int>::iterator it;
        it = vec1.begin() + 1;
        std::cout << "begin() + 1  -->\t";
        std::cout << *it << "(my base:" << *it.base() << ")"<< std::endl;
        
        // std::vector<int>::reverse_iterator rit2(it);
        ft::reverse_iterator< std::vector<int>::iterator > rit2(it);
        std::cout << "rit(it)      -->\t";
        std::cout << *rit2 << "(my base:" << *rit2.base() << ")"<< std::endl;
    }
    std::cout << std::endl;
    {
        rit = 2 + from;
        std::cout << *rit << "(my base:" << *rit.base() << ")"<< std::endl;
        std::cout << rit[0] << " --- " << rit[1] << std::endl;
        
        std::map<int, int> _map;
        _map.insert(std::pair<int, int>(7, 8));
        std::map<int, int>::reverse_iterator _rit_map = _map.rbegin();
        std::cout << _rit_map->first << std::endl;
    }
    return 0;
}