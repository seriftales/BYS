#include "mainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent), manager("../students.csv") {
    
    manager.loadFromFile();

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    setupMenuPage();
    setupListPage();
    setupAddPage();
    setupUpdatePage();

    stackedWidget->addWidget(menuPage);
    stackedWidget->addWidget(listPage);
    stackedWidget->addWidget(addPage);
    stackedWidget->addWidget(updatePage);

    stackedWidget->setCurrentWidget(menuPage);
    resize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenuPage() {
    menuPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(menuPage);

    QLabel *title = new QLabel("ÖĞRENCİ BİLGİ YÖNETİM SİSTEMİ");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 20px;");
    layout->addWidget(title);

    // Menü Butonları
    QPushButton *btn1 = new QPushButton("1. Tüm Öğrencileri Listele");
    QPushButton *btn2 = new QPushButton("2. Geçenleri Listele");
    QPushButton *btn3 = new QPushButton("3. Kalanları Listele");
    QPushButton *btn4 = new QPushButton("4. Öğrenci Ekle");
    QPushButton *btn5 = new QPushButton("5. Öğrenci Sil");
    QPushButton *btn6 = new QPushButton("6. Öğrenci Güncelle");
    QPushButton *btn7 = new QPushButton("7. Not Aralığına Göre Filtrele");
    QPushButton *btn8 = new QPushButton("8. Numaraya Göre Ara");
    QPushButton *btn0 = new QPushButton("0. Çıkış");

    layout->addWidget(btn1); layout->addWidget(btn2); layout->addWidget(btn3);
    layout->addWidget(btn4); layout->addWidget(btn5); layout->addWidget(btn6);
    layout->addWidget(btn7); layout->addWidget(btn8); layout->addWidget(btn0);

    // Butonları iş mantığına (Slotlara) bağlama
    connect(btn1, &QPushButton::clicked, this, &MainWindow::showAllStudents);
    connect(btn2, &QPushButton::clicked, this, &MainWindow::showPassedStudents);
    connect(btn3, &QPushButton::clicked, this, &MainWindow::showFailedStudents);
    connect(btn4, &QPushButton::clicked, this, &MainWindow::goToAddStudent);
    connect(btn5, &QPushButton::clicked, this, &MainWindow::deleteStudentAction);
    connect(btn6, &QPushButton::clicked, this, &MainWindow::goToUpdateStudent);
    connect(btn7, &QPushButton::clicked, this, &MainWindow::filterStudentsAction);
    connect(btn8, &QPushButton::clicked, this, &MainWindow::searchStudentAction);
    connect(btn0, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::setupListPage() {
    listPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(listPage);

    studentTable = new QTableWidget(0, 4);
    studentTable->setHorizontalHeaderLabels({"İsim", "Numara", "Ortalama", "Durum"});
    studentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *btnBack = new QPushButton("Ana Menüye Dön");
    layout->addWidget(studentTable);
    layout->addWidget(btnBack);

    connect(btnBack, &QPushButton::clicked, this, &MainWindow::goToMainMenu);
}

void MainWindow::setupAddPage() {
    addPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(addPage);
    QFormLayout *formLayout = new QFormLayout(); 
    addName = new QLineEdit(); addId = new QLineEdit();
    addV1 = new QLineEdit(); addV2 = new QLineEdit();
    addFin = new QLineEdit(); addOdev = new QLineEdit();
    addDevam = new QLineEdit();

    formLayout->addRow("Ad Soyad:", addName);
    formLayout->addRow("Numara:", addId);
    formLayout->addRow("Vize 1:", addV1);
    formLayout->addRow("Vize 2:", addV2);
    formLayout->addRow("Final:", addFin);
    formLayout->addRow("Ödev:", addOdev);
    formLayout->addRow("Devamsızlık:", addDevam);

    QPushButton *btnSave = new QPushButton("Kaydet");
    QPushButton *btnBack = new QPushButton("İptal");

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(btnSave);
    mainLayout->addWidget(btnBack);

    connect(btnSave, &QPushButton::clicked, this, &MainWindow::saveNewStudent);
    connect(btnBack, &QPushButton::clicked, this, &MainWindow::goToMainMenu);
}

void MainWindow::setupUpdatePage() {
    updatePage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(updatePage);
    QFormLayout *formLayout = new QFormLayout();

    updId = new QLineEdit(); updV1 = new QLineEdit();
    updV2 = new QLineEdit(); updFin = new QLineEdit();
    updOdev = new QLineEdit();

    formLayout->addRow("Güncellenecek Numara:", updId);
    formLayout->addRow("Yeni Vize 1:", updV1);
    formLayout->addRow("Yeni Vize 2:", updV2);
    formLayout->addRow("Yeni Final:", updFin);
    formLayout->addRow("Yeni Ödev:", updOdev);

    QPushButton *btnUpdate = new QPushButton("Güncelle");
    QPushButton *btnBack = new QPushButton("İptal");

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(btnUpdate);
    mainLayout->addWidget(btnBack);

    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::updateStudentAction);
    connect(btnBack, &QPushButton::clicked, this, &MainWindow::goToMainMenu);
}

void MainWindow::populateTable(const std::vector<Student>& list) {
    studentTable->setRowCount(list.size());
    for (size_t i = 0; i < list.size(); ++i) {
        studentTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(list[i].getName())));
        studentTable->setItem(i, 1, new QTableWidgetItem(QString::number(list[i].getId())));
        studentTable->setItem(i, 2, new QTableWidgetItem(QString::number(list[i].calculateAverage(), 'f', 2)));
        studentTable->setItem(i, 3, new QTableWidgetItem(list[i].isPassed() ? "Geçti" : "Kaldı"));
    }
    stackedWidget->setCurrentWidget(listPage);
}

