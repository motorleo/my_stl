#ifndef _MY_STL_VECTOR_H_
#define _MY_STL_VECTOR_H_
#include <memory>
#include <iterator>

namespace leo
{
//============================================
//       Normal_iterator
//============================================

#define iterator_base std::iterator<std::random_access_iterator_tag,T> 
template <typename T>
class __vec_iterator :	public iterator_base
{
public:
	typedef typename iterator_base::value_type       value_type;
	typedef typename iterator_base::difference_type  difference_type;
	typedef typename iterator_base::pointer          pointer;
	typedef typename iterator_base::reference        reference;
	__vec_iterator() : ptr() {}

	explicit __vec_iterator(pointer p) : ptr(p) {}

	__vec_iterator(const __vec_iterator& rhs) //expected NRV optimize
	{
		memcpy(this,&rhs,sizeof(this));
	}

	reference operator*() { return *ptr; }

	pointer operator->() { return &operator*(); }

	__vec_iterator& operator++()  { ++ptr;return *this; } 

	__vec_iterator operator++(int) 
   	{
		__vec_iterator<T> temp(*this);
	   	++(*this);
		return temp; 
	} 

	__vec_iterator& operator--() { --ptr;return *this; }

	__vec_iterator operator--(int) 
   	{
		__vec_iterator<T> temp(*this);
	   	--(*this);
		return temp; 
	}

	__vec_iterator operator+(difference_type n) 
	{
		return __vec_iterator(ptr+n);
	}

	__vec_iterator operator-(difference_type n)
	{
		return __vec_iterator(ptr-n);
	}

	__vec_iterator& operator+=(difference_type n) { ptr+=n;return *this; }

	__vec_iterator& operator-=(difference_type n) { ptr-=n;return *this; }

	reference operator[](difference_type n)
	{
		return *(ptr + n);
	}

	const pointer& base() const { return ptr; }
private:
	pointer ptr;
}; //__vec_iterator

//overload operator
template <typename T>
inline typename __vec_iterator<T>::difference_type
operator-(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() - rhs.base();
}

template <typename T>
inline bool 
operator==(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() == rhs.base();
}

template <typename T>
inline bool 
operator!=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() != rhs.base();
}

template <typename T>
inline bool 
operator<(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() < rhs.base();
}

template <typename T>
inline bool 
operator>(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() > rhs.base();
}

template <typename T>
inline bool 
operator<=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() <= rhs.base();
}

template <typename T>
inline bool
operator>=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() >= rhs.base();
}

//============================================
//      Const_iterator
//============================================

#define const_iterator_base std::iterator<std::random_access_iterator_tag,const T> 
template <typename T>
class __const_vec_iterator : public const_iterator_base
{
public:
	typedef typename const_iterator_base::value_type       value_type;   //const T
	typedef typename const_iterator_base::difference_type  difference_type;
	typedef typename const_iterator_base::pointer          pointer;      //const T*
	typedef typename const_iterator_base::reference        reference;    //const T&

	__const_vec_iterator() : ptr() {}

	explicit __const_vec_iterator(const pointer p) : ptr(p) {}

	__const_vec_iterator(const __const_vec_iterator& rhs) //expected NRV optimize
	{
		memcpy(this,&rhs,sizeof(this));
	}

	__const_vec_iterator(const __vec_iterator<T>& rhs) //allowed implicit conversion
	{
		memcpy(this,&rhs,sizeof(this));
	}

	reference operator*() { return *ptr; }

	pointer operator->() { return &operator*(); }

	__const_vec_iterator& operator++()  { ++ptr;return *this; } 

	__const_vec_iterator operator++(int) 
   	{
		__const_vec_iterator<T> temp(*this);
	   	++(*this);
		return temp; 
	} 

	__const_vec_iterator& operator--() { --ptr;return *this; }

	__const_vec_iterator operator--(int) 
   	{
		__const_vec_iterator<T> temp(*this);
	   	--(*this);
		return temp; 
	}

	__const_vec_iterator operator+(difference_type n) 
	{
		return __const_vec_iterator(ptr+n);
	}

	__const_vec_iterator operator-(difference_type n)
	{
		return __const_vec_iterator(ptr-n);
	}

	__const_vec_iterator& operator+=(difference_type n) { ptr+=n;return *this; }

	__const_vec_iterator& operator-=(difference_type n) { ptr-=n;return *this; }

	reference operator[](difference_type n)
	{
		return *(ptr + n);
	}

