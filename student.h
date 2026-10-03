#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#endif // STUDENT_H
using namespace std;

class Student {
private:
    string name;
    int number;
    float midterm, secondterm, final, task;
    int devamsizlik;
    static const int MAX_STUDENTS = 1000;
    static Student students[MAX_STUDENTS];
    static int studentCount;

public:
    Student();
    ~Student();

    void readFromCsv();
    void writeToCsv();
    void displayInfo() const;
    void displayAllStudents() const;
    void displayPassed() const;
    void displayFailed() const;
    void filterStudent() const;
    void findStudentbyName(const string& name) const;
    void findStudentbyNumber(int number) const;
    void updateStudent(int id);
    void deleteStudent(int id);
    float average() const;
    static void print(int filter, const string& fileName = "");
};

Student Student::students[MAX_STUDENTS];  // Öğrencileri tutacak array

int Student::studentCount = 0;

// Constructor
Student::Student() : name(""), number(0), midterm(0), secondterm(0), final(0), task(0), devamsizlik(0) {}

// Destructor
Student::~Student() {}

float Student::average() const {
    return (midterm * 0.20f + secondterm * 0.20f + task * 0.20f + final * 0.40f);
}

void Student::displayInfo() const {
    cout << "-----------------------------" << endl;
    cout << "İsim: " << name << endl;
    cout << "Numara: " << number << endl;
    cout << "Ara Sınav: " << midterm << endl;
    cout << "2. Sınav: " << secondterm << endl;
    cout << "Final: " << final << endl;
    cout << "Ödev: " << task << endl;
    cout << "Devamsızlık: " << devamsizlik << endl;
    cout << "Ortalama: " << fixed << setprecision(2) << average() << endl;
    cout << "Durum: " << (average() >= 50 ? "Geçti" : "Kaldı") << endl;
    cout << "-----------------------------" << endl;
}

void Student::displayAllStudents() const {
    if (studentCount == 0) {
        cout << "Ogrenci bulunmuyor!" << endl;
        return;
    }
    for (int i = 0; i < studentCount; ++i) {
        students[i].displayInfo();
        cout << endl;
    }
}

void Student::displayPassed() const {
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].average() >= 50) {
            students[i].displayInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Gecen ogrenci yok." << endl;
    }
}

void Student::displayFailed() const {
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].average() < 50) {
            students[i].displayInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Kalan ogrenci yok." << endl;
    }
}

void Student::filterStudent() const {
    float mingrade, maxgrade;

    cout << "Minimum not: ";
    cin >> mingrade;
    cout << "Maximum not: ";
    cin >> maxgrade;

    bool found = false;


    for (int i = 0; i < studentCount; ++i) {
        float avg = students[i].average();

        if (avg >= mingrade && avg <= maxgrade) {
            students[i].displayInfo();
            found = true;
        }
    }

    if (!found) {
        cout << "Bu not aralığında öğrenci bulunamadı!" << endl;
    }
}


void Student::findStudentbyName(const string& studentName) const {
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].name == studentName) {
            students[i].displayInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Ogrenci bulunamadi!" << endl;
    }
}

void Student::findStudentbyNumber(int studentID) const {
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].number == studentID) {
            students[i].displayInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Ogrenci bulunamadi!" << endl;
    }
}

void Student::updateStudent(int studentID) {
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].number == studentID) {
            found = true;
            cout << "Yeni ara sinav notunu giriniz: ";
            cin >> students[i].midterm;
            cout << "Yeni 2.sinav notunu giriniz: ";
            cin >> students[i].secondterm;
            cout << "Yeni final notunu giriniz: ";
            cin >> students[i].final;
            cout << "Yeni odev notunu giriniz: ";
            cin >> students[i].task;
            cout << "Bilgiler güncellendi." << endl;
            break;
        }
    }
    if (!found) {
        cout << "Ogrenci bulunamadi!" << endl;
    }

    // Dosyayı güncelle
    ofstream file("/home/kaan/ogrenci.csv", ios::trunc);
    if (!file.is_open()) {
        cerr << "Dosya açılamadı!" << endl;
        return;
    }

    for (int i = 0; i < studentCount; ++i) {
        file << students[i].name << "," << students[i].number << ","
            << students[i].midterm << "," << students[i].secondterm << ","
            << students[i].final << "," << students[i].task << ","
            << students[i].devamsizlik << endl;
    }
    file.close();
}

