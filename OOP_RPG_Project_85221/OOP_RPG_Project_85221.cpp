#include <iostream>
#include <String>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

//-----------------------------
//           ENTITIES 
//Entities
class Entity
{
private:
    string Name;
    float HP = 0;
    float HPMax = 0;
    string Description;
    float ATK = 0;
public:

    virtual void ShowInfo() = 0;

    //....Get and Set functions....
    string GetName() const
    {
        return Name;
    }
    string GetDescr() const
    {
        return Description;
    }
    float GetATK() const
    {
        return ATK;
    }
    float GetHP() const
    {
        return HP;
    }
    float GetMaxHP() const
    {
        return HPMax;
    }
    void SetName(string NewName)
    {
        Name = NewName;
    }
    void SetDescr(string NewDescr)
    {
        Description = NewDescr;
    }
    void SetATK(float NewATK)
    {
        ATK = NewATK;
    }
    void SetHP(float NewHP)
    {
        HP = NewHP;
    }
    void SetMaxHP(float NewHPMax)
    {
        HPMax = NewHPMax;
    }
    //....................
};


//-----------------------------
//Entities' skills
class Skill
{
private:
    string Name;
    float ATK;

public:
    Skill(string name, float atk)
    {
        Name = name;
        ATK = atk;
    }

    //....Get functions....
    void GetName() const
    {
        cout << Name;
    }
    float GetATK() const
    {
        return ATK;
    }
    //....................


    void ShowInfo() //Show information about the skills 
    {
        cout << "--SKILL INFORMATION--" << endl;
        cout << "Name: " << Name << endl;
        cout << "ATK: +" << ATK << " to main ATK value" << endl;
    }
};


//-----------------------------
//Characters' classes
class CharacterClass
{
private:
    string Name;
    string Description;
    vector<Skill> Skills;

public:

    CharacterClass() : Name(""), Description("") {}

    CharacterClass(string name, string descr, const Skill& skill)
    {
        Name = name;
        Description = descr;
        Skills.push_back(skill);
    }
    CharacterClass(string name, string descr, vector<Skill> skills)
    {
        Name = name;
        Description = descr;
        Skills = skills;
    }


    //....Skills....
    void AddSkill(Skill& skill)
    {
        Skills.push_back(skill);
    }


    void ShowSkills()
    {
        for (int i = 0; i < Skills.size(); ++i)
        {
            cout << i + 1 << ". ";
            Skills[i].ShowInfo();
            cout << endl;
        }
    }
    //....................


    void ShowInfo() //Show information about the skills 
    {
        cout << "--ClASS INFORMATION--" << endl;
        cout << "Name: " << Name << endl;
        cout << "Description: " << Description << endl;
        cout << "Skills list: " << endl;
        ShowSkills();
    }

    CharacterClass SearchByName(const string& name, vector<CharacterClass>& classes)
    {
        for (auto& characterClass : classes)
        {
            if (characterClass.GetName() == name)
            {
                return characterClass;
            }
        }
    }


    //....Get functions....
    vector<Skill> GetSkills() const
    {
        return Skills;
    }

    string GetName()
    {
        return Name;
    }
    //....................


};


//-----------------------------
//NPC
class NPC : public Entity
{
private:
    int EXP;
    float Coins;
public:
    NPC(string name, float hp, float hpmax, string descr, float atk, int exp, float coins)
    {
        EXP = exp;
        Coins = coins;
        SetName(name);
        SetHP(hp);
        SetMaxHP(hpmax);
        SetDescr(descr);
        SetATK(atk);
    }

    //....Get and set functions....
    int GetEXP()
    {
        return EXP;
    }
    float GetCoins()
    {
        return Coins;
    }
    void SetCoins(float newCoins)
    {
        Coins = newCoins;
    }
    void SetEXP(int newEXP)
    {
        EXP = newEXP;
    }
    //....................


    void ShowInfo()
    {
        cout << "--NPC INFORMATION--" << endl;
        cout << "Name: " << GetName() << endl;
        cout << "Description: " << GetDescr() << endl;
        cout << "Current HP: " << GetHP() << "/" << GetMaxHP() << endl;
        cout << "ATK: " << GetATK() << endl;
        cout << "XP received after the victory: " << GetEXP() << endl;
        cout << "Coins received after the victory: " << GetCoins() << endl;
    }
};



