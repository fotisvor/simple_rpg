#include <iostream>
#include <string>
#include <ctime>
#include "projectclasses.hpp"

using namespace std;



Item::Item(string in_name,double in_price,int in_min_level){
    name=in_name;
    price=in_price;
    min_level=in_min_level;
    equipped=false;
}

Item::~Item(){}

string Item::Getname(){
    return name;
}

int Item::Getprice(){return price;}
int Item::Getlevel(){return min_level;}
bool Item::Wearing(){return equipped;}
void Item::Wearstatus(bool x){equipped=x;}

Armor::Armor(string in_name,double in_price,int in_min_level,int in_prot):Item(in_name,in_price,in_min_level){
    protection=in_prot;
}

Armor::~Armor(){}

int Armor::Getprotection(){return protection;}

Weapon::Weapon(string in_name,double in_price,int in_min_level,int in_damage,int in_hands):Item(in_name,in_price,in_min_level){
    damage=in_damage;
    hands=in_hands;
}

Weapon::~Weapon(){}

int Weapon::Getdamage(){return damage;}
int Weapon::Gethands(){return hands;}

Potion::Potion(string in_name,double in_price,int in_min_level,string in_stat,int in_inc):Item(in_name,in_price,in_min_level){
    stat=in_stat;
    increase=in_inc;
}

Potion::~Potion(){}

string Potion::Getstat(){return stat;}
int Potion::Getincrease(){return increase;}

Spell::Spell(string in_name,double in_price,int in_min_level,int in_min,int in_max,int in_mana){
    name=in_name;
    price=in_price;
    min_level=in_min_level;
    min_damage=in_min;
    max_damage=in_max;
    spellmana=in_mana;
}

Spell::~Spell(){}

string Spell::Getname(){return name;}
int Spell::Getprice(){return price;}
int Spell::Getlevel(){return min_level;}
int Spell::Getmana(){return spellmana;}
int Spell::Getmindam(){return min_damage;}
int Spell::Getmaxdam(){return max_damage;}

IceSpell::IceSpell(string in_name,double in_price,int in_min_level,int in_min,int in_max,int in_mana):Spell(in_name,in_price,in_min_level,in_min,in_max,in_mana){}
IceSpell::~IceSpell(){}

void IceSpell::Reduct(Monster *foe){
    foe->Lowermaxdam(damage_reduction);
}

FireSpell::FireSpell(string in_name,double in_price,int in_min_level,int in_min,int in_max,int in_mana):Spell(in_name,in_price,in_min_level,in_min,in_max,in_mana){}
FireSpell::~FireSpell(){}

void FireSpell::Reduct(Monster *foe){
    foe->Lowerdef(defence_reduction);
}

LightningSpell::LightningSpell(string in_name,double in_price,int in_min_level,int in_min,int in_max,int in_mana):Spell(in_name,in_price,in_min_level,in_min,in_max,in_mana){}
LightningSpell::~LightningSpell(){}

void LightningSpell::Reduct(Monster *foe){
    foe->Loweravoid(avoid_reduction);
}

Living::Living(string in_name,int in_level){
    name=in_name;
    level=in_level;
    healthPower=100;
}

Living::~Living(){}

string Living::Getname(){
    return name;
}

int Living::Getlevel(){
    return level;
}

void Living::Addlevel(){
    level++;
}

int Living::Gethealth(){
    return healthPower;
}

bool Living::Isalive(){
    if(healthPower<=0)
        return false;
    return true;
}

void Living::IncreaseHP(){
    healthPower+=15;
    if(healthPower>100)
        healthPower=100;
}

Hero::Hero(string in_name,int in_str,int in_dex,int in_agil):Living(in_name,1){
    strength=in_str;
    dexterity=in_dex;
    agility=in_agil;
    currentarmors=0;
    currentpotions=0;
    currentspells=0;
    currentweapons=0;
    armors=new Armor*[max];
    for(int i=0;i<max;i++)
        armors[i]=NULL;
    weapons=new Weapon*[max];
    for(int i=0;i<max;i++)
        weapons[i]=NULL;
    potions=new Potion*[max];
    for(int i=0;i<max;i++)
        potions[i]=NULL;
    spells=new Spell*[max];
    for(int i=0;i<max;i++)
        spells[i]=NULL;
}

Hero::~Hero(){}

void Hero::Displaystats(){
    cout<<"Hero's name is: "<<this->Getname()<<endl;
    cout<<"level: "<<this->Getlevel()<<endl;
    cout<<"health: "<<this->Gethealth()<<endl;
    cout<<"magic power: "<<mana<<endl;
    cout<<"strength: "<<strength<<endl;
    cout<<"dexterity: "<<dexterity<<endl;
    cout<<"agility: "<<agility<<endl;
    cout<<"balance: "<<money<<" coins"<<endl;
    cout<<"experience: "<<exp<<endl;
}

void Hero::levelUp(){
    this->Addlevel();
    strength+=10;
    dexterity+=7;
    agility+=5;
    if(agility>99)
        agility=99;
    cout<<this->Getname()<<" has leveled up and is now level "<<this->Getlevel()<<"!"<<endl;
}

void Hero::Salary(int x){
    money+=this->Getlevel()*x*5;
}

void Hero::Increaseexp(int x){
    exp+=this->Getlevel()*x*20;
    if(exp>=this->Getlevel()*100){
        exp-=this->Getlevel()*100;
        this->levelUp();
    }
}

int Hero::Getstrength(){return strength;}
int Hero::Getdexterity(){return dexterity;}
int Hero::Getagility(){return agility;}
int Hero::Getprotection(){return protection;}
int Hero::Getcurarmors(){return currentarmors;}
int Hero::Getcurweapons(){return currentweapons;}
int Hero::Getcurpotions(){return currentpotions;}
int Hero::Getcurspells(){return currentspells;}

void Hero::Checkinventory(){
    cout<<"Hero is in possesion of these items:"<<endl;
    cout<<"Weapons:"<<endl;
    int i=0;
    while((weapons[i]!=NULL)&&(i<max)){
        cout<<weapons[i]->Getname()<<endl;
        i++;
    }
    cout<<"Armors:"<<endl;
    i=0;
    while((armors[i]!=NULL)&&(i<max)){
        cout<<armors[i]->Getname()<<endl;
        i++;
    }
    cout<<"Potions:"<<endl;
    i=0;
    while((potions[i]!=NULL)&&(i<max)){
        cout<<potions[i]->Getname()<<endl;
        i++;
    }
    cout<<"Hero is in possesion of these spells:"<<endl;
    i=0;
    while((spells[i]!=NULL)&&(i<max)){
        cout<<spells[i]->Getname()<<endl;
        i++;
    }
}

