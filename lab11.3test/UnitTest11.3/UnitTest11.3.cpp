#include "pch.h"
#include "CppUnitTest.h"
#include "../lab11.3test/11.3.cpp"  // Включити файл з кодом бази даних

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UTLab91A
{
    TEST_CLASS(DatabaseTest)
    {
    public:
        // Тест для функції searchByPhone, коли телефон не знайдений
        TEST_METHOD(SearchByPhone_InvalidPhone)
        {
            // Імітація вмісту файлу
            stringstream mockFileContent;
            mockFileContent << "12 202 Lucas Young\n"    // Запис з телефоном 12
                << "13 203 Daniel King\n"; // Запис з телефоном 13
            ofstream mockFile("test.db");
            mockFile << mockFileContent.str();
            mockFile.close();

            // Імітація введення користувача для пошуку
            stringstream mockInput("99");
            streambuf* oldCin = cin.rdbuf(mockInput.rdbuf());  // Перенаправлення cin для імітації введення

            // Перенаправлення виведення в stringstream для перевірки
            stringstream mockOutput;
            streambuf* oldCout = cout.rdbuf(mockOutput.rdbuf());  // Перенаправлення cout

            // Викликаємо функцію пошуку за номером телефону
            searchByPhone("test.db", "99");

            // Перевіряємо, що повідомлення про відсутність запису виведене
            string expectedOutput = "Phone number not found.\n";
            Assert::IsTrue(mockOutput.str().find(expectedOutput) != string::npos);

            // Відновлюємо cin і cout
            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);
        }
    };
}
