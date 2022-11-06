#ifndef __ALGORITHM_HPP_
#define __ALGORITHM_HPP_

#include <string>
#include <iostream>
#include <vector>

namespace ft {

template <class _InputIterator1, class _InputIterator2>
bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                          _InputIterator2 __first2, _InputIterator2 __last2)
{
    for (; __first2 != __last2; ++__first1, (void) ++__first2)
    {
        if (__first1 == __last1 || *__first1 < *__first2)
            return true;
        if (*__first2 < *__first1)
            return false;
    }
    return false;
}

template <class _InputIterator1, class _InputIterator2, class _Compare>
bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                          _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
{
    for (; __first2 != __last2; ++__first1, (void) ++__first2)
    {
        if (__first1 == __last1 || __comp(*__first1, *__first2))
            return true;
        if (__comp(*__first2, *__first1))
            return false;
    }
    return false;
}

template < class _InputIterator1, class _InputIterator2 >
bool equal(_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2) {
  for (; first1 != last1; ++first1, (void)++first2)
    if (!(*first1 == *first2)) return false;
  return true;
};


template < class _InputIterator1, class _InputIterator2, class _BinaryPredicate >
bool equal(_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2,
           _BinaryPredicate pred) {
  for (; first1 != last1; ++first1, (void)++first2)
    if (!bool(pred(*first1, *first2))) return false;
  return true;
}

}

#endif