#include<iostream>
#include<string>
#include<vector>
#include <stack> 
#include <typeinfo>

using namespace std;

// Memento
class HeroMemento
{
public:
    int Patrons{}; 
    int Lives{};

    HeroMemento(int patrons, int lives)
    {
        Patrons = patrons;
        Lives = lives;
    }
};

// Originator
class Hero
{
private:
    int patrons = 10; // кол-во патронов
    int lives = 5; // кол-во жизней
public:
    void Shoot()
    {
        if (patrons > 0)
        {
            patrons--;
            cout << "Shoot. It's " << patrons << "patrons left." << endl;
        }
        else
            cout << "No more";
    }
    // сохранение состояния
    HeroMemento SaveState()
    {
        cout << "Saving game..." << endl << patrons << "patrons, " << lives << " lives\n";
        return HeroMemento(patrons, lives);
    }

    // восстановление состояния
    void RestoreState(HeroMemento memento)
    {
        patrons = memento.Patrons;
        lives = memento.Lives;
        cout << "Restore game..." << endl << patrons << "patrons, " << lives << " lives\n";
    }
};


// Caretaker
class GameHistory
{
public:
    stack<HeroMemento> History; //get; private set; }
    GameHistory()
    {
        History = stack<HeroMemento>();
    }
};

int main()
{
    Hero hero = Hero();
    hero.Shoot(); // делаем выстрел, осталось 9 патронов
    GameHistory game = GameHistory();

    game.History.push(hero.SaveState()); // сохраняем игру

    hero.Shoot(); // делаем выстрел, осталось 8 патронов

    game.History.push(hero.SaveState()); // сохраняем игру

    game.History.pop();
    hero.RestoreState(game.History.top());

    hero.Shoot(); //делаем выстрел, осталось 8 патронов

    return 0;
}