	const pointer& base() const { return ptr; }
private:
	pointer ptr;  //const T*
}; //__const_vec_iterator

//overload operator
template <typename T>
inline typename __const_vec_iterator<T>::difference_type
operator-(const __const_vec_iterator<T>& lhs,const __const_vec_iterator<T>& rhs)
{
	return lhs.base() - rhs.base();
}

template <typename T>
inline bool 
operator==(const __const_vec_iterator<T>& lhs,const __const_vec_iterator<T>& rhs)
{
	return lhs.base() == rhs.base();
}

template <typename T>
inline bool 
operator!=(const __const_vec_iterator<T>& lhs,const __const_vec_iterator<T>& rhs)
{
	return lhs.base() != rhs.base();
}

template <typename T>
inline bool 
operator<(const __const_vec_iterator<T>& lhs,const __const_vec_iterator<T>& rhs)
{
	return lhs.base() < rhs.base();
}

template <typename T>
inline bool 
operator>(const __const_vec_iterator<T>& lhs,const __const_vec_iterator<T>& rhs)
{
	return lhs.base() > rhs.base();
}

template <typename T>
inline bool 
operator<=(const __const_vec_iterator<T>& lhs,const __const_vec_iterator<T>& rhs)
{
	return lhs.base() <= rhs.base();
}

template <typename T>
inline bool
operator>=(const __const_vec_iterator<T>& lhs,const __const_vec_iterator<T>& rhs)
{
	return lhs.base() >= rhs.base();
}

//============================================
//       vector
//============================================

