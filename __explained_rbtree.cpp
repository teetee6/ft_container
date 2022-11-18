#include <iostream>
#include <typeinfo>

typedef bool _Rb_tree_Color_type;
const _Rb_tree_Color_type _S_rb_tree_red = false;
const _Rb_tree_Color_type _S_rb_tree_black = true;

struct _Rb_tree_node_base
{
    typedef _Rb_tree_Color_type _Color_type;
    typedef _Rb_tree_node_base* _Base_ptr;

    _Color_type _M_color; 
    _Base_ptr _M_parent;
    _Base_ptr _M_left;
    _Base_ptr _M_right;

    static _Base_ptr _S_minimum(_Base_ptr __x)
    {
        while (__x->_M_left != 0) __x = __x->_M_left;
        return __x;
    }

    static _Base_ptr _S_maximum(_Base_ptr __x)
    {
        while (__x->_M_right != 0) __x = __x->_M_right;
        return __x;
    }
};

template <class _Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
    typedef _Rb_tree_node<_Value>* _Link_type;
    _Value _M_value_field;
};


struct _Rb_tree_base_iterator
{
    typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
    // typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;
    _Base_ptr _M_node; // _M_node는 위의 구조체들과 연동안되니 타입변환 필요

    void _M_increment()
    {
        if (_M_node->_M_right != 0) {
            _M_node = _M_node->_M_right;
            while (_M_node->_M_left != 0)
                _M_node = _M_node->_M_left;
        }
        else {
            _Base_ptr __y = _M_node->_M_parent;
            while (_M_node == __y->_M_right) {
                _M_node = __y;
                __y = __y->_M_parent;
            }
            if (_M_node->_M_right != __y)   // if 1 size(and _M_node == root), then _M_node = end();
                _M_node = __y;
        }
    }

    void _M_decrement()
    {
        if (_M_node->_M_color == _S_rb_tree_red && _M_node->_M_parent->_M_parent == _M_node) // if _M_node == end(), then _M_node = end() - 1;
            _M_node = _M_node->_M_right;
        else if (_M_node->_M_left != 0) {
            _Base_ptr __y = _M_node->_M_left;
            while (__y->_M_right != 0)
                __y = __y->_M_right;
            _M_node = __y;
        }
        else {
            _Base_ptr __y = _M_node->_M_parent;
            while (_M_node == __y->_M_left) {
                _M_node = __y;
                __y = __y->_M_parent;
            }
            _M_node = __y;
        }
    }
};
 
 template <class _Value, class _Ref, class _Ptr>
 struct _Rb_tree_iterator : public _Rb_tree_base_iterator
 {
    typedef _Value                                                  value_type;
    typedef _Ref                                                    reference;
    typedef _Ptr                                                    pointer;
    typedef _Rb_tree_iterator<_Value, _Value&, _Value*>             iterator;
    typedef _Rb_tree_iterator<_Value, const _Value&, const _Value*> const_iterator;
    typedef _Rb_tree_iterator<_Value, _Ref, _Ptr>                   _Self;
    typedef _Rb_tree_node<_Value>*                                  _Link_type;
 
   _Rb_tree_iterator() {}
   _Rb_tree_iterator(_Link_type __x) { _M_node = __x; }
   _Rb_tree_iterator(const iterator& __it) { _M_node = __it._M_node; }
 
    reference operator*() const { return _Link_type(_M_node)->_M_value_field; } // _M_node는 트리노드와 연동안되니 포인터 캐스팅후 사용
    pointer operator->() const { return &(operator*()); }
 
    _Self& operator++() { _M_increment(); return *this; }
    _Self operator++(int) {
        _Self __tmp = *this;
        _M_increment();
        return __tmp;
    }
     
    _Self& operator--() { _M_decrement(); return *this; }
    _Self operator--(int) {
        _Self __tmp = *this;
        _M_decrement();
        return __tmp;
    }
}; 

template <class _Value, class _Ref, class _Ptr>
inline bool operator==(const _Rb_tree_iterator<_Value, _Ref, _Ptr>& __x,
               const _Rb_tree_iterator<_Value, _Ref, _Ptr>& __y) {
  return __x._M_node == __y._M_node;
}

template <class _Value>
inline bool operator==(const _Rb_tree_iterator<_Value, const _Value&, const _Value*>& __x,
               const _Rb_tree_iterator<_Value, _Value&, _Value*>& __y) {
  return __x._M_node == __y._M_node;
}

template <class _Value>
inline bool operator==(const _Rb_tree_iterator<_Value, _Value&, _Value*>& __x,
               const _Rb_tree_iterator<_Value, const _Value&, const _Value*>& __y) {
  return __x._M_node == __y._M_node;
}

