#ifndef __ITERATOR_HPP_
#define __ITERATOR_HPP_

#include <iostream>     // std::cout
#include <typeinfo>     // typeid
#include <cstddef>
#include <vector>
#include <map>

// iterator_traits
namespace ft {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Iter>
struct iterator_traits
{
    typedef typename _Iter::difference_type   difference_type;
    typedef typename _Iter::value_type        value_type;
    typedef typename _Iter::pointer           pointer;
    typedef typename _Iter::reference         reference;
    typedef typename _Iter::iterator_category iterator_category;
};

template<class _Tp>
struct iterator_traits<_Tp*>
{
    typedef ptrdiff_t difference_type;
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef random_access_iterator_tag iterator_category;
};

template<class _Tp>
struct iterator_traits<const _Tp*>
{
    typedef ptrdiff_t difference_type;
    typedef _Tp value_type;
    typedef const _Tp* pointer;
    typedef const _Tp& reference;
    typedef random_access_iterator_tag iterator_category;
};

}   // ft NAMESPACE

// iterator
namespace ft {

template<class _Category, class _Tp, class _Distance = ptrdiff_t,
        class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
    typedef _Category  iterator_category;
};

}   // ft NAMESPACE

// reverse_iterator
namespace ft {

template <class _Iter>
class reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type,
                      typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference>
{
protected:
    _Iter current;
public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<_Iter>::difference_type difference_type;
    typedef typename iterator_traits<_Iter>::reference       reference;
    typedef typename iterator_traits<_Iter>::pointer         pointer;

    reverse_iterator() :  current() {}
    explicit reverse_iterator(_Iter __x) : current(__x) {}
    template <class _Up>
    reverse_iterator(const reverse_iterator<_Up>& __u) : current(__u.base()) {}
    template <class _Up>
    reverse_iterator& operator=(const reverse_iterator<_Up>& __u)
    { current = __u.base(); return *this; }

    _Iter base() const {return current;}
    reference operator*() const {_Iter __tmp = current; return *--__tmp;}
    pointer  operator->() const {return &(operator*());}
    reverse_iterator& operator++() {--current; return *this;}
    reverse_iterator  operator++(int) {reverse_iterator __tmp(*this); --current; return __tmp;}
    reverse_iterator& operator--() {++current; return *this;}
    reverse_iterator  operator--(int) {reverse_iterator __tmp(*this); ++current; return __tmp;}
    reverse_iterator  operator+ (difference_type __n) const {return reverse_iterator(current - __n);}
    reverse_iterator& operator+=(difference_type __n) {current -= __n; return *this;}
    reverse_iterator  operator- (difference_type __n) const {return reverse_iterator(current + __n);}
    reverse_iterator& operator-=(difference_type __n) {current += __n; return *this;}
    reference         operator[](difference_type __n) const {return *(*this + __n);}
};

template <class _Iter1, class _Iter2>
bool operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool operator<(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
bool operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
bool operator>(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool operator>=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() <= __y.base();
}

template <class _Iter1, class _Iter2>
bool operator<=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() >= __y.base();
}

template <class _Iter1, class _Iter2>
typename reverse_iterator<_Iter1>::difference_type
    operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __y.base() - __x.base();
}

template <class _Iter>
reverse_iterator<_Iter>
    operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)
{
    return reverse_iterator<_Iter>(__x.base() - __n);
}

template <class _Iter>
reverse_iterator<_Iter> make_reverse_iterator(_Iter __i)
{
    return reverse_iterator<_Iter>(__i);
}


}   // ft NAMESPACE

#endif