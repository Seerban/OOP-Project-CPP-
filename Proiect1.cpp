#include <iostream>
#include <cstring>
using namespace std;
//--------------------------------------------------------------------------------------------------------------------------------
class SistemAlimentare{
    string tipCombustibil;
    unsigned int numarRezervoare;
    float* capacitate; //arr cu fiecare rezervor
    float cantitate; //cantitate totala de combustibil
    double volum; //marimea sistemului

    public:
    //--------GETTERS--------
    string getTipCombustibil() const { return this->tipCombustibil; }
    unsigned int getNumarRezervoare() const { return this->numarRezervoare; }
    const float* getCapacitate() const { return this->capacitate; }
    float getCantitate() const { return this->cantitate; }
    double getVolum() const { return this->volum; } 
    //--------SETTERS--------
    void setTipCombustibil(string s) { this->tipCombustibil = s.length() > 0? s : "Unknown"; }
    void setNumarRezervoare(unsigned int x);
    void setCapacitate(float* arr);
    void setCantitate(float x) { this->cantitate = x < 0? 0 : x < total_capacitate()? x : total_capacitate(); }
    void setVolum(double x) { this->volum = x; }
    //--------CONSTR|DESTR--------
    SistemAlimentare();
    SistemAlimentare(string tipCombustibil, unsigned int numarRezervoare, float* capacitate, float cantitate, double volum);
    SistemAlimentare& operator=(SistemAlimentare& sistem);
    ~SistemAlimentare() { delete[] this->capacitate; }
    //--------METHODS--------
    //print|read
    friend ostream& operator<<(ostream& out, const SistemAlimentare& sistem);
    friend istream& operator>>(istream& in, const SistemAlimentare& sistem);
    //comparatie nivel de combustibil
    bool operator>(SistemAlimentare sistem) { return this->cantitate > sistem.getCantitate(); }
    bool operator<(SistemAlimentare sistem) { return this->cantitate < sistem.getCantitate(); }
    bool operator==(SistemAlimentare sistem) { return this->cantitate == sistem.getCantitate(); }
    //capacitate rezervor anume
    float operator[](unsigned int x);
    //total capacitate
    float total_capacitate() const;
    //procent combustibil
    float procent() const { return 100 * this->cantitate / this->total_capacitate(); }
};
void SistemAlimentare::setNumarRezervoare(unsigned int x)
{
    float* temp = new float[x];
    for(int i = 0; i < x; ++i) temp[i] = i < this->getNumarRezervoare()? this->capacitate[i] : 0;
    delete[] this->capacitate;
    this->capacitate = temp;
    this->numarRezervoare = x > 0? x : 1;
    this->cantitate = this->cantitate > this->total_capacitate()? total_capacitate() : this->cantitate;
}
void SistemAlimentare::setCapacitate(float* arr)
{
    for(int i = 0; i < this->numarRezervoare; ++i) this->capacitate[i] = arr[i] > 0? arr[i] : 0;
    this->cantitate = this->cantitate > total_capacitate()? total_capacitate() : this->cantitate;
}
SistemAlimentare::SistemAlimentare() : tipCombustibil("Jet"), numarRezervoare(2), cantitate(3000), volum(1000)
{
    this->capacitate = new float[2]{2000, 1000};
}
SistemAlimentare::SistemAlimentare(string tipCombustibil, unsigned int numarRezervoare, float* capacitate, float cantitate, double volum) : tipCombustibil(tipCombustibil.length() > 0? tipCombustibil : "Unknown"), numarRezervoare(numarRezervoare > 0? numarRezervoare : 1)
    {
        this->volum = volum > 0? volum : -volum;
        this->capacitate = capacitate;
        for(int i = 0; i < numarRezervoare; ++i) this->capacitate[i] = capacitate[i];
        this->cantitate = cantitate < 0? 0 : cantitate < this->total_capacitate()? cantitate : total_capacitate();
    }
