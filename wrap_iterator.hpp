#ifndef __WRAP_ITERATOR_HPP_
#define __WRAP_ITERATOR_HPP_

#include "iterator.hpp"

namespace ft {

template <class _Iter> //consider as [int] (official library is [int *])
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef ft::iterator< ft::random_access_iterator_tag, _Iter >      __iter_proto__;
    typedef typename ft::iterator_traits<__iter_proto__>::iterator_category iterator_category;
    typedef typename ft::iterator_traits<__iter_proto__>::value_type        value_type;
    typedef typename ft::iterator_traits<__iter_proto__>::difference_type   difference_type;
    typedef typename ft::iterator_traits<__iter_proto__>::pointer           pointer;
    typedef typename ft::iterator_traits<__iter_proto__>::reference         reference;
private:
    pointer __i;
public:
    __wrap_iter(pointer __x = NULL) : __i(__x) {}
    __wrap_iter(const __wrap_iter<_Iter>& __x) : __i(__x.base()) {}
    __wrap_iter& operator=(const __wrap_iter& __x)
    {
        if (this != &__x)
            __i = __x.__i;
        return *this;
    }
    virtual ~__wrap_iter() {}
	operator __wrap_iter<const _Iter>() {	//__wrap_iter<const _Iter> a = __wrap_iter<_Iter>  (((conversion operator))) const_iterator it = iterator;
		return __wrap_iter<const _Iter>(this->__i);
  	}
	// operator reverse_iterator<_Iter>() {	//reverse_iterator<_Iter> a = __wrap_iter<_Iter>
	// 	return reverse_iterator<_Iter *>(this->__i);
  	// }
    reference operator*() const { return *__i; }
    pointer  operator->() const { return &(*__i); }
    __wrap_iter& operator++() { ++__i; return *this; }
    __wrap_iter  operator++(int) {__wrap_iter __tmp(*this); ++(*this); return __tmp;}
    __wrap_iter& operator--() { --__i; return *this; }
    __wrap_iter  operator--(int) {__wrap_iter __tmp(*this); --(*this); return __tmp;}
    __wrap_iter  operator+ (difference_type __n) const {__wrap_iter __w(*this); __w += __n; return __w;}
    __wrap_iter& operator+=(difference_type __n) { __i += __n; return *this; }
    __wrap_iter  operator- (difference_type __n) const { return *this + (-__n); }
    __wrap_iter& operator-=(difference_type __n) { *this += -__n; return *this; }
    reference    operator[](difference_type __n) const { return __i[__n]; }
    pointer base() const { return __i; }
};

template <class _Iter1, class _Iter2>
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __y < __x;
}

template <class _Iter1, class _Iter2>
bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return !(__y < __x);
}

template <class _Iter1>
bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y)
{
    return !(__x == __y);
}

template <class _Iter1>
bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y)
{
    return __y < __x;
}

template <class _Iter1>
bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y)
{
    return !(__x < __y);
}

template <class _Iter1>
bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y)
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
typename __wrap_iter<_Iter1>::difference_type
    operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() - __y.base();
}

template <class _Iter>
__wrap_iter<_Iter> operator+(typename __wrap_iter<_Iter>::difference_type __n,
          const __wrap_iter<_Iter>& __x)
{
    return __x + __n;
}

}

#endif