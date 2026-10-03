cmake_minimum_required(VERSION 3.10)

# Projenin adı
project(OgrenciSistemi)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++17 standardını zorunlu kıl
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt'nin sinyal/slot ve arayüz dosyalarını C++'a çeviren motorları aktif et
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Sistemdeki Qt5 Widgets kütüphanesini bul
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Derlenecek dosyaları belirle (Yolları kendi hiyerarşine göre yazdım)
add_executable(OgrenciSistemi
    main.cpp
    Qt/mainWindow.cpp
    source/student.cpp
    source/studentManager.cpp
)

# Qt5 kütüphanelerini bizim projemize bağla (Linker)
target_link_libraries(OgrenciSistemi Qt5::Widgets)

# Header dosyalarının nerede olduğunu derleyiciye söyle (-I komutunun CMake karşılığı)
target_include_directories(OgrenciSistemi PRIVATE ${CMAKE_SOURCE_DIR}/header)
