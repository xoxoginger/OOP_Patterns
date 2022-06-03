#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <clocale>
using namespace std;

class EliteHouse;
class UsualHouse;

class Visitor { //продажники
public:
    virtual void VisitElite(const EliteHouse* element) const = 0;
    virtual void VisitUsual(const UsualHouse* element) const = 0;
};


class House { //жители - компонент
public:
    virtual ~House() {}
    virtual void Accept(Visitor* visitor) const = 0;
};


class EliteHouse : public House { //элитные ЖК
    
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitElite(this);
    }
    
    string ExclusiveMethodOfEliteHouse() const {
        return "Для вас - предложение по специальной цене: скидка 50%";
    }
};

class UsualHouse : public House { //обычные ЖК

public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitUsual(this);
    }
    string SpecialMethodOfUsualHouse() const {
        return "Для вас - предложение по специальной цене: скидка 50%";
    }
};


class HooverVisitor : public Visitor { //чел с пылесосами
public:
    void VisitElite(const EliteHouse* element) const override {
        cout << element->ExclusiveMethodOfEliteHouse() << " + \nНаш уникальный пылесос всего за 300000 \n";
    }

    void VisitUsual(const UsualHouse* element) const override {
        cout << element->SpecialMethodOfUsualHouse() << " + \nНаш уникальный пылесос всего за 150000 \n";
    }
};

class CosmeticsVisitor : public Visitor { //чел с косметикой
public:
    void VisitElite(const EliteHouse* element) const override {
        cout << element->ExclusiveMethodOfEliteHouse() << " \nСамый лучший набор косметики для ухода за собой - всего за 7000\n";
    }
    void VisitUsual(const UsualHouse* element) const override {
        cout << element->SpecialMethodOfUsualHouse() << " \nСамый лучший набор косметики для ухода за собой - всего за 3500\n";
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    array<const House*, 2> components = { new EliteHouse, new UsualHouse };
    cout << "The client code works with all visitors via the base Visitor interface:\n";
    HooverVisitor* visitor1 = new HooverVisitor;
    for (const House* comp : components) {
        comp->Accept(visitor1);
    }

    cout << "\n";
    cout << "It allows the same client code to work with different types of visitors:\n";
    CosmeticsVisitor* visitor2 = new CosmeticsVisitor;
    for (const House* comp : components) {
        comp->Accept(visitor2);
    }

    for (const House* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;

    return 0;
}
