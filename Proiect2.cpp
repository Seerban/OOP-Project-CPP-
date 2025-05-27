#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

class IO {
public:
    virtual ostream& afis(ostream& out) const = 0;
    virtual istream& citire(istream& in) = 0;    
};
//----------------------------------------------------------------
class Haina : public IO {
protected:
    unsigned int marime;
    float pret;
    vector<pair<string, float>> materiale;
public:
    //getters
    unsigned int getMarime() { return this->marime; }
    float getPret() { return this->pret; }
    vector<pair<string,float>> getMateriale() { return this->materiale; }
    //setters
    void setMarime(unsigned int m) { this->marime = m; }
    void setPret(float pret) { this->pret = pret > 0? pret : -pret; }
    void setMateriale(vector<pair<string,float>> mat) { this->materiale = mat; }
    //read?
    void readMarime() { cin>>this->marime; }
    void readPret() { cin>>this->pret; }
    void readMateriale();
    //operatori
    Haina operator+(const float f);
    Haina operator-(const float f);
    //constructor
    Haina();
    Haina(unsigned int marime, float pret, vector<pair<string,float>> materiale) : marime(marime), pret(pret), materiale(materiale) {}
    Haina(const Haina& h);
    Haina& operator=(const Haina& h);
    //IO
    virtual istream& citire(istream& in);
    virtual ostream& afis(ostream& out) const;
    friend ostream& operator<<(ostream& out, const Haina& h) { return h.afis(out); }
    friend istream& operator>>(istream& in, Haina& h) { return h.citire(in); }
    //materiale total 100%
    void fixMateriale();    
};
Haina::Haina()
    {
        this->marime = 10;
        this->pret = 100;
        this->materiale = {{"Bumbac", 80}, {"Matase", 20}};
    }
Haina::Haina(const Haina& h)
{
    this->marime = h.marime;
    this->pret = h.pret;
    this->materiale = h.materiale;
}
ostream& Haina::afis(ostream& out) const
{
    out<<"Marime "<<this->marime<<" | Pret "<<this->pret<<" | Materiale ";
    for(int i = 0; i < this->materiale.size(); ++i)
        out<<this->materiale[i].first<<' '<<this->materiale[i].second<<"% ";
    return out;
}
istream& Haina::citire(istream& in)
{
    cout<<"\nMarime (uint): "; in>>this->marime;
    cout<<"\nPret (float): "; in>>this->pret;
    int n;
    cout<<"\nNR Materiale: "; in>>n;
    this->materiale.clear();
    for(int i = 0; i < n; ++i)
    {
        string s;
        cout<<"Material (str): "; in>>s;
        float p;
        cout<<"Procent (float): "; in>>p;
        this->materiale.push_back(make_pair(s, p));
    }
    return in;
}
void Haina::fixMateriale()
{
    float sum = 0;
    for(int i = 0; i < this->materiale.size(); ++i) sum += this->materiale[i].second;
    float coef = 100 / sum;
    for(int i = 0; i < this->materiale.size(); ++i) this->materiale[i] = make_pair(this->materiale[i].first, this->materiale[i].second * coef);
}
Haina& Haina::operator=(const Haina& h)
{
    if( this != &h)
    {
        this->marime = h.marime;
        this->pret = h.pret;
        this->materiale = h.materiale;
    }
    return *this;
}
void Haina::readMateriale()
{
    this->materiale.clear();
    int i; cin>>i;
    for(i; i > 0; --i) {
        string s; float f;
        cin>>s>>f;
        this->materiale.push_back(make_pair(s, f));
    }
}
Haina Haina::operator+(const float f)
{
    Haina x = *this;
    x.pret = x.pret + f;
    return x;
}
Haina Haina::operator-(const float f)
{
    Haina x = *this;
    x.pret = x.pret - f;
    return x;
}

