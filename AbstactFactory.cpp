#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// Абстрактные базовые классы всех возможных видов животных
class Chicken
{
public:
	virtual void info() = 0; 
	virtual int eggs() = 0;
	virtual ~Chicken() {}
};

class Cow
{
public:
	virtual void info() = 0;
	virtual int milk() = 0;
	virtual ~Cow() {}
};

class Ship
{
public:
	virtual void info() = 0;
	virtual int wool() = 0;
	virtual ~Ship() {}
};


// Классы всех видов животных "Веселой фермы"
class FunnyFarmChicken : public Chicken
{
public:
	string color = "brown";
	void info() {
		cout << "FunnyFarmChicken" << endl;
	}
	int eggs() {
		int eggs = rand() % rand() / 10;
		cout << eggs << " eggs " << endl;
		return eggs;
	}

};

class FunnyFarmCow : public Cow
{
public:
	void info() {
		cout << "FunnyFarmCow" << endl;
	}
	int milk() {
		int milk = rand() % rand() / 10;
		cout << milk << " liters of milk " << endl;
		return milk;
	}
};

class FunnyFarmShip : public Ship
{
public:
	void info() {
		cout << "FunnyFarmShip" << endl;
	}
	int wool() {
		int wool = rand() % rand() / 10;
		cout << wool << " pounds of wool " << endl;
		return wool;
	}
};


// Классы всех видов животных фермы "Рога и Копыта"
class HornsAndHoovesChicken : public Chicken
{
public:
	string color = "white";
	void info() {
		cout << "HornsAndHoovesChicken" << endl;
	}

	int eggs() {
		int eggs = rand() % rand() / 10;
		cout << eggs << " eggs " << endl;
		return eggs;
	}
};

class HornsAndHoovesCow : public Cow
{
public:
	void info() {
		cout << "HornsAndHoovesCow" << endl;
	}

	int milk() {
		int milk = rand() % rand() / 10;
		cout << milk << " liters of milk " << endl;
		return milk;
	}
};

class HornsAndHoovesShip : public Ship
{
public:
	void info() {
		cout << "HornsAndHoovesShip" << endl;
	}
	int wool() {
		int wool = rand() % rand() / 10;
		cout << wool << " pounds of wool " << endl;
		return wool;
	}
};


// Абстрактная фабрика для производства животных
class AnimalsFactory
{
public:
	virtual Chicken* createChicken() = 0;
	virtual Cow* createCow() = 0;
	virtual Ship* createShip() = 0;
	virtual ~AnimalsFactory() {}
};


// Фабрика для создания животных для "Веселая ферма"
class FunnyFarmFactory : public AnimalsFactory
{
public:
	Chicken* createChicken() {
		return new FunnyFarmChicken;
	}
	Cow* createCow() {
		return new FunnyFarmCow;
	}
	Ship* createShip() {
		return new FunnyFarmShip;
	}
};


// Фабрика для создания животных для «Рога и Копыта»
class HornesAndHoovesFactory : public AnimalsFactory
{
public:
	Chicken* createChicken() {
		return new HornsAndHoovesChicken;
	}
	Cow* createCow() {
		return new HornsAndHoovesCow;
	}
	Ship* createShip() {
		return new HornsAndHoovesShip;
	}
};


// Класс, содержащий всех животных той или иной фермы
class Farm
{
public:

	vector<Chicken*> vc;
	vector<Cow*> vco;
	vector<Ship*> vs;

	~Farm() {
		int i;
		for (i = 0; i < vc.size(); i++) delete vc[i];
		for (i = 0; i < vco.size(); i++) delete vco[i];
		for (i = 0; i < vs.size(); i++) delete vs[i];
	}
	void info() {
		int i;
		for (i = 0; i < vc.size(); i++) vc[i]->info();
		for (i = 0; i < vco.size(); i++) vco[i]->info();
		for (i = 0; i < vs.size(); i++) vs[i]->info();
	}

	int total() {
		int i;
		int sum = 0;
		for (i = 0; i < vc.size(); i++) sum += vc[i]->eggs();
		for (i = 0; i < vco.size(); i++) sum += vco[i]->milk();
		for (i = 0; i < vs.size(); i++) sum += vs[i]->wool();

		return sum;
	}
};


// Здесь создаются животные той или иной фермы
class Production
{
public:
	Farm* createFarm(AnimalsFactory& factory) {
		Farm* p = new Farm;
		p->vc.push_back(factory.createChicken());
		p->vco.push_back(factory.createCow());
		p->vs.push_back(factory.createShip());
		return p;
	}
};


int main()
{
	srand(time(NULL));
	Production prod;
	FunnyFarmFactory FFFactory;
	HornesAndHoovesFactory HHFactory;

	Farm* FF = prod.createFarm(FFFactory);
	Farm* HH = prod.createFarm(HHFactory);
	
	cout << "Funny farm: " << endl << endl;
	FF->info();
	int FFTotal = FF->total();
	cout << FFTotal << " - FF sum" << endl;
	
	cout << "\nHorns And Hooves: " << endl << endl;
	HH->info();
	int HHTotal = HH->total();
	cout << HHTotal << " - HH sum" << endl << endl;
	
	if (FFTotal > HHTotal)
		cout << "FF win" << endl;
	else if (FFTotal < HHTotal)
		cout << "HH win" << endl;
	else
		cout << "Dead heat!" << endl;
	
	return 0;
}