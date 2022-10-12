#include <string>
#include <iostream>

template <typename _T1, typename _T2>
struct pair
{
    typedef _T1 first_type;
    typedef _T2 second_type;

    _T1 first;
    _T2 second;

    pair(const pair& __p) {  first = __p.first; second = __p.second; }
    pair() : first(), second() {}
    pair(_T1 const& __t1, _T2 const& __t2) : first(__t1), second(__t2) {}

    template <class _U1, class _U2>
    pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) { std::cout << "[type convertion, and copy!]\n";}

    pair& operator=(pair const& __p) {
        first = __p.first;
        second = __p.second;
        return *this;
    }
    void swap(pair& __p)
    {
        pair tmp;
        tmp.first = this->first;
        tmp.second = this->second;
        this->first = __p.first;
        this->second = __p.second;
        __p.first = tmp.first;
        __p.second = tmp.second;
    }
};

template <class _T1, class _T2>
bool operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __x.first == __y.first && __x.second == __y.second;
}

template <class _T1, class _T2>
bool operator!=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__x == __y);
}

template <class _T1, class _T2>
bool operator< (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);
}

template <class _T1, class _T2>
bool operator> (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __y < __x;
}

template <class _T1, class _T2>
bool operator>=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__x < __y);
}

template <class _T1, class _T2>
bool operator<=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__y < __x);
}

template <class _T1, class _T2>
void swap(pair<_T1, _T2>& __x, pair<_T1, _T2>& __y)
{
    __x.swap(__y);
}

template <class _T1, class _T2>
pair<_T1,_T2> make_pair(_T1 __x, _T2 __y)
{
    return pair<_T1, _T2>(__x, __y);
}

int main()
{
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        pair<int, std::string> pr(3, "good"), br(1, "bad");
        pair<int, std::string> kr(pr);
        std::cout << pr.first << ", " << pr.second << std::endl;
        std::cout << br.first << ", " << br.second << std::endl;
        std::cout << kr.first << ", " << kr.second << std::endl;
        kr = br;
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << std::endl;

        pair<char, const char *> tr('a', "tatata!");
        kr = tr;
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << std::endl;

        kr.swap(pr);
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << pr.first << ", " << pr.second << std::endl;
        ::swap(kr, pr);
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << pr.first << ", " << pr.second << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        pair<int, std::string> pr(3, "good"), br(1, "bad");
        pair<int, std::string> kr(pr);
        pair<int, std::string> zr(3, "zzzz");
        std::cout << (kr == pr) << (kr != pr) << (kr < pr) << (kr > pr) << (kr >= pr) << (kr <= pr) << std::endl;
        std::cout << (br == pr) << (br != pr) << (br < pr) << (br > pr) << (br >= pr) << (br <= pr) << std::endl;
        std::cout << (pr == br) << (pr != br) << (pr < br) << (pr > br) << (pr >= br) << (pr <= br) << std::endl;
        std::cout << (pr == zr) << (pr != zr) << (pr < zr) << (pr > zr) << (pr >= zr) << (pr <= zr) << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        pair<int, std::string> pr(make_pair<int, std::string>(1111, "hello?"));
        std::cout << pr.first << ", " << pr.second << std::endl;
        pair<int, std::string> br(1, "bad");
        pr = br;
        std::cout << pr.first << ", " << pr.second << std::endl;
    }
}