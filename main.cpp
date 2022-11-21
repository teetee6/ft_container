#include "map.hpp"
#include <string>
#include "utility.hpp"

int main() {
    ft::map<int, std::string, std::greater<int> > mp, mp2;
	mp.insert(ft::pair<int, std::string>(42, "lol"));
    mp.insert(ft::pair<int, std::string>(42, "mdr"));

    mp.insert(ft::pair<int, std::string>(50, "mdr"));
    mp.insert(ft::pair<int, std::string>(35, "funny"));

    mp.insert(ft::pair<int, std::string>(45, "bunny"));
    mp.insert(ft::pair<int, std::string>(21, "fizz"));
    mp.insert(ft::pair<int, std::string>(38, "buzz"));
    mp.insert(mp.begin(), ft::pair<int, std::string>(55, "fuzzy"));

    typedef ft::map<int, std::string>::iterator iter;
    for(iter it = mp.begin(); it != mp.end(); it++) {
        std::cout << it->first << " and " << it->second << std::endl;
    }
}