void Hero::Buyitem(Weapon *newweapon){
    if(currentweapons<max-1){    
        if(money>=newweapon->Getprice()&&this->Getlevel()>=newweapon->Getlevel()){
            currentweapons++;
            money-=newweapon->Getprice();
            for(int i=0;i<max;i++){
                if(weapons[i]==NULL){
                    weapons[i]=newweapon;
                    break;
                }  
            }
            cout<<"Successful purchase!"<<endl;
        }
        else if(money<newweapon->Getprice())
            cout<<"not enough money to buy this item"<<endl;
        else
            cout<<"you need to be level "<<newweapon->Getlevel()<<" in order to buy this item"<<endl;
    }
    else
        cout<<"Your weapon bag is full,purchase was unsuccessful"<<endl;
}

void Hero::Buyitem(Armor *newarmor){
    if(currentarmors<max-1){    
        if(money>=newarmor->Getprice()&&this->Getlevel()>=newarmor->Getlevel()){
            currentarmors++;
            money-=newarmor->Getprice();
            for(int i=0;i<max;i++){
                if(armors[i]==NULL){
                    armors[i]=newarmor;
                    break;
                }  
            }
            cout<<"Successful purchase!"<<endl;
        }
        else if(money<newarmor->Getprice())
            cout<<"not enough money to buy this item"<<endl;
        else
            cout<<"you need to be level "<<newarmor->Getlevel()<<" in order to buy this item"<<endl;
    }
    else
        cout<<"Your weapon bag is full,purchase was unsuccessful"<<endl;
}

void Hero::Buyitem(Potion *newpotion){
    if(currentpotions<max-1){    
        if(money>=newpotion->Getprice()&&this->Getlevel()>=newpotion->Getlevel()){
            currentweapons++;
            money-=newpotion->Getprice();
            for(int i=0;i<max;i++){
                if(potions[i]==NULL){
                    potions[i]=newpotion;
                    break;
                }  
            }
            cout<<"Successful purchase!"<<endl;
        }
        else if(money<newpotion->Getprice())
            cout<<"not enough money to buy this item"<<endl;
        else
            cout<<"you need to be level "<<newpotion->Getlevel()<<" in order to buy this item"<<endl;
    }
    else
        cout<<"Your weapon bag is full,purchase was unsuccessful"<<endl;
}

void Hero::Buyspell(Spell *newspell){
    if(currentspells<max-1){    
        if(money>=newspell->Getprice()&&this->Getlevel()>=newspell->Getlevel()){   
            currentspells++;
            money-=newspell->Getprice();
            for(int i=0;i<max;i++){
                if(spells[i]==NULL){
                    spells[i]=newspell;
                    break;
                }  
            }
            cout<<"Successful purchase!"<<endl;
        }
        else if(money<newspell->Getprice())
            cout<<"not enough money to buy this spell"<<endl;
        else
            cout<<"you need to be level "<<newspell->Getlevel()<<" in order to buy this spell"<<endl;
    }
    else
        cout<<"Your spell bag is full,purchase was unsuccessful"<<endl;
}

void Hero::Sellitem(Armor *selling){
    for(int i=0;i<max;i++){
        if(armors[i]==selling){
            armors[i]=NULL;
            break;
        }  
    }
    currentarmors--;
    money+=selling->Getprice()/2;
    cout<<"just sold "<<selling->Getname()<<" for "<<selling->Getprice()/2<<" coins"<<endl;
}

void Hero::Sellitem(Weapon *selling){
    for(int i=0;i<max;i++){
        if(weapons[i]==selling){
            weapons[i]=NULL;
            break;
        }  
    }
    currentweapons--;
    money+=selling->Getprice()/2;
    cout<<"just sold "<<selling->Getname()<<" for "<<selling->Getprice()/2<<" coins"<<endl;
}

void Hero::Sellitem(Potion *selling){
    for(int i=0;i<max;i++){
        if(potions[i]==selling){
            potions[i]=NULL;
            break;
        }  
    }
    currentpotions--;
    money+=selling->Getprice()/2;
    cout<<"just sold "<<selling->Getname()<<" for "<<selling->Getprice()/2<<" coins"<<endl;
}

void Hero::Sellspell(Spell *selling){
    for(int i=0;i<max;i++){
        if(spells[i]==selling){
            spells[i]=NULL;
            break;
        }  
    }
    currentspells--;
    money+=selling->Getprice()/2;
    cout<<"just sold "<<selling->Getname()<<" for "<<selling->Getprice()/2<<" coins"<<endl;
}

void Hero::Equip(Armor *arm){
    if(!arm->Wearing()){    
        if(wearingarmor<2){
            protection+=arm->Getprotection();
            wearingarmor++;
            arm->Wearstatus(true);
            cout<<"wearing "<<arm->Getname()<<endl;
        }
        else
            cout<<"already wearing armor"<<endl; 
    }
    else
        cout<<"already wearing "<<arm->Getname()<<endl;
}

void Hero::Unequip(Armor *unarm){
    if(unarm->Wearing()){    
        protection-=unarm->Getprotection();
        wearingarmor--;
        unarm->Wearstatus(false);
        cout<<"unequiped "<<unarm->Getname()<<endl;
    }
    else
        cout<<"hero has not equipped this armor"<<endl;
}

void Hero::Equip(Weapon *arm){
    if(!arm->Wearing()){    
        if(!hands){
            strength+=arm->Getdamage();
            hands=arm->Gethands();
            arm->Wearstatus(true);
            cout<<"equiped "<<arm->Getname()<<endl;
        }
        else if(hands==1){
            if(arm->Gethands()==1){
                strength+=arm->Getdamage();
                hands++;
                arm->Wearstatus(true);
                cout<<"equiped "<<arm->Getname()<<endl;
            }
            cout<<"hands are full,could not equip "<<arm->Getname()<<endl;
        }
        else
            cout<<"hands are full,could not equip "<<arm->Getname()<<endl;  
    }
    else
        cout<<"already wearing "<<arm->Getname()<<endl;
}

void Hero::Unequip(Weapon *unarm){
    if(unarm->Wearing()){    
        strength-=unarm->Getdamage();
        hands-=unarm->Gethands();
        unarm->Wearstatus(false);
        cout<<"unequiped "<<unarm->Getname()<<endl;
    }
    else
        cout<<"Hero has not equipped this weapon"<<endl;
}

void Living::Revive(){
    healthPower=50;
}

void Hero::Herorevive(){
    this->Revive();
}

void Living::Lowerhealth(int x){
    healthPower-=x;
}

void Monster::LowerHP(int x){
    this->Lowerhealth(x);
}

int Hero::Getmax(){return max;}

bool Hero::Hasspells(){
    for(int i=0;i<max;i++){
        if(spells[i]!=NULL)
            return true;
    }
    return false;
}

bool Hero::Haspotions(){
    for(int i=0;i<max;i++){
        if(potions[i]!=NULL)
            return true;
    }
    return false;
}

bool Hero::Hasweapons(){
    for(int i=0;i<max;i++){
        if(weapons[i]!=NULL)
            return true;
    }
    return false;
}

bool Hero::Hasarmors(){
    for(int i=0;i<max;i++){
        if(armors[i]!=NULL)
            return true;
    }
    return false;
}

void Hero::Printspells(){
    for(int i=0;i<max;i++){
        if(spells[i]!=NULL)
            cout<<i+1<<": "<<spells[i]->Getname()<<endl;
    }
}

