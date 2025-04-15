#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include "zmogus.h"

class Student : public Zmogus {
private:
    std::vector<int> nd_balai;
    int egzaminas;

public:
    
    friend std::istream& operator>>(std::istream& ivedimas, Student& s); // ivedimo operatorius
    friend std::ostream& operator<<(std::ostream& isvedimas, const Student& s); // isvedimo operatorius


    // Konstruktoriai
    Student();

    // Rule of five
    Student(const Student& kitas); // copy konstruktorius
    Student& operator=(const Student& kitas); // copy priskirimo operatorius

    //Destruktorius
    ~Student();

    Student(Student&& kitas); // move konstruktorius
    Student& operator=(Student&& kitas); // move priskirimo operatorius
    // Rule of five pabaiga

    // Getteriai
    std::string getVardas() const;
    std::string getPavarde() const;
    std::vector<int> getNdBalai() const;
    int getEgzaminas() const;

    // Setteriai
    void setVardas(const std::string& vardas);
    void setPavarde(const std::string& pavarde);
    void setNdBalai(const std::vector<int>& nd);
    void setEgzaminas(int egzaminas);

    // Kitos funkcijos
    double skaiciuotiVidurki() const;
    double skaiciuotiMediana() const;
    double galutinisPazymys(bool naudotiVidurki = true) const;
};

// Funkcijos generavimui ir įvedimui (naudos viešus metodus)
Student generuotiStudenta();
void generuotiPazymius(Student& studentas);
std::vector<Student> generuotiStudentus(int kiekis);
std::vector<Student> ivestiStudentus();

// Rikiavimo funkcijos (naudojasi getteriais)
bool palygintiPagalVarda(const Student& a, const Student& b);
bool palygintiPagalPavarde(const Student& a, const Student& b);
bool palygintiPagalVidurkiAsc(const Student& a, const Student& b);
bool palygintiPagalVidurkiDesc(const Student& a, const Student& b);
bool palygintiPagalMedianaAsc(const Student& a, const Student& b);
bool palygintiPagalMedianaDesc(const Student& a, const Student& b);
void rikiuotiStudentus(std::vector<Student>& studentai, char pasirinkimas, char tvarka = 'a');
void rikiuotiStudentusPagalPasirinkima(std::vector<Student>& studentai);

#endif
