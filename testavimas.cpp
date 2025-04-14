#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "studentas.h"
#include <cmath>


TEST_CASE("Studento konstruktorius") {
    // Naudojame numatytąjį konstruktorių
    Student s;

    // Tikriname, ar laukai inicializuoti teisingai
    CHECK(s.getVardas() == "");
    CHECK(s.getPavarde() == "");
    CHECK(s.getNdBalai().empty());
    CHECK(s.getEgzaminas() == 0);
}

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

    CHECK(s.skaiciuotiVidurki() == doctest::Approx(tikėtinasVidurkis));
    CHECK(s.skaiciuotiMediana() == doctest::Approx(tikėtinaMediana));

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

    Student s3;
    s3 = s1;
    CHECK(s3.getVardas() == "A");
    CHECK(s3.getPavarde() == "B");
    CHECK(s3.getNdBalai() == std::vector<int>({1, 2, 3}));
    CHECK(s3.getEgzaminas() == 4);
}

TEST_CASE("Perkėlimas (move)") {
    Student s1;
    s1.setVardas("X");
    s1.setPavarde("Y");
    s1.setNdBalai({6, 7});
    s1.setEgzaminas(8);

    // Move konstruktorius
    Student s2 = std::move(s1);
    CHECK(s2.getVardas() == "X");
    CHECK(s2.getPavarde() == "Y");
    CHECK(s2.getNdBalai() == std::vector<int>({6, 7}));
    CHECK(s2.getEgzaminas() == 8);

    // Move priskyrimo operatorius
    Student s3;
    s3 = std::move(s2);
    CHECK(s3.getVardas() == "X");
    CHECK(s3.getPavarde() == "Y");
    CHECK(s3.getNdBalai() == std::vector<int>({6, 7}));
    CHECK(s3.getEgzaminas() == 8);
}

TEST_CASE("Išvestis su operatoriais") {
    
    Student s;
    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.setNdBalai({10, 9, 8, 0});
    s.setEgzaminas(7);

    std::ostringstream output;
    output << s;

    std::string result = output.str();
    CHECK(result.find("Jonas") != std::string::npos);
    CHECK(result.find("Jonaitis") != std::string::npos);
    CHECK(result.find("7") != std::string::npos);
     
}
TEST_CASE("Destruktoriaus testavimas") {
    
    {
        Student s;
        s.setVardas("Test");
        s.setPavarde("Testavicius");
        s.setNdBalai({1, 2, 3});
        s.setEgzaminas(5);

        // Tikriname, ar teisingai
        CHECK(s.getVardas() == "Test");
        CHECK(s.getPavarde() == "Testavicius");
        CHECK(s.getNdBalai() == std::vector<int>({1, 2, 3}));
        CHECK(s.getEgzaminas() == 5);
    }
    // Jei destruktorius veikia teisingai, testas praeis be klaidų
}
