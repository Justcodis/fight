#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <new>

class Character
{
    protected:
    std::string name;
    int health;

    public:
    int get_hp()
    {
        return health;
    }

    std::string get_id()
    {
        return name;
    }

    Character(std::string nameplay, int healthplay)
    {
        name = nameplay;
        health = healthplay;
    }

    virtual void taken(int damage)
    {
        health = health - damage;
    }

    virtual void heal(int recover)
    {
        health = health + recover;
        std::cout << name << " healed " << recover << " HP!" << std::endl;
    }

    virtual void deal(int dealed, Character &target)
    {
        taken(dealed);
        std::cout << name << " dealed " << dealed << " damage to " << target.get_id() << std::endl;
    }
};

class Player : public Character
{
    private:
    int mana;

    public:
    int get_mana()
    {
        return mana;
    }
    Player(std::string nameplay, int healthplay, int manaplay) : Character(nameplay, healthplay)
    {
        mana = manaplay;
    }

    void castSpell(Character &target, int damage)
    {
        if (mana >= 20)
        {
            mana = mana - 20;
            std::cout << name << " have casted Magic!" << std::endl;
            target.taken(damage);
        }
        else
        {
            std::cout << "You don't have enough mana to cast!" << std::endl;
        }
    }
};

class Monster : public Character
{
    public:
    Monster(std::string nameplay, int healthplay) : Character(nameplay, healthplay)
    {}
};

int main()
{
    std::string nameme;
    std::string namethem;
    int action = 0;
    int * prob = new (std::nothrow) int[2];
    if (prob == nullptr)
    {
        std::cout << "Memory Allocation failed!" << std::endl;
        return 1;
    }

    std::cout << "Welcome to fight.cpp!" << std::endl << "What's your name?" << std::endl;
    std::cin >> nameme;

    Player you(nameme, 100, 50);

    std::cout << "What's enemy name you want?" << std::endl;
    std::cin >> namethem;

    Monster them(namethem, 100);

    srand(time(NULL));

    while (you.get_hp() > 0 && them.get_hp() > 0)
    {
        std::cout << you.get_id() << "'s HP " << you.get_hp() << std::endl << them.get_id() << "'s HP " << them.get_hp() << std::endl << you.get_id() << "'s have " << you.get_mana() << " mana" << std::endl << "Choose your action! (1 for attack, 2 for heal, 3 for cast Magic)(Critical Chance = 30%)" << std::endl;
        std::cin >> action;

        prob[0] = rand() % 100;

        if (action == 1 && prob[0] > 30)
        {
            you.deal(15, them);

            action = 0;
        }
        else if (action == 1 && prob[0] <= 30)
        {
            you.deal(30, them);
            std::cout << you.get_id() << " dealed critical damage" << std::endl;

            action = 0;
        }
        else if (action == 2)
        {
            you.heal(5);

            action = 0;
        }
        else if (action == 3)
        {
            you.castSpell(them, 40);
        }
        else if (action != 0 && action != 1 && action != 2)
        {
            std::cout << "Unknown command, choose carefully next time!" << std::endl << "Do not give up!" << std::endl;

            action = 0;
        }

        if (you.get_hp() <= 0 || them.get_hp() <= 0)
        {
            break;
        }

        prob[1] = rand() % 100;

        if (prob[1] < 65 && prob[1] >= 15)
        {
            them.deal(10, you);
        }
        else if (prob[1] < 15)
        {
            them.deal(20, you);
            std::cout << them.get_id() << " dealed critical damage" << std::endl;
        }
        else if (prob[1] >= 65)
        {
            them.heal(10);
        }

        if (you.get_hp() <= 0 || them.get_hp() <= 0)
        {
            break;
        }
    }
    delete[] prob;
    prob = nullptr;

    if (them.get_hp() <= 0)
    {
        std::cout << "You win!" << std::endl;
    }
    else
    {
        std::cout << "You lose" << std::endl;
    }
    return 0;
}