SistemAlimentare& SistemAlimentare::operator=(SistemAlimentare& sistem)
{
    if (this!=&sistem) {
        delete[] this->capacitate;
        this->tipCombustibil = sistem.getTipCombustibil();
        this->numarRezervoare = sistem.getNumarRezervoare();
        this->capacitate = new float[this->numarRezervoare];
        for(int i = 0; i < this->numarRezervoare; ++i) this->capacitate[i] = sistem.getCapacitate()[i];
        this->cantitate = sistem.getCantitate();
        this->volum = sistem.getVolum();
    }
    return *this;
}
float SistemAlimentare::total_capacitate() const
{
    float sum = 0;
    for(int i = 0; i < this->numarRezervoare; ++i) sum += this->capacitate[i];
    return sum;
}
ostream& operator<<(ostream& out, const SistemAlimentare& sistem)
{
    out<<"\nTip combustibil: "<<sistem.getTipCombustibil();
    out<<"\nCapacitate: "<<sistem.total_capacitate();
    out<<" = ";
    for(int i = 0; i < sistem.getNumarRezervoare(); ++i) out<<sistem.getCapacitate()[i]<<' ';
    out<<"\nProcent: "<<sistem.procent();
    out<<"\nVolum: "<<sistem.getVolum();
    return out;
}
istream& operator>>(istream& in, SistemAlimentare* sistem)
{
    string tip;
    unsigned int nr;
    float *capacitate;
    float cantitate;
    double volum;
    cout<<"\nTip: "; in>>tip;
    cout<<"Numar Rezervoare: "; in>>nr;
    for(int i = 0; i < nr; ++i) in>>capacitate[i];
    cout<<"Cantitate: "; in>>cantitate;
    cout<<"Volum: "; in>>volum;
    sistem = new SistemAlimentare(tip, nr, capacitate, cantitate, volum);
    return in;
}
float SistemAlimentare::operator[](unsigned int x)
{
    if (x < 0 || x > this->numarRezervoare) return 0;
    float can = this->cantitate;
    for(int i = 0; i < x; ++i)
        can -= this->capacitate[i];
    return can > this->capacitate[x]? this->capacitate[x] : can < 0? 0 : can;
}
//--------------------------------------------------------------------------------------------------------------------------------
class Fuzelaj{
    float marime[3]; //lungine, inaltime, latime
    double cdr; //coeficient de rezistenta aerodinamica
    float greutate;
    int locuri;
    double volumext; //volum exterior fuzelaj
    double volumint; //volum interior fuzelaj (<vol int)