void Hero::Printarmors(){
    for(int i=0;i<max;i++){
        if(armors[i]!=NULL)
            cout<<i+1<<": "<<armors[i]->Getname()<<endl;
    }
}

void Hero::Printweapons(){
    for(int i=0;i<max;i++){
        if(weapons[i]!=NULL)
            cout<<i+1<<": "<<weapons[i]->Getname()<<endl;
    }
}

void Hero::Printpotions(){
    for(int i=0;i<max;i++){
        if(potions[i]!=NULL)
            cout<<i+1<<": "<<potions[i]->Getname()<<endl;
    }
}

Spell *Hero::Getspell(int i){
    if(i<currentspells){
        return spells[i];
    }
    else
        cout<<"number you gave does not match a spell "<<endl;
    return NULL;   
}

Potion *Hero::Getpotion(int i){
    if(potions[i]!=NULL)
        return potions[i];
    else
        cout<<"number you gave does not match a potion "<<endl;
    return NULL;   
}

Weapon *Hero::Getweapon(int i){
    if(weapons[i]!=NULL)
        return weapons[i];
    else
        cout<<"number you gave does not match a weapon "<<endl;
    return NULL;   
}

Armor *Hero::Getarmor(int i){
    if(armors[i]!=NULL)
        return armors[i];
    else
        cout<<"number you gave does not match an armor "<<endl;
    return NULL;   
}

void Hero::Halfmoney(){
    money/=2;
}

void Hero::Increasemana(){
    mana+=20;
    if(mana>100)
        mana=100;
}

void Hero::Attack(Monster *beast){
    srand(time(NULL));
    int x=rand()%strength;
    x+=10;
    if(x>=beast->Getdefence())
        x-=beast->Getdefence();
    int y=rand()%(int)(1/beast->Getavoid());
    cout<<"Hero "<<this->Getname()<<" attacked "<<beast->Getname()<<" !"<<endl;
    if(y){
        beast->Lowerhealth(x);
        cout<<"Attack was successful,"<<beast->Getname()<<" lost "<<x<<" health!"<<endl;
        if(x==strength)
            cout<<"It was a critical hit!"<<endl;
    }
    else
        cout<<beast->Getname()<<" avoided the attack!"<<endl;
}

void Hero::Usepotion(Potion *p){
    cout<<this->Getname()<<" used "<<p->Getname()<<endl;
    if(p->Getstat()=="strength")
        strength+=p->Getincrease();
    else if(p->Getstat()=="mana")
        mana+=p->Getincrease();
    else if(p->Getstat()=="agility")
        agility+=p->Getincrease();
    else 
        dexterity+=p->Getincrease();
    for(int i=0;i<max;i++){
        if(potions[i]==p){
            potions[i]=NULL;
            currentpotions--;
            break;
        }  
    }
}

void Hero::Castspell(Spell *s,Monster *beast){
    if(mana>=s->Getmana()){
        mana-=s->Getmana();
        int x=rand()%((s->Getmaxdam())-(s->Getmindam()));
        x+=s->Getmindam();
        if(x>=beast->Getdefence())
            x-=beast->Getdefence();
        int y=rand()%(int)(beast->Getavoid()*100);
        cout<<"Hero "<<this->Getname()<<" used "<<s->Getname()<<" !"<<endl;
        if(y){
            beast->Lowerhealth(x);
            s->Reduct(beast);
            cout<<"Attack was successful,"<<beast->Getname()<<" lost "<<x<<" health!"<<endl;
            if(x==strength)
                cout<<"It was a critical hit!"<<endl;
        }
        else
            cout<<beast->Getname()<<" avoided the attack!"<<endl;   
    }
    else 
        cout<<"not enough magic power to use this spell"<<endl;
}

Warrior::Warrior(string in_name):Hero(in_name,40,20,40){}

Warrior::~Warrior(){}


Sorcerer::Sorcerer(string in_name):Hero(in_name,20,40,40){}

Sorcerer::~Sorcerer(){}



Paladin::Paladin(string in_name):Hero(in_name,40,40,20){}

Paladin::~Paladin(){}


Monster::Monster(string in_name,int in_level,int in_min,int in_max,int in_def,double in_avoid):Living(in_name,in_level){
    min_damage=in_min;
    max_damage=in_max;
    defence=in_def;
    avoid_chance=in_avoid/100;
}

Monster::~Monster(){}

int Monster::Getmindam(){return min_damage;}
int Monster::Getdefence(){return defence;}
int Monster::Getmaxdam(){return max_damage;}
double Monster::Getavoid(){return avoid_chance;}

void Monster::Lowermaxdam(int x){
    max_damage-=x;
}

void Monster::Lowerdef(int x){
    defence-=x;
}

void Monster::Loweravoid(int x){
    avoid_chance-=(double)x/100;
    if(avoid_chance<0.01)
        avoid_chance=0.01;
}


    
void Monster::Displaystats(){
    cout<<"monster name: "<<this->Getname()<<endl;
    cout<<"level: "<<this->Getlevel()<<endl;
    cout<<"health:"<<this->Gethealth()<<endl;
    cout<<"damage range: "<<min_damage<<" to "<<max_damage<<endl;
    cout<<"defence: "<<defence<<endl;
    cout<<"possibility to avoid attacks: "<<avoid_chance*100<<"%"<<endl; 
}

void Monster::Attack(Hero *foe){
    srand(time(NULL));
    int x=rand()%(max_damage-min_damage)+min_damage;
    if(x>=foe->Getprotection())
        x-=foe->Getprotection();
    int y=rand()%(int)(100/(double)(foe->Getagility()));
    cout<<"Monster "<<this->Getname()<<" attacked "<<foe->Getname()<<" !"<<endl;
    if(y){
        foe->Lowerhealth(x);
        cout<<"Attack was successful,"<<foe->Getname()<<" lost "<<x<<" health!"<<endl;
        if(x==max_damage)
            cout<<"It was a critical hit!"<<endl;
    }
    else
        cout<<foe->Getname()<<" avoided the attack!"<<endl;
}

Dragon::Dragon(string in_name,int in_level):Monster(in_name,in_level,10+2*(in_level-1),25+2*(in_level-1),5+(in_level-1),double(5+2*(in_level-1))){

}

Dragon::~Dragon(){cout<<"ddd"<<endl;}


Exoskeleton::Exoskeleton(string in_name,int in_level):Monster(in_name,in_level,5+2*(in_level-1),15+2*(in_level-1),15+(in_level-1),double(5+2*(in_level-1))){
}

Exoskeleton::~Exoskeleton(){cout<<"eee"<<endl;}



Spirit::Spirit(string in_name,int in_level):Monster(in_name,in_level,5+2*(in_level-1),15+2*(in_level-1),5+(in_level-1),double(10+2*(in_level-1))){
}

Spirit::~Spirit(){cout<<"sss"<<endl;}

Teamofheroes::Teamofheroes(){
    Team=new Hero*[3];
    for(int i=0;i<3;i++)
        Team[i]=NULL;
}

