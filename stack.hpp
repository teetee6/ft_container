#include <deque>

namespace ft {

  template<typename _Tp, typename Container = std::deque<_Tp> >
    class stack
    {
      template<typename _Tp1, typename _Seq1>
        friend bool
        operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

      template<typename _Tp1, typename _Seq1>
        friend bool
        operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

    public:
      typedef typename Container::value_type                value_type;
      typedef typename Container::reference                 reference;
      typedef typename Container::const_reference           const_reference;
      typedef typename Container::size_type                 size_type;
      typedef          Container                            container_type;

    protected:
      Container c;

    public:
      explicit stack(const Container& __c = Container()) : c(__c) { }
      bool empty() const    { return c.empty(); }
      size_type size() const    { return c.size(); }
      reference top() { return c.back(); }
      const_reference top() const { return c.back(); }

      void push(const value_type& __x) { c.push_back(__x); }
      void pop() { c.pop_back(); }
    };  // class stack

  template<typename _Tp, typename _Seq>
    inline bool operator==(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return __x.c == __y.c; }

  template<typename _Tp, typename _Seq>
    inline bool operator<(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return __x.c < __y.c; }

  template<typename _Tp, typename _Seq>
    inline bool operator!=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return !(__x == __y); }

  template<typename _Tp, typename _Seq>
    inline bool operator>(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return __y < __x; }

  template<typename _Tp, typename _Seq>
    inline bool operator<=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return !(__y < __x); }

  template<typename _Tp, typename _Seq>
    inline bool operator>=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return !(__x < __y); }

}   //namespace ft