//-----------------------------
//PLAYER
class Player : public Entity
{
private:
    int Level;
    float Money;
public:
    CharacterClass ClassType;
    Player(string name, float hp, float hpmax, string descr, float atk, int level, CharacterClass classType, float money)
        : ClassType(classType)
    {
        SetName(name);
        SetHP(hp);
        SetMaxHP(hpmax);
        SetDescr(descr);
        SetATK(atk);
        Level = level;
        Money = money;
    }


    //....Get and set functions....
    int GetLevel()
    {
        return Level;
    }
    void SetLevel(int NewLevel)
    {
        Level = NewLevel;
    }
    void SetMoney(float NewMoney)
    {
        Money = NewMoney;
    }
    float GetMoney()
    {
        return Money;
    }
    CharacterClass GetClass()
    {
        return ClassType;
    }
    void SetClass(const CharacterClass& characterClass)
    {
        ClassType = characterClass;
    }
    //....................


    void ShowInfo() override
    {
        cout << "--Player INFORMATION--" << endl;
        cout << "Name: " << GetName() << endl;
        cout << "Level: " << GetLevel() << endl;
        cout << "Description: " << GetDescr() << endl;
        cout << "Current HP: " << GetHP() << "/" << GetMaxHP() << endl;
        cout << "ATK: " << GetATK() << endl;
        cout << "Money: " << GetMoney() << " coins" << endl;
    }
};


//-----------------------------
//           ITEMS
class Item
{
private:
    string Name;
    string Description;
    float Price = 0;
    int Type = 0; // 1 - sword, 2 -- food
public:
    virtual void ShowInfo() = 0;

    //....Get and set functions....
    string GetName()
    {
        return Name;
    }
    string GetDescr()
    {
        return Description;
    }
    float GetPrice()
    {
        return Price;
    }
    int GetType()
    {
        return Type;
    }
    void SetName(string NewName)
    {
        Name = NewName;
    }
    void SetDescr(string NewDescr)
    {
        Description = NewDescr;
    }
    void SetPrice(float NewPrice)
    {
        Price = NewPrice;
    }
    void SetType(int NewType)
    {
        Type = NewType;
    }
    //....................


};

//-----------------------------
//FOOD
class Food : public Item
{
private:
    float Recovery; //How many HP you recover after eating 

public:
    //....Get and set functions....
    float GetRecov()
    {
        return Recovery;
    }
    void SetRecov(float NewRecov)
    {
        Recovery = NewRecov;
    }
    //....................

    Food(string name, string descr, float price, float recov, int type)
    {
        SetName(name);
        SetDescr(descr);
        SetPrice(price);
        SetRecov(recov);
        SetType(type);
    }

    void ShowInfo() override
    {
        cout << "--FOOD INFORMATION--" << endl;
        cout << "Name: " << GetName() << endl;
        cout << "Description: " << GetDescr() << endl;
        cout << "Price: " << GetPrice() << " coins" << endl;
        cout << "HP Recovery: " << GetRecov() << " %" << endl;
    }
};

//-----------------------------
//TOOLS 
class Weapon : public Item
{
private:
    float ATK;
public:
    //....Get and set functions....
    void SetATK(float NewATK)
    {
        ATK = NewATK;
    }
    float GetATK()
    {
        return ATK;
    }
    //....................

    Weapon(string name, string descr, float price, float atk, int type)
    {
        SetName(name);
        SetDescr(descr);
        SetPrice(price);
        SetType(type);
        SetATK(atk);
        SetType(type);
    }

    void ShowInfo() override //Show information about the weapon
    {
        cout << "--WEAPON INFORMATION--" << endl;
        cout << "Name: " << GetName() << endl;
        cout << "ATK: " << GetATK() << endl;
        cout << "Description: " << GetDescr() << endl;
        cout << "Price: " << GetPrice() << " coins" << endl;
    }
};


//-----------------------------
//FACTORIES
class ItemFactory {
public:
    static Food createFood(const string& name, const string& descr, float price, float recov, int type = 2)
    {
        return Food(name, descr, price, recov, type);
    }

    static Weapon createWeapon(const string& name, const string& descr, float price, float atk, int type)
    {
        return Weapon(name, descr, price, atk, type);
    }
};