//----------------------------------------------------------------
class Bluza : public virtual Haina {
protected:
    string guler;
public:
    string getGuler() { return this->guler; }
    void setGuler(string gul) { this->guler = gul; }
    void readGuler() { cin>>this->guler; }
    //constr
    Bluza() : Haina(), guler("Spread") {}
    Bluza(unsigned int marime, float pret, vector<pair<string,float>> materiale, string guler)
        : Haina(marime, pret, materiale), guler(guler) {}
    Bluza(const Bluza& b);
    Bluza& operator=(const Bluza& b);
    //IO
    virtual ostream& afis(ostream& out) const;
    virtual istream& citire(istream& in);
    friend ostream& operator<<(ostream& out, Bluza& b) { return b.afis(out); }
    friend istream& operator>>(istream& in, Bluza& b) { return b.citire(in); }
    //random guler
    void randGuler();
};
Bluza::Bluza(const Bluza& b)
{
    this->marime = b.marime;
    this->pret = b.pret;
    this->materiale = b.materiale;
    this->guler = b.guler;
}
Bluza& Bluza::operator=(const Bluza& b)
{
    if( this != &b)
    {
        this->marime = b.marime;
        this->pret = b.pret;
        this->materiale = b.materiale;
        this->guler = b.guler;
    }
    return *this;
}
ostream& Bluza::afis(ostream& out) const
{
    Haina::afis(out);
    out<<"| Guler: "<<this->guler;
    return out;
}
istream& Bluza::citire(istream& in)
{
    Haina::citire(in);
    cout<<"Guler (str): "; in>>this->guler;
    return in;
}
void Bluza::randGuler()
{
    srand(time(NULL));
    vector<string> gulere = {"Straight", "Spread", "Cutaway", "Button Down", "Snap Tab", "Club"};
    this->guler = gulere[rand() % gulere.size()];
}
//----------------------------------------------------------------
class Pantaloni : public virtual Haina {
protected:
    string fit;
public:
    string getFit() { return this->fit; }
    void setFit(string fit) { this->fit = fit; }
    void readFit() { cin>>this->fit; }
    //const
    Pantaloni() : Haina(), fit("Straight") {}
    Pantaloni(unsigned int marime, float pret, vector<pair<string,float>> materiale, string fit)
        : Haina(marime, pret, materiale), fit(fit) {}
    Pantaloni(const Pantaloni& p);
    Pantaloni& operator=(const Pantaloni& p);
    //IO
    virtual ostream& afis(ostream& out) const;
    virtual istream& citire(istream& in);
    friend ostream& operator<<(ostream& out, Pantaloni& p) { return p.afis(out); }
    friend istream& operator>>(istream& in, Pantaloni& p) { return p.citire(in); }
    //random fit
    void randFit();
};
Pantaloni::Pantaloni(const Pantaloni& p)
{
    this->marime = p.marime;
    this->pret = p.pret;
    this->materiale = p.materiale;
    this->fit = p.fit;
}
ostream& Pantaloni::afis(ostream& out) const
{
    Haina::afis(out);
    out<<"| Fit: "<<this->fit;
    return out;
}
istream& Pantaloni::citire(istream& in)
{
    Haina::citire(in);
    cout<<"Fit: "; in>>this->fit;
    return in;
}
Pantaloni& Pantaloni::operator=(const Pantaloni& p)
{
    if(this != &p)
    {
        this->marime = p.marime;
        this->pret = p.pret;
        this->materiale = p.materiale;
        this->fit = p.fit;
    }
    return *this;
}
void Pantaloni::randFit()
{
    srand(time(NULL));
    vector<string> fits = {"Straight", "Slim", "Athletic", "Relaxed", "Bootcut"};
    this->fit = fits[rand() % fits.size()];
}
//----------------------------------------------------------------
class Costum : public virtual Bluza, public virtual Pantaloni {
private:
    static unsigned int stoc;
    static float discount;
public:
    static float getDiscount() { return discount; }
    static void setDiscount(float x) { discount = x; }
    static void readDiscount() { cin>>discount; }
    static unsigned int getStoc() { return stoc; }
    //const
    Costum() : Haina() { this->guler = "Spread"; this->fit="Straight"; stoc++;}
    Costum(unsigned int marime, float pret, vector<pair<string,float>> mat, string guler, string fit) 
        : Haina(marime, pret, mat) {this->guler = guler; this->fit = fit; stoc++;}
    Costum(const Costum& c);
    Costum& operator=(const Costum& c);
    //IO
    ostream& afis(ostream& out) const;
    istream& citire(istream& in);
    friend ostream& operator<<(ostream& out, Costum& p) { return p.afis(out); }
    friend istream& operator>>(istream& in, Costum& p) { return p.citire(in); }
};
unsigned int Costum::stoc = 0;
float Costum::discount = 0;
Costum::Costum(const Costum& c)
{
    this->marime = c.marime;
    this->pret = c.pret;
    this->materiale = c.materiale;
    this->guler = c.guler;
    this->fit = c.fit;
}
ostream& Costum::afis(ostream& out) const
{
    Haina::afis(out);
    out<<" | Guler: "<<this->guler;
    out<<" | Fit: "<<this->fit;
    out<<" | Discount: "<<this->pret * discount;
    return out;
}
istream& Costum::citire(istream& in)
{
    Haina::citire(in);
    cout<<"Guler (str): "; in>>this->guler;
    cout<<"Fit (str): "; in>>this->fit;
    return in;
}
Costum& Costum::operator=(const Costum& c)
{
    if(this != &c)
    {
        this->marime = c.marime;
        this->pret = c.pret;
        this->materiale = c.materiale;
        this->guler = c.guler;
        this->fit = c.fit;
    }
    return *this;
}