Teamofheroes::~Teamofheroes(){
    for(int i=0;i<currentheroes;i++)
        delete Team[i];
}

void Teamofheroes::Enterhero(Hero *candidate){
    Team[currentheroes]=candidate;
    currentheroes++;
}

void Teamofheroes::Printteam(){
    cout<<"Hero team consists of:"<<endl;
    int i=0;
    while((Team[i]!=NULL)&&(i<3)){
        cout<<i+1<<". ";
        Team[i]->Displaystats();
        i++;
    }
}

void Teamofheroes::Printinventory(){
    cout<<"Hero team possesses:"<<endl;
    int i=0;
    while((Team[i]!=NULL)&&(i<3)){
        cout<<Team[i]->Getname()<<": "<<endl;
        Team[i]->Checkinventory();
        i++;
    }
}

Hero *Teamofheroes::member(int i){
    if(i<3)
        return Team[i];
    else
        cout<<"given index is out of bounds"<<endl;
    return NULL;
}

bool Teamofheroes::Lost(){
    for(int i=0;i<currentheroes;i++){
        if(Team[i]->Gethealth()>0)
            return false;
    }
    return true;
} 

void Teamofheroes::Battle(Teamofmonsters *foes){
    cout<<"A battle has begun!!!"<<endl;
    foes->Printteam();
    while(!(this->Lost())&&!(foes->Lost())){
        cout<<"Its your turn!"<<endl;
        for(int i=0;i<currentheroes;i++){
            if(Team[i]->Isalive()&&!(foes->Lost())){    
                cout<<"what is "<<Team[i]->Getname()<<" going to do?"<<endl;
                cout<<"A:Attack || C:Cast a spell || U:Use potion || E:Equip || UN:Unequip || D:Display hero stats"<<endl;
                string order;
                cin>>order;
                if(order=="A"){
                    cout<<"give the number of the monster you want to attack:"<<endl; 
                    foes->Printnames();
                    int number;
                    cin>>number;
                    while(number<1 || number>foes->Getnumber()){
                            cout<<"number does not match any creature please give a different one"<<endl;
                            cin>>number;
                    }
                    if(foes->member(number-1)->Isalive())
                        Team[i]->Attack(foes->member(number-1));
                    else{
                        cout<<"this monster has fainted choose another one"<<endl;
                        i--;
                    }
                    if(!foes->member(number-1)->Isalive())
                        cout<<foes->member(number-1)->Getname()<<" has fainted!"<<endl;
                }
                else if(order=="C"){
                    if(Team[i]->Hasspells()){
                        cout<<"give the number of the monster you want to cast a spell on:"<<endl; 
                        foes->Printnames();
                        int number;
                        cin>>number;
                        while(number<1 && number>foes->Getnumber()){
                            cout<<"number does not match any creature please give a different one"<<endl;
                            cin>>number;
                        }
                        cout<<"give number of spell you want to cast:"<<endl;
                        Team[i]->Printspells();
                        int spell;
                        cin>>spell;
                        Spell *s=Team[i]->Getspell(spell-1);
                        while(s==NULL){
                            cout<<"give different number:"<<endl;
                            cin>>spell;
                            s=Team[i]->Getspell(spell-1);
                        }
                        if(foes->member(number-1)->Isalive())
                            Team[i]->Castspell(s,foes->member(number-1)); 
                        else{
                            cout<<"this monster has fainted choose another one"<<endl;
                            i--;
                        }
                    }
                    else{
                        cout<<"hero has no spells available"<<endl;
                        i--;
                    }
                }
                else if(order=="U"){
                    if(Team[i]->Haspotions()){
                        cout<<"give number of potion you want to use"<<endl;
                        Team[i]->Printpotions();
                        int number;
                        cin>>number;
                        Potion *p=Team[i]->Getpotion(number-1);
                        while(p==NULL){
                            cout<<"give different number:"<<endl;
                            cin>>number;
                            p=Team[i]->Getpotion(number-1);
                        }
                        Team[i]->Usepotion(p);
                    }
                    else{
                        cout<<"hero has no potions available"<<endl;
                        i--;
                    }
                }
                else if(order=="E"){
                    cout<<"give: A for armor or W for Weapon"<<endl;
                    string equiping;
                    cin>>equiping;
                    if(equiping=="A"){
                        if(Team[i]->Hasarmors()){
                            cout<<"give number of armor you want to use"<<endl;
                            Team[i]->Printarmors();
                            int number;
                            cin>>number;
                            Armor *a=Team[i]->Getarmor(number-1);
                            while(a==NULL){
                                cout<<"give different number:"<<endl;
                                cin>>number;
                                a=Team[i]->Getarmor(number-1);
                            }
                            Team[i]->Equip(a);
                        }
                        else{
                            cout<<"hero has no armors available"<<endl;
                            i--;
                        }
                    }
                    else{
                        if(Team[i]->Hasweapons()){
                            cout<<"give number of weapon you want to use"<<endl;
                            Team[i]->Printweapons();
                            int number;
                            cin>>number;
                            Weapon *w=Team[i]->Getweapon(number-1);
                            while(w==NULL){
                                cout<<"give different number:"<<endl;
                                cin>>number;
                                w=Team[i]->Getweapon(number-1);
                            }
                            Team[i]->Equip(w);
                        }
                        else{
                            cout<<"hero has no weapons available"<<endl;
                            i--;
                        }
                    }
                }else if(order=="UN"){
                    cout<<"give: A for armor or W for Weapon"<<endl;
                    string unequiping;
                    cin>>unequiping;
                    if(unequiping=="A"){
                        if(Team[i]->Hasarmors()){
                            cout<<"give number of armor you want to unequip"<<endl;
                            Team[i]->Printarmors();
                            int number;
                            cin>>number;
                            Armor *a=Team[i]->Getarmor(number-1);
                            while(a==NULL){
                                cout<<"give different number:"<<endl;
                                cin>>number;
                                a=Team[i]->Getarmor(number-1);
                            }
                            Team[i]->Unequip(a);
                        }
                        else{
                            cout<<"hero has no armors available"<<endl;
                            i--;
                        }
                    }
                    else{
                        if(Team[i]->Hasweapons()){
                            cout<<"give number of weapon you want to unequip"<<endl;
                            Team[i]->Printweapons();
                            int number;
                            cin>>number;
                            Weapon *w=Team[i]->Getweapon(number-1);
                            while(w==NULL){
                                cout<<"give different number:"<<endl;
                                cin>>number;
                                w=Team[i]->Getweapon(number-1);
                            }
                            Team[i]->Unequip(w);
                        }
                        else{
                            cout<<"hero has no weapons available"<<endl;
                            i--;
                        }
                    }
                }
                else if(order=="D"){
                    cout<<"want to see stats of hero: H or monster: M?"<<endl;
                    string answer;
                    cin>>answer;
                    if(answer=="H"){
                        cout<<"give number between 1 and "<<currentheroes<<" of the hero you want to see:"<<endl;
                        int num;
                        cin>>num;
                        while(num<1 && num>currentheroes){
                            cout<<"number does not match any creature please give a different one"<<endl;
                            cin>>num;
                        }
                        Team[num-1]->Displaystats();
                        i--;
                    }
                    else if(answer=="M"){ 
                        cout<<"give number between 1 and "<<foes->Getnumber()<<" of the monster you want to see:"<<endl;
                        int num;
                        cin>>num;
                        while(num<1 && num>foes->Getnumber()){
                            cout<<"number does not match any creature please give a different one"<<endl;
                            cin>>num;
                        }
                        foes->member(num-1)->Displaystats();
                        i--;
                    }
                    else{
                        cout<<"this character doesn't match any order please give a different one"<<endl;
                        i--;
                    }
                }
                else{
                    cout<<"this character doesn't match any order please give a different one"<<endl;
                    i--;
                }
                
            }
            else
                cout<<Team[i]->Getname()<<" has fainted so he cannot attack"<<endl;
        }
        for(int i=0;i<foes->Getnumber();i++){
            if(foes->member(i)->Isalive()){   
                int x=rand()%currentheroes;
                foes->member(i)->Attack(Team[x]);
            }
            else
                cout<<"Monster "<<foes->member(i)->Getname()<<" has fainted so it cannot attack"<<endl;
        }
        for(int i=0;i<currentheroes;i++){
            if(Team[i]->Isalive()){    
                Team[i]->IncreaseHP();
                Team[i]->Increasemana();
            }
        }
        for(int i=0;i<foes->Getnumber();i++){
            if(foes->member(i)->Isalive())
                foes->member(i)->IncreaseHP();
        }
    }
    if(this->Lost()){
        cout<<"The battle was lost"<<endl;
        for(int i=0;i<currentheroes;i++)
            Team[i]->Halfmoney();
        
    }
    else{
        cout<<"Congratulations! The battle was won!"<<endl;
        for(int i=0;i<currentheroes;i++){
            Team[i]->Salary(foes->Getnumber());
            Team[i]->Increaseexp(foes->Getnumber());
        }
    }
    for(int i=0;i<currentheroes;i++){
        if(!Team[i]->Isalive())    
            Team[i]->Revive();
    }
}

