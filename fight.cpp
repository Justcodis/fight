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
    int damage;
    int role = 0;
    int crit = 30;
    int terrify = 0;

    public:
    int get_hp()
    {
        return health;
    }

    std::string get_id()
    {
        return name;
    }

    int get_dmg()
    {
        return damage;
    }

    int get_role()
    {
        return role;
    }

    int get_cr()
    {
        return crit;
    }

    void debuff(int less)
    {
        damage = damage - less;
    }

    Character(std::string nameplay, int healthplay, int damageplay)
    {
        name = nameplay;
        health = healthplay;
        damage = damageplay;
    }

    virtual ~Character() = default;

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
        target.taken(dealed);
        std::cout << name << " dealed " << dealed << " damage to " << target.get_id() << std::endl;
    }
    virtual void castSpell(Character &target, int madamage)
    {}
    virtual void terry(Character &target, int less)
    {}
    virtual void dodgeon()
    {}
    virtual void dodgeoff()
    {}
    virtual void healmana(int add)
    {}
    virtual int get_chc()
    {
        return 0;
    }
    virtual int get_dod()
    {
        return 0;
    }
    virtual int get_defense(int type)
    {
        return 0;
    }
    virtual int get_crdmg()
    {
        return 0;
    }
    virtual int get_mana()
    {
        return 0;
    }
};

class Mage : public Character
{
    private:
    int mana;

    public:
    int get_mana() override
    {
        return mana;
    }

    void healmana(int add) override
    {
        mana = mana + add;
        std::cout << name << " have regen " << add << " mana!" << std::endl;
    }

    Mage(std::string nameplay, int healthplay, int damageplay, int manaplay) : Character(nameplay, healthplay, damageplay)
    {
        mana = manaplay;
        role = 2;
        crit = 0;
    }

    void castSpell(Character &target, int madamage) override
    {
        if (mana >= 20)
        {
            mana = mana - 20;
            std::cout << name << " have casted Magic!" << std::endl;
            target.taken(madamage);
        }
        else
        {
            std::cout << "You don't have enough mana to cast!" << std::endl;
        }
    }
};

class Fighter : public Character
{
    private:
    int pydefense;
    int madefense;

    public:
    int get_defense(int type) override
    {
        if (type == 0)
        {
            return pydefense;
        }
        else{
            return madefense;
        }
    }
    Fighter(std::string nameplay, int healthplay, int damageplay, int pydefenseplay, int madefenseplay) : Character(nameplay, healthplay, damageplay)
    {
        pydefense = pydefenseplay;
        madefense = madefenseplay;
        role = 1;
    }
};

class Assassin : public Character
{
    private:
    int dodge;
    int chance;

    public:
    int get_chc() override
    {
        return chance;
    }
    int get_dod() override
    {
        int result = dodge;
        return result;
    }
    void dodgeon() override
    {
        dodge = rand() % 100;
    }
    void dodgeoff() override
    {}
    Assassin(std::string nameplay, int healthplay, int damageplay, int chanceplay) : Character(nameplay, healthplay, damageplay)
    {
        chance = chanceplay;
        role = 3;
    }

    void terry(Character &target, int less) override
    {
        target.debuff(less);
    }
};

class Marksman : public Character
{
    private:
    int critdmg;

    public:
    int get_crdmg() override
    {
        return critdmg;
    }
    Marksman(std::string nameplay, int healthplay, int damageplay, int crdamage, int crchance) : Character(nameplay, healthplay, damageplay)
    {
        critdmg = crdamage;
        role = 4;
        crit = crchance;
    }
};

class Monster : public Character
{
    public:
    Monster(std::string nameplay, int healthplay, int damageplay) : Character(nameplay, healthplay, damageplay)
    {}
};

class Game
{
    private:
    Character * you = nullptr;
    std::string nameme;
    std::string namethem;
    int failed = 0;
    int action = 0;
    int * prob;
    int retry = 0;
    int role;
    int block;

