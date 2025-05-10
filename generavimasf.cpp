#include "generavimasf.h"
#include "studentas.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <limits>

// Generuojame failus su studentais
void generuotiStudentuFailus(const std::vector<int>& kiekiai, std::vector<std::string>& failugen) {
    auto start = std::chrono::high_resolution_clock::now();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    for (int kiekis : kiekiai) {
        std::string failoPavadinimas = "Gstudentai" + std::to_string(kiekis) + ".txt";
        failugen.push_back(failoPavadinimas);
        std::ofstream outFile(failoPavadinimas);
        if (!outFile) {
            std::cerr << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
            continue;
        }

        outFile << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
        for (int i = 1; i <= 15; i++) {
            outFile << std::setw(10) << ("ND" + std::to_string(i));
        }
        outFile << std::setw(10) << "Egz." << std::endl;

        for (int i = 1; i <= kiekis; i++) {
            outFile << std::left << std::setw(20) << ("Vardas" + std::to_string(i))
                    << std::setw(20) << ("Pavarde" + std::to_string(i));
            for (int j = 0; j < 15; j++) {
                outFile << std::setw(10) << dist(gen);
            }
            outFile << std::setw(10) << dist(gen) << std::endl;
        }

        outFile.close();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Failo: " << failoPavadinimas << " generavimas užtruko: " << duration.count() << " sekundžių." << std::endl;
    }
}

