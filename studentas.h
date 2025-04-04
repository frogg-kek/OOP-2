#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

class Student {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd_balai;
    int egzaminas;

public:
    // Konstruktoriai
    Student();
    Student(const std::string& vardas, const std::string& pavarde, const std::vector<int>& nd, int egzaminas);

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
