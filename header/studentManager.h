#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "student.h"
#include <vector>
#include <string>

class StudentManager {
private:
    std::vector<Student> students;
    std::string dbPath;

public:
    StudentManager(const std::string& path);

    bool loadFromFile();
    bool saveToFile() const;

    void addStudent(const Student& student);
    bool deleteStudent(int id);
    bool updateStudent(int id, float newMid, float newSec, float newFin, float newTask);

    const std::vector<Student>& getAllStudents() const;
    std::vector<Student> getPassedStudents() const;
    std::vector<Student> getFailedStudents() const;
    Student const* findStudentById(int id) const;
    std::vector<Student> getStudentsByGradeRange(float minGrade, float maxGrade) const;
};

#endif