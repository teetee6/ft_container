#ifndef __FUNCTION_BASE_HPP_
#define __FUNCTION_BASE_HPP_

/* map */
namespace ft {
    template <class _Arg, class _Result>
    struct unary_function
    {
        typedef _Arg    argument_type;
        typedef _Result result_type;
    };
    
    template <class _Arg1, class _Arg2, class _Result>
    struct binary_function
    {
        typedef _Arg1   first_argument_type;
        typedef _Arg2   second_argument_type;
        typedef _Result result_type;
    };

    template <class _Pair>
    struct _Select1st : public unary_function<_Pair, typename _Pair::first_type>
    {
        typename _Pair::first_type& operator()(_Pair& __x) const { return __x.first; }
        const typename _Pair::first_type& operator()(const _Pair& __x) const { return __x.first; }
    };

    template <class T>
    struct _Identity : public unary_function<T, T>
    {
        T& operator()(T& __x) const { return __x; }
        const T& operator()(const T& __x) const { return __x; }
    };


    template <class _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp& __x, const _Tp& __y) const {return __x < __y;}
    };

}   //namespace ft

#endif