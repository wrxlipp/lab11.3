#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Функція для створення бази даних
void createDatabase(const string& filename) {
    ofstream file(filename, ios::trunc); // Відкриваємо файл для запису
    if (!file.is_open()) {
        cerr << "Failed to open the file for writing.\n"; // Не вдалося відкрити файл для запису
        return;
    }
    cout << "Database created.\n"; // База даних створена
    file.close();
}

// Функція для перегляду бази даних
void viewDatabase(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // Не вдалося відкрити файл для читання
        return;
    }

    string line;
    cout << "Database contents:\n"; // Вміст бази даних
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Функція для додавання запису
void addRecord(const string& filename) {
    ofstream file(filename, ios::app); // Відкриваємо файл для додавання
    if (!file.is_open()) {
        cerr << "Failed to open the file for writing.\n"; // Не вдалося відкрити файл для запису
        return;
    }

    string phone, room, employees;
    cout << "Enter phone number (two digits): "; // Введіть номер телефону (двозначний)
    cin >> phone;
    if (phone.length() != 2 || !isdigit(phone[0]) || !isdigit(phone[1])) {
        cerr << "Invalid phone number format.\n"; // Неправильний формат номера телефону
        return;
    }

    cout << "Enter room number: "; // Введіть номер приміщення
    cin >> room;

    cin.ignore(); // Очищаємо буфер
    cout << "Enter list of employees (1 to 4 names): "; // Введіть список службовців (від 1 до 4 прізвищ)
    getline(cin, employees);

    // Перевірка кількості службовців
    stringstream ss(employees);
    string word;
    int count = 0;
    while (ss >> word) count++;

    if (count < 1 || count > 4) {
        cerr << "The number of employees must be between 1 and 4.\n"; // Кількість службовців має бути від 1 до 4
        return;
    }

    file << phone << " " << room << " " << employees << endl;
    cout << "Record added to the database.\n"; // Запис додано до бази
    file.close();
}

// Функція для пошуку за номером телефону
void searchByPhone(const string& filename, const string& phone) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // Не вдалося відкрити файл для читання
        return;
    }

    string line, foundRoom, foundEmployees;
    while (getline(file, line)) {
        stringstream ss(line);
        string currentPhone, currentRoom, employees;
        ss >> currentPhone >> currentRoom;
        getline(ss, employees);
        if (currentPhone == phone) {
            foundRoom = currentRoom;
            foundEmployees = employees;
            break;
        }
    }
    file.close();

    if (foundRoom.empty()) {
        cout << "Phone number not found.\n"; // Телефон не знайдено
    }
    else {
        cout << "Room: " << foundRoom << "\nEmployees: " << foundEmployees << endl; // Приміщення: ... Службовці: ...
    }
}

// Функція для пошуку за номером приміщення
void searchByRoom(const string& filename, const string& room) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // Не вдалося відкрити файл для читання
        return;
    }

    string line, foundPhone;
    while (getline(file, line)) {
        stringstream ss(line);
        string currentPhone, currentRoom;
        ss >> currentPhone >> currentRoom;
        if (currentRoom == room) {
            foundPhone = currentPhone;
            break;
        }
    }
    file.close();

    if (foundPhone.empty()) {
        cout << "Room not found.\n"; // Приміщення не знайдено
    }
    else {
        cout << "Phone number: " << foundPhone << endl; // Номер телефону: ...
    }
}

// Функція для пошуку за прізвищем службовця
void searchByEmployee(const string& filename, const string& employee) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // Не вдалося відкрити файл для читання
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string phone, room, employees;
        ss >> phone >> room;
        getline(ss, employees);

        if (employees.find(employee) != string::npos) {
            cout << "Phone: " << phone << "\nRoom: " << room << endl; // Телефон: ... Приміщення: ...
            file.close();
            return;
        }
    }
    file.close();
    cout << "Employee not found.\n"; // Службовця не знайдено
}

// Меню програми
void menu() {
    string filename;
    cout << "Enter the filename: "; // Введіть ім'я файлу
    cin >> filename;

    int choice;
    do {
        cout << "\nMenu:\n"
            << "1. Create database\n" // Створити базу
            << "2. View database\n"   // Переглянути базу
            << "3. Add record\n"      // Додати запис
            << "4. Search by phone number\n" // Пошук за номером телефону
            << "5. Search by room number\n"  // Пошук за номером приміщення
            << "6. Search by employee name\n" // Пошук за прізвищем службовця
            << "0. Exit\n"            // Вихід
            << "Your choice: ";       // Ваш вибір
        cin >> choice;

        switch (choice) {
        case 1: createDatabase(filename); break;
        case 2: viewDatabase(filename); break;
        case 3: addRecord(filename); break;
        case 4: {
            string phone;
            cout << "Enter phone number: "; // Введіть номер телефону
            cin >> phone;
            searchByPhone(filename, phone);
            break;
        }
        case 5: {
            string room;
            cout << "Enter room number: "; // Введіть номер приміщення
            cin >> room;
            searchByRoom(filename, room);
            break;
        }
        case 6: {
            string employee;
            cout << "Enter employee name: "; // Введіть прізвище службовця
            cin >> employee;
            searchByEmployee(filename, employee);
            break;
        }
        case 0: cout << "Exiting.\n"; break; // Вихід
        default: cout << "Invalid choice.\n"; // Неправильний вибір
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