class EntityFactory {
public:
    static Player createPlayer(const string& name, float hp, float hpmax, const string& descr, float atk, int level, const CharacterClass& classType, float balance)
    {
        return Player(name, hp, hpmax, descr, atk, level, classType, balance);
    }

    static NPC createNPC(const string& name, float hp, float hpmax, const string& descr, float atk, int exp, float coins)
    {
        return NPC(name, hp, hpmax, descr, atk, exp, coins);
    }
};

class ClassFactory {
public:
    static CharacterClass createClass(const string& name, const string& descr, const vector<Skill>& skills)
    {
        return CharacterClass(name, descr, skills);
    }
};

class SkillFactory
{
public:
    static Skill createSkill(const string& name, float atk)
    {
        return Skill(name, atk);
    }
};


//-----------------------------
//     CREATE A PLAYER
class PlayerCreator
{
private:
    string Name;
    string ClassType;
    CharacterClass SelectedClass;
    vector<CharacterClass> Classes;

    void displayClasses()
    {
        for (auto& characterClass : Classes)
        {
            characterClass.ShowInfo();
            cout << endl;
        }
    }
    string chooseClass()
    {
        while (true)
        {
            cout << "Choose your class(Type the name): " << endl << endl;
            displayClasses();
            cout << "Your choice: ";
            cin >> ClassType;
            transform(ClassType.begin(), ClassType.end(), ClassType.begin(), ::tolower);

            for (auto& characterClass : Classes)
            {
                string className = characterClass.GetName();
                transform(className.begin(), className.end(), className.begin(), ::tolower);

                if (ClassType == className)
                {
                    SelectedClass = characterClass;
                    return ClassType;
                }
            }
            system("CLS");
            cout << "Please, choose one of the existing classes, traveler!" << endl;
        }
    }
    //............................

public:
    PlayerCreator(vector<CharacterClass>& classes, string name, string classtype, CharacterClass selectedclass)
    {
        Classes = classes;
        Name = name;
        ClassType = classtype;
        SelectedClass = selectedclass;
    }
    Player createPlayer()
    {
        string name;
        cout << "======================" << endl;
        cout << "  Character creation  " << endl;
        cout << "======================" << endl;
        cout << "Enter your name: " << endl;
        cout << "- ";
        cin >> name;
        system("CLS");
        string ClassType = chooseClass();
        system("CLS");

        return EntityFactory::createPlayer(name, 100.0f, 100.0f, "A strong traveler, who is ready for new adventures!", 5.0f, 0, SelectedClass, 10.0);
    }
};

//-----------------------------
//          INVENTORY
class Inventory
{
private:
    map<Item*, int> items; // Map is used to store quantity of items

public:
    void addItem(Item* item)
    {
        if (items.find(item) != items.end())
        {
            items[item]++;
        }
        else {
            items[item] = 1;
        }
        cout << item->GetName() << " was added to inventory." << endl;
    }

    void removeItem(Item* item)
    {
        if (items.find(item) != items.end()) {
            if (items[item] > 1)
            {
                items[item]--;
            }
            else {
                items.erase(item);
            }
            cout << "Item removed from inventory." << endl;
        }
        else {
            cout << "Item not found in inventory!" << endl;
        }
    }

    void showInventory() const
    {
        if (items.empty())
        {
            cout << "The inventory is empty." << endl;
            return;
        }

        cout << "Inventory contents:" << endl;
        for (const auto& itemPair : items)
        {
            Item* item = itemPair.first;
            int quantity = itemPair.second;
            cout << "- " << item->GetName() << " (Quantity: " << quantity << ")" << endl;
        }
    }

    //....Get and set functions....
    size_t GetSize() const
    {
        return items.size();
    }
    const map<Item*, int>& GetItems() const
    {
        return items;
    }
    //....................
};


//-----------------------------
//          FIGHT
class Fight
{
public:
    void ShowOptions()
    {
        cout << "-----------------" << endl;
        cout << "     BATTLE      " << endl;
        cout << "-----------------" << endl;
        cout << "What are you going to do?(1 - 3)" << endl;
        cout << "-------------" << endl;
        cout << "1. Fight" << endl;
        cout << "2. Use item" << endl;
        cout << "3. Get information" << endl;
        cout << "4. Run away " << endl;
        cout << "-------------" << endl;
        cout << "Your choice: ";
    }

