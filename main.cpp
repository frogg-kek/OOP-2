#include "studentas.h"
#include "failo_oper.h"
#include "papild.h"
#include "ListO.h"
#include "DequeO.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include "generavimasf.h"
#include "testai.h"

void generuotiFailus(std::vector<std::string>& failugen) {
    std::vector<int> kiekiai = {1000, 10000, 100000, 1000000, 10000000};
    generuotiStudentuFailus(kiekiai, failugen);

    std::ofstream outFile("generuotasMixas.txt", std::ios::trunc);
    for (const auto& failas : failugen) {
        outFile << failas << std::endl;
    }
}

void nuskaitytiSugeneruotusFailus(std::vector<std::string>& failugen, std::list<std::string>& failugenList, std::deque<std::string>& failugenDeque) {
    std::ifstream inFile("generuotasMixas.txt");
    std::string failas;
    while (std::getline(inFile, failas)) {
        failugen.push_back(failas);
        failugenList.push_back(failas);
        failugenDeque.push_back(failas);
    }
}

int main() {
    std::vector<Student> studentai;
    char pasirinkimas;
    std::vector<std::string> failugen;
    std::list<std::string> failugenList;
    std::deque<std::string> failugenDeque;

    std::cout << "Pasirinkite veiksmą:\n";
    std::cout << "1. Sugeneruoti studentų failus\n";
    std::cout << "2. Sugeneruoti studentų duomenis automatiškai\n";
    std::cout << "3. Įvesti studentų duomenis ranka\n";
    std::cout << "4. Nuskaityti studentų duomenis iš failo\n";
    std::cout << "5. Testai su failais\n";
    std::cout << "6. Baigti programą\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> pasirinkimas;

    switch (pasirinkimas) {
        case '1': {
            generuotiFailus(failugen);
            break;
        }
        case '2': {
            int studentuSk;
            std::cout << "Kiek studentų norite sugeneruoti? ";
            std::cin >> studentuSk;
            studentai = generuotiStudentus(studentuSk);
            std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavardė" << std::setw(25) << "Galutinis (Vidurkis)"
            << "Galutinis (Mediana)" << std::endl;

            std::cout << std::string(75, '-') << std::endl;

        for (const auto& s : studentai) {
            std::cout << std::left << std::setw(15) << s.getVardas()  << std::setw(15) << s.getPavarde() << std::fixed << std::setprecision(2)
            << std::setw(25) << s.galutinisPazymys(true)
            << s.galutinisPazymys(false) << std::endl;
    }
    //std::cout << studentai[5].getVardas() << std::endl; // patikra
            break;
        }
        case '3':
            studentai = ivestiStudentus();
            break;
        case '4': {
            std::vector<std::string> failuPavadinimai = {
                "studentai10000.txt",
                "studentai100000.txt",
                "studentai1000000.txt"
            };
            std::cout << "Pasirinkite failą naudojimui (1, 2 arba 3): ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;

            if (failoPasirinkimas >= 1 && failoPasirinkimas <= 3) {
                double skaitymoLaikas;
                studentai = nuskaitytiStudentus(failuPavadinimai[failoPasirinkimas - 1], skaitymoLaikas);
                std::cout << "Failo skaitymas užtruko: " << skaitymoLaikas << " sekundžių." << std::endl;
                rikiuotiStudentusPagalPasirinkima(studentai);
                pasirinktiIsvestiesBuda(studentai);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
                return 1;
            }
            break;
        }
        case '5': {
            nuskaitytiSugeneruotusFailus(failugen, failugenList, failugenDeque);
            if (!failugen.empty()) {
                std::cout << "Pasirinkite kokį konteinerį naudoti (v - vector, l - list, d - deque): ";
                char konteinerioPasirinkimas;
                std::cin >> konteinerioPasirinkimas;

                switch (konteinerioPasirinkimas) {
                    case 'v': {
                        if (!failugen.empty()) {
                            std::cout << "Pasirinkite failą naudojimui:\n";
                            for (size_t i = 0; i < failugen.size(); ++i) {
                                std::cout << i + 1 << ". " << failugen[i] << "\n";
                            }
                            std::cout << "Pasirinkimas: ";
                            int failoPasirinkimas;
                            std::cin >> failoPasirinkimas;

                            if (failoPasirinkimas >= 1 && failoPasirinkimas <= static_cast<int>(failugen.size())) {
                                rusiotiStudentusISFailus(failugen[failoPasirinkimas - 1], failugen);
                            } else {
                                std::cout << "Neteisingas pasirinkimas!" << std::endl;
                            }
                        } else {
                            std::cout << "Nėra failų vektoriuje." << std::endl;
                        }
                        break;
                    }
                    case 'l': {
                        if (!failugenList.empty()) {
                            std::cout << "Pasirinkite failą naudojimui:\n";
                            int index = 1;
                            for (const auto& failas : failugenList) {
                                std::cout << index++ << ". " << failas << "\n";
                            }
                            std::cout << "Pasirinkimas: ";
                            int failoPasirinkimas;
                            std::cin >> failoPasirinkimas;

                            if (failoPasirinkimas >= 1 && failoPasirinkimas <= static_cast<int>(failugenList.size())) {
                                auto it = std::next(failugenList.begin(), failoPasirinkimas - 1);
                                rusiotiStudentusISFailusList(*it, failugenList);
                            } else {
                                std::cout << "Neteisingas pasirinkimas!" << std::endl;
                            }
                        } else {
                            std::cout << "Nėra failų sąraše." << std::endl;
                        }
                        break;
                    }
                    case 'd': {
                        if (!failugenDeque.empty()) {
                            std::cout << "Pasirinkite failą naudojimui:\n";
                            for (size_t i = 0; i < failugenDeque.size(); ++i) {
                                std::cout << i + 1 << ". " << failugenDeque[i] << "\n";
                            }
                            std::cout << "Pasirinkimas: ";
                            int failoPasirinkimas;
                            std::cin >> failoPasirinkimas;

                            if (failoPasirinkimas >= 1 && failoPasirinkimas <= static_cast<int>(failugenDeque.size())) {
                                rusiotiStudentusISFailusDeque(failugenDeque[failoPasirinkimas - 1], failugenDeque);
                            } else {
                                std::cout << "Neteisingas pasirinkimas!" << std::endl;
                            }
                        } else {
                            std::cout << "Nėra failų deque." << std::endl;
                        }
                        break;
                    }
                    default:
                        std::cout << "Neteisingas pasirinkimas!" << std::endl;
                        break;
                }
            } else {
                std::cout << "Nėra sugeneruotų failų testavimui." << std::endl;
            }
            break;
        }
        case '6':
            return 0;
        default:
            std::cout << "Neteisingas pasirinkimas!" << std::endl;
            return 1;
    }
    return 0;
}