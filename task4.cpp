#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

int main()
{
	// Выбранный формат - HH:MM:SS DD:MM:YYYY
	std::string data = R"(23:59:59 12.12.2012 14:00:45 17.03.2002 this-is-not-time 23:57:35 22:57:35 31.12.2020 24:57:35 31.12.2020 24:57:35 32.12.2020)";
	std::regex pattern(R"((([0-1]\d|2[0-3])(:[0-5]\d){2}\s{1}(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\d\d))");

	std::copy(
		std::sregex_token_iterator(data.begin(), data.end(), pattern, { 0 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));
	system("pause");

	return EXIT_SUCCESS;
}