    public:
    //--------GETTERS--------
    const float* getMarime() const { return this->marime; }
    double getCDR() const { return this->cdr; }
    float getGreutate() const { return this->greutate; }
    int getLocuri() const { return this->locuri; }
    double getVolumExt() const { return this->volumext; }
    double getVolumInt() const { return this->volumint; }
    //--------SETTERS--------
    void setMarime(float x, float y, float z) { this->marime[0] = x; this->marime[1] = y; this->marime[2] = z; }
    void setCDR(double x) { this->cdr = x < 0.04? 0.04 : x; }
    void setGreutate(float x) { this->greutate = x < 0? -x : x; }
    void setLocuri(int x) { this->locuri = x < 1? 1 : x; }
    void setVolumExt(double x) { this->volumext = x > 0? x : 0; this->volumint = this->volumint > x? x : this->volumint; }
    void setVolumInt(double x) { this->volumint = x < 0? 0 : x < this->volumext? x : this->volumext; }
    //--------CONSTR|DESTR--------
    Fuzelaj() : marime({15,5,3}), cdr(0.6), greutate(1000), locuri(5), volumext(10000), volumint(4000) {};
    Fuzelaj(float x, float y, float z) : marime({x,y,z}), cdr(0.6), greutate(1000), locuri(5), volumext(10000), volumint(4000) {};
    Fuzelaj(float x, float y, float z, double cdr, float greutate, int locuri, double volumext, double volumint) : marime({x<0?-x:x, y<0?-y:y, z<0?-z:z}),
        cdr(cdr<0.04?0.04:cdr), greutate(greutate<0?-greutate:greutate), locuri(locuri<1?1:locuri), volumext(volumext<0?0:volumext), volumint(volumint<0? 0 : volumint>volumext? volumext : volumint) {};
    Fuzelaj& operator=(Fuzelaj fuzelaj);
    ~Fuzelaj() {}
    //--------METHODS--------
    //print|read
    friend ostream& operator<<(ostream& out, Fuzelaj& fuzelaj);
    friend istream& operator>>(istream& in, Fuzelaj& fuzelaj);
    //compara marimea fuzelajului (vol ext)
    bool operator>(Fuzelaj &fuzelaj) { return this->volumext > fuzelaj.getVolumExt(); }
    bool operator<(Fuzelaj &fuzelaj) { return this->volumext < fuzelaj.getVolumExt(); }
    bool operator==(Fuzelaj &fuzelaj) { return this->volumext == fuzelaj.getVolumExt(); }
    //marime pe axa x,y,z
    float operator[](char c) { return c == 'x'? this->marime[0] : c == 'y'? this->marime[1] : c == 'z'? marime[2] : 0; }
};
Fuzelaj& Fuzelaj::operator=(Fuzelaj fuzelaj)
{
    if (*this == fuzelaj) return *this;
    this->marime[0] = fuzelaj.getMarime()[0];
    this->marime[1] = fuzelaj.getMarime()[1];
    this->marime[2] = fuzelaj.getMarime()[2];
    this->cdr = fuzelaj.getCDR();
    this->greutate = fuzelaj.getGreutate();
    this->locuri = fuzelaj.getLocuri();
    this->volumext = fuzelaj.getVolumExt();
    this->volumint = fuzelaj.getVolumInt();
    return *this;
}
ostream& operator<<(ostream& out, Fuzelaj& fuzelaj)
{
    out<<"\nMarime: x="<<fuzelaj.getMarime()[0]<<" y="<<fuzelaj.getMarime()[1]<<" z="<<fuzelaj.getMarime()[2];
    out<<"\nCDR: "<<fuzelaj.getCDR();
    out<<"\nGreutate: "<<fuzelaj.getGreutate();
    out<<"\nLocuri: "<<fuzelaj.getLocuri();
    out<<"\nVolum Exterior: "<<int(fuzelaj.getVolumExt());
    out<<"\nVolum Interior: "<<int(fuzelaj.getVolumInt());
    return out;
}
istream& operator>>(istream& in, Fuzelaj& fuzelaj)
{
    float x,y,z,greutate;
    double cdr,vex,vin;
    int locuri;
    cout<<"\nMarime: x="; in>>x; cout<<" y="; in>>y; cout<<"z="; in>>z;
    cout<<"\nCDR: "; in>>cdr;
    cout<<"\nGreutate: "; in>>greutate;
    cout<<"\nLocuri: "; in>>locuri;
    cout<<"\nVolum Exterior: "; in>>vex;
    cout<<"\nVolum Interior: "; in>>vin;
    fuzelaj = Fuzelaj(x,y,z,cdr,greutate,locuri,vex,vin);
    return in;
}
//--------------------------------------------------------------------------------------------------------------------------------
class Motor{
    char tipMotor;
    float consum;
    float putere;
    double volum; //cubic centimeters

    public:
    //--------GETTERS--------
    char getTipMotor() const { return this->tipMotor; }
    float getConsum() const { return this->consum; }
    float getPutere() const { return this->putere; }
    double getVolum() const { return this->volum; }
    //--------SETTERS--------
    void setTipMotor(char c) { strchr("PTIRE", c) != NULL? c : 'P';} //P-Piston T-Turbine I-Inline R-Rotary E-Electric
    void setConsum(float x) { if(x==0) return; this->consum = x>0? x : -x; }
    void setPutere(float x) { if(x==0) return; this->putere = x>0? x : -x; }
    void setVolum(double x) { if(x==0) return; this->volum = x>0? x : -x; }
    //--------CONSTR|DESTR--------
    Motor() : tipMotor('P'), consum(10), putere(100), volum(100) {};
    Motor(char tip) : tipMotor(strchr("PTIRE", tip) != NULL? tip : 'P'), consum(10), putere(100), volum(100) {};
    Motor(char tip, float consum, float putere, double volum) : tipMotor(strchr("PTIRE", tip) != NULL? tip : 'P'),
    consum(consum<0?-consum:consum), putere(putere<0?-putere:putere), volum(volum<0?-volum:volum) {}
    Motor operator=(Motor motor);
    ~Motor(){};
    //Cast explicit
    Motor(string s);
    //Cast implicit
    operator string() { return this->model(); }
    //--------METHODS--------
    //print|read
    friend ostream& operator<<(ostream& out, Motor& motor);
    friend istream& operator>>(istream& in, Motor& motor);
    //adaugare putere
    void operator+(float x) { this->putere += x; }
    void operator-(float x) { this->putere -= x; }
    //numele modelului de motor
    string model() { return this->tipMotor + to_string(int(this->putere)); }
    //eficienta motorului
    float eficienta() { return this->putere / this->consum; }
    //verificare acelasi model
    bool operator==(Motor motor) {return this->model() == motor.model(); }
    //compara puterea
    bool operator>(Motor motor) {return this->putere > motor.getPutere(); }
    bool operator<(Motor motor) {return this->putere < motor.getPutere(); }
};
Motor::Motor(string s)
{
    float putere;
    bool valid = 1;
    if (strchr("PTIRE", s[0]) == NULL) valid = 0;
    if (valid) putere = stoi(s.substr(1));
    if (!valid) *this = Motor();
    else *this = Motor(s[0], 100, putere, 100);
}
Motor Motor::operator=(Motor motor)
{
    if (*this == motor) return *this;
    this->tipMotor = motor.getTipMotor();
    this->consum = motor.getConsum();
    this->putere = motor.getPutere();
    this->volum = motor.getVolum();
    return *this;
}
ostream& operator<<(ostream& out, Motor& motor)
{
    out<<"\n------"<<motor.model()<<"------\n";
    out<<"Motor de tip "<<motor.getTipMotor()<<" cu "<<motor.getPutere()<<" putere";
    out<<"\nVolum: "<<motor.getVolum();
    out<<"\nConsum: "<<motor.getConsum();
    return out;
}
istream& operator>>(istream& in, Motor& motor)
{
    char auxTip;
    float auxConsum, auxPutere;
    double auxVolum;
    in>>auxTip>>auxConsum>>auxPutere>>auxVolum;
    motor = Motor(auxTip, auxConsum, auxPutere, auxVolum);
    return in;
}
//--------------------------------------------------------------------------------------------------------------------------------
class Rotor{
    int nrElice;
    int lenElice;
    double viteza;
    double unghi;

