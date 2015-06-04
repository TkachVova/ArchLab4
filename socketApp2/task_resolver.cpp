#ifndef task_resolve
#define task_resolve

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class resolver
{
public:
	static bool IsPalindrom(string str)
	{
		int L = str.length();	//To find length of the string
		int C;	
		for(C=0;(C<L/2) && (str[C]==str[L-C-1]);C++);

		if(C==L/2)
			return true;
		else
			return false;
	}	
	
	static string FindPalindroms(string str, int n)
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
};


#endif
