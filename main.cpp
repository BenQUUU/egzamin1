#include <iostream>
#include <fstream>
#include<map>
#include<vector>
using namespace std;

/*
struct Zesp{
    double value_re;
    double value_im;
};
*/
class Zesp{
public:
    map<string,double> LiczbaZespolona;
};
class IWektor_Zesp{
public:
    virtual int Dlugosc() = 0;
    virtual void Ustaw(string c, double value, int i) = 0;
    virtual double Pobierz(string c, int i) = 0;
    virtual ~IWektor_Zesp(){
        //wirtualny destruktor
    }
};
class Wektor_Zesp: public IWektor_Zesp{
protected:
    vector<Zesp> wektor;
    int size;
public:
    Wektor_Zesp(){
        size = 0;
    }
    Wektor_Zesp(int sizeW){
        if(sizeW < 0 || sizeW > 100){
            throw out_of_range("Rozmiar wychodzi poza zakres!");
        }
        else{
            size = sizeW;
        }
    }
    int Dlugosc(){
        return size;
    }
    void Ustaw(string c, double value, int i){
        if(c == "re"){
            wektor.push_back(Zesp());
            //wektor[i].value_re = value;
            wektor[i].LiczbaZespolona["re"] = value;
        }
        else{
            //wektor[i].value_im = value;
            wektor[i].LiczbaZespolona["im"] = value;
        }
    }
    double Pobierz(string c, int i){
        if(c == "re"){
            //return wektor[i].value_re;
            return wektor[i].LiczbaZespolona["re"];
        }
        else{
            //return wektor[i].value_im;
            return wektor[i].LiczbaZespolona["im"];
        }
    }