    public:
    //--------GETTERS--------
    int getNrElice() const { return this->nrElice; }
    int getLenElice() const { return this->lenElice; }
    double getViteza() const { return this->viteza; }
    double getUnghi() const { return this->unghi; }
    //--------SETTERS--------
    void setNrElice(int x) { this->nrElice = x>1&&x<20? x : 2; }
    void setLenElice(int x) { this->lenElice = x>0? x : 10; }
    void setViteza(double x) { this->viteza = x; }
    void setUnghi(double x) { this->unghi = x >= -45 && x <= 45 ? x : 0; }
    //--------CONSTR|DESTR--------
    Rotor() : nrElice(2), lenElice(10), viteza(0), unghi(0) {};
    Rotor(int nrElice) : nrElice(nrElice), lenElice(10), viteza(0), unghi(0) {};
    Rotor(int nrElice, int lenElice) : nrElice(nrElice), lenElice(lenElice), viteza(0), unghi(0) {};
    Rotor(int nrElice, int lenElice, double viteza, double unghi);
    Rotor operator=(Rotor);
    friend istream& operator>>(istream& in, Rotor& rotor);
    ~Rotor(){};
    //cast explicit
    Rotor(string model);
    //cast implicit
    operator string() { return this->model(); }
    //--------METHODS--------
    //afisare
    friend ostream& operator<<(ostream& out, const Rotor& rotor);
    //numele modelului
    string model();
    //verificare acelasi model
    bool operator==(Rotor rotor) { return (this->model() == rotor.model())? true : false; }
    //forta simplificata de ridicare
    double fortaRidicare() { return (this->lenElice * this->nrElice * this->viteza);}
    //adaugare/stergere o elice
    void operator++() { this->setNrElice(this->getNrElice() + 1); }
    void operator--() { this->setNrElice(this->getNrElice() - getNrElice() == 2 ? 0 : 1);}
    //comparatie forta de ridicare
    bool operator<(Rotor rotor) { return this->fortaRidicare() < rotor.fortaRidicare();}
    bool operator>(Rotor rotor) { return this->fortaRidicare() > rotor.fortaRidicare();}
};
Rotor::Rotor(string model)
{
    bool valid = 1;
    if (model[0] != 'R' || model.length() < 3)
    {
        valid = 0;
        goto invalid_rmodel;
    }
    else
    {
        this->viteza = 0;
        this->unghi = 0;
        if (model[1] == '1')
        {
            this->nrElice = stoi(model.substr(1,2));
            if (model.length() < 4 || model[3] == '0')
            {
                valid = 0;
                goto invalid_rmodel;
            }
            this->lenElice = stoi(model.substr(3));
        }
        else
        {
            this->nrElice = stoi(model.substr(1,1));
            if (model.length() < 3 || model[2] == '0')
            {
                valid = 0;
                goto invalid_rmodel;
            }
            this->lenElice = stoi(model.substr(2));
        }
    invalid_rmodel:
        if (valid == 0)
        {
            *this = Rotor();
            cout<<"\n "<<model<<" Model Invalid\n";
        }
    }
}
Rotor::Rotor(int nrElice, int lenElice, double viteza, double unghi) : nrElice(nrElice), lenElice(lenElice), viteza(viteza), unghi(unghi)
{
    if (nrElice<2 || nrElice>19 || lenElice <= 0)
    {
        *this = Rotor();
        cout<<"Numar Invalid\n";
    }
}
string Rotor::model()
{
    return 'R' + to_string(this->getNrElice()) + to_string(this->getLenElice());
}
Rotor Rotor::operator=(Rotor rotor)
{
    if (*this == rotor) return *this;
    this->nrElice = rotor.getNrElice();
    this->lenElice = rotor.getLenElice();
    this->viteza = rotor.getViteza();
    this->unghi = rotor.getUnghi();
}
ostream& operator<<(ostream& out, Rotor& rotor)
{
    out<<"\n------"<<rotor.model()<<"------\n";
    out<<rotor.getNrElice()<<" elice cu len "<<rotor.getLenElice()<<"\n";
    out<<"Viteza este "<<rotor.getViteza();
    out<<"\nUnghiul este "<<rotor.getUnghi();
    return out;
}
istream& operator>>(istream& in, Rotor& rotor)
{
    string s;
    cout<<"Model ('R' + NrElice + LenElice): "; in>>s;
    rotor = Rotor(s);
    return in;
}
//--------------------------------------------------------------------------------------------------------------------------------
class Elicopter{
    static int id;
    string nume;
    int anFabricare;
    Fuzelaj* fuzelaj;
    Motor* motor;
    Rotor* rotor;
    SistemAlimentare* alimentare;
    unsigned int orePornit;

