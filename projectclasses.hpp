#include <string>

using namespace std;

class Monster;
class Teamofmonsters;

class Item{
        string name;
        double price;
        int min_level;
        bool equipped;
    public:
        Item(string,double,int);
        virtual ~Item();
        string Getname();
        int Getprice();
        int Getlevel();
        bool Wearing();
        void Wearstatus(bool);
};

class Weapon: public Item{
        int damage;
        int hands;
    public:
        Weapon(string,double,int,int,int);
        ~Weapon();
        int Getdamage();
        int Gethands();
};

class Armor: public Item{
        int protection;
    public:
        Armor(string,double,int,int);
        ~Armor();
        int Getprotection();
};

class Potion: public Item{
        string stat;
        int increase;
    public:
        Potion(string,double,int,string,int);
        ~Potion();
        string Getstat();
        int Getincrease();

};




class Spell{
        string name;
        double price;
        int min_level;
        int min_damage;
        int max_damage;
        int spellmana;
    public:
        Spell(string,double,int,int,int,int);
        virtual ~Spell();
        string Getname();
        int Getprice();
        int Getlevel();
        int Getmana();
        int Getmindam();
        int Getmaxdam();
        virtual void Reduct(Monster *)=0;
};

class IceSpell: public Spell{
        int damage_reduction=30;
    public:
        IceSpell(string,double,int,int,int,int);
        ~IceSpell();
        void Reduct(Monster *);
};

class FireSpell: public Spell{
        int defence_reduction=30;
    public:
        FireSpell(string,double,int,int,int,int);
        ~FireSpell();
        void Reduct(Monster *);
};



class LightningSpell: public Spell{
        int avoid_reduction=30;
    public:
        LightningSpell(string,double,int,int,int,int);
        ~LightningSpell();
       void Reduct(Monster *);
};

class Living{
        string name;
        int level;
        int healthPower;
    public:
        Living(string,int);
        virtual ~Living();
        void Addlevel();
        int Getlevel();
        string Getname();
        void Revive();
        void Lowerhealth(int);
        int Gethealth();
        bool Isalive();
        void IncreaseHP();
};


class Hero: public Living{
        int mana=100;
        int strength;
        int dexterity;
        int agility;
        double money=100;
        int exp=0;
        int protection=0;
        Armor **armors;
        Weapon **weapons;
        Potion **potions;
        Spell **spells;
        int currentarmors;
        int currentweapons;
        int currentpotions;
        int currentspells;
        int max=5;
        int hands=0;
        int wearingarmor=0;
    public:
        Hero(string,int,int,int);
        virtual ~Hero();
        void levelUp();
        int Getstrength();
        int Getdexterity();
        int Getagility();
        int Getprotection();
        int Getmax();
        int Getcurweapons();
        int Getcurarmors();
        int Getcurpotions();
        int Getcurspells();
        void Displaystats();
        void Checkinventory();
        void Buyitem(Armor *);
        void Buyitem(Weapon *);
        void Buyitem(Potion *);
        void Buyspell(Spell *); 
        void Sellitem(Armor *);
        void Sellitem(Weapon *);
        void Sellitem(Potion *);
        void Sellspell(Spell *); 
        void Usepotion(Potion *);
        void Equip(Armor *);
        void Unequip(Armor *);
        void Equip(Weapon *);
        void Unequip(Weapon *);
        void Attack(Monster *);
        void Castspell(Spell *,Monster *);
        void Herorevive();
        void LowerHP(int);
        bool Hasspells();
        bool Haspotions();
        bool Hasarmors();
        bool Hasweapons();
        void Printspells();
        void Printarmors();
        void Printweapons();
        void Printpotions();
        Spell *Getspell(int);
        Potion *Getpotion(int);
        Armor *Getarmor(int);
        Weapon *Getweapon(int);
        void Halfmoney();
        void Increasemana();
        void Salary(int);
        void Increaseexp(int);
};

class Warrior:public Hero{
    public:
        Warrior(string);
        ~Warrior();
};

class Sorcerer:public Hero{
    public:
        Sorcerer(string);
        ~Sorcerer();
};

class Paladin:public Hero{
    public:
        Paladin(string);
        ~Paladin();
};

class Monster: public Living{
        int min_damage;
        int max_damage;
        int defence;
        double avoid_chance;
    public:
        Monster(string,int,int,int,int,double);
        virtual ~Monster();
        int Getmindam();
        int Getmaxdam();
        int Getdefence();
        double Getavoid();
        void Displaystats();
        void Attack(Hero *);
        void LowerHP(int);
        void Lowermaxdam(int);
        void Lowerdef(int);
        void Loweravoid(int);
        
};

class Dragon: public Monster{
    public:
        Dragon(string,int);
        ~Dragon();
};

