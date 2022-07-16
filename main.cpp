#include <iostream>

#include <fstream>

#include <string>

using namespace std;



class Character {

private:

    string Name;

    string Type;
   
protected:
    
    Character(string NameA, string TypeA) {

        Name = NameA;

        Type = TypeA;

    }

public:

    string GetType() {

        return Type;

    }

    string GetName() {

        return Name;

    }

    virtual void Draw(){

        cout << "Type: " << Type;

        cout << ", Name: " << Name;

        cout << ", ";

    }

};



class Warrior : public Character {

private:

    double ArmorLevel;

public:

    Warrior(string nazwa, double Armor) : Character(nazwa, "Warrior") {

        if (nazwa.length() > 128 || Armor < 0) {

            throw out_of_range("Jedna ze zmiennych wychodzi poza zakres!");

        }

        ArmorLevel = Armor;

    }

    Warrior& SetArmorLevel(double armor) {

        this->ArmorLevel = armor;

        return *this;

    }

    double GetArmorLevel() {

        return ArmorLevel;

    }

    virtual void Draw() {

        Character::Draw();

        cout << "ArmorLevel: " << ArmorLevel << endl;

    }

    ~Warrior() {

        //destruktor

    }

};



class Enemy: public Character {

private:

    double Strenght;

    int ConcurrentWarriors;

public:

    Enemy(string nazwa, double StrenghtA, int ConcurrentWarriorsA) : Character(nazwa, "Enemy") {

        if (nazwa.length() > 128 || StrenghtA < 0 || ConcurrentWarriorsA < 0) {

            throw out_of_range("Jedna ze zmiennych wychodzi poza zakres!");

        }

        Strenght = StrenghtA;

        ConcurrentWarriors = ConcurrentWarriorsA;

    }

    Enemy& SetStrenght(double sila) {

        this->Strenght = sila;

        return *this;

    }

    double GetStrenght() {

        return Strenght;

    }

    int GetConcurrentWarriors() {

        return ConcurrentWarriors;

    }

    virtual void Draw() {

        Character::Draw();

        cout << "Strength: " << Strenght;

        cout << ", ConcurrentWarriors: " << ConcurrentWarriors << endl;

    }

    ~Enemy() {

        //destruktor

    }

};



int main()

{

    try {

        // TEST KLAS

        const int charactersCount = 6;

        Character* characters[charactersCount] = {};



        characters[0] = new Warrior("Batman", 10.2);

        characters[1] = new Enemy("Joker", 5.1, 3);

        characters[2] = new Warrior("Superman", 55.3);

        characters[3] = new Enemy("Ultra-Humanite", 17.2, 10);

        characters[4] = new Warrior("Daredevil", 33.7);

        characters[5] = new Enemy("Wilson Fisk", 3.1, 10);



        for (int i = 0; i < charactersCount; ++i)

        {

            characters[i]->Draw();

        }



        for (int i = 0; i < charactersCount; ++i) {

            if (characters[i])

                delete characters[i];

        }



        cout << endl << endl;

        //TEST WCZYTYWANIA Z PLIKU

        ifstream plik;

        plik.open("poli_data_characters.txt");



        if (!plik) {

            cout << "Blad odczytu pliku";

            exit(1);

        }



        string nazwa, linia;

        double sila, armor;

        int ilosc;

        int k = 0;

        Character* characters2[11] = {};



        while (!plik.eof()) {

            plik >> linia;

            if (plik.eof()) break;



            if (linia == "Warrior") {

                plik >> nazwa;

                plik >> armor;



                characters2[k] = new Warrior(nazwa, armor);

                k++;

            }

            else if (linia == "Enemy") {

                plik >> nazwa;

                plik >> sila;

                plik >> ilosc;



                characters2[k] = new Enemy(nazwa, sila, ilosc);

                k++;

            }

        }



        for (int i = 0; i < 11; i++)

        {

            characters2[i]->Draw();

        }



        for (int i = 0; i < 11; ++i) {

            if (characters2[i])

                delete characters2[i];

        }

    }

    catch (out_of_range& e) {

        cout << e.what() << endl;

    }



    return 0;

}