    public:
    int get_re()
    {
        return retry;
    }
    int get_fail()
    {
        return failed;
    }
    void changeretry()
    {
        retry = 0;
    }
    void check_alloc()
    {
        prob = new (std::nothrow) int[2];
        if (prob == nullptr)
        {
            std::cout << "Memory Allocation failed!" << std::endl;
            failed = 1;
            return;
        }
    }
    void unleak()
    {
        if (prob != nullptr)
        {
            delete[] prob;
            prob = nullptr;
        }
        if (you != nullptr)
        {
            delete you;
            you = nullptr;
        }
    }
    void play()
    {
        std::cout << "Welcome to fight.cpp!" << std::endl << "What's your name?" << std::endl;
        std::cin >> nameme;

        std::cout << "What role do you are?(1 is Fighter, 2 is Mage, 3 is Assassin, 4 is Marksman, else interger normal inheritance)" << std::endl;
        std::cin >> role;

        if (role == 1)
        {
            you = new Fighter(nameme, 100, 15, 20, 20);
        }
        else if (role == 2)
        {
            you = new Mage(nameme, 100, 10, 50);
        }
        else if (role == 3)
        {
            you = new Assassin(nameme, 100, 15, 25);
        }
        else if (role == 4)
        {
            you = new Marksman(nameme, 100, 15, 15, 50);
        }
        else
        {
            you = new Monster(nameme, 200, 15);
        }
        std::cout << "What's enemy name you want?" << std::endl;
        std::cin >> namethem;

        Monster them(namethem, 300, 10);

        while (you->get_hp() > 0 && them.get_hp() > 0)
        {
            if (role == 3)
            {
                you->dodgeon();
            }
            std::cout << you->get_id() << "'s HP = " << you->get_hp() << std::endl << them.get_id() << "'s HP = " << them.get_hp() << std::endl << "Choose your action! (1 for attack, 2 for heal, 3 for cast Magic/ Terrify)" << std::endl;
            if (role == 1)
            {
                std::cout << "Physical defense = " << you->get_defense(0) << std::endl;
                std::cout << "Magic defense = " << you->get_defense(1) << std::endl;
            }
            else if (role == 2)
            {
                std::cout << "Mana = " << you->get_mana() << std::endl;
            }
            else if (role == 3)
            {
                std::cout << "Dodge chance =" << you->get_chc() << "%" << std::endl;
            }
            else if (role == 4)
            {
                std::cout << "Critical chance = " << you->get_cr() << "%" << std::endl;
                std::cout << "Critical damage = " << you->get_crdmg() << std::endl;
            }

            if (role != 2 && role != 4)
            {
                std::cout << "Critical chance = 30%" << std::endl;
            }

            std::cin >> action;

            prob[0] = rand() % 100;

            if (action == 1 && prob[0] > you->get_cr() && role != 2 && role != 4)
            {
                you->deal(you->get_dmg(), them);

                action = 0;
            }
            else if (action == 1 && prob[0] <= you->get_cr() && role == 4)
            {
                you->deal(you->get_dmg() + (you->get_crdmg()* 2), them);
                std::cout << you->get_id() << " dealed high critical damage" << std::endl;

                action = 0;
            }
            else if (action == 1 && prob[0] <= you->get_cr() && role != 2 && role != 4)
            {
                you->deal(you->get_dmg() * 2, them);
                std::cout << you->get_id() << " dealed critical damage" << std::endl;

                action = 0;
            }
            else if (action == 1 && role == 2)
            {
                you->deal(10, them);

                action = 0;
            }
            else if (action == 2)
            {
                you->heal(5);
                if (role == 2)
                {
                    you->healmana(5);
                }

                action = 0;
            }
            else if (action == 3 && you->get_role() == 2)
            {
                you->castSpell(them, 40);

                action = 0;
            }
            else if (action == 3 && you->get_role() == 3)
            {
                you->terry(them, 15);

                action = 0;
            }
            else if (action != 0 && action != 1 && action != 2 && action != 3)
            {
                std::cout << "Unknown command, choose carefully next time!" << std::endl << "Do not give up!" << std::endl;

                action = 0;
            }

            if (you->get_hp() <= 0 || them.get_hp() <= 0)
            {
                break;
            }

            prob[1] = rand() % 100;

            if (you->get_dod() <= you->get_chc() && you->get_role() == 3)
            {
                std::cout << you->get_id() << " dodged " << them.get_id() << " attack!" << std::endl;
                you->dodgeoff();
                continue;
            }
            else if (you->get_dod() > you->get_chc() && you->get_role() == 3)
            {
                std::cout << you->get_id() << " unsucessfully dodged" << std::endl;
            }

            if (prob[1] < 65 && prob[1] >= 15)
            {
                them.deal((30 - you->get_defense(0)), *you);
            }
            else if (prob[1] < 15)
            {
                them.deal((60 - you->get_defense(0)), *you);
                std::cout << them.get_id() << " dealed critical damage" << std::endl;
            }
            else if (prob[1] >= 65)
            {
                them.heal(10);
            }
            if (role == 3)
            {
                you->dodgeoff();
            }

            if (you->get_hp() <= 0 || them.get_hp() <= 0)
            {
                break;
            }
        }

        if (them.get_hp() <= 0)
        {
            std::cout << "You win!" << std::endl;
        }
        else
        {
            std::cout << "You lose" << std::endl;
        }

        std::cout << "Retry? 1 if yes other integer no" << std::endl;
        std::cin >> retry;
    }
};

int main()
{
    srand(time(NULL));
    int retry = 0;
    do
    {
        Game start;
        start.check_alloc();
        if (start.get_fail() == 1)
        {
        return 1;
        }
        start.play();
        retry = start.get_re();
        start.unleak();
    } while (retry = 1);
    
    std::cout << "Thanks for Playing!";
    return 0;
}