    public:
    //--------GETTERS--------
    static int getId() { return id; }
    string getNume() const { return this->nume; }
    int getAnFabricare() const { return this->anFabricare; }
    Fuzelaj getFuzelaj()  { return *this->fuzelaj; }
    Motor getMotor()  { return *this->motor; }
    Rotor getRotor()  { return *this->rotor; }
    SistemAlimentare& getAlimentare() { return *this->alimentare; }
    int getOrePornit() const { return this->orePornit; }
    //--------SETTERS--------
    void setNume(string s) { this->nume = s.length() > 0? s : "Unknown"; }
    void setFuzelaj(Fuzelaj fuzelaj) { this->fuzelaj = &fuzelaj; }
    void setMotor(Motor motor) { this->motor = &motor; }
    void setRotor(Rotor rotor) { this->rotor = &rotor; }
    void setAlimentare(SistemAlimentare alimentare) { this->alimentare = &alimentare; }
    void setOrePornit(unsigned int x) { this->orePornit = x; }
    //--------CONSTR|DESTR--------
    Elicopter() : nume("Prototip " + to_string(id)), anFabricare(2024), fuzelaj(new Fuzelaj()), motor(new Motor()), rotor(new Rotor()), alimentare(new SistemAlimentare()), orePornit(0) {this->id++;}; 
    Elicopter(string nume) : nume(nume.length()>0? nume : "Prototip"+to_string(id)), anFabricare(2024), fuzelaj(new Fuzelaj()), motor(new Motor()), rotor(new Rotor()), alimentare(new SistemAlimentare()), orePornit(0) {this->id++;};
    Elicopter(string nume, int an, Fuzelaj fuz, Motor mot, Rotor rot, SistemAlimentare alim, int ore) : nume(nume.length()>0? nume : "Prototip"+to_string(id)), anFabricare(an), fuzelaj(&fuz), motor(&mot),
        rotor(&rot), alimentare(&alim), orePornit(ore<0?0:ore) {};
    ~Elicopter() { delete alimentare; delete fuzelaj; delete motor; delete rotor; }
    //cast implicit
    operator string() { return this->model(); }
    //--------METHODS--------
    //afisare simplu | detaliat
    friend ostream& operator<<(ostream& out, Elicopter elicopter);
    void detalii();
    Elicopter& operator=(Elicopter elicopter);
    //inc/dec ore pornite
    void operator++() { this->orePornit++; }
    void operator--() { this->orePornit -= this->orePornit? 1 : 0; }
    //model
    string model() { return this->nume + ' ' + string(*this->rotor) + ' ' + string(*this->motor); }
    //volum interior
    double volumInterior() { return this->fuzelaj->getVolumInt() - this->motor->getVolum() - this->alimentare->getVolum(); }
    double eficienta() { return 1 / this->fuzelaj->getCDR() * this->motor->eficienta(); }
    double ridicare() { return this->rotor->fortaRidicare() - this->fuzelaj->getGreutate(); }
};
ostream& operator<<(ostream& out, Elicopter elicopter)
{
    out<<"----"<<elicopter.getNume()<<"----"<<"An: "<<elicopter.getAnFabricare();
    out<<"\nMotor: "<<elicopter.getMotor().model();
    out<<"\nRotor: "<<elicopter.getRotor().model();
    //out<<"\nDimensiuni: x="<<elicopter.getFuzelaj().getMarime()[0]<<" y="<<elicopter.getFuzelaj().getMarime()[1]<<" z="<<elicopter.getFuzelaj().getMarime()[2];
    out<<"\nCombustibil: "<<elicopter.getAlimentare().procent()<<"% ("<<elicopter.getAlimentare().getCantitate()<<"/"<<elicopter.getAlimentare().total_capacitate()<<")\n";
    return out;
}
Elicopter& Elicopter::operator=(Elicopter elicopter)
{
    this->nume = elicopter.getNume();
    this->anFabricare = elicopter.getAnFabricare();
    *this->fuzelaj = elicopter.getFuzelaj();
    *this->motor = elicopter.getMotor();
    *this->rotor = elicopter.getRotor();
    *this->alimentare = elicopter.getAlimentare();
    this->orePornit = elicopter.getOrePornit();
    return *this;
}
void Elicopter::detalii()
{
    cout<<"----"<<this->nume<<' '<<this->anFabricare<<"----Ore: "<<this->orePornit<<"----";
    cout<<*this->fuzelaj;
    cout<<*this->motor;
    cout<<*this->rotor;
    cout<<"\nCombustibil: "<<this->alimentare->getCantitate()<<'/'<<this->alimentare->total_capacitate();
}
int Elicopter::id = 1;
//--------------------------------------------------------------------------------------------------------------------------------
int main()
{
    //Elicopter(Nume, An, Fuzelaj, Motor, Rotor, Alimentare, Ore)
    //Fuzelaj(x, y, z, cdr(rezistenta), greutate, locuri, volum_exterior, volum_interior)
    //Motor(tip(P|T|I|R|E), eficienta, putere, volum)
    //Rotor(nr elice, len elice, viteza, unghi)
    //SistemAlimentare(tip, nr rezervoare, array rezervoare, cantitate combustibil, volum)
    Elicopter x = Elicopter("Copter A");
    Elicopter y;
    cout<<x<<'\n'<<y<<'\n';;



    float rezervoare[4]{200,150,150,50};
    Elicopter apache = Elicopter("AH-64 Apache", 1997, Fuzelaj(15.06, 3.87, 4.1, 0.7, 8006, 3, 1000, 500), Motor('I', 100, 1600, 200), Rotor(4, 14, 0, 0), SistemAlimentare("A", 4, rezervoare, 300, 200), 0);
    apache.detalii();

    cout<<'\n'<<apache.eficienta()<<' '<<apache.volumInterior();
    Motor M1 = Motor('R', 80, 1800, 250); //Motor mai eficient dar mai mare
    apache.setMotor(M1);
    cout<<'\n'<<apache.eficienta()<<' '<<apache.volumInterior();

    cout<<"\n\nElicele nu se misca "<<apache.ridicare()<<"  \"Forta de ridicare\"";
    Rotor R1 = Rotor(4, 14, 100, 5); 
    apache.setRotor(R1);
    cout<<"\nElicele la viteza 200 si unghi 5: "<<apache.ridicare();
    cout<<"\nAdaugam 2 elice: ";
    ++R1; ++R1;
    apache.setRotor(R1);
    cout<<apache.ridicare();

    cout<<"\nCombustibil in toate rezervoarele: ";
    for(int i = 0; i < apache.getAlimentare().getNumarRezervoare(); ++i) cout<<i+1<<':'<<apache.getAlimentare()[i]<<'/'<<apache.getAlimentare().getCapacitate()[i]<<' ';

    cout<<"\n\n"<<string(apache);
}