void Student::deleteStudent(int studentID) {
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].number == studentID) {
            found = true;
            // Öğrenciyi diziden silme
            for (int j = i; j < studentCount - 1; ++j) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Öğrenci başarıyla silindi." << endl;
            break;
        }
    }

    if (!found) {
        cout << "Ogrenci bulunamadi!" << endl;
    }

    // Dosyayı güncelle
    ofstream file("/home/kaan/ogrenci.csv", ios::trunc);
    if (!file.is_open()) {
        cerr << "Dosya açılamadı!" << endl;
        return;
    }

    for (int i = 0; i < studentCount; ++i) {
        file << students[i].name << "," << students[i].number << ","
            << students[i].midterm << "," << students[i].secondterm << ","
            << students[i].final << "," << students[i].task << ","
            << students[i].devamsizlik << endl;
    }
    file.close();
}

void Student::readFromCsv()
{
    ifstream file("student.csv");
    string line;

    if (!file.is_open()) {
        cerr << "Dosya açılamadı!" << endl;
        return;
    }

    studentCount = 0;

    while (getline(file, line) && studentCount < MAX_STUDENTS) {
        stringstream ss(line);
        string nameStr, numberStr, midtermStr, secondtermStr, finalStr, taskStr, devamsizlikStr;

        if (getline(ss, nameStr, ',') &&
            getline(ss, numberStr, ',') &&
            getline(ss, midtermStr, ',') &&
            getline(ss, secondtermStr, ',') &&
            getline(ss, finalStr, ',') &&
            getline(ss, taskStr, ',') &&
            getline(ss, devamsizlikStr, ',')) {


            students[studentCount].name = nameStr;
            students[studentCount].number = stoi(numberStr);
            students[studentCount].midterm = stof(midtermStr);
            students[studentCount].secondterm = stof(secondtermStr);
            students[studentCount].final = stof(finalStr);
            students[studentCount].task = stof(taskStr);
            students[studentCount].devamsizlik = stoi(devamsizlikStr);

            studentCount++;
        }
    }

    file.close();
}



void Student::writeToCsv() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Öğrenci kapasitesine ulaşıldı!" << endl;
        return;
    }

    cout << "Öğrencinin adını giriniz: ";
    cin >> students[studentCount].name;
    cout << "Öğrencinin numarasını giriniz: ";
    cin >> students[studentCount].number;
    cout << "Öğrencinin ara sınav notunu giriniz: ";
    cin >> students[studentCount].midterm;
    cout << "Öğrencinin 2. sınav notunu giriniz: ";
    cin >> students[studentCount].secondterm;
    cout << "Öğrencinin final notunu giriniz: ";
    cin >> students[studentCount].final;
    cout << "Öğrencinin ödev notunu giriniz: ";
    cin >> students[studentCount].task;
    cout << "Öğrencinin devamsızlık bilgisini giriniz: ";
    cin >> students[studentCount].devamsizlik;

    ofstream file("student.csv", ios::app);
    if (!file.is_open()) {
        cerr << "Dosya açılamadı!" << endl;
        return;
    }

    file << students[studentCount].name << "," << students[studentCount].number << ","
        << students[studentCount].midterm << "," << students[studentCount].secondterm << ","
        << students[studentCount].final << "," << students[studentCount].task << ","
        << students[studentCount].devamsizlik << endl;

    studentCount++;
    file.close();
}

void Student::print(int filter, const string& fileName) {
    ostream* output;
    ofstream file;

    if (!fileName.empty()) {
        file.open(fileName);
        if (!file.is_open()) {
            cerr << "Dosya açılamadı!" << endl;
            return;
        }
        output = &file;
    }
    else {
        output = &cout;
    }

    bool found = false;
    for (int i = 0; i < studentCount; ++i) {

        bool printCondition = false;

        if (filter == -1) {
            printCondition = true;
        }
        else if (filter == 0 && students[i].average() < 50) {
            printCondition = true;
        }
        else if (filter == 1 && students[i].average() >= 50) {
            printCondition = true;
        }

        if (printCondition) {
            *output << "-----------------------------" << endl;
            *output << "İsim: " << students[i].name << endl;
            *output << "Numara: " << students[i].number << endl;
            *output << "Ortalama: " << fixed << setprecision(2) << students[i].average() << endl;
            *output << "Durum: " << (students[i].average() >= 50 ? "Geçti" : "Kaldı") << endl;
            *output << "-----------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        *output << "Hiçbir öğrenci bulunamadı!" << endl;
    }

    if (file.is_open()) {
        file.close();
    }
}