#include <iostream>
#include <iomanip>
#include <Windows.h> 

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    long double money, ex_rate = 0;
    std::cout << "Enter the money (US dollars): " << std::endl;
    std::cin >> money;

    money *= 100;

    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::showbase << "Amount entered (in US dollars): " << std::put_money(money) << std::endl;

    std::cout << "Enter the dollar-ruble exchange rate: " << std::endl;
    std::cin >> ex_rate;

    money = money * ex_rate;
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cout << std::showbase << "Amount entered (in rubles): " << std::put_money(money) << std::endl;
    system("pause");
    return EXIT_SUCCESS;
}