#define BOOST_TEST_MODULE iterator
#include <boost/test/included/unit_test.hpp>
#include "vector.h"
#include <string>

using leo::__vec_iterator;
using leo::__const_vec_iterator;

BOOST_AUTO_TEST_CASE (normal_iterator)
{
	//constructor
	int n[3] = {1,2,3};
	__vec_iterator<int> a,b(&n[0]);
	__vec_iterator<int> c(b);
	a = b;
	std::string s;
	__vec_iterator<std::string> d(&s);
	//overload operator
	BOOST_CHECK_EQUAL(*a,1);
	BOOST_CHECK_EQUAL(d->size(),0);
	BOOST_CHECK_EQUAL(*(++a),2);
	BOOST_CHECK_EQUAL(*(a++),2);
	BOOST_CHECK_EQUAL(*(--a),2);
	BOOST_CHECK_EQUAL(*(a--),2);
	BOOST_CHECK_EQUAL(*(a + 2),3);
	BOOST_CHECK_EQUAL(*(a += 2),3);
	BOOST_CHECK_EQUAL(*(a - 2),1);
	BOOST_CHECK_EQUAL(*(a -= 2),1);
	BOOST_CHECK_EQUAL(a[2],3);
	a[0] = 10;
	BOOST_CHECK_EQUAL(a[0],10);
	BOOST_CHECK(a == b);
	BOOST_CHECK(a <= b);
	BOOST_CHECK(a >= b);
	b+=2;
	BOOST_CHECK_EQUAL(b - a,2);
	BOOST_CHECK(a != b);
	BOOST_CHECK(a < b);
	BOOST_CHECK(a <= b);
	BOOST_CHECK(b > a);
	BOOST_CHECK(b >= a);
}

BOOST_AUTO_TEST_CASE (const_iterator)
{
	//constructor
	const int n[3] = {1,2,3};
	__const_vec_iterator<int> a,b(&n[0]);
	__const_vec_iterator<int> c(b);
	a = b;
	std::string s;
	__const_vec_iterator<std::string> d(&s);
	__vec_iterator<int> e;
	__const_vec_iterator<int> f(e);
	//overload operator
	BOOST_CHECK_EQUAL(*a,1);
	BOOST_CHECK_EQUAL(d->size(),0);
	BOOST_CHECK_EQUAL(*(++a),2);
	BOOST_CHECK_EQUAL(*(a++),2);
	BOOST_CHECK_EQUAL(*(--a),2);
	BOOST_CHECK_EQUAL(*(a--),2);
	BOOST_CHECK_EQUAL(*(a + 2),3);
	BOOST_CHECK_EQUAL(*(a += 2),3);
	BOOST_CHECK_EQUAL(*(a - 2),1);
	BOOST_CHECK_EQUAL(*(a -= 2),1);
	BOOST_CHECK_EQUAL(a[2],3);
	BOOST_CHECK(a == b);
	BOOST_CHECK(a <= b);
	BOOST_CHECK(a >= b);
	b+=2;
	BOOST_CHECK_EQUAL(b - a,2);
	BOOST_CHECK(a != b);
	BOOST_CHECK(a < b);
	BOOST_CHECK(a <= b);
	BOOST_CHECK(b > a);
	BOOST_CHECK(b >= a);
}


