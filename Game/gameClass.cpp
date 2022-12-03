#include <iostream>
#include "gameClass.h"
#include <cstdlib> 
#include <ctime>

Creature::Creature(const std::string& name, char sym, int hp, int damage, int gold_count)
    : m_name(name), m_symbol(sym), m_hp(hp), m_damage(damage), m_gold_count(gold_count)
{

}

Creature::~Creature()
{
}

std::string Creature::getName()
{
    return m_name;
}
char Creature::getSymbol()
{
    return m_symbol;
}
int	Creature::getHealth()
{
    return m_hp;
}
int	Creature::getDamage()
{
    return m_damage;
}
int	Creature::getGold()
{
    return m_gold_count;
}

void Creature::reduceHealth(int hp)
{
    m_hp -= hp;
}

bool Creature::isDead()
{
    return m_hp <= 0;
}

void Creature::addGold(int gold)
{
    m_gold_count += gold;
}

void fightMonster(Player& p, Monster& m)
{
    if (!p.isDead())
        std::cout << "\nYou have " << p.getHealth() << " hp\n";
    std::cout << "You hit the " << m.getName() << " for " << p.getDamage() << " damage \n";
    m.reduceHealth(p.getDamage());
    if (!m.isDead()) {
        std::cout << "the " << m.getName() << " has " << m.getHealth() << " hp\n";
        std::cout << "\nThe " << m.getName() << " hit you for " << m.getDamage() << " damage \n";
        p.reduceHealth(m.getDamage());
        std::cout << "You have " << p.getHealth() << " hp\n";
    }
    else {
        std::cout << "You killed the " << m.getName();
        p.levelUp();
        p.addGold(m.getGold());
        std::cout << ". You are now level " << p.getLevel() << ". You found " << m.getGold() << " gold. Your gold count is " << p.getGold() << ". Your health is " <<p.getHealth()<<"\n";
    }
}

void play(Player& p)
{
    Monster m = Monster::getRandomMonster();
    std::cout << "\nYou have encountered a";
    (m.getName() == "orc") ?
        std::cout << "n " << m.getName() << " (" << m.getSymbol() << ") was created.\n" :
        std::cout << " " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
    char sym;
    while (!p.isDead() && !m.isDead()) {
        std::cout << "\n(R)un or (F)ight?\n";
        std::cin >> sym;
        if (sym == 'R' || sym == 'r') {
            if (rand() % 2 == 1) {
                std::cout << "\nYou successfully fled.\n";
                break;
            }
            else {
                std::cout << "\nOh, no! You couldn't do that! The " << m.getName() << " hit you for " << m.getDamage() << " damage \n";
                p.reduceHealth(m.getDamage());
                std::cout << "You have " << p.getHealth() << " hp\n";
            }
        }
        else  if (sym == 'F' || sym == 'f') {
            fightMonster(p, m);
        }

        else {
            std::cout << "You wrote wrong!\n";
        }
    }
}

Player::Player(const std::string& name)
    : Creature(name, '@', 10, 1, 0)
    , m_level(1)
{

}

Player::~Player()
{
}

void Player::levelUp()
{
    m_level++;
    m_hp++;
    m_damage++;
}

int Player::getLevel()
{
    return m_level;
}

bool Player::hasWon()
{
    return (m_level >= 20);
}


Monster::Monster(Type type)
    : Creature(monsterData[(unsigned int)type].name
        , monsterData[(unsigned int)type].symbol
        , monsterData[(unsigned int)type].health
        , monsterData[(unsigned int)type].damage
        , monsterData[(unsigned int)type].gold)
{
}

Monster::~Monster()
{
}

Monster::MonsterData Monster::monsterData[(unsigned int)Monster::Type::MAX_TYPES]
{
    {"dragon", 'D', 20, 4, 100},
    {"orc",'o',4,2,25 },
    {"slime",'s',1,1,10 },
};

Monster::Type Monster::getRandomMonster()
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем генерацию значения из диапазона
    return static_cast<Monster::Type>(rand() * fraction * (((int)Monster::Type::MAX_TYPES - 1) - 0 + 1) + 0);
}