int main() {
    vector<Haina> haine;
    vector<Bluza> bluze;
    vector<Pantaloni> pant;
    vector<Costum> costume;
    while(true)
    {
        cout<<"\n1. Cout obj\n";
        cout<<"2. Obj nou\n";
        cout<<"3. Sterge obj\n";
        cout<<"4. Modifica obj\n";
        cout<<"5. Exit\n";
        int k,k2,k3,k4; cin>>k;
        switch(k) {
            case 1://cout obj
                cout<<"1. Haine("<<haine.size()<<")\n";
                cout<<"2. Bluze("<<bluze.size()<<")\n";
                cout<<"3. Pantaloni("<<pant.size()<<")\n";
                cout<<"4. Costume("<<costume.size()<<")\n";
                cout<<"5. Back\n";
                cin>>k2;
                switch(k2) {
                    case 1:
                        for(int i = 0; i < haine.size(); ++i) cout<<i+1<<':'<<haine[i]<<'\n';
                        break;
                    case 2:
                        for(int i = 0; i < bluze.size(); ++i) cout<<i+1<<':'<<bluze[i]<<'\n';
                        break;
                    case 3:
                        for(int i = 0; i < pant.size(); ++i) cout<<i+1<<':'<<pant[i]<<'\n';
                        break;
                    case 4:
                        for(int i = 0; i < costume.size(); ++i) cout<<i+1<<':'<<costume[i]<<'\n';
                        break;
                    default:
                        break;
                }
                break;
            case 2://obj nou
                cout<<"1. Haina\n";
                cout<<"2. Bluza\n";
                cout<<"3. Pantaloni\n";
                cout<<"4. Costum\n";
                cin>>k2;
                switch(k2) {
                    case 1:
                        cout<<"1. Default Const\n";
                        cout<<"2. Cin\n";
                        cin>>k3;
                        if(k3 == 1) haine.push_back(Haina());
                        else if(k3 == 2) {
                            Haina x; cin>>x;
                            haine.push_back(x);
                        }
                        break;
                    case 2:
                        cout<<"1. Default Const\n";
                        cout<<"2. Cin\n";
                        cin>>k3;
                        if(k3 == 1) bluze.push_back(Bluza());
                        else if(k3 == 2) {
                            Bluza x; cin>>x;
                            bluze.push_back(x);
                        }
                        break;
                    case 3:
                        cout<<"1. Default Const\n";
                        cout<<"2. Cin\n";
                        cin>>k3;
                        if(k3 == 1) pant.push_back(Pantaloni());
                        else if(k3 == 2) {
                            Pantaloni x; cin>>x;
                            pant.push_back(x);
                        }
                        break;
                    case 4:
                        cout<<"1. Default Const\n";
                        cout<<"2. Cin\n";
                        cin>>k3;
                        if(k3 == 1) costume.push_back(Costum());
                        else if(k3 == 2) {
                            Costum x; cin>>x;
                            costume.push_back(x);
                        }
                        break;
                    default:
                        break;
                }
                break;
            case 3://sterge obj
                cout<<"1. Haina("<<haine.size()<<")\n";
                cout<<"2. Bluza("<<bluze.size()<<")\n";
                cout<<"3. Pantaloni("<<pant.size()<<")\n";
                cout<<"4. Costum("<<costume.size()<<")\n";
                cin>>k2;
                cout<<"Index: ";
                cin>>k3;
                switch(k2) {
                    case 1:
                        haine.erase(haine.begin() + k3);
                        break;
                    case 2:
                        bluze.erase(bluze.begin() + k3);
                        break;
                    case 3:
                        pant.erase(pant.begin() + k3);
                        break;
                    case 4:
                        costume.erase(costume.begin() + k3);
                        break;
                    default:
                        break;
                }
                break;
            case 4://modifica obj
                cout<<"1. Haina("<<haine.size()<<")\n";
                cout<<"2. Bluza("<<bluze.size()<<")\n";
                cout<<"3. Pantaloni("<<pant.size()<<")\n";
                cout<<"4. Costum("<<costume.size()<<")\n";
                cout<<"5. Discount\n";
                cin>>k2;
                cout<<"Index: ";
                cin>>k3;
                switch(k2) {
                    case 1:
                        cout<<"1. setMarime\n";
                        cout<<"2. setPret\n";
                        cout<<"3. setMateriale\n";
                        cout<<"4. FixMateriale\n";
                        cin>>k4;
                        switch (k4)
                        {
                        case 1:
                            haine[k3].readMarime();
                            break;
                        case 2:
                            haine[k3].readPret();
                            break;
                        case 3:
                            haine[k3].readMateriale();
                            break;
                        case 4:
                            haine[k3].fixMateriale();
                        default:
                            break;
                        }
                    case 2:
                        cout<<"1. setMarime\n";
                        cout<<"2. setPret\n";
                        cout<<"3. setMateriale\n";
                        cout<<"4. setGuler\n";
                        cout<<"5. FixMateriale\n";
                        cout<<"6. RandGuler\n";
                        cin>>k4;
                        switch (k4)
                        {
                        case 1:
                            bluze[k3].readMarime();
                            break;
                        case 2:
                            bluze[k3].readPret();
                            break;
                        case 3:
                            bluze[k3].readMateriale();
                            break;
                        case 4:
                            bluze[k3].readGuler();
                            break;
                        case 5:
                            bluze[k3].fixMateriale();
                            break;
                        case 6:
                            bluze[k3].randGuler();
                            break;
                        default:
                            break;
                        }
                        break;
                    case 3:
                        cout<<"1. setMarime\n";
                        cout<<"2. setPret\n";
                        cout<<"3. setMateriale\n";
                        cout<<"4. setFit\n";
                        cout<<"5. FixMateriale\n";
                        cout<<"6. RandFit\n";
                        cin>>k4;
                        switch (k4)
                        {
                        case 1:
                            pant[k3].readMarime();
                            break;
                        case 2:
                            pant[k3].readPret();
                            break;
                        case 3:
                            pant[k3].readMateriale();
                            break;
                        case 4:
                            pant[k3].readFit();
                            break;
                        case 5:
                            pant[k3].fixMateriale();
                            break;
                        case 6:
                            pant[k3].randFit();
                            break;
                        default:
                            break;
                        }
                        break;
                    case 4:
                        cout<<"1. setMarime\n";
                        cout<<"2. setPret\n";
                        cout<<"3. setMateriale\n";
                        cout<<"4. setGuler\n";
                        cout<<"5. setFit\n";
                        cout<<"6. FixMateriale\n";
                        cout<<"7. RandGuler\n";
                        cout<<"8. RandFit\n";
                        cin>>k4;
                        switch (k4)
                        {
                        case 1:
                            costume[k3].readMarime();
                            break;
                        case 2:
                            costume[k3].readPret();
                            break;
                        case 3:
                            costume[k3].readMateriale();
                            break;
                        case 4:
                            costume[k3].readGuler();
                            break;
                        case 5:
                            costume[k3].readFit();
                            break;
                        case 6:
                            costume[k3].fixMateriale();
                            break;
                        case 7:
                            costume[k3].randGuler();
                            break;
                        case 8:
                            costume[k3].randFit();
                            break;
                        default:
                            break;
                        }
                        break;
                    case 5:
                        Costum::readDiscount();
                        break;
                    default:
                        break;
                }
                break;
            case 5://exit
                return 0;
            default:
                break;
        }
    }
}