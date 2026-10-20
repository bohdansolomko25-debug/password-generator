#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <cctype>
#include <windows.h>

using namespace std;

// Функція №1 — генерація пароля
string generatePassword(int length)
{
    const string characters =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%^&*";

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, characters.size() - 1);

    string password;

    for (int i = 0; i < length; i++)
    {
        password += characters[distribution(generator)];
    }

    return password;
}

// Функція №2 — перевірка складності пароля
bool checkPasswordStrength(const string& password)
{
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (char c : password)
    {
        if (isupper(static_cast<unsigned char>(c)))
            hasUpper = true;
        else if (islower(static_cast<unsigned char>(c)))
            hasLower = true;
        else if (isdigit(static_cast<unsigned char>(c)))
            hasDigit = true;
        else
            hasSpecial = true;
    }

    return password.length() >= 8 &&
        hasUpper &&
        hasLower &&
        hasDigit &&
        hasSpecial;
}

// Функція №3 — запис пароля у файл
void savePasswordToFile(const string& password)
{
    ofstream file("password.txt");

    if (file.is_open())
    {
        file << password;
        file.close();

        cout << "Пароль збережено у файл password.txt" << endl;
    }
    else
    {
        cout << "Помилка відкриття файлу!" << endl;
    }
}

int main()
{
    // Налаштування кодування консолі Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Довжина пароля — 12 символів
    int length = 12;

    cout << "=================================" << endl;
    cout << "       Генератор паролів" << endl;
    cout << "=================================" << endl;

    // Генерація пароля
    string password = generatePassword(length);

    cout << "Згенерований пароль: " << password << endl;

    // Перевірка складності
    if (checkPasswordStrength(password))
    {
        cout << "Складність: Висока" << endl;
    }
    else
    {
        cout << "Складність: Низька" << endl;
    }

    // Збереження у файл
    savePasswordToFile(password);

    cout << "Програму завершено." << endl;

    return 0;
}