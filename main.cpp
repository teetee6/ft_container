#include "set.hpp"
#include <string>
#include "utility.hpp"
#include <list>
#include <set>

int main() {
    std::set<int> a;
    std::list<int> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(i);
	ft::set<int> st(lst.begin(), lst.end());

    st.erase(st.begin());
    // st.erase(3);

}