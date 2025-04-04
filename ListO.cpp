#include "ListO.h"
#include "studentas.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <iostream>
#include <list>

// Skaitymas ir rūšiavimas įgyvendinant 3 strategijas pasirinktinai
void rusiotiStudentusISFailusList(const std::string& failopavadinimas, std::list<std::string>& failugenList) {
    bool darboPabaiga = false;
    if (darboPabaiga) {
        return;
    }

    std::cout << "Pasirinkite failą naudojimui:\n";
    int index = 1;
    for (const auto& failas : failugenList) {
        std::cout << index++ << ". " << failas << "\n";
    }
    std::cout << "Pasirinkimas: ";
    int failoPasirinkimas;
    std::cin >> failoPasirinkimas;

    if (failoPasirinkimas < 1 || failoPasirinkimas > static_cast<int>(failugenList.size())) {
        std::cout << "Neteisingas pasirinkimas!" << std::endl;
        return;
    }

    auto it = failugenList.begin();
    std::advance(it, failoPasirinkimas - 1);
    std::string pasirinktasFailas = *it;

    std::ifstream inFile(pasirinktasFailas);
    if (!inFile) {
        std::cerr << "Nepavyko atidaryti failo: " << pasirinktasFailas << std::endl;
        return;
    }

    std::list<Student> studentai;
    std::string vardas, pavarde;
    int balas;

    // Skaitymo pradžia
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

    // Skaitymo pabaiga
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Failo: " << pasirinktasFailas << " skaitymas su List užtruko: " << duration.count() << " sekundžių." << std::endl;

    rikiuotiStudentusPriesSkirstymaList(studentai);

    char strategijosPasirinkimas;
    std::cout << "Pasirinkite strategiją:\n";
    std::cout << "1. Paprasta strategija\n";
    std::cout << "2. Bendro studentų konteinerio skaidymas\n";
    std::cout << "3. Naudojant algoritmus\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> strategijosPasirinkimas;

    if (strategijosPasirinkimas == '1') {
        // Paprasta strategija
        std::list<Student> vargsciukai;
        std::list<Student> kietiakai;

        start = std::chrono::high_resolution_clock::now();
        for (const auto& studentas : studentai) {
            if (studentas.galutinisPazymys(true) < 5.0) {
                vargsciukai.push_back(studentas);
            } else {
                kietiakai.push_back(studentas);
            }
        }

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

        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Skirstymas į failus su List ir #1 strategija užtruko: " << duration.count() << " sekundžių." << std::endl;
    } else if (strategijosPasirinkimas == '2') {
        // Bendro studentų konteinerio skaidymas
        std::list<Student> vargsciukai;

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
        std::cout << "Skirstymas į failus su List ir #2 strategija užtruko: " << duration.count() << " sekundžių." << std::endl;
    } else if (strategijosPasirinkimas == '3') {
        // Naudojant algoritmus
        start = std::chrono::high_resolution_clock::now();
        auto it = std::partition(studentai.begin(), studentai.end(), [](const Student& studentas) {
            return studentas.galutinisPazymys(true) < 5.0;
        });

        std::list<Student> vargsciukai(studentai.begin(), it);
        std::list<Student> kietiakai(it, studentai.end());

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

        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Skirstymas su List ir #3 strategija užtruko: " << duration.count() << " sekundžių." << std::endl;
    }

    failugenList.erase(std::remove(failugenList.begin(), failugenList.end(), failopavadinimas), failugenList.end());
    while (!failugenList.empty()) {
        char pasirinkimas;
        std::cout << "Ar norite baigti darbą? (y/n): ";
        std::cin >> pasirinkimas;

        if (pasirinkimas == 'Y' || pasirinkimas == 'y') {
            darboPabaiga = true;
            return;
        } else {
            std::cout << "Pasirinkite failą naudojimui:\n";
            int index = 1;
            for (const auto& failas : failugenList) {
                std::cout << index++ << ". " << failas << "\n";
            }
            std::cout << "Pasirinkimas: ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;

            if (failoPasirinkimas >= 1 && failoPasirinkimas <= static_cast<int>(failugenList.size())) {
                auto it = failugenList.begin();
                std::advance(it, failoPasirinkimas - 1);
                rusiotiStudentusISFailusList(*it, failugenList);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
            }
        }
    }
}

void rikiuotiStudentusPriesSkirstymaList(std::list<Student>& studentai) {
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
    if (rikiavimoPasirinkimas == '1') {
        studentai.sort([](const Student& a, const Student& b) {
            return a.getVardas() < b.getVardas();
        });
    } else if (rikiavimoPasirinkimas == '2') {
        studentai.sort([](const Student& a, const Student& b) {
            return a.getPavarde() < b.getPavarde();
        });
    } else if (rikiavimoPasirinkimas == '3') {
        if (tvarka == 'a') {
            studentai.sort([](const Student& a, const Student& b) {
                return a.galutinisPazymys(true) < b.galutinisPazymys(true);
            });
        } else if (tvarka == 'd') {
            studentai.sort([](const Student& a, const Student& b) {
                return a.galutinisPazymys(true) > b.galutinisPazymys(true);
            });
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Rikiavimas užtruko: " << duration.count() << " sekundžių." << std::endl;
}