template <class _Value, class _Ref, class _Ptr>
inline bool operator!=(const _Rb_tree_iterator<_Value, _Ref, _Ptr>& __x,
               const _Rb_tree_iterator<_Value, _Ref, _Ptr>& __y) {
  return __x._M_node != __y._M_node;
}

template <class _Value>
inline bool operator!=(const _Rb_tree_iterator<_Value, const _Value&, const _Value*>& __x,
               const _Rb_tree_iterator<_Value, _Value&, _Value*>& __y) {
  return __x._M_node != __y._M_node;
}

template <class _Value>
inline bool operator!=(const _Rb_tree_iterator<_Value, _Value&, _Value*>& __x,
               const _Rb_tree_iterator<_Value, const _Value&, const _Value*>& __y) {
  return __x._M_node != __y._M_node;
}

inline void 
_Rb_tree_rotate_left(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
{
  _Rb_tree_node_base* __y = __x->_M_right;
  __x->_M_right = __y->_M_left;
  if (__y->_M_left !=0)
    __y->_M_left->_M_parent = __x;
  __y->_M_parent = __x->_M_parent;

  if (__x == __root)
    __root = __y;
  else if (__x == __x->_M_parent->_M_left)
    __x->_M_parent->_M_left = __y;
  else
    __x->_M_parent->_M_right = __y;
  __y->_M_left = __x;
  __x->_M_parent = __y;
}

inline void 
_Rb_tree_rotate_right(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
{
  _Rb_tree_node_base* __y = __x->_M_left;
  __x->_M_left = __y->_M_right;
  if (__y->_M_right != 0)
    __y->_M_right->_M_parent = __x;
  __y->_M_parent = __x->_M_parent;

  if (__x == __root)
    __root = __y;
  else if (__x == __x->_M_parent->_M_right)
    __x->_M_parent->_M_right = __y;
  else
    __x->_M_parent->_M_left = __y;
  __y->_M_right = __x;
  __x->_M_parent = __y;
}

// Rebalance after insert
inline void 
_Rb_tree_rebalance(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root) //(new_node, root)
{
  __x->_M_color = _S_rb_tree_red;
  while (__x != __root && __x->_M_parent->_M_color == _S_rb_tree_red) {
    if (__x->_M_parent == __x->_M_parent->_M_parent->_M_left) {
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_right;
      if (__y && __y->_M_color == _S_rb_tree_red) { // parent==red, uncle==red (recoloring)
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __y->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        __x = __x->_M_parent->_M_parent;
      }
      else {    // restructuring
        if (__x == __x->_M_parent->_M_right) { // if k is right child, first left-rotate() about k's parent
          __x = __x->_M_parent;
          _Rb_tree_rotate_left(__x, __root);
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        _Rb_tree_rotate_right(__x->_M_parent->_M_parent, __root);
      }
    }
    else {
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_left;
      if (__y && __y->_M_color == _S_rb_tree_red) {
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __y->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        __x = __x->_M_parent->_M_parent;
      }
      else {
        if (__x == __x->_M_parent->_M_left) {
          __x = __x->_M_parent;
          _Rb_tree_rotate_right(__x, __root);
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        _Rb_tree_rotate_left(__x->_M_parent->_M_parent, __root);
      }
    }
  }
  __root->_M_color = _S_rb_tree_black;
}

inline _Rb_tree_node_base*
_Rb_tree_rebalance_for_erase(_Rb_tree_node_base* __z,
                             _Rb_tree_node_base*& __root,
                             _Rb_tree_node_base*& __leftmost,
                             _Rb_tree_node_base*& __rightmost)
{
    /////////////// delete node and set ,according to the number of its child(0, 1, 2) handling ///////////////
    // z = original_location
  _Rb_tree_node_base* __y = __z; // z = delete node
  _Rb_tree_node_base* __x = 0; // __x is replace node into replaced node's location. (and doubly-black node)
  _Rb_tree_node_base* __x_parent = 0;   // doubly-black node's parent
  if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
    __x = __y->_M_right;     // __x might be null.
  else
    if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
      __x = __y->_M_left;    // __x is not null.
    else {                   // __z has two non-null children.  Set __y to
      __y = __y->_M_right;   //   __z's successor.  __x might be null.
      while (__y->_M_left != 0)
        __y = __y->_M_left;
      __x = __y->_M_right;
    }
  // y has two child
  if (__y != __z) {          // relink y in place of z.  y is z's successor
    // y를 서브트리 루트로 올리는과정
    __z->_M_left->_M_parent = __y; 
    __y->_M_left = __z->_M_left;
    if (__y != __z->_M_right) {
      __x_parent = __y->_M_parent;
      if (__x) __x->_M_parent = __y->_M_parent;
      __y->_M_parent->_M_left = __x;      // __y must be a child of _M_left
      __y->_M_right = __z->_M_right;
      __z->_M_right->_M_parent = __y;
    }
    else
      __x_parent = __y;  
    if (__root == __z)
      __root = __y;
    else if (__z->_M_parent->_M_left == __z)
      __z->_M_parent->_M_left = __y;
    else 
      __z->_M_parent->_M_right = __y;
    __y->_M_parent = __z->_M_parent;
    
    std::swap(__y->_M_color, __z->_M_color);
    __y = __z;  // y is not doubly-black or red-and-black. 이제 y를 삭제된 위치를 가리키게 하자.
    // __y now points to node to be actually deleted
  }
  // y has zero or one child
  else {                        // __y == __z
  // __x = replace node (just move up!)
  // __y = delete node       
    __x_parent = __y->_M_parent;
    if (__x) __x->_M_parent = __y->_M_parent;   
    if (__root == __z)
      __root = __x;
    else 
      if (__z->_M_parent->_M_left == __z)
        __z->_M_parent->_M_left = __x;
      else
        __z->_M_parent->_M_right = __x;
    if (__leftmost == __z) 
      if (__z->_M_right == 0)        // __z->_M_left must be null also
        __leftmost = __z->_M_parent;
    // makes __leftmost == _M_header if __z == __root
      else
        __leftmost = _Rb_tree_node_base::_S_minimum(__x);
    if (__rightmost == __z)  
      if (__z->_M_left == 0)         // __z->_M_right must be null also
        __rightmost = __z->_M_parent;  
    // makes __rightmost == _M_header if __z == __root
      else                      // __x == __z->_M_left
        __rightmost = _Rb_tree_node_base::_S_maximum(__x);
  }

    /////////////// doubly-black handling ///////////////
  // x = doubly-black
  if (__y->_M_color != _S_rb_tree_red) { // case1~4
    while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))    // x is doubly-black
    {
      if (__x == __x_parent->_M_left) {
        _Rb_tree_node_base* __w = __x_parent->_M_right;
        if (__w->_M_color == _S_rb_tree_red) {  // case1
          __w->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rb_tree_rotate_left(__x_parent, __root);
          __w = __x_parent->_M_right;
        }
        if ((__w->_M_left == 0 || 
             __w->_M_left->_M_color == _S_rb_tree_black) &&
            (__w->_M_right == 0 || 
             __w->_M_right->_M_color == _S_rb_tree_black)) { // case2
          __w->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {  // entering here means that w is black, and its childs are not black, either.
          if (__w->_M_right == 0 || 
              __w->_M_right->_M_color == _S_rb_tree_black) {    // case3
            if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
            __w->_M_color = _S_rb_tree_red;
            _Rb_tree_rotate_right(__w, __root);
            __w = __x_parent->_M_right;
          }
          __w->_M_color = __x_parent->_M_color; // case4
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
          _Rb_tree_rotate_left(__x_parent, __root);
          break;
        }
      } else {                  // same as above, with _M_right <-> _M_left.
        _Rb_tree_node_base* __w = __x_parent->_M_left;
        if (__w->_M_color == _S_rb_tree_red) {
          __w->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rb_tree_rotate_right(__x_parent, __root);
          __w = __x_parent->_M_left;
        }
        if ((__w->_M_right == 0 || 
             __w->_M_right->_M_color == _S_rb_tree_black) &&
            (__w->_M_left == 0 || 
             __w->_M_left->_M_color == _S_rb_tree_black)) {
          __w->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          if (__w->_M_left == 0 || 
              __w->_M_left->_M_color == _S_rb_tree_black) {
            if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
            __w->_M_color = _S_rb_tree_red;
            _Rb_tree_rotate_left(__w, __root);
            __w = __x_parent->_M_left;
          }
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
          _Rb_tree_rotate_right(__x_parent, __root);
          break;
        }
      }
    }
    if (__x) __x->_M_color = _S_rb_tree_black;
  }
  return __y;
}





// Base class to encapsulate the differences between old SGI-style
// allocators and standard-conforming allocators.  In order to avoid
// having an empty base class, we arbitrarily move one of rb_tree's
// data members into the base class.

// _Base for general standard-conforming allocators.
template <class _Tp, class _Alloc, bool _S_instanceless>
class _Rb_tree_alloc_base {
public:
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;
  allocator_type get_allocator() const { return _M_node_allocator; }

  _Rb_tree_alloc_base(const allocator_type& __a)
    : _M_node_allocator(__a), _M_header(0) {}

protected:
  typename _Alloc_traits<_Rb_tree_node<_Tp>, _Alloc>::allocator_type
           _M_node_allocator;
  _Rb_tree_node<_Tp>* _M_header; // cache노드. left는 leftMost, right는 rightMost, parent는 root를 캐싱하고 있을 것임

  _Rb_tree_node<_Tp>* _M_get_node() { return _M_node_allocator.allocate(1); }
  void _M_put_node(_Rb_tree_node<_Tp>* __p) { _M_node_allocator.deallocate(__p, 1); }
};


// Specialization for instanceless allocators.
template <class _Tp, class _Alloc>
class _Rb_tree_alloc_base<_Tp, _Alloc, true> {
public:
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Rb_tree_alloc_base(const allocator_type&) : _M_header(0) {}

protected:
  _Rb_tree_node<_Tp>* _M_header;

  typedef typename _Alloc_traits<_Rb_tree_node<_Tp>, _Alloc>::_Alloc_type
          _Alloc_type;

  _Rb_tree_node<_Tp>* _M_get_node() { return _Alloc_type::allocate(1); }
  void _M_put_node(_Rb_tree_node<_Tp>* __p) { _Alloc_type::deallocate(__p, 1); }
};

template <class _Tp, class _Alloc>
struct _Rb_tree_base
  : public _Rb_tree_alloc_base<_Tp, _Alloc,
                               _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
{
  typedef _Rb_tree_alloc_base<_Tp, _Alloc,
                              _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
          _Base;
  typedef typename _Base::allocator_type allocator_type;

  _Rb_tree_base(const allocator_type& __a) : _Base(__a) { _M_header = _M_get_node(); }
  ~_Rb_tree_base() { _M_put_node(_M_header); }

};


template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          class _Alloc = std::allocator<_Value> >
class _Rb_tree : protected _Rb_tree_base<_Value, _Alloc> {
  typedef _Rb_tree_base<_Value, _Alloc> _Base;
protected:
  typedef _Rb_tree_node_base* _Base_ptr;
  typedef _Rb_tree_node<_Value> _Rb_tree_node;
  typedef _Rb_tree_Color_type _Color_type;
public:
  typedef _Key key_type;
  typedef _Value value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef _Rb_tree_node* _Link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

protected:
  using _Base::_M_get_node;
  using _Base::_M_put_node;
  using _Base::_M_header;

protected:

  _Link_type _M_create_node(const value_type& __x)
  {
    _Link_type __tmp = _M_get_node();
    __STL_TRY { // try
      construct(&__tmp->_M_value_field, __x);
    }
    __STL_UNWIND(_M_put_node(__tmp)); // catch(...) { action; throw; }
    return __tmp;
  }

  _Link_type _M_clone_node(_Link_type __x)
  {
    _Link_type __tmp = _M_create_node(__x->_M_value_field);
    __tmp->_M_color = __x->_M_color;
    __tmp->_M_left = 0;
    __tmp->_M_right = 0;
    return __tmp;
  }

  void destroy_node(_Link_type __p)
  {
    destroy(&__p->_M_value_field);
    _M_put_node(__p);
  }

protected:
  size_type _M_node_count; // keeps track of size of tree
  _Compare _M_key_compare;

  _Link_type& _M_root() const   { return (_Link_type&) _M_header->_M_parent; } //cache
  _Link_type& _M_leftmost() const   { return (_Link_type&) _M_header->_M_left; } //cache
  _Link_type& _M_rightmost() const  { return (_Link_type&) _M_header->_M_right; } //cache

  static _Link_type& _S_left(_Link_type __x)    { return (_Link_type&)(__x->_M_left); }
  static _Link_type& _S_right(_Link_type __x)   { return (_Link_type&)(__x->_M_right); }
  static _Link_type& _S_parent(_Link_type __x)  { return (_Link_type&)(__x->_M_parent); }
  static reference _S_value(_Link_type __x) { return __x->_M_value_field; }
  static const _Key& _S_key(_Link_type __x) { return _KeyOfValue()(_S_value(__x)); }
  static _Color_type& _S_color(_Link_type __x)  { return (_Color_type&)(__x->_M_color); }

  static _Link_type& _S_left(_Base_ptr __x)     { return (_Link_type&)(__x->_M_left); }
  static _Link_type& _S_right(_Base_ptr __x)    { return (_Link_type&)(__x->_M_right); }
  static _Link_type& _S_parent(_Base_ptr __x)   { return (_Link_type&)(__x->_M_parent); }
  static reference _S_value(_Base_ptr __x)  { return ((_Link_type)__x)->_M_value_field; }
  static const _Key& _S_key(_Base_ptr __x)  { return _KeyOfValue()(_S_value(_Link_type(__x)));} 
  static _Color_type& _S_color(_Base_ptr __x)   { return (_Color_type&)(_Link_type(__x)->_M_color); }

  static _Link_type _S_minimum(_Link_type __x)  { return (_Link_type)  _Rb_tree_node_base::_S_minimum(__x); }
  static _Link_type _S_maximum(_Link_type __x)  { return (_Link_type) _Rb_tree_node_base::_S_maximum(__x); }

public:
  typedef _Rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef _Rb_tree_iterator<value_type, const_reference, const_pointer> 
          const_iterator;

  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;

private:
  iterator _M_insert(_Base_ptr __x, _Base_ptr __y, const value_type& __v);
  _Link_type _M_copy(_Link_type __x, _Link_type __p); // copy from __x to __p 
  void _M_erase(_Link_type __x);

public:
                                // allocation/deallocation
  _Rb_tree()
    : _Base(allocator_type()), _M_node_count(0), _M_key_compare() // _Base()이거할때 _M_header노드 하나 달랑 만들어짐
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp)
    : _Base(allocator_type()), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp, const allocator_type& __a)
    : _Base(__a), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x) 
    : _Base(__x.get_allocator()),
      _M_node_count(0), _M_key_compare(__x._M_key_compare)
  { 
    if (__x._M_root() == 0)
      _M_empty_initialize();
    else {
      _S_color(_M_header) = _S_rb_tree_red;
      _M_root() = _M_copy(__x._M_root(), _M_header);
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
    }
    _M_node_count = __x._M_node_count;
  }
  ~_Rb_tree() { clear(); }
  _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& 
  operator=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x);

