#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int id;
    char name[50];
    char department[30];
    float cgpa;
};

void mainMenu();
void addStudent();
void listStudents();
void searchStudent();
void deleteStudent();

Student student;
fstream file;

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;

    cout << "\n\n\t ___Student Management System___";
    cout << "\n\n\t 1. Add Student";
    cout << "\n\t 2. List Students";
    cout << "\n\t 3. Search Student";
    cout << "\n\t 4. Delete Student";
    cout << "\n\t 5. Exit";
    cout << "\n\n\tEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            listStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            exit(0);
        default:
            cout << "\nInvalid choice. Try again.\n";
            mainMenu();
    }
}

void addStudent() {
    file.open("students.dat", ios::app | ios::binary);

    cout << "\n\n\tEnter Student ID: ";
    cin >> student.id;
    cout << "\tEnter Name: ";
    cin.ignore();
    cin.getline(student.name, 50);
    cout << "\tEnter Department: ";
    cin.getline(student.department, 30);
    cout << "\tEnter CGPA: ";
    cin >> student.cgpa;

    file.write(reinterpret_cast<char*>(&student), sizeof(student));
    file.close();

    cout << "\nStudent added successfully!";
    mainMenu();
}

void listStudents() {
    file.open("students.dat", ios::in | ios::binary);

    if (!file) {
        cout << "\nNo records found!";
    } else {
        cout << "\n\n\tID\tName\t\tDepartment\tCGPA\n";
        cout << "\t-------------------------------------------\n";
        while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
            cout << "\t" << student.id << "\t" << student.name << "\t" << student.department << "\t" << student.cgpa << "\n";
        }
    }
    file.close();

    mainMenu();
}

void searchStudent() {
    int id, found = 0;

    cout << "\n\n\tEnter Student ID to Search: ";
    cin >> id;

    file.open("students.dat", ios::in | ios::binary);

    while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.id == id) {
            cout << "\n\tStudent Found:";
            cout << "\n\tID: " << student.id;
            cout << "\n\tName: " << student.name;
            cout << "\n\tDepartment: " << student.department;
            cout << "\n\tGPA: " << student.cgpa << "\n";
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "\n\tStudent not found!";
    }
    file.close();

    mainMenu();
}

void deleteStudent() {
    int id, found = 0;

    cout << "\n\n\tEnter Student ID to Delete: ";
    cin >> id;

    fstream tempFile;
    file.open("students.dat", ios::in | ios::binary);
    tempFile.open("temp.dat", ios::out | ios::binary);

    while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.id == id) {
            found = 1;
            cout << "\n\tDeleting student record...";
        } else {
            tempFile.write(reinterpret_cast<char*>(&student), sizeof(student));
        }
    }

    file.close();
    tempFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        cout << "\n\tStudent deleted successfully!";
    } else {
        cout << "\n\tStudent not found!";
    }

    mainMenu();
}
