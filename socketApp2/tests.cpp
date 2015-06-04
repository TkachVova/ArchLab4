#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE TestingSOMEFUNCTIONS
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <iostream>
using namespace std;
 
bool IsPalindrom(string str)
	{
		int L = str.length();	//To find length of the string
		int C;	
		for(C=0;(C<L/2) && (str[C]==str[L-C-1]);C++);

		if(C==L/2)
			return true;
		else
			return false;
	}	
string FindPalindroms(string str, int n) 
	{
		string result;    
		string word;
		stringstream ss(str); 
	
		while (ss >> word)
		{	
			if(word.length() ==n)
			{
				if(IsPalindrom(word)){
					 result+=word +="  ";
					}
			}
		}	
		return result;
	}

BOOST_AUTO_TEST_CASE(MyTestCase) 
{
	// To simplify this example test, let's suppose we'll test 'float'.
	// Some test are stupid, but all should pass. 

	BOOST_CHECK_EQUAL(IsPalindrom("aaabbaaa"), 1);
	BOOST_CHECK_EQUAL(IsPalindrom("aabb"), 0);
	
} 

BOOST_AUTO_TEST_CASE(MyTestCase2) 
{
	// To simplify this example test, let's suppose we'll test 'float'.
	// Some test are stupid, but all should pass. 

	BOOST_CHECK_EQUAL(FindPalindroms("aabb abc", 3), "");
	BOOST_CHECK_EQUAL(FindPalindroms("aabbaa abc", 6), "aabbaa  ");
	
} 