private:
// m_header (cache) 셋팅
  void _M_empty_initialize() {
    _S_color(_M_header) = _S_rb_tree_red; // used to distinguish header from 
                                          // __root, in iterator.operator++
    _M_root() = 0;  // m_header->parent 설정임. m_header그 자체는 아무값 없음
    _M_leftmost() = _M_header;  // m_header->left
    _M_rightmost() = _M_header; // m_header->right
  }

public:    
                                // accessors:
  _Compare key_comp() const { return _M_key_compare; }
  iterator begin() { return _M_leftmost(); }
  const_iterator begin() const { return _M_leftmost(); }
  iterator end() { return _M_header; }
  const_iterator end() const { return _M_header; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { 
    return const_reverse_iterator(end()); 
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { 
    return const_reverse_iterator(begin());
  } 
  bool empty() const { return _M_node_count == 0; }
  size_type size() const { return _M_node_count; }
  size_type max_size() const { return size_type(-1); }

  void swap(_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __t) {
    std::swap(_M_header, __t._M_header);
    std::swap(_M_node_count, __t._M_node_count);
    std::swap(_M_key_compare, __t._M_key_compare);
  }
    
public:
                                // insert/erase
  pair<iterator,bool> insert_unique(const value_type& __x);
  iterator insert_equal(const value_type& __x);

  iterator insert_unique(iterator __position, const value_type& __x);
  iterator insert_equal(iterator __position, const value_type& __x);

  template <class _InputIterator>
  void insert_unique(_InputIterator __first, _InputIterator __last);
  template <class _InputIterator>
  void insert_equal(_InputIterator __first, _InputIterator __last);

  void erase(iterator __position);
  size_type erase(const key_type& __x);
  void erase(iterator __first, iterator __last);
  void erase(const key_type* __first, const key_type* __last);
  void clear() {
    if (_M_node_count != 0) {
      _M_erase(_M_root()); // 메모리 싹 지움
      _M_leftmost() = _M_header;
      _M_root() = 0;
      _M_rightmost() = _M_header;
      _M_node_count = 0;
    }
  }      

public:
                                // set operations:
  iterator find(const key_type& __x);
  const_iterator find(const key_type& __x) const;
  size_type count(const key_type& __x) const;
  iterator lower_bound(const key_type& __x);
  const_iterator lower_bound(const key_type& __x) const;
  iterator upper_bound(const key_type& __x);
  const_iterator upper_bound(const key_type& __x) const;
  pair<iterator,iterator> equal_range(const key_type& __x);
  pair<const_iterator, const_iterator> equal_range(const key_type& __x) const;

public:
                                // Debugging.
  bool __rb_verify() const;
};

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator==(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator<(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
          const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(), 
                                 __y.begin(), __y.end());
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator!=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__x == __y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator>(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
          const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return __y < __x;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator<=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__y < __x);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator>=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__x < __y);
}


