#include <QApplication>
#include "Qt/mainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setStyleSheet(
        "QMainWindow { background-color: #f1f8e9; }" 
        
        // Etiketler 
        "QLabel { color: #1b5e20; font-size: 14px; font-weight: 500; }"
        
        // Buton Tasarımı
        "QPushButton {"
        "   background-color: #4caf50;"     // Ana yeşil
        "   color: white;"                  // Yazı rengi
        "   border: none;"
        "   border-radius: 6px;"           
        "   padding: 10px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #43a047; }"
        "QPushButton:pressed { background-color: #2e7d32; }"
        
        // Metin Giriş Kutuları 
        "QLineEdit {"
        "   border: 2px solid #a5d6a7;"
        "   border-radius: 4px;"
        "   padding: 5px;"
        "   background-color: white;"
        "}"
        "QLineEdit:focus { border: 2px solid #4caf50; }"
        
        // Tablo Tasarımı
        "QTableWidget {"
        "   background-color: white;"
        "   alternate-background-color: #e8f5e9;" 
        "   gridline-color: #81c784;"
        "   border: 1px solid #81c784;"
        "   selection-background-color: #81c784;" 
        "   selection-color: black;"
        "}"
        // Tablo Başlıkları
        "QHeaderView::section {"
        "   background-color: #388e3c;"
        "   color: white;"
        "   font-weight: bold;"
        "   padding: 5px;"
        "   border: 1px solid #2e7d32;"
        "}"
    );

    MainWindow window;
    window.show();

    return app.exec();
}