#define BOOST_TEST_MODULE vector
#include "../vector.h"
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <stdio.h>

using leo::vector;

void print(const vector<int>& v)
{
	for (int i = 0;i != v.size();++i)
		printf("%d  ",v[i]);
	printf("\n");
}

BOOST_AUTO_TEST_CASE (constructor)
{
	{
		const vector<int> 
			a,
			b(10),
			c(10,2),
			d(b),
			e(d.begin(),d.end());
	}
	{
		 vector<std::string> 
			a,
			b(10),
			c(10,"s"),
			d(b),
			e(d.begin(),d.end());
		a = b;
	}
	{
		vector<int> 
			a,
			b(10),
			c(10,2),
			d(b),
			e(d.begin(),d.end());
		a = b;
	}
}

BOOST_AUTO_TEST_CASE (normal_member)
{
	vector<int> a;
	for (int i = 0;i != 10;++i) 
	{
		a.push_back(i);
		BOOST_CHECK_EQUAL(a[i],i);
		BOOST_CHECK_EQUAL(a.at(i),i);
	}
	bool if_throw = false;
	try
	{
		a.at(123);
	}
	catch (...)
	{
		if_throw = true;
	}
	if (!if_throw) BOOST_ERROR("no throw");
	BOOST_CHECK_EQUAL(*(a.begin()),0);
	BOOST_CHECK_EQUAL(*(a.end() - 1),9);
	BOOST_CHECK_EQUAL(*(a.rbegin()),9);
	BOOST_CHECK_EQUAL(*(a.rend() - 1),0);
	BOOST_CHECK_EQUAL(a.front(),0);
	BOOST_CHECK_EQUAL(a.back(),9);
	vector<int> b;
	BOOST_CHECK_EQUAL(b.size(),0);
	BOOST_CHECK_EQUAL(b.capacity(),0);
	BOOST_CHECK(b.empty());
	b.resize(4);
	BOOST_CHECK_EQUAL(b.size(),4);
	BOOST_CHECK_EQUAL(b.capacity(),4);
	BOOST_CHECK(!b.empty());
	b.reserve(6);
	BOOST_CHECK_EQUAL(b.size(),4);
	BOOST_CHECK_EQUAL(b.capacity(),6);
}

BOOST_AUTO_TEST_CASE(modifiers)
{
	vector<int>	a;
	a.assign(3,4);
	BOOST_CHECK_EQUAL(a.size(),3);
	BOOST_CHECK_EQUAL(a[2],4);
	a.clear();
	for (int i = 0;i != 10;++i)
	{
		a.push_back(i);
	}
	BOOST_CHECK_EQUAL(a.size(),10);
	BOOST_CHECK_EQUAL(a[3],3);
	vector<int> b;
	b.assign(a.begin(),a.end());
	BOOST_CHECK_EQUAL(b.size(),10);
	BOOST_CHECK_EQUAL(b[0],0);
	BOOST_CHECK_EQUAL(b[2],2);
	BOOST_CHECK_EQUAL(b[3],3);
	b.pop_back();
	BOOST_CHECK_EQUAL(b.size(),9);
	b.insert(b.begin() + 1,6);
	BOOST_CHECK_EQUAL(b[1],6);
	b.erase(b.begin() + 1);
	BOOST_CHECK_EQUAL(b[1],1);
	print(b);
	b.erase(b.end() - 3,b.end());
	printf("after erase:\n");
	print(b);
	b.insert(b.begin() + 1,b.begin(),b.end());
	printf("after insert(iterator):\n");
	print(b);
	b.insert(b.begin() + 1,6,9);
	printf("after insert(fill_n):\n");
	print(b);
	printf("before swap:\n");
	print(a);print(b);
	a.swap(b);
	printf("after swap:\n");
	print(a);print(b);
	std::allocator<int> alloc = a.get_allocator();
	swap(a,b);
	BOOST_CHECK(a != b);
	b.assign(a.begin(),a.end());
	BOOST_CHECK(a == b);
	b.push_back(99);
	BOOST_CHECK(a < b);
	BOOST_CHECK(b > a);
	BOOST_CHECK(a <= b);
	BOOST_CHECK(b >= a);
	vector<int> c;
}