    Wektor_Zesp operator+(Wektor_Zesp &obj){
        Wektor_Zesp wynik;
        if(size != obj.size){
            throw exception();
        }
        else{
            wynik.size = obj.size;
            for(int i = 0; i < obj.size; i++){
                wynik.wektor.push_back(Zesp());
                //wynik.wektor[i].value_re = wektor[i].value_re + obj.wektor[i].value_re;
                //wynik.wektor[i].value_im = wektor[i].value_im + obj.wektor[i].value_im;
                wynik.wektor[i].LiczbaZespolona["re"] = wektor[i].LiczbaZespolona["re"] + obj.wektor[i].LiczbaZespolona["re"];
                wynik.wektor[i].LiczbaZespolona["im"] = wektor[i].LiczbaZespolona["im"] + obj.wektor[i].LiczbaZespolona["im"];
            }
        }
        return wynik;
    }
    Wektor_Zesp operator-(Wektor_Zesp &obj){
        Wektor_Zesp wynik;
        if(size != obj.size){
            throw exception();
        }
        else{
            wynik.size = obj.size;
            for(int i = 0; i < obj.size; i++){
                wynik.wektor.push_back(Zesp());
                //wynik.wektor[i].value_re = wektor[i].value_re - obj.wektor[i].value_re;
                //wynik.wektor[i].value_im = wektor[i].value_im - obj.wektor[i].value_im;
                wynik.wektor[i].LiczbaZespolona["re"] = wektor[i].LiczbaZespolona["re"] - obj.wektor[i].LiczbaZespolona["re"];
                wynik.wektor[i].LiczbaZespolona["im"] = wektor[i].LiczbaZespolona["im"] - obj.wektor[i].LiczbaZespolona["im"];
            }
        }
        return wynik;
    }
    Wektor_Zesp operator*(double liczba){
        Wektor_Zesp wynik;

        wynik.size = size;
        for(int i = 0; i < size; i++){
            wynik.wektor.push_back(Zesp());
            //wynik.wektor[i].value_re = wektor[i].value_re * liczba;
            //wynik.wektor[i].value_im = wektor[i].value_im * liczba;
            wynik.wektor[i].LiczbaZespolona["re"] = wektor[i].LiczbaZespolona["re"] * liczba;
            wynik.wektor[i].LiczbaZespolona["im"] = wektor[i].LiczbaZespolona["im"] * liczba;
        }

        return wynik;
    }
    Wektor_Zesp operator/(double liczba){
        Wektor_Zesp wynik;

        if(liczba == 0) throw runtime_error("Nie mozna dzielic przez zero!");
        wynik.size = size;
        for(int i = 0; i < size; i++){
            wynik.wektor.push_back(Zesp());
            //wynik.wektor[i].value_re = wektor[i].value_re / liczba;
            //wynik.wektor[i].value_im = wektor[i].value_im / liczba;
            wynik.wektor[i].LiczbaZespolona["re"] = wektor[i].LiczbaZespolona["re"] / liczba;
            wynik.wektor[i].LiczbaZespolona["im"] = wektor[i].LiczbaZespolona["im"] / liczba;
        }

        return wynik;
    }
};
class WektorIO: public Wektor_Zesp{
public:
    WektorIO(const Wektor_Zesp &obj): Wektor_Zesp(obj){}
    void Wczytaj(){
        double val = 0;
            for(int i = 0; i < size; i++){
                cout << "Podaj wartosc rzeczywista: ";
                cin >> val;
                Ustaw("re", val, i);
                cout << "Podaj wartosc urojona: ";
                cin >> val;
                Ustaw("im", val, i);
            }
    }
    void Wyswietl(){
        for(int i = 0; i < size; i++){
            if(Pobierz("im", i) < 0){
                cout << Pobierz("re", i) << " - i" << -Pobierz("im", i) << endl;
            }
            else{
                cout << Pobierz("re", i) << " + i" << Pobierz("im", i) << endl;
            }
        }
    }
    void Wczytaj_z_pliku(string nazwa){
        double val = 0;
        ifstream plik;
        plik.open(nazwa);

        if(!plik){
            cout << "Blad odczytu!" << endl;
            exit(1);
        }

        int i = 0;
        while(!plik.eof()){
            if(plik.eof()) break;
            if(i == 0) {
                plik >> size;
                i++;
            }
            else{
                for(int j = 0; j < size; j++){
                    plik >> val;
                    Ustaw("re", val, j);
                    plik >> val;
                    Ustaw("im", val, j);
                }
            }
        }
        plik.close();
    }
    void Zapis_do_pliku(string nazwa){
        ofstream plik;
        plik.open(nazwa, ios::app);

        if(!plik){
            cout << "Blad odczytu!" << endl;
            exit(1);
        }

        plik << size;
        plik << '\n';
        for(int i = 0; i < size; i++){
            plik << Pobierz("re", i) << endl;
            plik << Pobierz("im", i) << endl;
        }
        plik << '\n';

        plik.close();
    }
};


int main() {
    try{
        WektorIO z1(3);
        WektorIO z2(3);
        WektorIO z3(3);
        WektorIO z4(3);
        WektorIO z5(3);
        WektorIO z6(3);
        WektorIO z7(3);

        z1.Wczytaj();
        cout << endl << "z1: " << endl;
        z1.Wyswietl();

        cout << endl;
        z2.Wczytaj_z_pliku("zespolona.txt");
        cout << endl<< "z2: "<< endl;;
        z2.Wyswietl();

        cout << endl;
        z3 = z1 + z2;
        cout << endl << "z3: " << endl;
        z3.Wyswietl();

        cout << endl;
        z4 = z1 - z2;
        cout << endl << "z4: " << endl;
        z4.Wyswietl();

        cout << endl;
        z5 = z4 * 2;
        cout << endl << "z5: " << endl;
        z5.Wyswietl();

        cout << endl;
        z6 = z5 / 5;
        z6.Zapis_do_pliku("wynik.txt");

    }
    catch(out_of_range &e){
        cout << e.what() << endl;
    }
    catch(exception &e){
        cout << "Rozmiary wektorow sa roznej dlugosc!" << endl;
    }
    catch(runtime_error &e){
        cout << e.what() << endl;
    }

    return 0;
}
