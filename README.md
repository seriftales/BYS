# Öğrenci Bilgi Yönetim Sistemi 
Bu proje,  C++ Nesne Yönelimli Programlama ve Katmanlı Mimari prensipleri kullanılarak oluşturulmuştur 

Tek Sorumluluk Prensibi : Veri modeli  ve iş mantığı/veritabanı işlemleri tamamen birbirinden izole edilmiştir.

Dinamik Bellek Yönetimi: Sabit boyutlu C dizileri yerine std::vector kullanılarak bellek taşması riskleri önlenmiştir..


## 🚀 Özellikler
Öğrenci Ekleme, Silme ve Güncelleme 

Numaraya göre hızlı arama

Başarı durumuna ve Not aralığına göre dinamik filtreleme

Verilerin students.csv dosyasına kalıcı olarak kaydedilmesi 

Etkileşimli tablolar ve QSS ile özelleştirilmiş Material Design yeşil tema.

## 🛠️ Kurulum ve Bağımlılıklar (Linux / Ubuntu)
Projeyi derleyebilmek için sisteminizde C++ derleme araçlarının ve Qt5 kütüphanelerinin kurulu olması gerekmektedir. Terminali açıp aşağıdaki komutu çalıştırın:

``` bash 
sudo apt update
sudo apt install build-essential cmake qtbase5-dev qt5-qmake

```

## ⚙️ Derleme ve Çalıştırma 
Projenin ana dizininde sırasıyla şu komutları çalıştırın:

 1.Derleme klasörünü oluşturun ve içine girin:
``` bash 
mkdir build
cd build

```
 2.CMake ile Makefile haritasını oluşturun:

``` bash 
cmake ..

```
3.Projeyi derleyin:

``` bash 
make

```

4.Uygulamayı başlatın:

``` bash 

./OgrenciSistemi

```
## 📁 Proje Dizin Yapısı

```text 
.
├── CMakeLists.txt        # Proje derleme ve linking kuralları
├── main.cpp              # Uygulama giriş noktası 
├── header/               # Sınıf bildirimleri 
│   ├── student.h
│   ├── studentmanager.h
├── source/               # Sınıf tanımlamaları 
│   ├── student.cpp
│   ├── studentmanager.cpp
└── qt/                   # Arayüz Katmanı
    ├── mainwindow.h
    ├── mainwindow.cpp

``` 
