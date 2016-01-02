#ifndef _MY_STL_VECTOR_H_
#define _MY_STL_VECTOR_H_
#include <memory>
#include <iterator>

namespace leo
{
//============================================
//       iterator
//============================================

//normal iterator
template <typename T>
class __vec_iterator : 
	public std::iterator<std::random_access_iterator_tag,T>
{
public:
	__vec_iterator() : ptr(NULL) {}

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
		return __vec_iterator(lhs.ptr+n);
	}

	__vec_iterator& operator+=(difference_type n) { ptr+=n;return *this; }

	__vec_iterator& operator-=(difference_type n) { ptr-=n;return *this; }

	const pointer& base() const { return ptr; }
private:
	pointer ptr;
};

//reload operator
//for __vec_iterator
template<typename T>
inline __vec_iterator::difference_type
operator-(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() - rhs.base();
}

template<typename T>
inline bool operator==(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() == rhs.base();
}

template<typename T>
inline bool operator!=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() != rhs.base();
}

template<typename T>
inline bool operator<(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() < rhs.base();
}

template<typename T>
inline bool operator>(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() > rhs.base();
}

template<typename T>
inline bool operator<=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename T>
inline bool operator>=(const __vec_iterator<T>& lhs,const __vec_iterator<T>& rhs)
{
	return lhs.base() >= rhs.base();
}


}

#endif
