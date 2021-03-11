#include <iostream>
#include <regex>
#include <string>
#include <vector>

void Analyzer(std::string s, std::regex pattern)
{
	std::smatch matches;
	if (std::regex_search(s, matches, pattern))
	{
		for (std::size_t i = 0; i < matches.size(); ++i)
		{
			std::cout << matches[i] << " | ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char** argv)
{
	std::regex pattern1(R"(^[\s?\w*\.*\-*\_*\+*\'*\%*]{1,64}\@([A-Za-z0-9-]+\.[A-Za-z0-9-]+)$)");
	std::vector<std::string> vec_data;
	vec_data.push_back("Maslennikov.DV@phystech.edu"); // TRUE
	vec_data.push_back("this_is_not_email"); // FALSE
	vec_data.push_back("this_is_also@@not_email"); // FALSE
	vec_data.push_back("oh_yeah-what.s+A-BeAuTiFuL@email.com"); // TRUE
	vec_data.push_back("'KONO+DIO'@DA.mem"); // TRUE
	vec_data.push_back("i_like_underscore@but_its_not_allowed_in_this_part.example.com"); // FALSE
	vec_data.push_back("ab(c)d, e:f; g<h>i[j\k]l@example.com"); // FALSE
	vec_data.push_back("1234567890123456789012345678901234567890123456789012345678901234+x@example.com"); // FALSE
	vec_data.push_back("user% example.com@example.org"); // TRUE
	vec_data.push_back("@phystech.edu"); // FALSE
	for (size_t i = 0; i < vec_data.size(); i++)
	{
		Analyzer(vec_data[i], pattern1); // вывод подходящих email
	}
	system("pause");
	return EXIT_SUCCESS;
}