int Teamofheroes::Getcurrent(){return currentheroes;}
int Teamofheroes::Getx(){return x;}
int Teamofheroes::Gety(){return y;}
void Teamofheroes::Setx(int inx){x=inx;}
void Teamofheroes::Sety(int iny){y=iny;}

Teamofmonsters::Teamofmonsters(){
    monsters=new Monster*[5];
    for(int i=0;i<5;i++)
        monsters[i]=NULL;
}

Teamofmonsters::~Teamofmonsters(){
    for(int i=0;i<currentmonsters;i++)
        delete monsters[i];
}

void Teamofmonsters::Entermonster(Monster *candidate){
    monsters[currentmonsters]=candidate;
    currentmonsters++;
}

Monster *Teamofmonsters::member(int i){
    if(i<5)
        return monsters[i];
    else
        cout<<"given index is out of bounds"<<endl;
    return NULL;
}

int Teamofmonsters::Getnumber(){return currentmonsters;}

void Teamofmonsters::Printteam(){
    cout<<"Monster team consists of:"<<endl;
    int i=0;
    while((monsters[i]!=NULL)&&(i<5)){
        monsters[i]->Displaystats();
        i++;
    }
}

void Teamofmonsters::Printnames(){
    int i=0;
    while((monsters[i]!=NULL)&&(i<5)){
        cout<<i+1<<": "<<monsters[i]->Getname()<<endl;
        i++;
    }
}

bool Teamofmonsters::Lost(){
    for(int i=0;i<currentmonsters;i++){
        if(monsters[i]->Gethealth()>0)
            return false;
    }
    return true;
} 

Tile::Tile(int inx,int iny){
    x=inx;
    y=iny;
}

Tile::~Tile(){}

int Tile::Getx(){return x;}
int Tile::Gety(){return y;}

Common::Common(int inx,int iny,string names[15]):Tile(inx,iny){
    team=NULL;
    foes=NULL;
    for(int i=0;i<15;i++)
        monsternames[i]=names[i];
    
}

Common::~Common(){}

bool Common::Enter(Teamofheroes *in_team){
    cout<<"team has moved to "<<this->Getx()+1<<","<<this->Gety()+1<<endl;
    team=in_team;
    srand(time(NULL));
    int x=rand()%5;
    if(!x){
        Teamofmonsters *foes=Createmonsterteam();
        team->Battle(foes);
        for(int i=0;i<foes->Getnumber();i++)
            foes->member(i)->~Monster();
    }
    return true;
}

Teamofmonsters *Common::Createmonsterteam(){
    int sum=0;
    for(int i=0;i<team->Getcurrent();i++)
        sum+=team->member(i)->Getlevel();
    int level=int(sum/team->Getcurrent());
    int x=rand()%5;
    Teamofmonsters *foes= new Teamofmonsters();
    for(int i=0;i<=x;i++){
        int y=rand()%15;
        Monster *newmonster;
        if(y<5)
            newmonster=new Dragon(monsternames[y],level);
        else if(y<10)
            newmonster=new Exoskeleton(monsternames[y],level);
        else
            newmonster=new Spirit(monsternames[y],level);
        foes->Entermonster(newmonster);
    }
    return foes;
}

Market::Market(int inx,int iny,Armor *ar[5],Weapon *we[5],Potion *po[5],Spell *sp[15]):Tile(inx,iny){
    for(int i=0;i<5;i++){
        weapons[i]=we[i];
        armors[i]=ar[i];
        potions[i]=po[i];
    }
    for(int i=0;i<15;i++){
        spells[i]=sp[i];
    }
}

Market::~Market(){}

void Market::Printarmors(){
    cout<<"Armors:"<<endl;
    int i=0;
    while((armors[i]!=NULL)&&(i<max)){
        cout<<i+1<<". "<<armors[i]->Getname()<<" price: "<<armors[i]->Getprice()<<" minimum level: "<<armors[i]->Getlevel()<<" protection: "<<armors[i]->Getprotection()<<endl;
        i++;
    }   
}

void Market::Printpotions(){
    cout<<"Potions:"<<endl;
    int i=0;
    while((potions[i]!=NULL)&&(i<max)){
        cout<<i+1<<". "<<potions[i]->Getname()<<" price: "<<potions[i]->Getprice()<<" minimum level: "<<potions[i]->Getlevel()<<" increase: "<<potions[i]->Getincrease()<<endl;
        i++;
    }
}

void Market::Printspells(){
    cout<<"Spells:"<<endl;
    int i=0;
    while((spells[i]!=NULL)&&(i<(max+10))){
        if(i==0)
            cout<<"Ice spells:"<<endl;
        else if(i==5)
            cout<<"Fire spells:"<<endl;
        else if(i==10)
            cout<<"Lightning spells:"<<endl;
        cout<<i+1<<". "<<spells[i]->Getname()<<" price: "<<spells[i]->Getprice()<<" minimum level: "<<spells[i]->Getlevel()<<" max damage: "<<spells[i]->Getmaxdam()<<" needed magic power: "<<spells[i]->Getmana()<<endl;
        i++;
    }
}

