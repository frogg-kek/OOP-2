// Funkcijos susijusios su failų operacijomis
#include "failo_oper.h"
#include "studentas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>

// Funkcija studentų nuskaitymui iš failo
std::vector<Student> nuskaitytiStudentus(const std::string& failoPavadinimas, double& skaitymoLaikas) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Student> studentai;

    try {
        std::ifstream inFile(failoPavadinimas);
        if (!inFile) {
            throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
        }

        std::string line;
        // Praleisti antraštę
        if (!std::getline(inFile, line)) {
            throw std::runtime_error("Failas tuščias arba sugadintas: " + failoPavadinimas);
        }

        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string vardas, pavarde;
            ss >> vardas >> pavarde;

            if (ss.fail()) {
                std::cerr << "Klaida skaitant studento duomenis eilutėje: " << line << std::endl;
                continue;
            }

            std::vector<int> visiPazymiai;
            int paz;
            while (ss >> paz) {
                if (paz >= 0 && paz <= 10)
                    visiPazymiai.push_back(paz);
            }

            if (visiPazymiai.size() < 1) {
                std::cerr << "Klaida: Studentas " << vardas << " " << pavarde << " neturi pakankamai pažymių." << std::endl;
                continue;
            }

            // Paskutinis pažymys – egzaminas
            int egzaminas = visiPazymiai.back();
            visiPazymiai.pop_back();

            Student s;
            s.setVardas(vardas);
            s.setPavarde(pavarde);
            s.setNdBalai(visiPazymiai);
            s.setEgzaminas(egzaminas);

            studentai.push_back(s);
        }

    } catch (const std::exception& e) {
        std::cerr << "Klaida nuskaitant studentus: " << e.what() << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    skaitymoLaikas = std::chrono::duration<double>(end - start).count();
    return studentai;
}

// Funkcija rezultatų spausdinimui į ekraną
void spausdintiRezultatus(const std::vector<Student>& studentai) {
    std::cout << "\n" << std::left
              << std::setw(15) << "Vardas"
              << std::setw(15) << "Pavardė"
              << std::setw(25) << "Galutinis (Vidurkis)"
              << "Galutinis (Mediana)" << std::endl;

    std::cout << std::string(75, '-') << std::endl;

    for (const auto& s : studentai) {
        std::cout << std::left
                  << std::setw(15) << s.getVardas()
                  << std::setw(15) << s.getPavarde()
                  << std::fixed << std::setprecision(2)
                  << std::setw(25) << s.galutinisPazymys(true)
                  << s.galutinisPazymys(false) << std::endl;
    }
}

// Funkcija rezultatų rašymui į failą
void rasytiRezultatus(const std::string& failoPavadinimas, const std::vector<Student>& studentai) {
    std::ofstream outFile(failoPavadinimas);
    if (!outFile.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    outFile << std::left
            << std::setw(15) << "Vardas"
            << std::setw(15) << "Pavardė"
            << std::setw(25) << "Galutinis (Vidurkis)"
            << "Galutinis (Mediana)" << std::endl;

    outFile << std::string(75, '-') << std::endl;

    for (const auto& s : studentai) {
        outFile << std::left
                << std::setw(15) << s.getVardas()
                << std::setw(15) << s.getPavarde()
                << std::fixed << std::setprecision(2)
                << std::setw(25) << s.galutinisPazymys(true)
                << s.galutinisPazymys(false) << std::endl;
    }
}

// Funkcija rezultatų išvesties pasirinkimui
void pasirinktiIsvestiesBuda(const std::vector<Student>& studentai) {
    char pasirinkimas;
    std::cout << "\nAr norite spausdinti rezultatus į ekraną ar į failą? (e/f): ";
    std::cin >> pasirinkimas;

    if (pasirinkimas == 'e' || pasirinkimas == 'E') {
        spausdintiRezultatus(studentai);
    } else if (pasirinkimas == 'f' || pasirinkimas == 'F') {
        rasytiRezultatus("kursiokai.txt", studentai);
        std::cout << "Rezultatai išsaugoti faile: kursiokai.txt\n";
    } else {
        std::cerr << "Neteisingas pasirinkimas!\n";
    }
}
