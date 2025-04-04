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
        // Praleisti antraštės eilutę
        if (!std::getline(inFile, line)) {
            throw std::runtime_error("Failas tuščias arba sugadintas: " + failoPavadinimas);
        }

        while (std::getline(inFile, line)) {
            Student studentas;
            std::stringstream ss(line);
            std::string vardas, pavarde;
            ss >> vardas >> pavarde;

            if (ss.fail()) {
                std::cerr << "Klaida skaitant studento duomenis eilutėje: " << line << std::endl;
                continue;  // Pereiname prie kitos eilutės
            }

            studentas.setVardas(vardas);
            studentas.setPavarde(pavarde);

            int pazymys;
            std::vector<int> pazymiai;
            while (ss >> pazymys) {
                pazymiai.push_back(pazymys);
            }

            if (pazymiai.empty()) {
                std::cerr << "Klaida: Studentas " << vardas << " " << pavarde << " neturi pažymių." << std::endl;
                continue;  // Pereiname prie kitos eilutės
            }

            studentas.setNdBalai(std::vector<int>(pazymiai.begin(), pazymiai.end() - 1));
            studentas.setEgzaminas(pazymiai.back());
            studentai.push_back(studentas);
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
    std::cout << "\nVardas        Pavardė       Galutinis (Vidurkis)     Galutinis (Mediana)" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    for (const auto& studentas : studentai) {
        double galutinisVidurkis = studentas.galutinisPazymys(true);
        double galutinisMediana = studentas.galutinisPazymys(false);

        std::cout << std::left << std::setw(12) << studentas.getVardas()
                  << std::setw(14) << studentas.getPavarde()
                  << std::fixed << std::setprecision(2) << std::setw(25) << galutinisVidurkis
                  << galutinisMediana << std::endl;
    }
}

// Funkcija rezultatų rašymui į failą
void rasytiRezultatus(const std::string& failoPavadinimas, const std::vector<Student>& studentai) {
    std::ofstream outFile(failoPavadinimas);
    if (outFile.is_open()) {
        outFile << std::left << std::setw(20) << "Vardas" 
                << std::setw(20) << "Pavardė" 
                << std::setw(30) << "Galutinis (Vidurkis)" 
                << "Galutinis (Mediana)" << std::endl;
        outFile << "-------------------------------------------------------------------------------" << std::endl;
        
        for (const auto& studentas : studentai) {
            double galutinisVidurkis = studentas.galutinisPazymys(true);
            double galutinisMediana = studentas.galutinisPazymys(false);

            outFile << std::left << std::setw(20) << studentas.getVardas()
                    << std::setw(20) << studentas.getPavarde()
                    << std::fixed << std::setprecision(2) << std::setw(30) << galutinisVidurkis
                    << galutinisMediana << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
    }  
}

// Funkcija rezultatų išvesties būdo pasirinkimui
void pasirinktiIsvestiesBuda(const std::vector<Student>& studentai) {
    char outputChoice;
    std::cout << "Ar norite spausdinti rezultatus į ekraną ar į failą? (e/f): ";
    std::cin >> outputChoice;
    
    if (outputChoice == 'e' || outputChoice == 'E') {
        // Spausdinti rezultatus į ekraną
        spausdintiRezultatus(studentai);
    } else if (outputChoice == 'f' || outputChoice == 'F') {
        // Rašyti rezultatus į failą
        rasytiRezultatus("kursiokai.txt", studentai);
    } else {
        std::cout << "Neteisingas pasirinkimas!" << std::endl;
    }
}