void Market::Printweapons(){
    int i=0;
    cout<<"Weapons: "<<endl;
    while((weapons[i]!=NULL)&&(i<max)){
        cout<<i+1<<". "<<weapons[i]->Getname()<<" price: "<<weapons[i]->Getprice()<<" minimum level: "<<weapons[i]->Getlevel()<<" damage: "<<weapons[i]->Getdamage()<<" needed hands: "<<weapons[i]->Gethands()<<endl;
        i++;
    }
}

void Market::Enterweapon(Weapon *item){
    for(int i=0;i<max;i++){
        if(weapons[i]==NULL){
            weapons[i]=item;
                break;
        }  
    }
}

void Market::Enterarmor(Armor *item){
    for(int i=0;i<max;i++){
        if(armors[i]==NULL){
            armors[i]=item;
                break;
        }  
    }
}

void Market::Enterpotion(Potion *item){
    for(int i=0;i<max;i++){
        if(potions[i]==NULL){
            potions[i]=item;
                break;
        }  
    }
}

void Market::Enterspell(Spell *item){
    for(int i=0;i<(max+5);i++){
        if(spells[i]==NULL){
            spells[i]=item;
                break;
        }  
    }
}

bool Market::Enter(Teamofheroes *team){
    cout<<"team has moved to "<<this->Getx()+1<<","<<this->Gety()+1<<endl;
    cout<<"Welcome to the market!!"<<endl;
    for(int i=0;i<team->Getcurrent();i++){
        cout<<"What do you want "<<team->member(i)->Getname()<<" to do?"<<endl;
        cout<<"Give: B:buy  ||  S:sell  ||  N:nothing"<<endl;
        char ans;
        cin>>ans;
        if(ans=='N')
            continue;
        else if(ans=='B'){
            cout<<"What do you want to buy?"<<endl;
            cout<<"Give: A:Armor  ||  W:Weapon  ||  P:Potion  ||  S:Spell"<<endl;
            char item;
            cin>>item;
            if(item=='A'){
                cout<<"give number of the armor you want to purchase:"<<endl;
                this->Printarmors();
                int num;
                cin>>num;
                while(num<1||num>max){
                    cout<<"give different number:"<<endl;
                    cin>>num;
                }
                team->member(i)->Buyitem(armors[num-1]);
                cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                char more;
                cin>>more;
                if(more=='Y')
                    i--;
            }
            else if(item=='W'){
                cout<<"give number of the weapon you want to purchase:"<<endl;
                this->Printweapons();
                int num;
                cin>>num;
                while(num<1||num>max){
                    cout<<"give different number:"<<endl;
                    cin>>num;
                }
                team->member(i)->Buyitem(weapons[num-1]);
                cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                char more;
                cin>>more;
                if(more=='Y')
                    i--;
            }
            else if(item=='P'){
                cout<<"give number of the potion you want to purchase:"<<endl;
                this->Printpotions();
                int num;
                cin>>num;
                while(num<1||num>max){
                    cout<<"give different number:"<<endl;
                    cin>>num;
                }
                team->member(i)->Buyitem(potions[num-1]);
                cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                char more;
                cin>>more;
                if(more=='Y')
                    i--;
            }
            else if(item=='S'){
                cout<<"give number of the spell you want to purchase:"<<endl;
                this->Printspells();
                int num;
                cin>>num;
                while(num<1||num>max+10){
                    cout<<"give different number:"<<endl;
                    cin>>num;
                }
                team->member(i)->Buyspell(spells[num-1]);
                cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                char more;
                cin>>more;
                if(more=='Y')
                    i--;
            }
            else{
                cout<<"Please give a valid character"<<endl;
                i--;
            }
        }
        else if(ans=='S'){
            cout<<"What do you want to sell?"<<endl;
            cout<<"Give: A:Armor  ||  W:Weapon  ||  P:Potion  ||  S:Spell"<<endl;
            char item;
            cin>>item;
            if(item=='A'){
                if(team->member(i)->Hasarmors()){    
                    cout<<"give number of the armor you want to sell:"<<endl;
                    team->member(i)->Printarmors();
                    int num;
                    cin>>num;
                    while(num<1||num>team->member(i)->Getcurarmors()){
                        cout<<"give different number:"<<endl;
                        cin>>num;
                    }
                    Armor *a = team->member(i)->Getarmor(num-1);
                    team->member(i)->Sellitem(a);
                    cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                    char more;
                    cin>>more;
                    if(more=='Y')
                        i--;
                }
                else
                    cout<<"this hero has no armors to sell"<<endl;
            }
            else if(item=='W'){
                if(team->member(i)->Hasweapons()){    
                    cout<<"give number of the weapon you want to sell:"<<endl;
                    team->member(i)->Printweapons();
                    int num;
                    cin>>num;
                    while(num<1||num>team->member(i)->Getcurweapons()){
                        cout<<"give different number:"<<endl;
                        cin>>num;
                    }
                    Weapon *a = team->member(i)->Getweapon(num-1);
                    team->member(i)->Sellitem(a);
                    cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                    char more;
                    cin>>more;
                    if(more=='Y')
                        i--;
                }
                else
                    cout<<"hero has no weapons to sell"<<endl;
            }
            else if(item=='P'){
                if(team->member(i)->Haspotions()){    
                    cout<<"give number of the potion you want to sell:"<<endl;
                    team->member(i)->Printpotions();
                    int num;
                    cin>>num;
                    while(num<1||num>team->member(i)->Getcurpotions()){
                        cout<<"give different number:"<<endl;
                        cin>>num;
                    }
                    Potion *a = team->member(i)->Getpotion(num-1);
                    team->member(i)->Sellitem(a);
                    cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                    char more;
                    cin>>more;
                    if(more=='Y')
                        i--;
                }
                else
                    cout<<"Hero has no potoins to sell"<<endl;
            }
            else if(item=='S'){
                if(team->member(i)->Hasspells()){    
                    cout<<"give number of the spell you want to sell:"<<endl;
                    team->member(i)->Printspells();
                    int num;
                    cin>>num;
                    while(num<1||num>=team->member(i)->Getcurspells()){
                        cout<<"give different number:"<<endl;
                        cin>>num;
                    }
                    Spell *a = team->member(i)->Getspell(num-1);
                    team->member(i)->Sellspell(a);
                    cout<<"Do you want to buy/sell anything else for this hero? Y:Yes || N:No"<<endl;
                    char more;
                    cin>>more;
                    if(more=='Y')
                        i--;
                }
                else
                    cout<<"Hero has no spells to sell"<<endl;
            }
            else{
                cout<<"Please give a valid character"<<endl;
                i--;
            } 
        }
        else{
            cout<<"Please give a valid character:"<<endl;
            i--;
        }
    }
    cout<<"Thanks for visiting the market, we hope to see you back soon"<<endl;
    cout<<"Good luck on your journey!!"<<endl;
    return true;
}

NonAccessible::NonAccessible(int inx,int iny):Tile(inx,iny){}

