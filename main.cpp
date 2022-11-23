#include "set.hpp"
#include <string>
#include "utility.hpp"
#include <list>
#include <set>
#include "map.hpp"
#include <iostream>

int main() {
    // std::set<int> a;
    // std::list<int> lst;
	// unsigned int lst_size = 10;
	// for (unsigned int i = 0; i < lst_size; ++i)
	// 	lst.push_back(i);
	// ft::set<int> st(lst.begin(), lst.end());

    // st.erase(st.begin());
    // // st.erase(3);
    ft::map<int, int> Map;
    Map.insert(ft::pair<int, int>(3,5));
    ft::map<int, int>::iterator it = Map.begin();
}