template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline void 
swap(_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
     _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  __x.swap(__y);
}


template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::operator=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x)
{
  if (this != &__x) {
                                // Note that _Key may be a constant type.
    clear();
    _M_node_count = 0;
    _M_key_compare = __x._M_key_compare;        
    if (__x._M_root() == 0) {
      _M_root() = 0;
      _M_leftmost() = _M_header;
      _M_rightmost() = _M_header;
    }
    else {
      _M_root() = _M_copy(__x._M_root(), _M_header); // 모든 노드를 (우측 노드부터->좌측 노드로) 복사해주는거에 지나지 않는다. // _M_header->parent = _M_header 가 여기서 설정된다
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
      _M_node_count = __x._M_node_count;
    }
  }
  return *this;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::_M_insert(_Base_ptr __x_, _Base_ptr __y_, const _Value& __v) // y는 부모, x는 자식
{
  _Link_type __x = (_Link_type) __x_; // __x는 NIL노드
  _Link_type __y = (_Link_type) __y_; // y는 x의 부모
  _Link_type __z;

  //(__x != 0는 필요한가? _M_header가 다 포괄할거 같습니다만...) ==> 필요함 x==0일때 end()갱신하는 호출있음
  // __y의 왼쪽자식 = __z
  if (__y == _M_header || __x != 0 || _M_key_compare(_KeyOfValue()(__v), _S_key(__y))) {  //새로운 노드는 y의 왼쪽자식이다
    __z = _M_create_node(__v);
    _S_left(__y) = __z;               // also makes _M_leftmost() = __z 
                                      //    when __y == _M_header
    if (__y == _M_header) { // 텅텅빈 트리였다
      _M_root() = __z;
      _M_rightmost() = __z; // leftmost()는 위의 left()로 퉁칠수있음
    }
    else if (__y == _M_leftmost()) // leftmost 갱신
      _M_leftmost() = __z;   // maintain _M_leftmost() pointing to min node
  }
  // __y의 오른쪽자식 = __z
  else {
    __z = _M_create_node(__v);
    _S_right(__y) = __z;
    if (__y == _M_rightmost())
      _M_rightmost() = __z;  // maintain _M_rightmost() pointing to max node
  }
  _S_parent(__z) = __y;
  _S_left(__z) = 0;
  _S_right(__z) = 0;
  _Rb_tree_rebalance(__z, _M_header->_M_parent);
  ++_M_node_count;
  return iterator(__z);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::insert_equal(const _Value& __v) 
{
  _Link_type __y = _M_header; // parent
  _Link_type __x = _M_root(); // child (적절한 위치인 맨 끝노드까지 파고 내려감)(최종적으로 NIL가 될거임)
  while (__x != 0) {
    __y = __x;
    __x = _M_key_compare(_KeyOfValue()(__v), _S_key(__x)) ?  // v < x
            _S_left(__x) : _S_right(__x);
  }
  return _M_insert(__x, __y, __v);
}


template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
std::pair<typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator, bool>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::insert_unique(const _Value& __v)
{
  _Link_type __y = _M_header;
  _Link_type __x = _M_root();
  bool __comp = true;
  while (__x != 0) {
    __y = __x;
    __comp = _M_key_compare(_KeyOfValue()(__v), _S_key(__x)); // v < x
    __x = __comp ? _S_left(__x) : _S_right(__x);
  }
  iterator __j = iterator(__y);
  if (__comp) // 왼쪽자식
    if (__j == begin()) // leftMost 라면
      return pair<iterator,bool>(_M_insert(__x, __y, __v), true);
    else
      --__j;  // unique인지 확인하는 용임
  if (_M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))  // v보다 이터낮은건 v보다 작은 값일때만 넣겠다
    return pair<iterator,bool>(_M_insert(__x, __y, __v), true);
  return pair<iterator,bool>(__j, false); // 동일한 값이면 넣지 않겠다
}

template <class _Key, class _Val, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator 
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>
  ::insert_unique(iterator __position, const _Val& __v)
{
  // root노드부터 탐색하지 않고, 바로 넣을수 있다면 바로넣겠다.(캐싱)
  if (__position._M_node == _M_header->_M_left) { // begin()
    if (size() > 0 && 
       _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)))  // __v < leftMost();
      return _M_insert(__position._M_node, __position._M_node, __v);  // __position 자식으로 __v 노드 새로 만들어줌 (왼쪽으로 넣어지니 position위치에 v넣은 의미가 와닿음)
    // first argument just needs to be non-null 
    else  // __position == end()
      return insert_unique(__v).first;  // 적당한곳 찾아가서 넣어짐(비어있을때, ==이 나올수 있어서 애매한 경우는 다 이쪽) (사실 왼쪽으로 넣으나 오른쪽으로 넣으나 그게 조정되서 position위치로 가리켜질것임)
  } else if (__position._M_node == _M_header) { // end()
    if (_M_key_compare(_S_key(_M_rightmost()), _KeyOfValue()(__v))) // rightMost() < __v;
      return _M_insert(0, _M_rightmost(), __v);
    else
      return insert_unique(__v).first;
  } else {
    iterator __before = __position;
    --__before;
    if (_M_key_compare(_S_key(__before._M_node), _KeyOfValue()(__v)) // before < v < position
        && _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node))) {
      if (_S_right(__before._M_node) == 0)  // before의 rChild가 없으면, 거기에 넣으면 position이니까 바로 넣는다
        return _M_insert(0, __before._M_node, __v); //right child
      else  // before가 rChild를 갖는다는것은, position이 lChild가 없다는것이다(그림으로 봐야 이해됨)
        return _M_insert(__position._M_node, __position._M_node, __v); //left child
    // first argument just needs to be non-null 
    } else
      return insert_unique(__v).first;
  }
}

