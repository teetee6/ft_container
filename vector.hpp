#ifndef __VECTOR_HPP_
#define __VECTOR_HPP_

#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "wrap_iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft {

template <class _Tp, class _Allocator = std::allocator<_Tp> >
class vector
{
public:
    typedef _Tp                                      value_type;
    typedef _Allocator                               allocator_type;

    typedef typename allocator_type::reference               reference;
    typedef typename allocator_type::const_reference         const_reference;
    typedef typename allocator_type::pointer                 pointer;
    typedef typename allocator_type::const_pointer           const_pointer;
    
	typedef typename ft::__wrap_iter<value_type>             iterator;
    typedef typename ft::__wrap_iter<const value_type>       const_iterator;
    typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

    typedef typename allocator_type::size_type               size_type;
    typedef typename allocator_type::difference_type         difference_type;


private:
    allocator_type									__alloc;
	pointer                                         __begin_;
    pointer                                         __end_;
    pointer											__end_cap_;

public:
	explicit vector(const allocator_type& alloc = allocator_type())
		: __alloc(alloc), __begin_(NULL), __end_(NULL), __end_cap_(NULL){};
	explicit vector(size_type n, 
			const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: __alloc(alloc) {
    	this->__begin_ = this->__end_ = this->__alloc.allocate(n);	// A pointer to the initial element in the block of storage.
    	this->__end_cap_ = this->__begin_ + n;
    	while (n--) this->__alloc.construct(this->__end_++, val);
	};
	template <typename _InputIterator>
	vector(_InputIterator __first, _InputIterator __last, 
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<_InputIterator >::value >::type* = NULL) // is_integral<false>일때만 진입함
		: __alloc(alloc) {
		size_type n = ft::distance(__first, __last);
		this->__begin_ = this->__end_ = this->__alloc.allocate(n);
		this->__end_cap_ = this->__begin_ + n;
		while (__first != __last) this->__alloc.construct(this->__end_++, *__first++);
	}

    ~vector()
    {
        this->clear();
    	this->__alloc.deallocate(this->__begin_, this->capacity());
    }

    vector(const vector& __x)  : __alloc(__x.__alloc) {
		size_type n = __x.size();
		this->__begin_ = this->__end_ = this->__alloc.allocate(n);
		this->__end_cap_ = this->__begin_ + n;

		pointer tmp = __x.__begin_;
		while (n--) this->__alloc.construct(this->__end_++, *tmp++);
	};

    vector& operator=(const vector& __x)  {
		if (this != &__x) {
			this->clear();
			this->insert(this->__begin_, __x.begin(), __x.end());
		}
		return *this;
	};

	iterator               begin() 			{return iterator(this->__begin_);}
	const_iterator         begin()   const 	{return const_iterator(this->__begin_);}
	iterator               end()			{return iterator(this->__end_);}
	const_iterator         end()     const	{return const_iterator(this->__end_);}

    reverse_iterator       rbegin()			{return       reverse_iterator(end());}
    const_reverse_iterator rbegin()  const 	{return const_reverse_iterator(end());}
    reverse_iterator       rend() 			{return       reverse_iterator(begin());}
    const_reverse_iterator rend()    const 	{return const_reverse_iterator(begin());}
    
    size_type size() const {return this->__end_ - this->__begin_;}
    size_type capacity() const {return (this->__end_cap_ - this->__begin_); }
     
    bool empty() const {return this->__begin_ == this->__end_;}
    size_type max_size() const {return this->__alloc.max_size();}
    void reserve(size_type __n) {
		if (__n > capacity()) {
			if (__n > max_size())
				throw std::out_of_range("reserve() Out of range exception");
			
			pointer __new_end_, __new_start_;
			__new_end_ = __new_start_ = this->__alloc.allocate(__n);

			for(pointer iter = this->__begin_; iter != this->__end_; ++iter) {
				this->__alloc.construct(__new_end_, *iter);
				++__new_end_;
			}
			while(this->__end_ != this->__begin_) {
				--this->__end_;
				this->__alloc.destroy(this->__end_);
			}
			this->__alloc.deallocate(this->__begin_, this->capacity());
			
			this->__begin_ = __new_start_;
			this->__end_ = __new_end_;
			this->__end_cap_ = this->__begin_ + __n;
    	}
	}
	void resize(size_type __sz, const_reference __x = value_type()) {
		if (__sz > max_size())
			throw std::out_of_range("resize() Out of range exception");
		size_type __cs = size();
		if (__cs < __sz)	// fill in rest spaces (if not enough memory, capacity *= 2) 
		{
			{	// in lieu of this->insert(this->__end_, __sz - __cs, __x)! because when realloation() new_capacity must be 2 times, not + __n
				size_type __n = __sz - __cs;
				iterator __position = this->__end_;
				const_reference __x = __x;
				if (__n > 0)
				{
					pointer __p = this->__begin_ + (__position - begin());
					if (__n <= static_cast<size_type>(this->capacity() - this->size())) // enough memory
					{
						pointer __iter = this->__end_;
						if (__p < __iter) { // just move hops
							while (__iter != __p) {
								--__iter;
								this->__alloc.construct(__iter + __n, *__iter);
								this->__alloc.destroy(__iter);
							}
						}
						this->__end_ += __n;
						while (__n--) this->__alloc.construct(__iter + __n, __x); // insert elements
					}
					else // reallocate
					{
						size_type new_capacity = capacity() * 2;
						while (new_capacity < size() + __n)	new_capacity *= 2;
						pointer __new_end_, __new_start_;
						__new_end_ = __new_start_ = this->__alloc.allocate(new_capacity);

						pointer __iter;
						for(__iter = this->__begin_; __iter != __p; ++__iter) {	// copy from origin
							this->__alloc.construct(__new_end_++, *__iter);
							this->__alloc.destroy(__iter);
						}
						while (__n--) this->__alloc.construct(__new_end_++, __x); // insert elements
						for(; __iter != __end_; ++__iter) {	// copy from origin
							this->__alloc.construct(__new_end_++, *__iter);
							this->__alloc.destroy(__iter);
						}
						this->__alloc.deallocate(this->__begin_, this->capacity());
						
						this->__begin_ = __new_start_;
						this->__end_ = __new_end_;
						this->__end_cap_ = this->__begin_ + new_capacity;
					}
				}
			}
		}
		else if (__cs > __sz) {		// shrink
			while (__cs-- > __sz) {
				--this->__end_;
        		this->__alloc.destroy(this->__end_);
      		}
		}
	}

    reference       operator[](size_type __n) {
		if (__n >= size())
        	throw std::out_of_range("operator[] Out of range exception");
		return this->__begin_[__n];
	}
    const_reference operator[](size_type __n) const {
		if (__n >= size())
        	throw std::out_of_range("operator[] Out of range exception");
		return this->__begin_[__n];
	}
    
	reference       at(size_type __n) {
		if (__n >= size())
        	throw std::out_of_range("at() Out of range exception");
    	return this->__begin_[__n];
	}
    const_reference at(size_type __n) const {
		if (__n >= size())
        	throw std::out_of_range("at() Out of range exception");
    	return this->__begin_[__n];
	}

    reference       front() { return *this->__begin_;}
    const_reference front() const { return *this->__begin_; }
    reference       back() { return *(this->__end_ - 1); }
    const_reference back()  const { return *(this->__end_ - 1); }
    allocator_type get_allocator() const  {return this->__alloc();}

	void clear() 
    {
		while (this->__begin_ != this->__end_) {
     		this->__alloc.destroy(--this->__end_);
    	}
    }
	void push_back(const_reference __x) {

		if (this->__end_ != this->__end_cap_) {
			this->__alloc.construct(this->__end_, __x);
			++this->__end_;
		}
		else {
			size_type __cap;
			if (this->size() == 0)
				__cap = 1;
			else
				__cap = (this->__end_cap_ - this->__begin_) * 2;
			this->reserve(__cap);
			// this->insert(this->end(), __x);
			this->__alloc.construct(this->__end_, __x);
			++this->__end_;
		}
    }
    void pop_back() {
		--this->__end_;
		this->__alloc.destroy(this->__end_);
	}

////////////////////////////////////////////////////////////
    template <class _InputIterator>
    void assign(_InputIterator __first, _InputIterator __last, 
			typename ft::enable_if<!ft::is_integral< _InputIterator >::value >::type* = NULL) {
		size_type __new_size = static_cast<size_type>(ft::distance(__first, __last));
		if (__new_size <= capacity()) // just destroy and construct
		{
			this->clear();
			while (__first != __last) this->__alloc.construct(this->__end_++, *__first++);
		}
		else // reallocate
		{
			this->clear();
			this->__alloc.deallocate(this->__begin_, this->capacity());
			this->__begin_ = this->__end_ = this->__alloc.allocate(__new_size);
			this->__end_cap_ = this->__begin_ + __new_size;
    		while (__first != __last) this->__alloc.construct(this->__end_++, *__first++);
		}
	}
    void assign(size_type __n, const_reference __u) {
		if (__n <= capacity()) // just destroy and construct
		{
			this->clear();
			while (__n--) this->__alloc.construct(this->__end_++, __u);
		}
		else // reallocate
		{
			// size_type new_capacity = capacity() * 2;
			this->clear();
			this->__alloc.deallocate(this->__begin_, this->capacity());
			this->__begin_ = this->__end_ = this->__alloc.allocate(__n);
			this->__end_cap_ = this->__begin_ + __n;
    		while (__n--) this->__alloc.construct(this->__end_++, __u);
		}
	}

    iterator insert(iterator __position, const_reference __x) {
		const size_type __n = __position - begin();
		// this->insert(__position, 1, __x);
	{
		pointer __p = this->__begin_ + (__position - begin());
		if (1 <= static_cast<size_type>(this->capacity() - this->size())) // enough memory
		{
			pointer __iter = this->__end_;
			if (__p < __iter) { // just move hops
				while (__iter != __p) {
					--__iter;
					this->__alloc.construct(__iter + 1, *__iter);
					this->__alloc.destroy(__iter);
				}
			}
			this->__end_ += 1;
			this->__alloc.construct(__iter + 1, __x); // insert elements
		}
		else // reallocate
		{
			size_type new_capacity = capacity() * 2;
			pointer __new_end_, __new_start_;
			__new_end_ = __new_start_ = this->__alloc.allocate(new_capacity);

			pointer __iter;
			for(__iter = this->__begin_; __iter != __p; ++__iter) {	// copy from origin
				this->__alloc.construct(__new_end_++, *__iter);
				this->__alloc.destroy(__iter);
			}
			this->__alloc.construct(__new_end_++, __x); // insert elements
			for(; __iter != __end_; ++__iter) {	// copy from origin
				this->__alloc.construct(__new_end_++, *__iter);
				this->__alloc.destroy(__iter);
			}
			this->__alloc.deallocate(this->__begin_, this->capacity());
			
			this->__begin_ = __new_start_;
			this->__end_ = __new_end_;
			this->__end_cap_ = this->__begin_ + new_capacity;
		}
	}
		return iterator(this->__begin_ + __n);
	}

    void insert(iterator __position, size_type __n, const_reference __x) {
		if (__n > 0)
		{
			pointer __p = this->__begin_ + (__position - begin());
			if (__n <= static_cast<size_type>(this->capacity() - this->size())) // enough memory
			{
				pointer __iter = this->__end_;
				if (__p < __iter) { // just move hops
					while (__iter != __p) {
						--__iter;
						this->__alloc.construct(__iter + __n, *__iter);
						this->__alloc.destroy(__iter);
					}
				}
				this->__end_ += __n;
				while (__n--) this->__alloc.construct(__iter + __n, __x); // insert elements
			}
			else // reallocate
			{
				size_type new_capacity = capacity() + __n;
				while (new_capacity < size() + __n)	new_capacity *= 2;
				pointer __new_end_, __new_start_;
				__new_end_ = __new_start_ = this->__alloc.allocate(new_capacity);

				pointer __iter;
				for(__iter = this->__begin_; __iter != __p; ++__iter) {	// copy from origin
					this->__alloc.construct(__new_end_++, *__iter);
					this->__alloc.destroy(__iter);
				}
				while (__n--) this->__alloc.construct(__new_end_++, __x); // insert elements
				for(; __iter != __end_; ++__iter) {	// copy from origin
					this->__alloc.construct(__new_end_++, *__iter);
					this->__alloc.destroy(__iter);
				}
				this->__alloc.deallocate(this->__begin_, this->capacity());
				
				this->__begin_ = __new_start_;
				this->__end_ = __new_end_;
				this->__end_cap_ = this->__begin_ + new_capacity;
			}
		}
		return ;
	}
    template <class _InputIterator>
	void insert(iterator __position, _InputIterator __first, _InputIterator __last,
		typename ft::enable_if<!ft::is_integral< _InputIterator >::value >::type* = NULL) {
		size_type __n = ft::distance(__first, __last);
		
		if (__n > 0)
		{
			pointer __p = this->__begin_ + (__position - begin());
			if (__n <= static_cast<size_type>(this->capacity() - this->size())) // enough memory
			{
				pointer __iter = this->__end_;
				if (__p < __iter) { // just move hops (from end-1 to __position)
					while (__iter != __p) {
						--__iter;
						this->__alloc.construct(__iter + __n, *__iter);
						this->__alloc.destroy(__iter);
					}
				}
				this->__end_ += __n;
				while (__n--) this->__alloc.construct(__iter + __n, *--__last); // insert elements at __position
			}
			else // reallocate
			{
				size_type new_capacity = capacity() * 2;
				if (new_capacity == 0)
					new_capacity = 1;
				else
					while (new_capacity < size() + __n)	new_capacity *= 2;
				pointer __new_end_, __new_start_;
				__new_end_ = __new_start_ = this->__alloc.allocate(new_capacity);

				pointer __iter;
				for(__iter = this->__begin_; __iter != __p; ++__iter) {
					this->__alloc.construct(__new_end_++, *__iter);
					this->__alloc.destroy(__iter);
				}

				while (__first != __last)	this->__alloc.construct(__new_end_++, *__first++); // insert elements
				
				for(; __iter != __end_; ++__iter) {
					this->__alloc.construct(__new_end_++, *__iter);
					this->__alloc.destroy(__iter);
				}
				this->__alloc.deallocate(this->__begin_, this->capacity());
				
				this->__begin_ = __new_start_;
				this->__end_ = __new_end_;
				this->__end_cap_ = this->__begin_ + new_capacity;
			}
		}
		return ;
	}
    
	iterator erase(iterator __position) {
		// size_type __n = this->end() - __position;
		// // if (__n <= 0) return (iterator(__position));
		// // std::cout << __n << std::endl;
		// pointer __iter = this->__begin_ + __n;
		// this->__alloc.destroy(__iter);
		// while (__n--) {
		// 	this->__alloc.construct(__iter, *(__iter + 1));
		// 	this->__alloc.destroy(++__iter);
		// }
		// --this->__end_;
		// return (iterator(__position));
		return (erase(__position, __position + 1));
	}
    iterator erase(iterator __first, iterator __last) {
		size_type __n = ft::distance(__first, __last);
		pointer __iter, __ret_iter;
		__iter = __ret_iter = this->__begin_ + (__first - begin());
		pointer __p = this->__end_;
		
		if (__iter < __p && __n > 0) {
			while (__iter + __n != __p) {
				this->__alloc.destroy(__iter);
				this->__alloc.construct(__iter, *(__iter + __n));
				++__iter;
			}
			this->__end_ = __iter;
			while (__iter != __p) this->__alloc.destroy(__iter++);
		}
		return (iterator(__ret_iter));
	}

    

    void swap(vector& x) {
		if (&x == this) return;

		pointer __tmp_begin_ = x.__begin_;
		pointer __tmp_end_ = x.__end_;
		pointer __tmp_end_cap_ = x.__end_cap_;
		x.__begin_ = this->__begin_;
		x.__end_ = this->__end_;
		x.__end_cap_ = this->__end_cap_;
		this->__begin_ = __tmp_begin_;
		this->__end_ = __tmp_end_;
		this->__end_cap_ = __tmp_end_cap_;
  	};
};

template < class T, class Alloc >
bool operator==(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
};


template < class T, class Alloc >
bool operator!=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) {
  return !(lhs == rhs);
};


template < class T, class Alloc >
bool operator<(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());  // if same, return false
};


template < class T, class Alloc >
bool operator<=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) {
  return (!(rhs < lhs));
};


template < class T, class Alloc >
bool operator>(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) {
  return (rhs < lhs);
};


template < class T, class Alloc >
bool operator>=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) {
  return (!(lhs < rhs));
};


template < class T, class Alloc >
void swap(vector< T, Alloc >& x, vector< T, Alloc >& y) {
  x.swap(y);
};

}

#endif