NonAccessible::~NonAccessible(){}

bool NonAccessible::Enter(Teamofheroes *team){
    cout<<"this tile is not accessible"<<endl;
    return false;
}

Grid::Grid(){
    team=new Teamofheroes();
    for(int i=0;i<10;i++){
        weapons[i]=new Weapon(itemnames[i],(i+1)*10,i+1,(i+1)*9,i%2);
        armors[i]=new Armor(itemnames[i+10],(i+1)*10,i+1,(i+1)*5);
        srand(time(NULL));
        int x=rand()%4;
        string stat;
        if(x==0)
            stat="strength";
        else if(x==1)
            stat="mana";
        else if(x==2)
            stat="agility";
        else
            stat="dexterity";
        potions[i]=new Potion(itemnames[i+20],(i+1)*10,i+1,stat,(i+1)*5);
        icespells[i]=new IceSpell(spellnames[i],(i+1)*10,i+1,2*(i+1),10*(i+1),(i+1)*7);
        firespells[i]= new FireSpell(spellnames[i+10],(i+1)*10,i+1,2*(i+1),10*(i+1),(i+1)*7);
        lightningspells[i]= new LightningSpell(spellnames[i+20],(i+1)*10,i+1,2*(i+1),10*(i+1),(i+1)*7);
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<10;j++){
            if((matrix[i][j]=='c')||(matrix[i][j]=='s')){
                string names[15];
                for(int z=0;z<15;z++){
                    int x=rand()%30;
                    bool exists=false;
                    for(int y=0;y<z;y++){
                        if(names[y]==monsternames[x]){
                            exists=true;
                            break;
                        }
                    }
                    while(exists==true){
                        x=rand()%30;
                        exists=false;
                        for(int y=0;y<z;y++){
                            if(names[y]==monsternames[x]){
                                exists=true;
                                break;
                            }
                        }
                    }
                    names[z]=monsternames[x];
                }
                map[i][j]= new Common(i,j,names);
            }
            else if(matrix[i][j]=='x'){
                map[i][j]= new NonAccessible(i,j);
            }
            else{
                Armor *ar[5];
                Weapon *we[5];
                Potion *po[5];
                Spell *sp[15];
                for(int z=0;z<5;z++){
                    ar[z]=NULL;
                    we[z]=NULL;
                    po[z]=NULL;
                    sp[z]=NULL;
                    sp[z+5]=NULL;
                    sp[z+10]=NULL;
                }
                for(int z=0;z<5;z++){
                    int x=rand()%10;
                    bool exists=false;
                    for(int y=0;y<z;y++){
                        if(ar[y]==armors[x]){
                            exists=true;
                            break;
                        }
                    }
                    while(exists==true){
                        x=rand()%10;
                        exists=false;
                        for(int y=0;y<z;y++){
                            if(ar[y]==armors[x]){
                                exists=true;
                                break;
                            }
                        }
                    }
                    ar[z]=armors[x];
                }
                for(int z=0;z<5;z++){
                    int x=rand()%10;
                    bool exists=false;
                    for(int y=0;y<z;y++){
                        if(we[y]==weapons[x]){
                            exists=true;
                            break;
                        }
                    }
                    while(exists==true){
                        x=rand()%10;
                        exists=false;
                        for(int y=0;y<z;y++){
                            if(we[y]==weapons[x]){
                                exists=true;
                                break;
                            }
                        }
                    }
                    we[z]=weapons[x];
                }
                for(int z=0;z<5;z++){
                    int x=rand()%10;
                    bool exists=false;
                    for(int y=0;y<z;y++){
                        if(po[y]==potions[x]){
                            exists=true;
                            break;
                        }
                    }
                    while(exists==true){
                        x=rand()%10;
                        exists=false;
                        for(int y=0;y<z;y++){
                            if(po[y]==potions[x]){
                                exists=true;
                                break;
                            }
                        }
                    }
                    po[z]=potions[x];
                }
                for(int z=0;z<15;z++){
                    if(z<5){
                        int x=rand()%10;
                        bool exists=false;
                        for(int y=0;y<z;y++){
                            if(sp[y]==icespells[x]){
                                exists=true;
                                break;
                            }
                        }
                        while(exists==true){
                            x=rand()%10;
                            exists=false;
                            for(int y=0;y<z;y++){
                                if(sp[y]==icespells[x]){
                                    exists=true;
                                    break;
                                }
                            }
                        }
                        sp[z]=icespells[x];
                    }
                    else if(z<10){
                        int x=rand()%10;
                        bool exists=false;
                        for(int y=5;y<z;y++){
                            if(sp[y]==firespells[x]){
                                exists=true;
                                break;
                            }
                        }
                        while(exists==true){
                            x=rand()%10;
                            exists=false;
                            for(int y=5;y<z;y++){
                                if(sp[y]==firespells[x]){
                                    exists=true;
                                    break;
                                }
                            }
                        }
                        sp[z]=firespells[x];
                    }
                    else{
                        int x=rand()%10;
                        bool exists=false;
                        for(int y=10;y<z;y++){
                            if(sp[y]==lightningspells[x]){
                                exists=true;
                                break;
                            }
                        }
                        while(exists==true){
                            x=rand()%10;
                            exists=false;
                            for(int y=10;y<z;y++){
                                if(sp[y]==lightningspells[x]){
                                    exists=true;
                                    break;
                                }
                            }
                        }
                        sp[z]=lightningspells[x];
                    }
                }
                map[i][j]=new Market(i,j,ar,we,po,sp);    
            }
        }
    }
}

Grid::~Grid(){
    delete team;
    for(int i=0;i<5;i++){
        for(int j=0;j<10;j++)
            map[i][j]->~Tile();
    }
    for(int i=0;i<10;i++){
        armors[i]->~Armor();
        weapons[i]->~Weapon();
        potions[i]->~Potion();
        icespells[i]->~IceSpell();
        firespells[i]->~FireSpell();
        lightningspells[i]->~LightningSpell();
    }
}

void Grid::Print(){
    for(int i=0;i<5;i++){
        for(int j=0;j<10;j++){
            if(matrix[i][j]=='x')
                cout<<"*";
            else if(matrix[i][j]=='m')
                if(i==team->Getx()&&j==team->Gety())
                    cout<<"team";
                else
                    cout<<"Market";
            else if(matrix[i][j]=='s')
                if(i==team->Getx()&&j==team->Gety())
                    cout<<"team";
                else
                    cout<<"Start";
            else if(i==team->Getx()&&j==team->Gety())
                cout<<"team";
            cout<<"\t";
        }
        cout<<endl;
        cout<<endl;
    }
}

