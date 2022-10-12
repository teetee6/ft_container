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

struct comp {
    bool operator()(int a, int b) const {
        return (a < b);
    }
};

bool eq(int a, int b) {
    return (a == b);
}

int main()
{
    std::string str1 = "abcde";
    std::string str2 = "abcd";
    std::string str3 = "abcdd";
    std::string str4 = "abcde";

    std::string str5 = "abcdf";
    std::string str6 = "abcdeg";
    std::cout << ft::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(str1.begin(), str1.end(), str3.begin(), str3.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(str1.begin(), str1.end(), str4.begin(), str4.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(str1.begin(), str1.end(), str5.begin(), str5.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(str1.begin(), str1.end(), str6.begin(), str6.end(), comp()) << std::endl;
    std::cout << "[" << ft::lexicographical_compare(str1.begin(), str1.end(), str6.begin(), str6.end()) << "]" << std::endl;
    std::cout << std::endl;

    int arr1[5] = {1,2,3,4,5};
    int arr2[5] = {1,2,3,4};
    int arr3[5] = {1,2,3,4,4};
    int arr4[5] = {1,2,3,4,5};

    int arr5[5] = {1,2,3,4,6};
    int arr6[6] = {1,2,3,4,5,6};
    std::vector<int> vec1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    std::vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    std::vector<int> vec3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    std::vector<int> vec4(arr4, arr4 + sizeof(arr4) / sizeof(int));
    std::vector<int> vec5(arr5, arr5 + sizeof(arr5) / sizeof(int));
    std::vector<int> vec6(arr6, arr6 + sizeof(arr6) / sizeof(int));
    std::cout << ft::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(vec1.begin(), vec1.end(), vec3.begin(), vec3.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(vec1.begin(), vec1.end(), vec4.begin(), vec4.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(vec1.begin(), vec1.end(), vec5.begin(), vec5.end(), comp()) << std::endl;
    std::cout << ft::lexicographical_compare(vec1.begin(), vec1.end(), vec6.begin(), vec6.end(), comp()) << std::endl;
    std::cout << std::endl;

    std::cout << "---------------------------------------------------------------------" <<std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec2.begin(), comp()) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec3.begin(), comp()) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec4.begin(), comp()) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec5.begin(), comp()) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec6.begin(), comp()) << std::endl;
    std::cout << std::endl;

    std::cout << ft::equal(vec1.begin(), vec1.end(), vec2.begin(), eq) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec3.begin(), eq) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec4.begin(), eq) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec5.begin(), eq) << std::endl;
    std::cout << ft::equal(vec1.begin(), vec1.end(), vec6.begin(), eq) << std::endl;
    std::cout << "[" << ft::equal(vec1.begin(), vec1.end(), vec6.begin()) << "]" << std::endl;
    std::cout << std::endl;
}