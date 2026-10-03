#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// Öğrenci Sınıfı (Veri Modeli)
class Student {
private:
    int id;
    std::string name;
    float midtermScore, secondTermScore, finalScore, taskScore;
    int absences;

    static constexpr float MIDTERM_WEIGHT = 0.20f;
    static constexpr float SECOND_WEIGHT = 0.20f;
    static constexpr float TASK_WEIGHT = 0.20f;
    static constexpr float FINAL_WEIGHT = 0.40f;

public:
    Student(int id, const std::string& name, float mid, float sec, float fin, float task, int abs);

    int getId() const;
    std::string getName() const;
    float getMidterm() const;
    float getSecond() const;
    float getFinal() const;
    float getTask() const;
    int getAbsences() const;

    float calculateAverage() const;
    bool isPassed() const;
    std::string toCsvLine() const;
};

#endif