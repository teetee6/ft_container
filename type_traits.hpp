#ifndef __TYPE_TRAITS_HPP_
#define __TYPE_TRAITS_HPP_

#include <typeinfo>
#include <iostream>

namespace ft {
    template <bool, class _Tp = void> struct enable_if {};
    template <class _Tp> struct enable_if<true, _Tp> {typedef _Tp type;};
}

namespace ft {

template <class _Tp, _Tp __v>
struct integral_constant
{
  static const _Tp value = __v;
  typedef _Tp   value_type;
  typedef integral_constant type;
  operator value_type() const {return value;}
  value_type operator ()() const {return value;}
};

#define _LIBCPP_BOOL_CONSTANT(__b) integral_constant<bool,(__b)>
typedef _LIBCPP_BOOL_CONSTANT(true)  true_type;
typedef _LIBCPP_BOOL_CONSTANT(false) false_type;

template <class _Tp> struct __libcpp_is_integral                     : public false_type {};
template <>          struct __libcpp_is_integral<bool>               : public true_type {};
template <>          struct __libcpp_is_integral<char>               : public true_type {};
template <>          struct __libcpp_is_integral<signed char>        : public true_type {};
template <>          struct __libcpp_is_integral<unsigned char>      : public true_type {};
template <>          struct __libcpp_is_integral<wchar_t>            : public true_type {};
template <>          struct __libcpp_is_integral<short>              : public true_type {};
template <>          struct __libcpp_is_integral<unsigned short>     : public true_type {};
template <>          struct __libcpp_is_integral<int>                : public true_type {};
template <>          struct __libcpp_is_integral<unsigned int>       : public true_type {};
template <>          struct __libcpp_is_integral<long>               : public true_type {};
template <>          struct __libcpp_is_integral<unsigned long>      : public true_type {};
template <>          struct __libcpp_is_integral<long long>          : public true_type {};
template <>          struct __libcpp_is_integral<unsigned long long> : public true_type {};
#ifndef _LIBCPP_HAS_NO_INT128
template <>          struct __libcpp_is_integral<__int128_t>         : public true_type {};
template <>          struct __libcpp_is_integral<__uint128_t>        : public true_type {};
#endif

template <class _Tp> struct is_integral : public __libcpp_is_integral<_Tp> {};

}

#endif