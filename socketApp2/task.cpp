#ifndef task_class
#define task_class

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>

using namespace boost::archive;

class task
{
public: 
	task() = default;
	task(int data_len) 
	{
		if (data_len > 1024)
			this->data_len = 1024; 
		else
			this->data_len = data_len;
		text = "abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt \
				abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt \
				abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt \
				abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt \
				abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt \
				abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt \
				abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt \
				abcbca dasd aghhga trrt qwerty oiu rrr q dd lql vqqv dad mom qwewq poppop tgbbgt";
	}  
	task(int number, std::string text)   
	{  
		this->number = number;  
		this->text = text;   
	}
	int number;
	int data_len; 
	std::string text; 

  	std::string save()
	{
		std::stringstream ss;  
		text_oarchive oa(ss);
		std::cout << "data_len: " << this->data_len << "\n"; 
		//std::cout << "text before: " << this->text << "\n"; 
		this->number = rand() % 6 + 1;  
		if (text.length() > data_len)
             this->text = this->text.substr(0, this->data_len);
		//std::cout << "text after: " << this->text << "\n";
		task t(this->number, this->text);
		oa << t; 
		return ss.str();  
	}   

	task load(std::string input) 
	{
		//std::cout << "load_input: " << input << "\n";
		std::stringstream ss; 
		ss << input; 
		text_iarchive ia(ss);   
		task t;
		ia >> t;
		this->number = t.number;
		this->text = t.text;
		return t;
	}

private:
  	friend class boost::serialization::access;

  	template <typename Archive>
  	void serialize(Archive &ar, const unsigned int version) 
	{ 
		ar & number;
      	ar & text;
	}

};


#endif