    void Battle(Player& player, NPC& mob, Inventory& inventory)
    {
        int choice = 0;
        while (player.GetHP() > 0 && mob.GetHP() > 0 && choice != 4)
        {
            while (true)
            {
                cout << mob.GetName() << " is here!" << endl;
                cout << "Mob's HP: " << mob.GetHP() << "/" << mob.GetMaxHP() << endl;
                cout << "Your HP: " << player.GetHP() << "/" << player.GetMaxHP() << endl;
                ShowOptions();
                cin >> choice;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("CLS");
                }
                else
                {
                    break;
                }
            }
            system("CLS");
            switch (choice)
            {
            case 1:
                int SkillChoice;
                while (true)
                {
                    cout << "What skill do you want to use?(Number)" << endl;
                    player.ClassType.ShowSkills();
                    cin >> SkillChoice;
                    if (!cin)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("CLS");
                    }
                    else
                    {
                        break;
                    }
                }
                if (SkillChoice > 0 && SkillChoice <= player.ClassType.GetSkills().size())
                {
                    Skill chosenSkill = player.ClassType.GetSkills()[SkillChoice - 1];
                    cout << "You've used ";
                    chosenSkill.GetName();
                    cout << "!" << endl;
                    mob.SetHP(mob.GetHP() - (player.GetATK() + chosenSkill.GetATK()));
                    player.SetHP(player.GetHP() - mob.GetATK());
                }
                else
                {
                    cout << "Wrong choice, friend! Try again!" << endl;
                }

                break;
            case 2:
            {
                int ItemChoice;
                cout << "What item do you want to use?" << endl;
                inventory.showInventory();
                cin >> ItemChoice;
                const map<Item*, int>& items = inventory.GetItems();
                int index = 1;
                Item* selectedItem = nullptr;
                for (const auto& itemPair : items)
                {
                    if (index == ItemChoice)
                    {
                        selectedItem = itemPair.first;
                        break;
                    }
                    index++;
                }
                if (selectedItem == nullptr)
                {
                    cout << "You wrote a wrong number, buddy!" << endl;
                    break;
                }
                if (selectedItem->GetType() == 2)
                {
                    Food* foodItem = dynamic_cast<Food*>(selectedItem);
                    if (foodItem)
                    {
                        float recovery = foodItem->GetRecov();
                        player.SetHP(player.GetHP() + recovery);
                        if (player.GetHP() > player.GetMaxHP())
                        {
                            player.SetHP(player.GetMaxHP());
                        }
                        cout << foodItem->GetName() << " used. Recovered " << recovery << " HP!" << endl;

                        inventory.removeItem(selectedItem);
                    }
                }
                else
                {
                    cout << "This item is not food!" << endl;
                }
                break;
            }
            case 3:
                mob.ShowInfo();
                cout << endl << endl;
                break;
            case 4:
                cout << "It's ok, you have plenty of time to become stronger!" << endl;
                break;

            }
        }
        if (player.GetHP() <= 0)
        {
            cout << "You lost! Try again next time, buddy!" << endl;
            player.SetHP(player.GetMaxHP());
        }
        if (mob.GetHP() <= 0)
        {
            cout << "You won! You got: " << endl;
            cout << "- " << mob.GetEXP() << " XP" << endl;
            cout << "- " << mob.GetCoins() << " Coins" << endl;
            player.SetLevel(player.GetLevel() + mob.GetEXP());
            player.SetMoney(player.GetMoney() + mob.GetCoins());
        }
        mob.SetHP(mob.GetMaxHP());

    }
};


//-----------------------------
//          SHOP
class Shop
{
private:
    vector<Food> FoodList;
    vector<Weapon> WeaponList;
    Inventory& PlayerInventory;
    Player& player;
public:
    Shop(vector<Food> foodList, vector<Weapon> weaponList, Inventory& inventory, Player& player)
        : FoodList(foodList), WeaponList(weaponList), PlayerInventory(inventory), player(player) {}

    void ShowFood()
    {
        cout << "-- FOOD --" << endl;
        for (size_t i = 0; i < FoodList.size(); ++i)
        {
            cout << i + 1 << ". ";
            FoodList[i].ShowInfo();
        }
        cout << "---------------------" << endl << endl;
    }