template <typename T,typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef T                                         value_type;
	typedef Alloc					                  allocator_type;
	typedef typename allocator_type::reference        reference;
	typedef typename allocator_type::const_reference  const_reference;
	typedef typename allocator_type::pointer          pointer;
	typedef typename allocator_type::const_pointer    const_pointer;
	typedef __vec_iterator<value_type>                iterator;
	typedef __const_vec_iterator<value_type>          const_iterator;
	typedef size_t                                    size_type;
	typedef std::ptrdiff_t                            difference_type;

	//Construtor
	vector() : _imp() {}

	vector(size_type n,const value_type& value) : _imp(n,value) {}

	explicit vector(size_type n) : _imp(n) {}

	vector(iterator begin,iterator end) : _imp(begin,end) {}

	vector(const_iterator begin,const_iterator end) : _imp(begin,end) {}

	vector(const vector& vec) : _imp(vec.begin(),vec.end()) {}

	vector& operator=(const vector& rhs)
	{
		if (*this != rhs)
		{
			_imp.selfdelete();
			_imp.initialize_Copy(rhs.begin(),rhs.end());
		}
		return *this;
	}

	//Iterator
	iterator begin() { return iterator(_imp._begin); }

	const_iterator begin() const { return const_iterator(_imp._begin); }

	iterator end() { return iterator(_imp._end); }

	const_iterator end() const { return const_iterator(_imp._end); }

	//Capacity
	size_type size() const { return _imp._end - _imp._begin; }

	void resize(size_type n) { resize(n,value_type()); }

	void resize(size_type n,const value_type& value)
	{
		if (n < size())
		{
			erase(begin() + n,end());
		}
		else
		{
			insert(end(),n - size(),value);
		}
	}
			
	size_type capacity() const { return _imp._end_of_storage - _imp._begin; }

	bool empty() { return _imp._begin == _imp._end; }

	void reserve(size_type n)
	{
		if (n > capacity())
		{
			iterator temp(_imp.allocate(n));
			uninitialized_copy(begin(),end(),temp);
			size_type old_size = size();
			_imp.selfdelete();
			_imp._begin = temp.base();
			_imp._end = _imp._begin + old_size;
			_imp._end_of_storage = _imp._begin + n;
		}
	}

	//Element access
	reference operator[](size_type n) { return *(_imp._begin + n); }

	const_reference operator[](size_type n) const
	{
		return *(_imp._begin + n);
	}	

	reference at(size_type n) 
	{
		if (n < size())
		{
			return operator[](n);
		}
		else
		{
			throw std::out_of_range("vector<T>::at");
		}
	}

	const_reference at(size_type n) const
	{
		if (n < size())
		{
			return operator[](n);
		}
		else
		{
			throw std::out_of_range("vector<T>::at");
		}
	}

	reference front() { return *_imp._begin; }

	const_reference front() const { return *_imp._begin; }

	reference back() { return *(_imp._end - 1); }

	const_reference back() const { return *(_imp._end - 1); }

	//Modifiers
	void assign(const_iterator first,const_iterator last)
	{
		size_type n = first - last;
		if (n > capacity())
		{
			_imp.selfdelete();
			_imp.initialize_Copy(first,last);
		}
		else
		{
			if (n < size())
			{
				std::copy(first,last,begin());
				iterator new_end = begin() + n;
				erase(new_end,end());
			}
			else
			{
				std::copy(first,first + size(),begin());
				std::uninitialized_copy(first + size(),last,end());
				_imp._end = _imp._begin + n;
			}
		}
	}

	void assign(iterator begin,iterator end)
	{
		assign(const_iterator(begin),const_iterator(end));
	}

	void assign(size_type n,const value_type& value)
	{
		if (n > capacity())
		{
			_imp.selfdelete();
			_imp.initialize_Imp(n,value);
		}
		else
		{
			if (n < size())
			{
				std::fill_n(begin(),n,value);
				iterator new_end = begin() + n;
				erase(new_end,end());
			}
			else
			{
				std::fill_n(begin(),size(),value);
				std::uninitialized_fill_n(end(),n - size(),value);
				_imp._end = _imp._begin + n;
			}
		}
	}

	void push_back(const value_type& value)
	{
		if (_imp._end != _imp._end_of_storage)
		{
			_imp.construct(_imp._end,value);
			++_imp._end;
		}
		else
		{
			insert(end(),value);//reallocate memory
		}
	}

	void pop_back()
	{
		--_imp._end;
		_imp.destroy(_imp._end);
	}

	iterator insert(iterator position,const value_type& value)
	{
		if (_imp._end != _imp._end_of_storage)
		{
			_imp.construct(_imp._end,*(_imp._end - 1));
			++_imp._end;
			std::copy_backward(position,(end() - 2),(end() - 1));
			*position = value;
			return position;
		}
		else
		{
			//reallocate
			size_type old_capacity = capacity();
			size_type new_capacity = old_capacity ? old_capacity * 2 : 1;
			pointer new_begin = _imp.allocate(new_capacity);
			iterator current(new_begin);
			//3 step copy and construct
			std::uninitialized_copy(begin(),position,current);
			current += position - begin();
			_imp.construct(&*(current),value);
			std::uninitialized_copy(position,end(),(current + 1));
			//deallocate old one
			_imp.selfdelete();
			_imp._begin = new_begin;
			_imp._end = new_begin + old_capacity + 1;
			_imp._end_of_storage = new_begin + new_capacity;
			return current;
		}
	}

	iterator insert(iterator position,size_type n,const value_type& value)
	{
		if (n == 0) return position;
		if ((size() + n) <= capacity())
		{
			size_type n_elem = end() - position;//count element from position to end;
			if (n > n_elem)
			{
				std::uninitialized_fill_n(end(),n - n_elem,value);
				std::uninitialized_copy(position,end(),end() + (n - n_elem));
				std::fill_n(position,n_elem,value);
			}
			else
			{
				std::uninitialized_copy(end() - n,end(),end());
				std::copy_backward(position,end() - n,end());
				std::fill_n(position,n,value);
			}
			_imp._end += n;
			return position;
		}
		else
		{
			//reallocate
			size_type old_size = size();
			size_type old_capacity = capacity();
			size_type new_capacity = std::max(old_capacity * 2,old_size + n);
			pointer new_begin = _imp.allocate(new_capacity);
			iterator current(new_begin);
			//3 step copy and construct
			std::uninitialized_copy(begin(),position,current);
			current += position - begin();
			std::uninitialized_fill_n(current,n,value);
			std::uninitialized_copy(position,end(),current + n);
			//deallocate old one
			_imp.selfdelete();
			_imp._begin = new_begin;
			_imp._end = new_begin + old_size + n;
			_imp._end_of_storage = new_begin + new_capacity;
			return current;
		}
	}

	iterator insert(iterator position,iterator first,iterator last)
	{
		size_type n = last - first;
		if (n == 0) return position;
		if ((size() + n) <= capacity())
		{
			size_type n_elem = end() - position;//count element from position to end;
			if (n > n_elem)
			{
				std::uninitialized_copy(last - (n - n_elem),last,end());
				std::uninitialized_copy(position,end(),end() + (n - n_elem));
				std::copy(first,first + n_elem,position);
			}
			else
			{
				std::uninitialized_copy(end() - n,end(),end());
				std::copy_backward(position,end() - n,end());
				std::copy(first,last,position);
			}
			_imp._end += n;
			return position;
		}
		else
		{
			//reallocate
			size_type old_size = size();
			size_type old_capacity = capacity();
			size_type new_capacity = std::max(old_capacity * 2,old_size + n);
			pointer new_begin = _imp.allocate(new_capacity);
			iterator current(new_begin);
			//3 step copy and construct
			std::uninitialized_copy(begin(),position,current);
			current += position - begin();
			std::uninitialized_copy(first,last,current);
			std::uninitialized_copy(position,end(),current + n);
			//deallocate old one
			_imp.selfdelete();
			_imp._begin = new_begin;
			_imp._end = new_begin + old_size + n;
			_imp._end_of_storage = new_begin + new_capacity;
			return current;
		}
	}

	iterator erase(iterator position)
	{
		std::copy(position + 1,end(),position);
		--_imp._end;
		_imp.destroy(_imp._end);
		return position;
	}

	iterator erase(iterator first,iterator last)
	{
		size_type n = last - first;
		std::copy(last,end(),first);
		_imp.destroy(_imp._end - n,_imp._end);
		_imp._end -= n;
		return first;
	}

	void swap(vector& rhs)
	{
		if (*this != rhs)
		{
			using std::swap;
			swap(this->_imp._begin,rhs._imp._begin);
			swap(this->_imp._end,rhs._imp._end);
			swap(this->_imp._end_of_storage,rhs._imp._end_of_storage);
		}
	}

	void clear()
	{
		erase(begin(),end());
	}

	//Allocator
	allocator_type get_allocator() const { return allocator_type(); }

