#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <algorithm>

class Student {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd_balai;
    int egzaminas;

public:
    // Constructors
    Student();
    Student(const std::string& vardas, const std::string& pavarde, const std::vector<int>& nd_balai, int egzaminas);
    Student(const Student& other); // Copy constructor
    Student(Student&& other) noexcept; // Move constructor

    // Destructor
    ~Student();

    // Getters
    std::string getVardas() const;
    std::string getPavarde() const;
    std::vector<int> getNdBalai() const;
    int getEgzaminas() const;

    // Setters
    void setVardas(const std::string& vardas);
    void setPavarde(const std::string& pavarde);
    void setNdBalai(const std::vector<int>& nd_balai);
    void setEgzaminas(int egzaminas);

    // Utility functions
    double skaiciuotiVidurki() const;
    double skaiciuotiMediana() const;
    double galutinisPazymys(bool naudotiVidurki = true) const;

    // Static functions for sorting
    static bool palygintiPagalVarda(const Student& a, const Student& b);
    static bool palygintiPagalPavarde(const Student& a, const Student& b);
    static bool palygintiPagalVidurkiAsc(const Student& a, const Student& b);
    static bool palygintiPagalVidurkiDesc(const Student& a, const Student& b);
    static bool palygintiPagalMedianaAsc(const Student& a, const Student& b);
    static bool palygintiPagalMedianaDesc(const Student& a, const Student& b);
};

// Functions for generating and managing students
Student generuotiStudenta();
void generuotiPazymius(Student& studentas);
std::vector<Student> generuotiStudentus(int kiekis);
std::vector<Student> ivestiStudentus();

// Sorting functions
void rikiuotiStudentus(std::vector<Student>& studentai, char pasirinkimas, char tvarka = 'a');
void rikiuotiStudentusPagalPasirinkima(std::vector<Student>& studentai);

#endif