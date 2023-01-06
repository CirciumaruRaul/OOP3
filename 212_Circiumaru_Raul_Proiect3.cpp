#include <iostream>
#include <typeinfo>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string.h>
#include <stdexcept>
#include <stdexcept>

using namespace std;
using std::runtime_error;

void Clear()
{
    #if defined _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

template <class T>
class Repository
{
protected:
    vector<T*> elemente;
public:
    void AdaugaElement(T* element)
    {
        this->elemente.push_back(element);
    }
    void StergeElement(T* element)
    {
        typename vector<T*>::iterator it;
        for (it = this->elemente.begin(); it != this->elemente.end(); it++)
        {
            if (*it == element)
            {
                this->elemente.erase(it);
                break;
            }
        }
    }
    void StergeElement(int pozitie)
    {
        this->elemente.erase(this->elemente.begin() + pozitie);
    }
};

template<class T>
void Citire(T& x)
{
    cin >> x;
}

template<typename Container>
void delete_them(Container& c) { 
    while(!c.empty()){
        delete c.back();

    }
}

class IOinterface
{
public:
    virtual istream& citire(istream& in)= 0;
    virtual ostream& afisare(ostream& out) const = 0;
};

class Obiecte:public IOinterface
{
protected:
    float pret;
    string nume;
    const int iD;
    static int contor;
public:
    Obiecte():iD(contor++){
        this->pret = 10.0;
        this->nume = "Ceva";
    }
    Obiecte(float pret, string nume):iD(contor++){
        this->pret = pret;
        this->nume = nume;
    }
    Obiecte(const Obiecte& O):iD(contor++)
    {
        this->pret = O.pret;
        this->nume = O.nume;
    }
    Obiecte& operator= (const Obiecte& O)
    {
        if(this != &O)
            this->pret = O.pret;
            this->nume = O.nume;
        return *this;
    }
    Obiecte operator+(float i)
    {
        Obiecte aux(*this);
        aux.pret +=i;
        return aux;
    }
    friend Obiecte operator +(Obiecte O, Obiecte A)
    {
        Obiecte aux;
        aux.nume = O.nume + "+" + A.nume;
        aux.pret = O.pret + A.pret;
        return aux;
    }
    void  setmodifPret(float i)
    {
        if (i > 0){
            this->pret = this->pret + (this->pret * (i/100));
        }
        else{
            this->pret = this->pret - (this->pret * (abs(i)/100));
        }
    }
    string getnume()
    {
        return this->nume;
    }
    istream& citire(istream& in)
    {
        cout<<"Care este numele?\n";
        in>>this->nume;
        cout<<"Pretul este de: "<<" ";
        in>>this->pret;
        return in;
    }
    friend istream& operator >> (istream& in, Obiecte& O)
    {
        return O.citire(in);
    }
    ostream& afisare(ostream& out)const
    {
        out<<"Nume: "<<this->nume<<endl;
        out<<"Pret: "<<this->pret<<endl;
        return out;
    }
    friend ostream& operator << (ostream& out, const Obiecte& O)
    {
        return O.afisare(out);
    }
    virtual void print(){cout<<"da";}
    ~Obiecte(){}
};
class Amplificator:public Obiecte
{
protected:
    int amperi;
public:
    Amplificator():Obiecte()
    {
        this->amperi = 1;
    }
    Amplificator(int pret, string nume, int amperi):Obiecte(pret, nume)
    {
        this->amperi = amperi;
    }
    Amplificator(const Amplificator& A):Obiecte(A)
    {
        this->amperi = A.amperi;
    }
    Amplificator operator = (const Amplificator& A)
    {
        if (this != &A)
        {
            Obiecte::operator=(A);
            this->amperi = A.amperi;
        }
        return *this;
    }
    istream& citire(istream& in)
    {
        Obiecte::citire(in);
        cout<<"Care sunt amperi de iesire?\n";
        in>>this->amperi;
        return in;
    }
    ostream& afisare(ostream& out)const
    {
        Obiecte::afisare(out);
        out<<"Amperii de iesire sunt:";
        out<<this->amperi;
        return out;
    }
    void print(){cout<<"poate";}
    ~Amplificator(){}
};

class AmplificatorCuBoxa:public Amplificator
{
protected:
    int decibeli;
public:
    AmplificatorCuBoxa():Amplificator()
    {
        this->decibeli = 10;
    }
    AmplificatorCuBoxa(int pret, string nume, int amperi, int decibeli):Amplificator(pret,nume,amperi)
    {
        this->decibeli = decibeli;
    }
    AmplificatorCuBoxa(const AmplificatorCuBoxa& ACB):Amplificator(ACB)
    {
        this->decibeli = ACB.decibeli;
    }
    AmplificatorCuBoxa operator= (const AmplificatorCuBoxa& ACB)
    {
        if (this != &ACB)
        {
            Amplificator::operator=(ACB);
            this->decibeli = ACB.decibeli;
        }
        return *this;
    }
    istream& citire(istream& in)
    {
        Amplificator::citire(in);
        cout<<"Care sunt decibelii maximi pe care ii poate atinge ACB-ul?\n";
        in>>this->decibeli;
        return in;
    }   
    ostream& afisare(ostream& out)
    {
        Amplificator::afisare(out);
        out<<"Decibelii pe care ii poate atinge ACB-ul sunt:"<<this->decibeli;
        return out;
    }
    void print(){cout<<"daca";}
    ~AmplificatorCuBoxa(){}
};

class Acoustica:virtual public Obiecte
{
protected:
    int cutieRez;
    float marime;
public:
    Acoustica():Obiecte()
    {
        this->cutieRez = 8;
        this->marime = 4;
    }
    Acoustica(int pret, string nume, int cutieRez, float marime):Obiecte(pret, nume)
    {
        this->cutieRez = cutieRez;
        this->marime = marime;
    }
    Acoustica(const Acoustica& A):Obiecte(A)
    {
        this->cutieRez = A.cutieRez;
        this->marime = A.marime;
    }
    Acoustica& operator = (const Acoustica& A)
    {
        if(this != &A)
        {
            Obiecte::operator=(A);
            this->cutieRez = A.cutieRez;
            this->marime = A.marime;
        }
        return *this;
    }
    istream& citire(istream& in)
    {
        Obiecte::citire(in);
        cout<<"Volumul cutiei de rezonanta este: \n";
        in>>this->cutieRez;
        cout<<"Marimea chitarii este de: \n";
        in>>this->marime;
        return in;
    }
    ostream& afisare(ostream& out)const
    {
        Obiecte::afisare(out);
        out<<"Volumul este de: "<<this->cutieRez<<endl;
        out<<"Marimea este de: "<<this->marime<<"/4"<<endl;
        return out;
    }
    void print(){cout<<"poate1";}
    ~Acoustica(){}
};

class Electrica:virtual public Obiecte
{
protected:
    string doze;
    bool floydrose;
public:
    Electrica():Obiecte()
    {
        this->doze = "de calitate superioara";
        this->floydrose = true;
    }
    Electrica( int pret, string nume, string doze, bool floydrose):Obiecte(pret, nume)
    {
        this->doze = doze;
        this->floydrose =floydrose;
    }
    Electrica(const Electrica& E):Obiecte(E)
    {
        this->doze = E.doze;
        this->floydrose = E.floydrose;
    }
    Electrica& operator = (const Electrica& E)
    {
        if(this != &E)
        {
            Obiecte::operator=(E);
            this->doze = E.doze;
            this->floydrose= E.floydrose;
        }
        return *this;
    }
    istream& citire(istream& in)
    {
        Obiecte::citire(in);
        cout<<"Dozele echipate sunt: \n";
        in>>this->doze;
        cout<<"Are floydrose sau nu?(1 or 0) \n";
        in>>this->floydrose;
        return in;
    }
    ostream& afisare(ostream& out)const
    {
        Obiecte::afisare(out);
        out<<"Dozele sunt: "<<this->doze<<endl;
        out<<"Floydrose: "<<this->floydrose<<endl;
        return out;
    }
    void setdoze(string doza)
    {
        this->doze = doza;
    }
    void print(){cout<<"poate2";}
    ~Electrica(){}
};

class ElectroAcoustic:public Acoustica, public Electrica
{
private:
    bool baterie;
public:
    ElectroAcoustic():Acoustica(),Electrica(), Obiecte()
    {
        this->baterie = true;
    }
    ElectroAcoustic(int pret, string nume,int cutieRez, float marime, string doze, bool floydrose, bool baterie):Acoustica(pret,nume,cutieRez,marime), Electrica(pret, nume, doze, floydrose), Obiecte(pret, nume)
    {
        this->baterie = baterie;
    }
    ElectroAcoustic(const ElectroAcoustic& EA):Electrica(EA)
    {
        this->cutieRez = EA.cutieRez;
        this->marime = EA.marime;
        this->baterie = EA.baterie;
    }
    ElectroAcoustic& operator = (const ElectroAcoustic& EA)
    {
        if (this != &EA)
        {
            Electrica::operator=(EA);
            this->cutieRez = EA.cutieRez;
            this->marime = EA.marime;
            this->baterie = EA.baterie;
        }   
        return *this;
    }
    istream& citire(istream& in)
    {
        Acoustica::citire(in);
        cout<<"Ce doze are?\n";
        in>>this->doze;
        cout<<"Are floydrose sau nu?(true or false) \n";
        in>>this->floydrose;
        cout<<"Are baterie?(true or false)\n";
        in>>this->baterie;
        return in;
    }
    ostream& afisare(ostream& out)const
    {
        Acoustica::afisare(out);
        out<<"Dozele sunt: "<<this->doze<<endl;
        out<<"Floydrose: "<<this->floydrose<<endl;
        out<<"Baterie:"<<this->baterie<<endl;
        return out;
    }
    void print(){cout<<"poate3";}
    ~ElectroAcoustic(){}
};
class MeniuSingleton:public Repository<Obiecte>
{
private:
    static MeniuSingleton *obiect;
    MeniuSingleton(){}
public:
    static MeniuSingleton* getInstance()
    {
        if(!obiect)
            obiect = new MeniuSingleton();
        return obiect;
    }
    void MainMenu()
    {
        Repository R;
        Acoustica ac;
        Amplificator a;
        AmplificatorCuBoxa acb;
        Electrica e;
        ElectroAcoustic ea;
        set<string> ObiecteleDinMagazin;
        ObiecteleDinMagazin.insert("Amplificator");
        ObiecteleDinMagazin.insert("AmplificatorCuBoxa");
        ObiecteleDinMagazin.insert("Acoustica");
        ObiecteleDinMagazin.insert("Electrica");
        ObiecteleDinMagazin.insert("Electro-Acoustica");
        vector<Obiecte*> v;
        v.push_back(&a);
        v.push_back(&acb);
        v.push_back(&e);
        R.AdaugaElement(&a);
        R.AdaugaElement(&acb);
        R.AdaugaElement(&e);
        map<string,int> Stoc;
        Stoc["Amplificator"] = 1;
        Stoc["AmplificatorCuBoxa"] = 1;
        Stoc["Acoustica"] = 0;
        Stoc["Electrica"] = 1;
        Stoc["ElectroAcoustica"] = 0;
        list<Obiecte*> ListaCumparaturi;
        Clear();
        while(1)
        {
            try{
            cout << "Te rog alege o optiune:\n";
            cout << "1. Adauga un nou obiect:\n";
            cout << "2. Afisaza stocul de obiecte din magazin:\n";
            cout << "3. Creaza o comanda:\n";
            cout << "4. Sterge obiecte din comanda:\n";
            cout << "0: Inchide programul.\n";
            string comanda;
            string x;
            Citire(comanda);
                if(comanda == "1")
                {
                    Clear();
                    int i = 0;
                    cout<< "Ce fel de obiect vrei sa adaugi?\n";
                    set<string>::iterator it;
                    for(it = ObiecteleDinMagazin.begin(); it != ObiecteleDinMagazin.end();++it)
                    {
                        cout<<i<<" "<<*it<<"\n";
                        ++i;
                    }
                    Citire(x);
                    if (x == "1")
                    {
                        Obiecte *O = dynamic_cast<Obiecte*>(&a);
                        cout<<"Ai selectat Amplificator:\n";
                        Amplificator* Am = dynamic_cast<Amplificator*>(O);
                        while(1)
                        {
                            cout<<"Introdu datele:\n";
                            if(cin>>*Am)
                            break;
                            cout<<"Datele nu corespund!\n";
                            cin.clear();
                        }
                        v.push_back(&*Am);
                        R.AdaugaElement(&*Am);
                        Stoc["Amplificator"] ++;
                        Clear();
                    }
                    else if (x == "2")
                    {
                        Obiecte *A = dynamic_cast<Obiecte*>(&acb);
                        cout << "Ai selectat Amplificator cu boxe";
                        AmplificatorCuBoxa* ACB = dynamic_cast<AmplificatorCuBoxa*>(A);
                        while(1)
                        {
                            cout<<"Introdu datele:\n";
                            if(cin>>*ACB)
                            break;
                            cout<<"Datele nu corespund!\n";
                            cin.clear();
                        }
                        v.push_back(&*ACB);
                        R.AdaugaElement(&*ACB);
                        Stoc["AmplificatorCuBoxa"]++;
                        Clear();
                    }
                    else if (x == "3")
                    {
                        Obiecte *O = dynamic_cast<Obiecte*>(&e);
                        cout << "Ai selectat Electrica\n";
                        Electrica* E = dynamic_cast<Electrica*>(O);
                        while(1)
                        {
                            cout<<"Introdu datele:\n";
                            if(cin>>*E)
                            break;
                            cout<<"Datele nu corespund!\n";
                            cin.clear();
                        }
                        v.push_back(&*E);
                        R.AdaugaElement(&*E);
                        Stoc["Electrica"]++;
                        Clear();
                    }
                    else if(x == "4")
                    {
                        Obiecte *O = dynamic_cast<Obiecte*>(&ea);
                        cout << "Ai selectat ElectroAcoustic\n";
                        ElectroAcoustic* EA = dynamic_cast<ElectroAcoustic*>(O);
                        while(1)
                        {
                            cout<<"Introdu datele:\n";
                            if(cin>>*EA)
                            break;
                            cout<<"Datele nu corespund!\n";
                            cin.clear();
                        }
                        v.push_back(&*EA);
                        R.AdaugaElement(*&EA);
                        Stoc["ElectroAcoustica"]++;
                        Clear();
                    }
                    else if(x == "0")
                    {
                        Obiecte* O = dynamic_cast<Obiecte*>(&ac);
                        cout << "Ai selectat Acoustica\n";
                        Acoustica* A = dynamic_cast<Acoustica*>(O);
                        while(1)
                        {
                            cout<<"Introdu datele:\n";
                            if(cin>>*A)
                            break;
                            Clear();
                            cout<<"Datele nu corespund!\n";
                            cin.clear();
                        }
                        v.push_back(&*A);
                        R.AdaugaElement(&*A);
                        Stoc["Acoustica"]++;
                        Clear();
                    }
                    else
                    {
                        throw x;
                    }
                }
                else if(comanda == "2")
                {
                    map<string,int>::iterator it = Stoc.begin();
                    while(it != Stoc.end())
                    {
                        cout<<it->first<<":"<<it->second<<endl;
                        ++it;
                    }
                    cout<<"Introdu orice pentru a revenii la meiniul principal!\n";
                    Citire(x);
                    Clear();
                }
                else if(comanda == "3")
                {
                    Clear();
                    Obiecte aux;
                    cout<<"Ce obiecte vrei sa adaugi la comanda ta?\n";
                    int j,i;
                    for(int i=0; i < v.size(); i++)
                    {
                        cout<<i<<endl<<*v[i]<<endl<<endl;
                    }
                    cout<<"Ai ales sa adaugi un obiect la comanda!\n";
                    cin.get();
                    i = 1;
                    if(i!=0){
                    while(1)
                    {
                        cout<<"Introdu indexul obiectului:\n";
                        cin >> j;
                        if(cin){
                            if(j>=0 && j<v.size())
                                break;
                        }
                        else
                            cout<<"Indexul nu corespunde!\n";
                        cin.clear();
                        cin.ignore(1000,'\n');
                    }
                    i--;
                    ListaCumparaturi.push_back(v[j]);
                    auto it = v.begin();
                    advance(it,j);
                    v.erase(it);
                    if(dynamic_cast<Amplificator*>(v[j]))
                    {
                        //ai ramas aici boule ca nu se modifica vectorul de obiecte din magazin!
                        Stoc["Amplificator"]--;
                    }
                    else if(dynamic_cast<AmplificatorCuBoxa*>(v[j]))
                    {
                        Stoc["AmplificatorCuBoxa"]--;
                    }
                    else if(dynamic_cast<Acoustica*>(v[j]))
                    {
                        Stoc["Acoustica"]--;
                    }
                    else if(dynamic_cast<Electrica*>(v[j]))
                    {
                        Stoc["Electrica"]--;
                    }
                    else if(dynamic_cast<ElectroAcoustic*>(v[j]))
                    {
                        Stoc["ElectroAcoustica"]--;
                    }
                    aux = aux + *v[j];
                    cout<<"Doresti sa continui la check-out?\nApasa 1 pentru check-out sau 2 pentru revenire la meniul pricipal.\n";
                    cin>>x;
                    if(x == "1")
                    {
                        cout<<"Comanda ta este:\n";
                        cout<<aux<<endl;
                        cin.get();
                        cin.get();
                        ListaCumparaturi.clear();
                        exit(1);
                    }
                    else if (x == "2")
                    {
                        cout<<"\n";
                        cin.get();
                    }
                    else
                        throw x;
                }
                else{
                    cout<<"----------------\n";
                    cout<<"De ce ai ales 0?\nCine credea ca uit de 0?\n";
                    cout<<"----------------\n";
                }
                }
                else if(comanda == "4")
                {
                    Clear();
                    if(ListaCumparaturi.size() == 0)
                    {
                        cout<<"Nu ai nimic in cosul de cumparaturi.\n";
                    }
                    else if(ListaCumparaturi.size()==1)
                    {
                        list<Obiecte*>::iterator i = ListaCumparaturi.begin();
                        v.push_back(*i);
                        int n = v.size();
                        if(dynamic_cast<Amplificator*>(v[n-1]))
                        {
                            Stoc["Amplificator"]++;
                        }
                        else if(dynamic_cast<AmplificatorCuBoxa*>(v[n-1]))
                        {
                            Stoc["AmplificatorCuBoxa"]++;
                        }
                        else if(dynamic_cast<Acoustica*>(v[n-1]))
                        {
                            Stoc["Acoustica"]++;
                        }
                        else if(dynamic_cast<Electrica*>(v[n-1]))
                        {
                            Stoc["Electrica"]++;
                        }
                        else if(dynamic_cast<ElectroAcoustic*>(v[n-1]))
                        {
                            Stoc["ElectroAcoustica"]++;
                        }
                        ListaCumparaturi.clear();
                        cout<<"Ai sters singurului obiect din cosul de cumparaturi!\n";
                    }
                    else
                    {
                    list<Obiecte*>::iterator iter;
                    int i,pozitie = 0;
                    for (iter = ListaCumparaturi.begin(); iter != ListaCumparaturi.end(); ++iter)
                    {
                        cout<<pozitie<<endl<<**iter<<endl;
                        pozitie++;
                    }
                    cout<<"Te rog, selecteaza indexul obiectului pe care il doresti sa il stergi!\n";
                    cin>>i;
                    if(i>=0 && i < ListaCumparaturi.size())
                    {
                        for (iter = ListaCumparaturi.begin(); iter != ListaCumparaturi.end(); ++iter)
                            if(i == 0)
                                break;
                            else
                                i--;
                        v.push_back(*iter);
                        R.AdaugaElement(*iter);
                        int n = v.size();
                        if(dynamic_cast<Amplificator*>(v[n-1]))
                        {
                            Stoc["Amplificator"]++;
                        }
                        else if(dynamic_cast<AmplificatorCuBoxa*>(v[n-1]))
                        {
                            Stoc["AmplificatorCuBoxa"]++;
                        }
                        else if(dynamic_cast<Acoustica*>(v[n-1]))
                        {
                            Stoc["Acoustica"]++;
                        }
                        else if(dynamic_cast<Electrica*>(v[n-1]))
                        {
                            Stoc["Electrica"]++;
                        }
                        else if(dynamic_cast<ElectroAcoustic*>(v[n-1]))
                        {
                            Stoc["ElectroAcoustica"]++;
                        }
                        ListaCumparaturi.erase(iter);
                        delete *iter;
                    }
                    else
                    {
                        throw i;
                    }
                    cout<<"Apasa enter pentru a revenii la meiniul principal!\n";
                    cin.get();
                    }
                }
                else if(comanda == "0")
                {
                    exit(1);
                }
                else
                    throw comanda;
            }
            catch(int)
            {
                Clear();
                cout<<"Index out of bounds!\n";
            }
            catch(string da){
                Clear();
                cout<<"Optiunea introdusa este invalida, te rog incearca din nou!\n";
            }
        }
    }
};
MeniuSingleton * MeniuSingleton::obiect = 0;
int Obiecte::contor = 1;

int main()
{   
    MeniuSingleton *meniu = meniu->getInstance();
    meniu->MainMenu();
    return 0;
}