void Grid::Traverse(){
    char ans='g';
    team->Setx(1);
    team->Sety(0);
    this->Print();
    while(ans!='Q'){
        cout<<"What do you want to do?"<<endl;
        cout<<"W:Go up  ||  A:Go left  ||  S:Go down  ||  D:Go right  ||"<<endl;
        cout<<"M:Display map  ||  I:Display inventory  ||  H:Display hero's info  ||  E:Equip  ||  U:Unequip  || P:Use potion  ||  Q:Quit game"<<endl;
        cin>>ans;
        if(ans=='W'){
            if(team->Getx()>0){
                if(map[team->Getx()-1][team->Gety()]->Enter(team)==true){
                    team->Setx(team->Getx()-1);
                }
            }
            else
                cout<<"you have reached the top, go to a different direction"<<endl;
        }
        else if(ans=='A'){
            if(team->Gety()>0){
                if(map[team->Getx()][team->Gety()-1]->Enter(team)==true){
                    team->Sety(team->Gety()-1);
                }
            }
            else
                cout<<"you have reached the edge on the left, go to a different direction"<<endl;
        }
        else if(ans=='S'){
            if(team->Getx()<4){
                if(map[team->Getx()+1][team->Gety()]->Enter(team)==true){
                    team->Setx(team->Getx()+1);
                }
            }
            else
                cout<<"you have reached the bottom, go to a different direction"<<endl;
        }
        else if(ans=='D'){
            if(team->Gety()<9){
                if(map[team->Getx()][team->Gety()+1]->Enter(team)==true){
                    team->Sety(team->Gety()+1);
                }
            }
            else
                cout<<"you have reached the edge on the right, go to a different direction"<<endl;
        }
        else if(ans=='M')
            this->Print();
        else if(ans=='I')
            team->Printinventory();
        else if(ans=='H')
            team->Printteam();
        else if(ans=='E'){
            cout<<"give number of hero you want to equip something to: "<<endl;
            team->Printteam();
            int i;
            cin>>i;
            while(i<1||i>=team->Getcurrent()+1){
                cout<<"please give a valid number"<<endl;
                cin>>i;
            }
            i--;
            cout<<"give: A for armor or W for Weapon"<<endl;
            char equiping;
            cin>>equiping;
            if(equiping=='A'){
                if(team->member(i)->Hasarmors()){
                    cout<<"give number of armor you want to use"<<endl;
                        team->member(i)->Printarmors();
                        int number;
                        cin>>number;
                        while(number<1 || number>team->member(i)->Getcurarmors()){
                            cout<<"give different number:"<<endl;
                            cin>>number;
                        }
                        Armor *a=team->member(i)->Getarmor(number-1);
                        team->member(i)->Equip(a);
                    }
                else
                    cout<<"hero has no armors available"<<endl;
            }
            else{
                if(team->member(i)->Hasweapons()){
                    cout<<"give number of weapon you want to use"<<endl;
                    team->member(i)->Printweapons();
                    int number;
                    cin>>number;
                    while(number<1 || number>team->member(i)->Getcurweapons()){
                        cout<<"give different number:"<<endl;
                        cin>>number;
                    }
                    Weapon *a=team->member(i)->Getweapon(number-1);
                    team->member(i)->Equip(a);
                }
                else
                    cout<<"hero has no weapons available"<<endl;
            }
        }
        else if(ans=='U'){
            cout<<"give number of hero you want to unequip something from: "<<endl;
            team->Printteam();
            int i;
            cin>>i;
            while(i<1||i>=team->Getcurrent()+1){
                cout<<"please give a valid number"<<endl;
                cin>>i;
            }
            i--;
            cout<<"give: A for armor or W for Weapon"<<endl;
            char unequiping;
            cin>>unequiping;
            if(unequiping=='A'){
                if(team->member(i)->Hasarmors()){
                    cout<<"give number of armor you want to unequip"<<endl;
                    team->member(i)->Printarmors();
                    int number;
                    cin>>number;
                    while(number<1 || number>team->member(i)->Getcurarmors()){
                        cout<<"give different number:"<<endl;
                        cin>>number;
                    }
                    Armor *a=team->member(i)->Getarmor(number-1);
                    team->member(i)->Unequip(a);
                }
                else
                    cout<<"hero has no armors available"<<endl;
            }
            else{
                if(team->member(i)->Hasweapons()){
                    cout<<"give number of weapon you want to unequip"<<endl;
                    team->member(i)->Printweapons();
                    int number;
                    cin>>number;
                    while(number<1 || number>team->member(i)->Getcurweapons()){
                        cout<<"give different number:"<<endl;
                        cin>>number;
                    }
                    Weapon *a=team->member(i)->Getweapon(number-1);
                    team->member(i)->Unequip(a);
                }
                else
                    cout<<"hero has no weapons available"<<endl;
            }
        }
        else if(ans=='P'){
            cout<<"give number of hero you want to usa a potion: "<<endl;
            team->Printteam();
            int i;
            cin>>i;
            while(i<1||i>=team->Getcurrent()+1){
                cout<<"please give a valid number"<<endl;
                cin>>i;
            }
            i--;
            if(team->member(i)->Haspotions()){
                cout<<"give number of potion you want to use"<<endl;
                team->member(i)->Printpotions();
                int number;
                cin>>number;
                cin>>number;
                while(number<1 || number>team->member(i)->Getcurpotions()){
                    cout<<"give different number:"<<endl;
                    cin>>number;
                }
                Potion *a=team->member(i)->Getpotion(number-1);
                team->member(i)->Usepotion(a);
            }
            else
                cout<<"hero has no potions available"<<endl;
        }
        else if(ans!='Q')
            cout<<"this character doesn't match any order please give a different one"<<endl;
    }
    cout<<"Thanks for playing, we hope to see you back again!!"<<endl;
}

void Grid::StartGame(){
    cout<<"Welcome to the Game!"<<endl;
    cout<<"In this game you will explore a map, fighting monsters along the way"<<endl;
    cout<<"You might also want to visit the market to get everything you need for your journey!"<<endl;
    cout<<"But first create your team!"<<endl;
    cout<<"How many members do you want your team to consist of? (up to 3)"<<endl;
    int num;
    cin>>num;
    while(num<1||num>3){
        cout<<"please give a number from 1 to 3"<<endl;
        cin>>num;
    }
    for(int i=0;i<num;i++){
        cout<<"give a name to your hero"<<endl;
        string name;
        cin>>name;
        cout<<"what do you want your hero to be?"<<endl;
        cout<<"P:Paladin  ||  W:Warrior  ||  S:Sorcerer"<<endl;
        char type;
        cin>>type;
        if(type=='P'){
            Hero *newhero=new Paladin(name);
            team->Enterhero(newhero);
            cout<<"your team now has a paladin called "<<name<<"!"<<endl;
        }
        else if(type=='W'){
            Hero *newhero=new Warrior(name);
            team->Enterhero(newhero);
            cout<<"your team now has a warrior called "<<name<<"!"<<endl;
        }
        else if(type=='S'){
            Hero *newhero=new Sorcerer(name);
            team->Enterhero(newhero);
            cout<<"your team now has a sorcerer called "<<name<<"!"<<endl;
        }
        else{
            cout<<"Please give a valid character"<<endl;
            i--;
        }
    }
    cout<<"You are now ready to start your journey!"<<endl;
    this->Traverse();
}
int main(){
    Grid map;
    map.StartGame();
    return 0;
}