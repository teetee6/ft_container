#ifndef __UTILITY_HPP_
#define __UTILITY_HPP_

#include "iterator.hpp"

namespace ft {

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
    pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {} //

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

// distance로 바꿀까?
template < class InputIterator >
typename ft::iterator_traits< InputIterator >::difference_type difference(InputIterator first, InputIterator last) {
  typedef typename ft::iterator_traits< InputIterator >::difference_type size_type;
  size_type n = 0;
  
  while(first != last)
  {
	++n;
	++first;
  }
  return n;
}

}

#endif