    void ShowWeapons()
    {
        cout << "-- WEAPON --" << endl;
        for (size_t i = 0; i < WeaponList.size(); ++i)
        {
            cout << i + 1 << ". ";
            WeaponList[i].ShowInfo();
        }
        cout << "---------------------" << endl << endl;
    }

    void BuyFood()
    {
        int choice;
        while (true)
        {
            ShowFood();
            cout << "Select the food you want to buy (0 to cancel): ";
            cin >> choice;

            if (!cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("CLS");
            }
            else
            {
                break;
            }
        }
        if (choice <= 0 || choice > FoodList.size())
        {
            cout << "Purchase canceled." << endl;
            return;
        }

        Food& selectedFood = FoodList[choice - 1];
        if (player.GetMoney() >= selectedFood.GetPrice())
        {
            player.SetMoney(player.GetMoney() - selectedFood.GetPrice());

            bool itemFound = false;
            for (auto& itemPair : PlayerInventory.GetItems())
            {
                if (itemPair.first->GetName() == selectedFood.GetName())
                {
                    PlayerInventory.addItem(itemPair.first);
                    itemFound = true;
                    break;
                }
            }

            if (!itemFound)
            {
                PlayerInventory.addItem(&selectedFood);
            }

            cout << "You purchased " << selectedFood.GetName() << "!" << endl;
        }
        else
        {
            cout << "Not enough coins!" << endl;
        }
    }

    void BuyWeapon()
    {
        int choice;
        while (true)
        {
            ShowWeapons();
            cout << "Select the weapon you want to buy (0 to cancel): ";
            cin >> choice;
            if (!cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("CLS");
            }
            else
            {
                break;
            }
        }
        if (choice <= 0 || choice > WeaponList.size())
        {
            cout << "Purchase canceled." << endl;
            return;
        }

        Weapon& selectedWeapon = WeaponList[choice - 1];
        if (player.GetMoney() >= selectedWeapon.GetPrice())
        {
            player.SetMoney(player.GetMoney() - selectedWeapon.GetPrice());


            Item* oldWeapon = nullptr;
            for (const auto& itemPair : PlayerInventory.GetItems())
            {
                if (itemPair.first->GetType() == 1)
                {
                    oldWeapon = itemPair.first;
                    break;
                }
            }

            if (oldWeapon)
            {
                Weapon* oldWeaponPtr = dynamic_cast<Weapon*>(oldWeapon);
                if (oldWeaponPtr)
                {
                    player.SetATK(player.GetATK() - oldWeaponPtr->GetATK());
                    PlayerInventory.removeItem(oldWeapon);
                    cout << "Your old weapon " << oldWeaponPtr->GetName() << " has been replaced." << endl;
                }
            }
            PlayerInventory.addItem(&selectedWeapon);
            player.SetATK(player.GetATK() + selectedWeapon.GetATK());
        }
        else
        {
            cout << "Not enough coins!" << endl;
        }
    }

