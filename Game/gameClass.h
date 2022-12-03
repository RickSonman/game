#pragma once
class Player;
class Monster;
class Creature
{
public:
    Creature(const std::string& name, char sym, int hp, int damage, int gold_count);
    ~Creature();
    std::string getName();
    char getSymbol();
    int	getHealth();
    int	getDamage();
    int	getGold();
    void reduceHealth(int hp);
    bool isDead();
    void addGold(int gold);

protected:
    std::string m_name;
    char m_symbol;
    int m_hp;
    int m_damage;
    int m_gold_count;
};

class Player : public Creature
{
public:
    Player(const std::string& name);
    ~Player();
    void levelUp();
    int getLevel();
    bool hasWon();

private:
    int m_level;
};

class Monster : public Creature
{

public:
    enum class Type
    {
        DRAGON,
        ORC,
        SLIME,
        MAX_TYPES
    };

    struct MonsterData
    {
        std::string name;
        char symbol;
        int health;
        int damage;
        int gold;
    };

    static MonsterData monsterData[(unsigned int)Type::MAX_TYPES];
    static Type getRandomMonster();
    Monster(Type type);
    ~Monster();

};

void fightMonster(Player& p, Monster& m);
void play(Player& p);