#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "studentas.h"
#include <cmath>

TEST_CASE("Studento set/get metodai") {
    Student s;
    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.setNdBalai({8, 9, 10});
    s.setEgzaminas(9);

    CHECK(s.getVardas() == "Jonas");
    CHECK(s.getPavarde() == "Jonaitis");
    CHECK(s.getNdBalai() == std::vector<int>({8, 9, 10}));
    CHECK(s.getEgzaminas() == 9);
}

TEST_CASE("Skaičiavimai - vidurkis ir mediana") {
    Student s;
    s.setNdBalai({5, 7, 9});
    s.setEgzaminas(8);

    double tikėtinasVidurkis = (5 + 7 + 9) / 3.0;
    double tikėtinaMediana = 7;

    CHECK(std::abs(s.skaiciuotiVidurki() - tikėtinasVidurkis) < 1e-6);
    CHECK(std::abs(s.skaiciuotiMediana() - tikėtinaMediana) < 1e-6);
}

TEST_CASE("Galutinis pažymys") {
    Student s;
    s.setNdBalai({10, 10, 10});
    s.setEgzaminas(10);

    // Vidurkis = 10, Mediana = 10 -> Galutinis = 0.4 * 10 + 0.6 * 10 = 10
    CHECK(s.galutinisPazymys(true) == doctest::Approx(10.0));
    CHECK(s.galutinisPazymys(false) == doctest::Approx(10.0));
}

TEST_CASE("Kopijavimas ir priskyrimas") {
    Student s1;
    s1.setVardas("A");
    s1.setPavarde("B");
    s1.setNdBalai({1, 2, 3});
    s1.setEgzaminas(4);

    Student s2 = s1;
    CHECK(s2.getVardas() == "A");
    CHECK(s2.getPavarde() == "B");
    CHECK(s2.getNdBalai() == std::vector<int>({1, 2, 3}));
    CHECK(s2.getEgzaminas() == 4);
}