    void BuyItems()
    {
        int choice;
        while (true)
        {
            while (true)
            {
                cout << "=================" << endl;
                cout << "    Buy items    " << endl;
                cout << "=================" << endl;
                cout << "What would you like to buy?" << endl;
                cout << "1. Food" << endl;
                cout << "2. Weapon" << endl;
                cout << "3. Exit" << endl;
                cin >> choice;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("CLS");
                }
                else
                {
                    break;
                }
            }
            system("CLS");
            switch (choice)
            {
            case 1:
                BuyFood();
                break;
            case 2:
                BuyWeapon();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void ShopMenu()
    {
        int choice;
        while (true)
        {
            while (true)
            {
                cout << "=================" << endl;
                cout << "      Shop       " << endl;
                cout << "=================" << endl;
                cout << "Hello, traveler! What would you like to do?" << endl;
                cout << "1. Buy items" << endl;
                cout << "2. Leave" << endl;
                cout << "-----------------" << endl;
                cout << "Your choice: ";
                cin >> choice;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("CLS");
                }
                else
                {
                    break;
                }
            }
            system("CLS");

            switch (choice)
            {
            case 1:
                BuyItems();
                break;
            case 2:
                cout << "Thank you for visiting the shop!" << endl;
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }
};

//-----------------------------
//          SAVE PROGRESS
class SaveFiles
{
public:
    void Save(Inventory inventory, Player player)
    {
        //...........................................
        //Character stats
        json j;
        j["name"] = player.GetName();
        j["hp"] = player.GetHP();
        j["maxhp"] = player.GetMaxHP();
        j["description"] = player.GetDescr();
        j["attack"] = player.GetATK();
        j["level"] = player.GetLevel();
        j["class"] = player.GetClass().GetName();
        j["defense"] = player.GetMoney();
        //...........................................

         //...........................................
        //Inventory
        json inventoryJson = json::array();
        for (const auto& itemPair : inventory.GetItems())
        {
            Item* item = itemPair.first;
            int quantity = itemPair.second;

            inventoryJson.push_back({ {"name", item->GetName()}, {"quantity", quantity} });
        }
        j["inventory"] = inventoryJson;
        //...........................................


        ofstream file("GameSave.json");
        if (file.is_open())
        {
            file << j.dump(1);
            cout << "Congratulations, friend! Your game is saved! :D" << endl;
            file.close();
        }
        else
        {
            cout << "Something went wrong, your progress can not be saved :C" << endl;
        }
    }


    void Load(Inventory& inventory, Player& player, vector<CharacterClass>& classes, vector<Food>& FoodList, vector<Weapon>& WeaponList)
    {
        ifstream file("GameSave.json");
        if (!file.is_open()) {
            cout << "Sorry, buddy! You don't have any save files" << endl;
            return;
        }
        nlohmann::json j;
        file >> j;
        file.close();
        try
        {
            //...........................................
            //...........................................
            // Character stats
            if (j.contains("name") && j["name"].is_string())
                player.SetName(j["name"].get<string>());
            if (j.contains("hp") && j["hp"].is_number_float())
                player.SetHP(j["hp"].get<float>());
            if (j.contains("maxhp") && j["maxhp"].is_number_float())
                player.SetMaxHP(j["maxhp"].get<float>());
            if (j.contains("description") && j["description"].is_string())
                player.SetDescr(j["description"].get<string>());
            if (j.contains("attack") && j["attack"].is_number_float())
                player.SetATK(j["attack"].get<float>());
            if (j.contains("level") && j["level"].is_number_integer())
                player.SetLevel(j["level"].get<int>());
            if (j.contains("defense") && j["defense"].is_number_float())
                player.SetMoney(j["defense"].get<float>());
            if (j.contains("class") && j["class"].is_string())
            {
                string SearchClass = j["class"].get<string>();
                CharacterClass foundClass = foundClass.SearchByName(SearchClass, classes);
                if (foundClass.GetName() != "") {
                    player.SetClass(foundClass);
                }
                else {
                    cout << "Class not found!" << endl;
                }
            }
            //...........................................

            //...........................................
            // Inventory
            inventory = Inventory();
            if (j.contains("inventory") && j["inventory"].is_array())
            {
                for (const auto& itemData : j["inventory"])
                {
                    if (!itemData.contains("name") || !itemData["name"].is_string() ||
                        !itemData.contains("quantity") || !itemData["quantity"].is_number_integer())
                    {
                        cout << "Invalid format" << endl;
                        continue;
                    }

                    string itemName = itemData["name"].get<string>();
                    int quantity = itemData["quantity"].get<int>();
                    bool itemFound = false;
                    for (Food& food : FoodList) {
                        if (food.GetName() == itemName)
                        {
                            for (int i = 0; i < quantity; ++i)
                            {
                                inventory.addItem(&food);
                            }
                            itemFound = true;
                            break;
                        }
                    }
                    if (!itemFound)
                    {
                        for (Weapon& weapon : WeaponList)
                        {
                            if (weapon.GetName() == itemName)
                            {
                                for (int i = 0; i < quantity; ++i)
                                {
                                    inventory.addItem(&weapon);
                                }
                                itemFound = true;
                                break;
                            }
                        }
                    }

                    if (!itemFound)
                    {
                        cout << "Item not found: " << itemName << ". Skipping." << endl;
                    }
                }
            }
            //...........................................
        }
        catch (const nlohmann::json::type_error& e)
        {
            cout << "Error loading save file: " << e.what() << endl;
        }
    }
};
//-----------------------------
//        RANDOM NUMBERS
class RandomNumberGeneration
{
public:
    int RandomNumber(int from, int to)
    {
        srand(static_cast<unsigned>(time(0)));
        int RandomNumber = from + rand() % to;
        return RandomNumber;
    }
};
//-----------------------------
//            MENU
class Menu
{
public:

    void DisplayMenu()
    {
        cout << "=================" << endl;
        cout << "      Menu       " << endl;
        cout << "=================" << endl;
        cout << "1. Player's info" << endl;
        cout << "2. Inventory" << endl;
        cout << "3. Fight " << endl;
        cout << "4. Shop" << endl;
        cout << "5. Save" << endl;
        cout << "6. Load save file" << endl;
        cout << "7. Exit" << endl;
        cout << "-----------------" << endl;
        cout << "Your choice: ";
    }

    void ShowMenu(int choice, Player& player, Inventory& inventory, NPC& Zombie, NPC& Ghost, NPC& Skeleton, Shop& shop, vector<Food>& FoodList, vector<Weapon>& WeaponList, vector<CharacterClass>& classes)
    {
        while (choice != -1)
        {
            DisplayMenu();
            while (true)
            {
                cin >> choice;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("CLS");
                    DisplayMenu();
                }
                else
                {
                    break;
                }
            }

            //--------------------------------------
            // Initiliazitation 
            RandomNumberGeneration random;
            int RandomNumber = random.RandomNumber(1, 3);
            string exit;
            string ChoiceInventory;
            int ItemChoice;
            //--------------------------------------

            system("CLS");
            switch (choice)
            {

            case 1:
                //============================
                //SHOW PLAYER INFO 
                player.ShowInfo();
                cout << endl;
                player.ClassType.ShowInfo();
                cout << "Type anything to leave: ";
                cin >> exit;
                system("CLS");
                break;
            case 2:
                //============================
                //SHOW INVENTORY 
                while (ChoiceInventory != "n" && ChoiceInventory != "N")
                {
                    inventory.showInventory();
                    cout << "Do you want to see info about any item?(Y/N): ";
                    cin >> ChoiceInventory;
                    system("CLS");

                    if (ChoiceInventory == "Y" || ChoiceInventory == "y")
                    {
                        while (true)
                        {
                            cout << "What item do you want to choose?(Number)" << endl;
                            inventory.showInventory();
                            cin >> ItemChoice;
                            system("CLS");
                            if (!cin)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else
                            {
                                break;
                            }
                        }
                        if (ItemChoice > 0 && ItemChoice <= inventory.GetSize())
                        {
                            int index = 1;
                            Item* selectedItem = nullptr;

                            for (const auto& itemPair : inventory.GetItems())
                            {
                                if (index == ItemChoice)
                                {
                                    selectedItem = itemPair.first;
                                    break;
                                }
                                index++;
                            }
                            if (selectedItem != nullptr)
                            {
                                selectedItem->ShowInfo();
                            }
                            else
                            {
                                cout << "Item is not found" << endl;
                            }
                        }
                        else
                        {
                            cout << "Invalid item choice!" << endl;
                        }
                    }
                    if (ChoiceInventory == "N" || ChoiceInventory == "n")
                    {
                        system("CLS");
                        break;
                    }
                }
                system("CLS");
                break;
            case 3:
                //============================
                //FIGHT 
                Fight fight;
                if (RandomNumber == 1)
                {
                    Zombie.SetEXP(random.RandomNumber(1, 2));
                    Zombie.SetCoins(random.RandomNumber(1, 5));
                    fight.Battle(player, Zombie, inventory);
                }
                if (RandomNumber == 2)
                {
                    Ghost.SetEXP(random.RandomNumber(2, 4));
                    Ghost.SetCoins(random.RandomNumber(5, 10));
                    fight.Battle(player, Ghost, inventory);
                }
                if (RandomNumber == 3)
                {
                    Skeleton.SetEXP(random.RandomNumber(4, 10));
                    Skeleton.SetCoins(random.RandomNumber(10, 20));
                    fight.Battle(player, Skeleton, inventory);
                }
                break;
            case 4:
                //============================
                //SHOP
                shop.ShopMenu();
                system("CLS");
                break;
            case 5:
                //============================
                //SAVE PROGRESS
                SaveFiles saveFiles;
                saveFiles.Save(inventory, player);
                break;
            case 6:
                //============================
                //LOAD SAVE FILE
                saveFiles.Load(inventory, player, classes, FoodList, WeaponList);
                break;
            case 7:
                //============================
                //EXIT THE GAME
                choice = -1;
                break;
            }
        }
    }
    Player BeginningMenu(Player& player, Inventory& inventory, vector<Food>& FoodList, vector<Weapon>& WeaponList, vector<CharacterClass>& classes)
    {
        string answer;
        cout << "=================" << endl;
        cout << "     WELCOME     " << endl;
        cout << "=================" << endl;
        cout << "Welcome, traveler!" << endl;
        cout << "It's time to start your adventure!" << endl;
        cout << "Do you have any save files?" << endl;
        while (true)
        {
            cout << "Your answer(Y/N): ";
            cin >> answer;
            if (answer == "Y" || answer == "y")
            {
                SaveFiles saveFiles;
                saveFiles.Load(inventory, player, classes, FoodList, WeaponList);
                if (player.GetName() == "")
                {
                    PlayerCreator playerCreator(classes, "", "", CharacterClass());
                    player = playerCreator.createPlayer();
                }
                return player;
            }
            if (answer == "N" || answer == "n")
            {
                PlayerCreator playerCreator(classes, "", "", CharacterClass());
                player = playerCreator.createPlayer();
                return player;
            }
            else
            {
                cout << "Hey, friend, I don't get it! Try again, please!" << endl;
            }
        }

    }
};


int main()
{
    //-------------------------------------------
    //INITIALIZATION
    Inventory inventory;
    Menu menu;
    RandomNumberGeneration random;

    //NPC LIST
    NPC Zombie = EntityFactory::createNPC("Zombie", 50, 50, "He shouldn't be a problem", 5, 0, 0);
    NPC Ghost = EntityFactory::createNPC("Ghost", 100, 100, "Scary guy", 15, 0, 0);
    NPC Skeleton = EntityFactory::createNPC("Skeleton King", 500, 500, "Very strong enemy", 30, 0, 0);

    //FOOD LIST 
    Food Bread = ItemFactory::createFood("Bread", "Still warm!", 5.0, 10.0, 2);
    Food Apple = ItemFactory::createFood("Apple", "It should be very sweet.", 2.0, 5.0, 2);
    Food HealPotion = ItemFactory::createFood("Heal Potion", "Restores all HP", 20.0, 100.0, 2);
    Food DeathPotion = ItemFactory::createFood("Death Potion", "Why would you even use it..?", 20.0, -100.0, 2);
    vector<Food> FoodList = { Bread, Apple, HealPotion, DeathPotion };

    //WEAPONS LIST
    Weapon WoodenSword = ItemFactory::createWeapon("Wooden Sword", "It would be a good start", 10.0, 5, 1);
    Weapon IronSword = ItemFactory::createWeapon("Iron Sword", "I feel power!", 20.0, 10, 1);
    Weapon MagicSword = ItemFactory::createWeapon("Magic Sword", "Unstoppable", 50.0, 20, 1);
    vector<Weapon> WeaponList = { WoodenSword, IronSword, MagicSword };

    //SKILLS LIST
    Skill SimpleSpell = SkillFactory::createSkill("Simple Spell", 10.0);
    Skill SecondSpell = SkillFactory::createSkill("Second Spell", 20.0);
    Skill OneHit = SkillFactory::createSkill("One Hit", 20.0);
    Skill TwoHits = SkillFactory::createSkill("Two Hits", 30.0);

    //CLASSES LIST 
    vector<Skill> WitchSkills = { SimpleSpell, SecondSpell };
    CharacterClass Witch = ClassFactory::createClass("Witch", "A very strong magician", WitchSkills);
    vector<Skill> DwarfSkills = { OneHit, TwoHits };
    CharacterClass Dwarf = ClassFactory::createClass("Dwarf", "Small, but strong", DwarfSkills);
    vector<CharacterClass> classes = { Witch, Dwarf };

    Player player = EntityFactory::createPlayer("", 0, 0, "", 0, 0, Witch, 0);
    //-------------------------------------------

    int MenuChoice = 0;

    player = menu.BeginningMenu(player, inventory, FoodList, WeaponList, classes);

    Shop shop(FoodList, WeaponList, inventory, player);
    menu.ShowMenu(MenuChoice, player, inventory, Zombie, Skeleton, Ghost, shop, FoodList, WeaponList, classes);

}