private:
	//for vector data.
	//can do allocate and deallocate.
	class _vector_Imp : public Alloc 
	{
	public:
		pointer _begin;
		pointer _end;
		pointer _end_of_storage;

		_vector_Imp() 
			: Alloc(),_begin(NULL),_end(NULL),_end_of_storage(NULL) {}

		_vector_Imp(size_type n,const value_type& value)
			: Alloc()
		{
			initialize_Imp(n,value);
		}

		explicit _vector_Imp(size_type n)
			: Alloc()
		{
			initialize_Imp(n,value_type());
		}

		_vector_Imp(iterator b,iterator e)
			: Alloc()
		{
			initialize_Copy(const_iterator(b),const_iterator(e));
		}

		_vector_Imp(const_iterator b,const_iterator e)
			: Alloc()
		{
			initialize_Copy(b,e);
		}

		_vector_Imp(const _vector_Imp& imp)
		{
			initialize_Copy(imp._begin,imp._end);
		}

		~_vector_Imp()
		{
			selfdelete();
		}
		
		void selfdelete()
		{
			destroy(_begin,_end);
			Alloc::deallocate(_begin,_end - _begin);
		}

		void destroy(pointer p) { Alloc::destroy(p);}

		void destroy(pointer begin,pointer end)
		{
			for (;begin != end;++begin) Alloc::destroy(begin);
		}

		void initialize_Imp(size_type n,const value_type& value)
		{
			_begin = Alloc::allocate(n);
			std::uninitialized_fill_n(iterator(_begin),n,value);
			_end = _begin + n;
			_end_of_storage = _end;
		}

		void initialize_Copy(const_iterator b,const_iterator e)
		{
			size_type n = e - b;
			_begin = Alloc::allocate(n);
			std::uninitialized_copy(b,e,iterator(_begin));
			_end = _begin + n;
			_end_of_storage = _end;
		}


	};
	_vector_Imp _imp;
};//vector

//========================================
//      Non-member function overloads
//========================================

template <typename T,typename Alloc>
inline bool 
operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() == rhs.size() &&
		std::equal(lhs.begin(),lhs.end(),rhs.begin()))
	{
		return true;
	}
	return false;
}

template <typename T,typename Alloc>
inline bool
operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <typename T,typename Alloc>
inline bool
operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return std::lexicographical_compare(lhs.begin(),lhs.end(),
										rhs.begin(),rhs.end());
}


template <typename T,typename Alloc>
inline bool 
operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs > rhs);
}

template <typename T,typename Alloc>
inline bool
operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return rhs < lhs;
}

template<typename T,typename Alloc>
inline bool 
operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template <typename T, typename Alloc>
inline void 
swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
{
	lhs.swap(rhs);
}

}//namespace leo

#endif
