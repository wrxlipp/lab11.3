#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ������� ��� ��������� ���� �����
void createDatabase(const string& filename) {
    ofstream file(filename, ios::trunc); // ³�������� ���� ��� ������
    if (!file.is_open()) {
        cerr << "Failed to open the file for writing.\n"; // �� ������� ������� ���� ��� ������
        return;
    }
    cout << "Database created.\n"; // ���� ����� ��������
    file.close();
}

// ������� ��� ��������� ���� �����
void viewDatabase(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // �� ������� ������� ���� ��� �������
        return;
    }

    string line;
    cout << "Database contents:\n"; // ���� ���� �����
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// ������� ��� ��������� ������
void addRecord(const string& filename) {
    ofstream file(filename, ios::app); // ³�������� ���� ��� ���������
    if (!file.is_open()) {
        cerr << "Failed to open the file for writing.\n"; // �� ������� ������� ���� ��� ������
        return;
    }

    string phone, room, employees;
    cout << "Enter phone number (two digits): "; // ������ ����� �������� (����������)
    cin >> phone;
    if (phone.length() != 2 || !isdigit(phone[0]) || !isdigit(phone[1])) {
        cerr << "Invalid phone number format.\n"; // ������������ ������ ������ ��������
        return;
    }

    cout << "Enter room number: "; // ������ ����� ���������
    cin >> room;

    cin.ignore(); // ������� �����
    cout << "Enter list of employees (1 to 4 names): "; // ������ ������ ���������� (�� 1 �� 4 ������)
    getline(cin, employees);

    // �������� ������� ����������
    stringstream ss(employees);
    string word;
    int count = 0;
    while (ss >> word) count++;

    if (count < 1 || count > 4) {
        cerr << "The number of employees must be between 1 and 4.\n"; // ʳ������ ���������� �� ���� �� 1 �� 4
        return;
    }

    file << phone << " " << room << " " << employees << endl;
    cout << "Record added to the database.\n"; // ����� ������ �� ����
    file.close();
}

// ������� ��� ������ �� ������� ��������
void searchByPhone(const string& filename, const string& phone) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // �� ������� ������� ���� ��� �������
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
        cout << "Phone number not found.\n"; // ������� �� ��������
    }
    else {
        cout << "Room: " << foundRoom << "\nEmployees: " << foundEmployees << endl; // ���������: ... ���������: ...
    }
}

// ������� ��� ������ �� ������� ���������
void searchByRoom(const string& filename, const string& room) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // �� ������� ������� ���� ��� �������
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
        cout << "Room not found.\n"; // ��������� �� ��������
    }
    else {
        cout << "Phone number: " << foundPhone << endl; // ����� ��������: ...
    }
}

// ������� ��� ������ �� �������� ���������
void searchByEmployee(const string& filename, const string& employee) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file for reading.\n"; // �� ������� ������� ���� ��� �������
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string phone, room, employees;
        ss >> phone >> room;
        getline(ss, employees);

        if (employees.find(employee) != string::npos) {
            cout << "Phone: " << phone << "\nRoom: " << room << endl; // �������: ... ���������: ...
            file.close();
            return;
        }
    }
    file.close();
    cout << "Employee not found.\n"; // ��������� �� ��������
}

// ���� ��������
void menu() {
    string filename;
    cout << "Enter the filename: "; // ������ ��'� �����
    cin >> filename;

    int choice;
    do {
        cout << "\nMenu:\n"
            << "1. Create database\n" // �������� ����
            << "2. View database\n"   // ����������� ����
            << "3. Add record\n"      // ������ �����
            << "4. Search by phone number\n" // ����� �� ������� ��������
            << "5. Search by room number\n"  // ����� �� ������� ���������
            << "6. Search by employee name\n" // ����� �� �������� ���������
            << "0. Exit\n"            // �����
            << "Your choice: ";       // ��� ����
        cin >> choice;

        switch (choice) {
        case 1: createDatabase(filename); break;
        case 2: viewDatabase(filename); break;
        case 3: addRecord(filename); break;
        case 4: {
            string phone;
            cout << "Enter phone number: "; // ������ ����� ��������
            cin >> phone;
            searchByPhone(filename, phone);
            break;
        }
        case 5: {
            string room;
            cout << "Enter room number: "; // ������ ����� ���������
            cin >> room;
            searchByRoom(filename, room);
            break;
        }
        case 6: {
            string employee;
            cout << "Enter employee name: "; // ������ ������� ���������
            cin >> employee;
            searchByEmployee(filename, employee);
            break;
        }
        case 0: cout << "Exiting.\n"; break; // �����
        default: cout << "Invalid choice.\n"; // ������������ ����
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
