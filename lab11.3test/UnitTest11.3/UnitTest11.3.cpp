#include "pch.h"
#include "CppUnitTest.h"
#include "../lab11.3test/11.3.cpp"  // �������� ���� � ����� ���� �����

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UTLab91A
{
    TEST_CLASS(DatabaseTest)
    {
    public:
        // ���� ��� ������� searchByPhone, ���� ������� �� ���������
        TEST_METHOD(SearchByPhone_InvalidPhone)
        {
            // ������� ����� �����
            stringstream mockFileContent;
            mockFileContent << "12 202 Lucas Young\n"    // ����� � ��������� 12
                << "13 203 Daniel King\n"; // ����� � ��������� 13
            ofstream mockFile("test.db");
            mockFile << mockFileContent.str();
            mockFile.close();

            // ������� �������� ����������� ��� ������
            stringstream mockInput("99");
            streambuf* oldCin = cin.rdbuf(mockInput.rdbuf());  // ��������������� cin ��� ������� ��������

            // ��������������� ��������� � stringstream ��� ��������
            stringstream mockOutput;
            streambuf* oldCout = cout.rdbuf(mockOutput.rdbuf());  // ��������������� cout

            // ��������� ������� ������ �� ������� ��������
            searchByPhone("test.db", "99");

            // ����������, �� ����������� ��� ��������� ������ ��������
            string expectedOutput = "Phone number not found.\n";
            Assert::IsTrue(mockOutput.str().find(expectedOutput) != string::npos);

            // ³��������� cin � cout
            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);
        }
    };
}
