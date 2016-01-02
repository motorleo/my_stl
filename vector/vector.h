#ifndef _MY_STL_VECTOR_H_
#define _MY_STL_VECTOR_H_
#include <memory>
#include <iterator>

namespace leo
{
//============================================
//       iterator
//============================================

#define iterator_base std::iterator<std::random_access_iterator_tag,T> 
//normal iterator
template <typename T>
class __vec_iterator :	public iterator_base
{
public:
	typedef typename iterator_base::difference_type  difference_type;
	typedef typename iterator_base::pointer          pointer;
	typedef typename iterator_base::reference        reference;
	__vec_iterator() : ptr() {}

	explicit __vec_iterator(T* p) : ptr(p) {}

	__vec_iterator(const __vec_iterator& rhs) //expect NRV optimize
	{
		if (this != rhs)
		{
			memcpy(this,&rhs,sizeof(this));
		}
	}

	reference operator*() { return *ptr; }

	pointer operator->() { return &operator*(); } //FIXME:must i do that?

	__vec_iterator& operator++()  { ++ptr;return *this; } //FIXME:iter++?

	__vec_iterator& operator--() { --ptr;return *this; }

	__vec_iterator& operator+(difference_type n) 
	{
		return __vec_iterator(ptr+n);
	}

	__vec_iterator& operator-(difference_type n)
	{
		return __vec_iterator(ptr+n);
	}

	__vec_iterator& operator+=(difference_type n) { ptr+=n;return *this; }

	__vec_iterator& operator-=(difference_type n) { ptr-=n;return *this; }

	const pointer& base() const { return ptr; }
private:
	pointer ptr;
}; //__vec_iterator

//overload operator
template<typename T>
inline typename __vec_iterator<T>::difference_type
operator-(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() - rhs.base();
}

template<typename T>
inline bool 
operator==(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() == rhs.base();
}

template<typename T>
inline bool 
operator!=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() != rhs.base();
}

template<typename T>
inline bool 
operator<(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() < rhs.base();
}

template<typename T>
inline bool 
operator>(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() > rhs.base();
}

template<typename T>
inline bool 
operator<=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename T>
inline bool
operator>=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() >= rhs.base();
}


}

#endif