// --- İŞ MANTIĞI VE BUTON SLOTLARI ---

void MainWindow::goToMainMenu() { stackedWidget->setCurrentWidget(menuPage); }
void MainWindow::goToAddStudent() { stackedWidget->setCurrentWidget(addPage); }
void MainWindow::goToUpdateStudent() { stackedWidget->setCurrentWidget(updatePage); }

void MainWindow::showAllStudents() { populateTable(manager.getAllStudents()); }
void MainWindow::showPassedStudents() { populateTable(manager.getPassedStudents()); }
void MainWindow::showFailedStudents() { populateTable(manager.getFailedStudents()); }

void MainWindow::saveNewStudent() {
    std::string name = addName->text().toStdString();
    int id = addId->text().toInt();
    float v1 = addV1->text().toFloat();
    float v2 = addV2->text().toFloat();
    float fin = addFin->text().toFloat();
    float odev = addOdev->text().toFloat();
    int devam = addDevam->text().toInt();

    manager.addStudent(Student(id, name, v1, v2, fin, odev, devam));
    QMessageBox::information(this, "Başarılı", "Öğrenci eklendi.");
    goToMainMenu();
}

void MainWindow::deleteStudentAction() {
    bool ok;
    int id = QInputDialog::getInt(this, "Öğrenci Sil", "Silinecek numarayı giriniz:", 0, 0, 9999999, 1, &ok);
    if (ok) {
        if (manager.deleteStudent(id)) {
            QMessageBox::information(this, "Başarılı", "Öğrenci silindi.");
        } else {
            QMessageBox::warning(this, "Hata", "Öğrenci bulunamadı.");
        }
    }
}

void MainWindow::updateStudentAction() {
    int id = updId->text().toInt();
    if (manager.findStudentById(id) != nullptr) {
        float v1 = updV1->text().toFloat();
        float v2 = updV2->text().toFloat();
        float fin = updFin->text().toFloat();
        float odev = updOdev->text().toFloat();
        
        manager.updateStudent(id, v1, v2, fin, odev);
        QMessageBox::information(this, "Başarılı", "Notlar güncellendi.");
        goToMainMenu();
    } else {
        QMessageBox::warning(this, "Hata", "Bu numarada bir öğrenci yok.");
    }
}

void MainWindow::filterStudentsAction() {
    bool ok1, ok2;
    float minNot = QInputDialog::getDouble(this, "Filtre", "Minimum Not:", 0, 0, 100, 2, &ok1);
    if (!ok1) return;
    
    float maxNot = QInputDialog::getDouble(this, "Filtre", "Maksimum Not:", 100, 0, 100, 2, &ok2);
    if (!ok2) return;

    populateTable(manager.getStudentsByGradeRange(minNot, maxNot));
}

void MainWindow::searchStudentAction() {
    bool ok;
    int id = QInputDialog::getInt(this, "Öğrenci Ara", "Aranacak numarayı giriniz:", 0, 0, 9999999, 1, &ok);
    if (ok) {
        const Student* s = manager.findStudentById(id);
        if (s != nullptr) {
            QString info = QString("İsim: %1\nNumara: %2\nOrtalama: %3\nDurum: %4")
                           .arg(QString::fromStdString(s->getName()))
                           .arg(s->getId())
                           .arg(s->calculateAverage())
                           .arg(s->isPassed() ? "Geçti" : "Kaldı");
            QMessageBox::information(this, "Bulundu", info);
        } else {
            QMessageBox::warning(this, "Hata", "Öğrenci bulunamadı.");
        }
    }
}