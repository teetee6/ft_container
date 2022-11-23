#include "set.hpp"
#include <string>
#include "utility.hpp"
#include <list>
#include <set>
#include "map.hpp"
#include <iostream>

int main() {
    std::set<int> a;
    std::list<int> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(i);
	ft::set<int> st(lst.begin(), lst.end());

    // st.erase(st.begin());
    st.insert(st.begin(), 3);
    // // st.erase(3);
    
}