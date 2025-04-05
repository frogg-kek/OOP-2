#include "studentas.h"
#include "papild.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <random>
#include <limits>

// Konstruktoriai
Student::Student() : vardas(""), pavarde(""), nd_balai{}, egzaminas(0) {}

Student::Student(const std::string& vardas, const std::string& pavarde, const std::vector<int>& nd, int egzaminas)
    : vardas(vardas), pavarde(pavarde), nd_balai(nd), egzaminas(egzaminas) {}

// Destruktorius
Student::~Student() {
    // Jei norėtum debug'int, kada studentas sunaikinamas:
    std::cout << "Studentas sunaikintas: " << vardas << " " << pavarde << std::endl;
}

// Getteriai
std::string Student::getVardas() const { return vardas; }
std::string Student::getPavarde() const { return pavarde; }
std::vector<int> Student::getNdBalai() const { return nd_balai; }
int Student::getEgzaminas() const { return egzaminas; }

// Setteriai
void Student::setVardas(const std::string& v) { vardas = v; }
void Student::setPavarde(const std::string& p) { pavarde = p; }
void Student::setNdBalai(const std::vector<int>& nd) { nd_balai = nd; }
void Student::setEgzaminas(int e) { egzaminas = e; }

// Skaičiavimo metodai
double Student::skaiciuotiVidurki() const {
    if (nd_balai.empty()) return 0.0;
    return static_cast<double>(std::accumulate(nd_balai.begin(), nd_balai.end(), 0)) / nd_balai.size();
}

double Student::skaiciuotiMediana() const {
    if (nd_balai.empty()) return 0.0;
    std::vector<int> kopija = nd_balai;
    std::sort(kopija.begin(), kopija.end());
    size_t dydis = kopija.size();
    return (dydis % 2 == 0) ? (kopija[dydis/2 - 1] + kopija[dydis/2]) / 2.0 : kopija[dydis/2];
}

double Student::galutinisPazymys(bool naudotiVidurki) const {
    double ndRez = naudotiVidurki ? skaiciuotiVidurki() : skaiciuotiMediana();
    return 0.4 * ndRez + 0.6 * egzaminas;
}

// --- Pagalbinės funkcijos ---

Student generuotiStudenta() {
    Student s;
    std::string vardai[] = {"Jonas", "Petras", "Ona", "Ieva", "Marius"};
    std::string pavardes[] = {"Jonaitis", "Petraitis", "Onaitė", "Ievaitė", "Maraitis"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4);

    s.setVardas(vardai[dist(gen)]);
    s.setPavarde(pavardes[dist(gen)]);
    return s;
}

void generuotiPazymius(Student& s) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> paz(0, 10);
    std::uniform_int_distribution<> kiekis(1, 10);

    std::vector<int> balai;
    for (int i = 0; i < kiekis(gen); ++i) {
        balai.push_back(paz(gen));
    }
    s.setNdBalai(balai);
    s.setEgzaminas(paz(gen));
}

std::vector<Student> generuotiStudentus(int kiekis) {
    std::vector<Student> studentai;
    for (int i = 0; i < kiekis; i++) {
        Student s = generuotiStudenta();
        generuotiPazymius(s);
        studentai.push_back(s);
    }
    return studentai;
}

std::vector<Student> ivestiStudentus() {
    std::vector<Student> studentai;
    char pasirinkimas;

    do {
        Student s;
        std::string vardas, pavarde;
        std::vector<int> nd;
        int egz;

        std::cout << "\nĮveskite studento vardą: ";
        std::cin >> vardas;
        while (!tikrintiRaides(vardas)) {
            std::cerr << "Netinkamas vardas. Bandykite dar kartą: ";
            std::cin >> vardas;
        }
        s.setVardas(vardas);

        std::cout << "Įveskite studento pavardę: ";
        std::cin >> pavarde;
        while (!tikrintiRaides(pavarde)) {
            std::cerr << "Netinkama pavardė. Bandykite dar kartą: ";
            std::cin >> pavarde;
        }
        s.setPavarde(pavarde);

        std::cout << "Įveskite namų darbų pažymius (baigti - ne skaičius): ";
        int balas;
        while (std::cin >> balas) {
            if (balas >= 0 && balas <= 10) {
                nd.push_back(balas);
            } else {
                std::cerr << "Blogas pažymys. Kartokite: ";
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        s.setNdBalai(nd);

        std::cout << "Įveskite egzamino pažymį: ";
        std::cin >> egz;
        while (egz < 0 || egz > 10 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Neteisingas įvestas balas. Kartokite: ";
            std::cin >> egz;
        }
        s.setEgzaminas(egz);

        studentai.push_back(s);

        std::cout << "Ar norite pridėti dar vieną studentą? (y/n): ";
        std::cin >> pasirinkimas;
    } while (pasirinkimas == 'y' || pasirinkimas == 'Y');

    return studentai;
}

// --- Rikiavimas ---

bool palygintiPagalVarda(const Student& a, const Student& b) {
    return a.getVardas() < b.getVardas();
}

bool palygintiPagalPavarde(const Student& a, const Student& b) {
    return a.getPavarde() < b.getPavarde();
}

bool palygintiPagalVidurkiAsc(const Student& a, const Student& b) {
    return a.galutinisPazymys(true) < b.galutinisPazymys(true);
}

bool palygintiPagalVidurkiDesc(const Student& a, const Student& b) {
    return a.galutinisPazymys(true) > b.galutinisPazymys(true);
}

bool palygintiPagalMedianaAsc(const Student& a, const Student& b) {
    return a.galutinisPazymys(false) < b.galutinisPazymys(false);
}

bool palygintiPagalMedianaDesc(const Student& a, const Student& b) {
    return a.galutinisPazymys(false) > b.galutinisPazymys(false);
}

void rikiuotiStudentus(std::vector<Student>& studentai, char pasirinkimas, char tvarka) {
    switch (pasirinkimas) {
        case '1': std::sort(studentai.begin(), studentai.end(), palygintiPagalVarda); break;
        case '2': std::sort(studentai.begin(), studentai.end(), palygintiPagalPavarde); break;
        case '3':
            if (tvarka == 'a' || tvarka == 'A')
                std::sort(studentai.begin(), studentai.end(), palygintiPagalVidurkiAsc);
            else
                std::sort(studentai.begin(), studentai.end(), palygintiPagalVidurkiDesc);
            break;
        case '4':
            if (tvarka == 'a' || tvarka == 'A')
                std::sort(studentai.begin(), studentai.end(), palygintiPagalMedianaAsc);
            else
                std::sort(studentai.begin(), studentai.end(), palygintiPagalMedianaDesc);
            break;
        default:
            std::cerr << "Neteisingas pasirinkimas!" << std::endl;
    }
}

void rikiuotiStudentusPagalPasirinkima(std::vector<Student>& studentai) {
    char pasirinkimas, tvarka = 'a';
    std::cout << "Pasirinkite rikiavimo būdą:\n"
              << "1. Pagal vardą\n"
              << "2. Pagal pavardę\n"
              << "3. Pagal galutinį vidurkį\n"
              << "4. Pagal galutinę medianą\n"
              << "Pasirinkimas: ";
    std::cin >> pasirinkimas;

    if (pasirinkimas == '3' || pasirinkimas == '4') {
        std::cout << "Pasirinkite tvarką (a - didėjimo, d - mažėjimo): ";
        std::cin >> tvarka;
    }

    rikiuotiStudentus(studentai, pasirinkimas, tvarka);
}
