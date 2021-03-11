#include <iostream>
#include <locale>
#include <string>
#include <boost/locale.hpp>
#include <Windows.h>
#include <vector>

std::string convert_locale_to_utf(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

std::u32string UTF_32_Transliterator(std::u32string rus_string, size_t size)
{
	std::u32string eng_string;
	std::vector<int> rus_codes = { ' ', 1040, 1041, 1042, 1043, 1044, 1045, 1047, 1048, 1049, 1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1066, 1067, 1068, 1025, 1046, 1063, 1064, 1069, 1070, 1071, 1065 };
	std::vector<int> translit_codes = { ' ', 65, 66, 86, 71, 68, 69, 90, 73, 74, 75, 76, 77, 78, 79, 80, 82, 83, 84, 85, 70, 72, 67, 34, 89, 39, 89, 90, 67, 83, 69, 89, 89, 83, 79, 72, 72, 72, 39, 85, 65, 72, 72 };
	// к сожалению, в этих двух векторах элементы идут не по порядку, и придумать способа лучше и надежнее, чем ввод вручную, я не смог
	// P.S. проверку на правильность ввода сделал ниже - вывел весь алфавит
	// P.S.S. и по той же причине не получилось красиво и органично добавить буквы нижнего регистра :(
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < rus_codes.size(); j++)
		{
			if ((rus_string[i] == rus_codes[j]) && (j <= 25))
			{
				eng_string.push_back(translit_codes[j]);
				break;
			}
			else
			{
				if ((rus_string[i] == rus_codes[j]) && (j != 33))
				{
					eng_string.push_back(translit_codes[j]);
					eng_string.push_back(translit_codes[j + 8]);
					break;
				}
				else if ((rus_string[i] == rus_codes[j]) && (j == 33))
				{
					eng_string.push_back(translit_codes[j]);
					eng_string.push_back(translit_codes[j + 8]);
					eng_string.push_back(translit_codes[j + 9]);
					break;
				}
			}
		}
	}
	return eng_string;
}

void Transliterator(std::string rus_string)
{
	std::cout << "Original string: " << rus_string << std::endl;
	std::string u8string1 = convert_locale_to_utf(rus_string);
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	//std::cout << "UTF-8: " << u8string1 << std::endl; // UTF-8

	std::u32string u32string = boost::locale::conv::utf_to_utf < char32_t, char >(u8string1); // UTF-32
	/*std::cout << "UTF-32: ";
	for (auto c : u32string)
	{
		std::cout << c << ' ';
	}*/
	std::u32string u32string2 = UTF_32_Transliterator(u32string, rus_string.size());

	std::string u8string2 = boost::locale::conv::utf_to_utf < char, char32_t >(u32string2);
	//std::cout << "UTF-8: " << u8string2 << std::endl; // UTF-8

	std::string eng_string = convert_utf_to_locale(u8string2);
	system("chcp 1251");
	std::cout << "Transformed string: " << eng_string << std::endl;
	std::cout << std::endl;
}


int main()
{
	system("chcp 1251");
	size_t String_Container_Size;
	std::cout << "Введите количество слов: ";
	std::cin >> String_Container_Size;
	std::vector<std::string> String_Container(String_Container_Size);
	for (size_t i = 0; i < String_Container_Size; i++)
	{
		std::cout << "Введите " << i + 1 << " слово (заглавными буквами): ";
		std::cin >> String_Container[i];
	}
	std::cout << std::endl;
	for (size_t i = 0; i < String_Container_Size; i++)
	{
		Transliterator(String_Container[i]);
	}

	std::string rus_string1 = "САМОЕ СЛОЖНОЕ СЛОВОСОЧЕТАНИЕ ДЛЯ ПЕРЕВОДА";
	Transliterator(rus_string1);

	std::string rus_string2 = "А Б В Г Д Е Ё Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я";
	Transliterator(rus_string2);
	return EXIT_SUCCESS;
}
