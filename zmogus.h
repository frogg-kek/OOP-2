#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vardas;
    std::string pavarde;

public:
    virtual ~Zmogus() = default;

    
    virtual std::string getVardas() const = 0;
    virtual std::string getPavarde() const = 0;

    virtual void setVardas(const std::string& v) = 0;
    virtual void setPavarde(const std::string& p) = 0;
};

#endif