class Exoskeleton: public Monster{
    public:
        Exoskeleton(string,int);
        ~Exoskeleton();
};

class Spirit: public Monster{
    public:
        Spirit(string,int);
        ~Spirit();
};

class Teamofheroes{
        Hero **Team;
        int currentheroes=0;
        int x,y;
    public:
        Teamofheroes();
        ~Teamofheroes();
        void Enterhero(Hero *);
        void Printteam();
        void Printinventory();
        Hero *member(int);
        bool Lost();
        int Getcurrent();
        int Getx();
        int Gety();
        void Setx(int);
        void Sety(int);
        void Battle(Teamofmonsters *);
};

class Teamofmonsters{
        Monster **monsters;
        int currentmonsters=0;
    public:
        Teamofmonsters();
        ~Teamofmonsters();
        void Entermonster(Monster *);
        void Printteam();
        void Printnames();
        Monster *member(int);
        int Getnumber();
        bool Lost();
};

class Tile{
        int x;
        int y;
    public:
        Tile(int,int);
        virtual ~Tile();
        virtual bool Enter(Teamofheroes *)=0;
        int Getx();
        int Gety();
};

class Common:public Tile{
        Teamofheroes *team;
        Teamofmonsters *foes;
        string monsternames[15];
    public:
        Common(int,int,string names[15]);
        ~Common();
        Teamofmonsters *Createmonsterteam();
        bool Enter(Teamofheroes *);       
};

class Market:public Tile{ 
        int max=5;
        Armor *armors[5];
        Weapon *weapons[5];
        Potion *potions[5];
        Spell *spells[15];
    public:
        Market(int,int,Armor *ar[5],Weapon *we[5],Potion *po[5],Spell *sp[15]);
        ~Market();
        void Printspells();
        void Printarmors();
        void Printweapons();
        void Printpotions();
        int Getspells();
        int Getarmors();
        int Getpotions();
        int Getweapons();
        void Enterspell(Spell *);
        void Enterpotion(Potion *);
        void Enterweapon(Weapon *);
        void Enterarmor(Armor *);
        bool Enter(Teamofheroes *);
};

class NonAccessible:public Tile{
    public:
        NonAccessible(int,int);
        ~NonAccessible();
        bool Enter(Teamofheroes *);
};

class Grid{
        Teamofheroes *team;
        Tile *map[5][10];
        char matrix[5][10]= {
            {'x','x','x','x','x','x','x','x','x','x'},
            {'s','m','c','c','c','c','c','c','c','x'},
            {'x','c','c','c','c','c','c','m','c','x'},
            {'x','c','c','c','m','c','c','c','c','x'},
            {'x','x','x','x','x','x','x','x','x','x'}
            };
        string monsternames[30]  = {"Urogalan","Vergadain","Ye'Cind","Yondalla","Annam",
                "Bahamut","Blibdoolpoolp","Diirinka","Eadro","Great Mother",
                "Grolantor","Hiatea","Iallanis","Ilneval","Io",
                "Karontor","Kiaransalee","Khurgorbaeyag","Luthic","Memnor",
                "Nomog-Geaya","Gruumsh","Hruggek","Ilsensine","Jubilex",
                "Skerrit","Lolth","Orcus","Sekolah","Shekinester"};
        string  itemnames[30] = {"Excalibur","Ragnarok","Balmung","Save the Queen","Heartbreaker",
                "Vendetta","Avenger","Vigilante","Dance Macabre","Punisher",
                "Soldier's Shield","Mage's Shield","Silver Shield","Onyx Shield","Sorcery Shield",
                "Warrior's Shield","Glorious Shield","Metal Shield","Magic Shield","Seeker's Shield",
                "Nomog-Geaya","Gruumsh","Hruggek","Ilsensine","Jubilex",
                "Skerrit","Lolth","Orcus","Sekolah","Shekinester"};
        string spellnames[30] = {"Breath of Suitengu","The Inner Ocean","Surging Soul","Endless Depth","Kharmic Intent",
                "Whispered Blade","Arrow of Purity","Blazing Arrows","Burn the Soul","Fire Wings",
                "Siphon","Void","Bolt Strike","Freeze Wave","Inferno Blaze",
                "Inferno","Fireball","Explosion","Meteor","Dragon Fire",
                "Tempest","Whirlwhind","Cyclone""Vortex","Wyvern’s Wings",
                "Shock","Bolt","Plasma","Gust","Gale"};
        Weapon *weapons[10];
        Armor *armors[10];
        Potion *potions[10];
        IceSpell *icespells[10];
        FireSpell *firespells[10];
        LightningSpell *lightningspells[10];
    public:
        Grid();
        ~Grid();
        void Print();
        void StartGame();
        void Traverse();
};