#include <iostream>
#include <iomanip>
#include  "header/studentManager.h"

using namespace std;

void printStudent(const Student& s) {
    cout << "-----------------------------\n";
    cout << "İsim: " << s.getName() << "\n";
    cout << "Numara: " << s.getId() << "\n";
    cout << "Ortalama: " << fixed << setprecision(2) << s.calculateAverage() << "\n";
    cout << "Durum: " << (s.isPassed() ? "Geçti" : "Kaldı") << "\n";
    cout << "-----------------------------\n";
}

void printStudentList(const vector<Student>& list) {
    if (list.empty()) {
        cout << "Kayit bulunamadi.\n";
        return;
    }
    for (const auto& s : list) {
        printStudent(s);
    }
}

int main() {
    StudentManager manager("students.csv");
    manager.loadFromFile();

    int secim;
    do {
        cout << "\n1. Tum Ogrencileri Listele\n"
             << "2. Gecenleri Listele\n"
             << "3. Kalanlari Listele\n"
             << "4. Ogrenci Ekle\n"
             << "5. Ogrenci Sil\n"
             << "6. Öğrenci Güncelle\n"
             << "7. Filtrele\n"
                << "8. Numaraya Gore Filtrele\n"
             << "0. Cikis\n"
             << "Secim: ";
        cin >> secim;

        if (secim == 1) {
            printStudentList(manager.getAllStudents());
        } 
        else if (secim == 2) {
            printStudentList(manager.getPassedStudents());
        } 
        else if (secim == 3) {
            printStudentList(manager.getFailedStudents());
        } 
        else if (secim == 4) {
            string ad; int id, devamsizlik;
            float v1, v2, fin, odev;
            cout << "Ad: "; cin >> ad;
            cout << "Numara: "; cin >> id;
            cout << "Vize 1: "; cin >> v1;
            cout << "Vize 2: "; cin >> v2;
            cout << "Final: "; cin >> fin;
            cout << "Odev: "; cin >> odev;
            cout << "Devamsizlik: "; cin >> devamsizlik;

            manager.addStudent(Student(id, ad, v1, v2, fin, odev, devamsizlik));
            cout << "Eklendi.\n";
        }
        else if (secim == 5) {
            int id;
            cout << "Silinecek Numara: "; cin >> id;
            if (manager.deleteStudent(id)) {
                cout << "Silindi.\n";
            } else {
                cout << "Ogrenci bulunamadi.\n";
            }
         }
    
        else if (secim == 7) {
            float minNot, maxNot;
            cout << "Minimum notu giriniz: "; 
            cin >> minNot;
            cout << "Maksimum notu giriniz: "; 
            cin >> maxNot;

            vector<Student> filtrelenmisListe = manager.getStudentsByGradeRange(minNot, maxNot);
            printStudentList(filtrelenmisListe);
        }
    
        else if (secim == 6) {
            int id;
            float yeniVize1, yeniVize2, yeniFinal, yeniOdev;
            cout << "Guncellenecek ogrencinin numarasi: "; 
            cin >> id;
    
            if (manager.findStudentById(id) != nullptr) {
                cout << "Yeni Vize 1: "; cin >> yeniVize1;
                cout << "Yeni Vize 2: "; cin >> yeniVize2;
                cout << "Yeni Final: "; cin >> yeniFinal;
                cout << "Yeni Odev: "; cin >> yeniOdev;

            if (manager.updateStudent(id, yeniVize1, yeniVize2, yeniFinal, yeniOdev)) {
                cout << "Ogrenci basariyla guncellendi.\n";
            }
            } else {
                 cout << "Bu numaraya ait ogrenci bulunamadi!\n";
            }
        }

        else if (secim == 8) {
            int arananId;
            cout << "Aradiginiz ogrencinin numarasini giriniz: ";
            cin >> arananId;

            const Student* bulunanOgrenci = manager.findStudentById(arananId);

            if (bulunanOgrenci != nullptr) {
                printStudent(*bulunanOgrenci);
            } else {
                cout << "Bu numaraya ait bir ogrenci kayitlarda bulunamadi!\n";
            }
        }
    
    
        } while (secim != 0);

    return 0;
}