template <class _Key, class _Val, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>
  ::insert_equal(iterator __position, const _Val& __v)
{
  if (__position._M_node == _M_header->_M_left) { // begin()
    if (size() > 0 && 
    !_M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))  // v <= m_node
      return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    else
      return insert_equal(__v);
  } else if (__position._M_node == _M_header) {// end()
    if (!_M_key_compare(_KeyOfValue()(__v), _S_key(_M_rightmost())))  // v >= rightMose()
      return _M_insert(0, _M_rightmost(), __v);
    else
      return insert_equal(__v);
  } else {
    iterator __before = __position;
    --__before;
    if (!_M_key_compare(_KeyOfValue()(__v), _S_key(__before._M_node)) // before <= v <= position
        && !_M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v))) {
      if (_S_right(__before._M_node) == 0)
        return _M_insert(0, __before._M_node, __v); 
      else
        return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    } else
      return insert_equal(__v);
  }
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
  template<class _II>
void _Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_equal(_II __first, _II __last)
{
  for ( ; __first != __last; ++__first)
    insert_equal(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc> 
  template<class _II>
void _Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_unique(_II __first, _II __last) {
  for ( ; __first != __last; ++__first)
    insert_unique(*__first);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(iterator __position)
{
  _Link_type __y = 
    (_Link_type) _Rb_tree_rebalance_for_erase(__position._M_node,
                                              _M_header->_M_parent,
                                              _M_header->_M_left,
                                              _M_header->_M_right);
  destroy_node(__y);
  --_M_node_count;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::size_type 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::erase(const _Key& __x)
{
  pair<iterator,iterator> __p = equal_range(__x);
  size_type __n = 0;
  distance(__p.first, __p.second, __n);
  erase(__p.first, __p.second);
  return __n;
}

template <class _Key, class _Val, class _KoV, class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type 
_Rb_tree<_Key,_Val,_KoV,_Compare,_Alloc>
  ::_M_copy(_Link_type __x, _Link_type __p) //  _M_root() = _M_copy(__x._M_root(), _M_header); 
  // M_copy()밖에서 _M_header->M_Left 같은 자식설정 해주니, 이 함수 내에서 M_header를 부모로 설정하는작업을 해달라는 거임
{
                        // structural copy.  __x and __p must be non-null.
                        // x노드 하나씩 내려가면서 계속 clone함.
  _Link_type __top = _M_clone_node(__x);
  __top->_M_parent = __p; // _M_header 주소값을 넣어줌 (위에서 말한 M_header를 부모로 설정해주는작업)
 
  __STL_TRY {
    if (__x->_M_right)
      __top->_M_right = _M_copy(_S_right(__x), __top); // 오른쪽에 대한건 위탁. _M_copy()자체는 왼쪽으로 쭈욱 내려가는형태.
    __p = __top;
    __x = _S_left(__x);

    while (__x != 0) {
      _Link_type __y = _M_clone_node(__x);
      __p->_M_left = __y;   // p는 항상 y의 부모다
      __y->_M_parent = __p;
      if (__x->_M_right)
        __y->_M_right = _M_copy(_S_right(__x), __y);
      __p = __y;
      __x = _S_left(__x);
    }
  }
  __STL_UNWIND(_M_erase(__top));

    // __x에 대한 복사본(복사된 노드들의 트리)를 반환
  return __top;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::_M_erase(_Link_type __x)  // 우측 리프->좌측 리프로 휩쓸어버리기~
{
                                // erase without rebalancing
  while (__x != 0) {  // 왼쪽으로 찔끔찔끔 간당
    _M_erase(_S_right(__x));
    _Link_type __y = _S_left(__x);
    destroy_node(__x);
    __x = __y;
  }
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(iterator __first, iterator __last)
{
  if (__first == begin() && __last == end())
    clear();
  else
    while (__first != __last) erase(__first++);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(const _Key* __first, const _Key* __last) 
{
  while (__first != __last) erase(*__first++);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::find(const _Key& __k)
{
  _Link_type __y = _M_header;      // Last node which is not less than __k. 
  _Link_type __x = _M_root();      // Current node. 

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k))  // x >= k
      __y = __x, __x = _S_left(__x);
    else  // x < k
      __x = _S_right(__x);

  iterator __j = iterator(__y);   
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? //못찾았거나 || k(15) < j(18) 이면 못찾은것임 
     end() : __j;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::find(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) {
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);
  }
  const_iterator __j = const_iterator(__y);   
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ?
    end() : __j;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::size_type 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::count(const _Key& __k) const
{
  pair<const_iterator, const_iterator> __p = equal_range(__k);
  size_type __n = 0;
  distance(__p.first, __p.second, __n);
  return __n;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::lower_bound(const _Key& __k)
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);

  return iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::lower_bound(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k)) // x >= k
      __y = __x, __x = _S_left(__x);
    else  // x < k
      __x = _S_right(__x);

  return const_iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::upper_bound(const _Key& __k)
{
  _Link_type __y = _M_header; /* Last node which is greater than __k. */
  _Link_type __x = _M_root(); /* Current node. */

   while (__x != 0) 
     if (_M_key_compare(__k, _S_key(__x))) // k < x
       __y = __x, __x = _S_left(__x);
     else // k >= x
       __x = _S_right(__x);

   return iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::upper_bound(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is greater than __k. */
  _Link_type __x = _M_root(); /* Current node. */

   while (__x != 0) 
     if (_M_key_compare(__k, _S_key(__x)))
       __y = __x, __x = _S_left(__x);
     else
       __x = _S_right(__x);

   return const_iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline 
std::pair<typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator,
     typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::equal_range(const _Key& __k)
{
  return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
}

template <class _Key, class _Value, class _KoV, class _Compare, class _Alloc>
inline 
std::pair<typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator,
     typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator>
_Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>
  ::equal_range(const _Key& __k) const
{
  return pair<const_iterator,const_iterator>(lower_bound(__k),
                                             upper_bound(__k));
}

inline int
__black_count(_Rb_tree_node_base* __node, _Rb_tree_node_base* __root)
{
  if (__node == 0)
    return 0;
  int __sum = 0;
  do {
    if (__node->_M_color == _S_rb_tree_black) 
      ++__sum;
    if (__node == __root) 
      break;
    __node = __node->_M_parent;
  } while (1);
  return __sum;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
bool _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::__rb_verify() const
{
  if (_M_node_count == 0 || begin() == end())
    return _M_node_count == 0 && begin() == end() &&
      _M_header->_M_left == _M_header && _M_header->_M_right == _M_header;
  
  int __len = __black_count(_M_leftmost(), _M_root());
  for (const_iterator __it = begin(); __it != end(); ++__it) {
    _Link_type __x = (_Link_type) __it._M_node;
    _Link_type __L = _S_left(__x);
    _Link_type __R = _S_right(__x);

    if (__x->_M_color == _S_rb_tree_red)
      if ((__L && __L->_M_color == _S_rb_tree_red) ||
          (__R && __R->_M_color == _S_rb_tree_red))
        return false;

    if (__L && _M_key_compare(_S_key(__x), _S_key(__L)))
      return false;
    if (__R && _M_key_compare(_S_key(__R), _S_key(__x)))
      return false;

    if (!__L && !__R && __black_count(__x, _M_root()) != __len)
      return false;
  }

  if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
    return false;
  if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
    return false;

  return true;
}

// Class rb_tree is not part of the C++ standard.  It is provided for
// compatibility with the HP STL.

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          class _Alloc = std::allocator<_Value> >
struct rb_tree : public _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>
{
  typedef _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> _Base;
  typedef typename _Base::allocator_type allocator_type;

  rb_tree(const _Compare& __comp = _Compare(),
          const allocator_type& __a = allocator_type())
    : _Base(__comp, __a) {}
  
  ~rb_tree() {}
};

int main() {
    _Rb_tree_iterator<int, int, int*> it;
    *it;
}