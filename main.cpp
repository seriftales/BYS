
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "student.h"
using namespace std;


int main() {
    Student student;
    int secim;
    char devam;

    student.readFromCsv();

    do {

        cout << "******************************************************" << endl;
        cout << "*    OGRENCI BiLGİ YONETİM SISTEMINE  HOSGELDINIZ    *" << endl;
        cout << "******************************************************" << endl;
        cout << "Lutfen Yapmak Istediginiz Islemi Seciniz:" << endl;
        cout << "------------------------------------------" << endl;
        cout <<"1.Tum Ogrencileri Listele" << endl;
        cout <<"2.Kalan Ogrencileri Listele" << endl;
        cout <<"3.Gecen Ogrencileri Listele" << endl;
        cout <<"4.Verilen Filtreyle Ogrencileri Dosyaya Yazdir" << endl;
        cout <<"5.Adi Girilen Ogrenci veya Ogrencilerin Bilgilerini Listele"<<endl;
        cout <<"6.Numarasi Girilen Ogrencinin Bilgilerini Listele"<<endl;
        cout <<"7.Belirli Bir Not Araligindaki Ogrencileri Listele"<<endl;
        cout <<"8.Yeni Ogrenci Ekle"<<endl;
        cout <<"9.Ogrenci Bilgisi Guncelle"<<endl;
        cout <<"10.Ogrenci Sil"<<endl;
        cout <<"0.Cikis" << endl;
        cout << "Seciminizi giriniz (0-10): ";
        cin >> secim;

        string dosyaAdi;
        string studentName;
        int studentID;

        switch (secim) {
        case 1:
            student.displayAllStudents();
            break;

        case 2:
            student.displayFailed();
            break;

        case 3:
            student.displayPassed();
            break;

        case 4:
            int filter;
            cout << "Filtreyi giriniz (-1: Tum Ogrenciler, 0: Kalanlar, 1: Gecenler): ";
            cin >> filter;

            cout << "Dosya adini giriniz (ornek: output.txt): ";
            cin >> dosyaAdi;

            Student::print(filter, dosyaAdi);
            cout << "Ogrenciler dosyaya yazildi: " << dosyaAdi << endl;
            break ;

            case 5 :
                cout<<"\nAramak istediginiz ogrencinin adini giriniz:";
                cin>>studentName;

                student.findStudentbyName(studentName);
                break ;
            case 6 :
                cout<<"\nAramak istediginiz ogrencinin numarasini giriniz:";
                cin>>studentID;
                student.findStudentbyNumber(studentID);
                break ;

            case 7:
                cout<<"Araligi giriniz!"<<endl ;
                student.filterStudent();
                break ;

            case 8 :
                student.writeToCsv();
                cout<<"Ogrenci bilgisi dosyaya eklendi."<<endl;
                break ;

            case 9:
                cout << "Guncellemek istediginiz ogrencinin numarasini giriniz: ";
                cin >> studentID;
                student.updateStudent(studentID);
                break;

            case 10:
                cout << "Silmek istediginiz ogrencinin numarasini giriniz: ";
                cin >> studentID;
                student.deleteStudent(studentID);
                break;

            case 0:
                cout<<"Programdan cikiliyor..."<<endl;
                return 0 ;


            default:
            cout << "Gecersiz secim, tekrar deneyin." << endl;
        }

        cout << "Devam etmek istiyor musunuz? (E/e): ";
        cin >> devam;

    } while (devam == 'E' || devam == 'e');

    cout << "Programdan cikiliyor..." << endl;
    return 0;
}