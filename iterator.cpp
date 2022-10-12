#include <iostream>     // std::cout
#include <typeinfo>     // typeid
#include <cstddef>

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

}

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

}

// reverse_iterator
namespace ft {



}

int main() {
  typedef ft::iterator_traits<int*> traits;
  if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
    std::cout << "int* is a random-access iterator";
  return 0;
}