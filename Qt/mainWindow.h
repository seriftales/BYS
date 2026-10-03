#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include "studentManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Yönlendirme ve Sayfa Geçişleri
    void goToMainMenu();
    void goToAddStudent();
    void goToUpdateStudent();

    void showAllStudents();      // 1
    void showPassedStudents();   // 2
    void showFailedStudents();   // 3
    void saveNewStudent();       // 4
    void deleteStudentAction();  // 5
    void updateStudentAction();  // 6
    void filterStudentsAction(); // 7
    void searchStudentAction();  // 8

private:
    StudentManager manager;
    QStackedWidget *stackedWidget;
    
    // Sayfalar
    QWidget *menuPage;
    QWidget *listPage;
    QWidget *addPage;
    QWidget *updatePage;

    // Ortak Tablo
    QTableWidget *studentTable;
    
    // Ekleme Formu Elemanları
    QLineEdit *addName, *addId, *addV1, *addV2, *addFin, *addOdev, *addDevam;
    
    // Güncelleme Formu Elemanları
    QLineEdit *updId, *updV1, *updV2, *updFin, *updOdev;

    // Kurulum ve Yardımcı Fonksiyonlar
    void setupMenuPage();
    void setupListPage();
    void setupAddPage();
    void setupUpdatePage();
    void populateTable(const std::vector<Student>& list); 
};

#endif