// Rūšiuojame studentus į gerus ir blogus, skaitome iš failo
void rusiotiStudentusISFailus(const std::string& failopavadinimas, std::vector<std::string>& failugen) {
    std::ifstream inFile(failopavadinimas);
    if (!inFile) {
        std::cerr << "Nepavyko atidaryti failo: " << failopavadinimas << std::endl;
        return;
    }

    std::vector<Student> studentai;
    std::string vardas, pavarde;
    int balas;

    auto start = std::chrono::high_resolution_clock::now();

    std::string eilute;
    std::getline(inFile, eilute); // Praleidžiame antraštę

    while (inFile >> vardas >> pavarde) {
        Student studentas;
        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);

        std::vector<int> nd_balai;
        for (int i = 0; i < 15; i++) {
            inFile >> balas;
            nd_balai.push_back(balas);
        }
        studentas.setNdBalai(nd_balai);

        int egzaminas;
        inFile >> egzaminas;
        studentas.setEgzaminas(egzaminas);

        studentai.push_back(studentas);
    }
    inFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Failo: " << failopavadinimas << " skaitymas užtruko: " << duration.count() << " sekundžių." << std::endl;

    rikiuotiStudentusPriesRusiavima(studentai);

    // Strategijos pasirinkimas
    char strategijosPasirinkimas;
    std::cout << "Pasirinkite strategiją:\n";
    std::cout << "1. Paprasta strategija\n";
    std::cout << "2. Bendro studentų konteinerio skaidymas\n";
    std::cout << "3. Naudojant algoritmus\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> strategijosPasirinkimas;

    if (strategijosPasirinkimas == '1') {
        // Paprasta strategija
        std::vector<Student> vargsciukai;
        std::vector<Student> kietiakai;

        start = std::chrono::high_resolution_clock::now();
        for (const auto& studentas : studentai) {
            if (studentas.galutinisPazymys(true) < 5.0) {
                vargsciukai.push_back(studentas);
            } else {
                kietiakai.push_back(studentas);
            }
        }
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Paprasta strategija užtruko: " << duration.count() << " sekundžių." << std::endl;

        // Rašome į failus
        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for (const auto& studentas : vargsciukai) {
            vargsciukaiFile << studentas.getVardas() << " " << studentas.getPavarde() << " " << studentas.galutinisPazymys(true) << std::endl;
        }
        for (const auto& studentas : kietiakai) {
            kietiakaiFile << studentas.getVardas() << " " << studentas.getPavarde() << " " << studentas.galutinisPazymys(true) << std::endl;
        }

        vargsciukaiFile.close();
        kietiakaiFile.close();
    } else if (strategijosPasirinkimas == '2') {
        // Bendro studentų konteinerio skaidymas
        std::vector<Student> vargsciukai;

        start = std::chrono::high_resolution_clock::now();
        auto it = studentai.begin();
        while (it != studentai.end()) {
            if (it->galutinisPazymys(true) < 5.0) {
                vargsciukai.push_back(*it);
                it = studentai.erase(it);
            } else {
                ++it;
            }
        }
        

        // Rašome į failus
        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for (const auto& studentas : vargsciukai) {
            vargsciukaiFile << studentas.getVardas() << " " << studentas.getPavarde() << " " << studentas.galutinisPazymys(true) << std::endl;
        }
        for (const auto& studentas : studentai) {
            kietiakaiFile << studentas.getVardas() << " " << studentas.getPavarde() << " " << studentas.galutinisPazymys(true) << std::endl;
        }

        vargsciukaiFile.close();
        kietiakaiFile.close();

        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Konteinerio skaidymas užtruko: " << duration.count() << " sekundžių." << std::endl;

    } else if (strategijosPasirinkimas == '3') {
        // Naudojant algoritmus
        start = std::chrono::high_resolution_clock::now();
        auto it = std::partition(studentai.begin(), studentai.end(), [](const Student& studentas) {
            return studentas.galutinisPazymys(true) < 5.0;
        });
        

        // Rašome į failus
        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for (auto itVargsciukai = studentai.begin(); itVargsciukai != it; ++itVargsciukai) {
            vargsciukaiFile << itVargsciukai->getVardas() << " " << itVargsciukai->getPavarde() << " " << itVargsciukai->galutinisPazymys(true) << std::endl;
        }
        for (auto itKietiakai = it; itKietiakai != studentai.end(); ++itKietiakai) {
            kietiakaiFile << itKietiakai->getVardas() << " " << itKietiakai->getPavarde() << " " << itKietiakai->galutinisPazymys(true) << std::endl;
        }

        vargsciukaiFile.close();
        kietiakaiFile.close();

        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Algoritmų naudojimas užtruko: " << duration.count() << " sekundžių." << std::endl;

    }

    // Pašaliname panaudotą failą iš sąrašo
    failugen.erase(std::remove(failugen.begin(), failugen.end(), failopavadinimas), failugen.end());
    while (!failugen.empty()) {
        char pasirinkimas;
        std::cout << "Ar norite baigti darbą? (y/n): ";
        std::cin >> pasirinkimas;

        if (pasirinkimas == 'Y' || pasirinkimas == 'y') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } else {
            std::cout << "Pasirinkite failą naudojimui:\n";
            for (size_t i = 0; i < failugen.size(); ++i) {
                std::cout << i + 1 << ". " << failugen[i] << "\n";
            }
            std::cout << "Pasirinkimas: ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;

            if (failoPasirinkimas >= 1 && failoPasirinkimas <= failugen.size()) {
                rusiotiStudentusISFailus(failugen[failoPasirinkimas - 1], failugen);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
            }
        }
    }
}

// Rikiavimo funkcija
void rikiuotiStudentusPriesRusiavima(std::vector<Student>& studentai) {
    char rikiavimoPasirinkimas;
    std::cout << "Pasirinkite rikiavimo būdą:\n";
    std::cout << "1. Pagal vardą\n";
    std::cout << "2. Pagal pavardę\n";
    std::cout << "3. Pagal galutinį vidurkį\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> rikiavimoPasirinkimas;

    char tvarka = 'a';
    if (rikiavimoPasirinkimas == '3') {
        std::cout << "Pasirinkite rikiavimo tvarką:\n";
        std::cout << "a. Didėjimo tvarka\n";
        std::cout << "d. Mažėjimo tvarka\n";
        std::cout << "Pasirinkimas: ";
        std::cin >> tvarka;
    }

    auto start = std::chrono::high_resolution_clock::now();
    rikiuotiStudentus(studentai, rikiavimoPasirinkimas, tvarka);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Rikiavimas užtruko: " << duration.count() << " sekundžių." << std::endl;
}