#include <iostream>

using namespace std;

class line;

class point        // Třída bod,
{                  // datový prvek x typu double doplňte.
    double x;
public:
    point() {}

    point(double x_) { x = x_; } // konstruktor s jedním parametremjen přenese hodnotu z parametru x_ do x
    friend ostream &operator<<(ostream &o, point &p); // přátelská funkce, operátor <<
    friend class line;

    bool at(line &l);              // Leží bod na úsečce? Vrátí ano/ne.
    bool at(point &p) { return p.x == x; } // Je parametr p stejný bod jako v objektu? Vrátí ano/ne.
};         // Nezapomenout středník.

ostream &operator<<(ostream &o, point &p) {
    o << p.x;           // vypíše jen souřadnici bodu
    return o; // vrací levý argument, aby šlo << řetězit
}


class line                   // třída úsečka
{
    point begin, end;
public:
    line() {}                  // konstruktor bez parametrů
    line(point Begin, point End) {
        begin = Begin;
        end = End;
    }  // konstruktor se dvěma parametry (koncovými body), zapamatuje si je
    friend ostream &operator<<(ostream &o, line &l); // je třeba dodělat obdobně jako u point
    friend class on_line;  
    bool at(point &p) { return (begin.x <= p.x && p.x <= end.x); } // Leží bod p na nebo mezi begin a end?Vrátí ano/ne.
};      // Nezapomenout středník, jinak chybové hlášení pak bývá matoucí.

ostream &operator<<(ostream &o, line &l) {
    o << "(" << l.begin << "," << l.end << ")";
    return o;
}

bool point::at(line &l) { return l.at(*this); }


const int N = 10;           // max. velikost polí uvnitř on_line


class on_line {
    point points[N];
    line lines[N];
    int n_points, n_lines;   // počet bodů, počet úseček
public:
    on_line();         // konstruktor bez parametrů
    on_line(point p);  // konstruktor z jednoho bodu
    on_line(line l);   // konstruktor z jedné úsečky
    friend ostream &operator<<(ostream &o, on_line &ol); // je třeba dopsat
    void add(point p); // Přidání bodu, pokud tam není nebo neleží na nějaké úsečce
    void add(line l);  // Přidání úsečky s vyřešením překryvu.
};

on_line::on_line() { n_points = n_lines = 0; }

on_line::on_line(point p) {
    points[0] = p;
    n_points = 1;
    n_lines = 0;
}

on_line::on_line(line l) {
    lines[0] = l;
    n_points = 0;
    n_lines = 1;
}

ostream &operator<<(ostream &o, on_line &ol) {
    int i;
    cout << "{ ";
    for (i = 0; i < ol.n_points; i++) {
        if (i) cout << ", ";
        cout << ol.points[i];
    }
    for (i = 0; i < ol.n_lines; i++) {
        if (i || ol.n_points) cout << ", ";
        cout << ol.lines[i];
    }
    cout << " }";
    return o;
}

void on_line::add(point p)                   // Překročení N neřešeno!
{
    int i;
    for (i = 0; i < n_points; i++) if (points[i].at(p)) return; // Nepřidávat, pokud už tam je.
    for (i = 0; i < n_lines; i++) if (lines[i].at(p)) return; // Nepřidávat, pokud leži na některé úsečce.
    points[n_points++] = p;                                  // Vlastní pridání bodu.
}

void on_line::add(line l)                    // Překročení N neřešeno!
{
    int i;
    for (i = 0; i < n_points; i++)
        if (points[i].at(l)) // Je existující bod na nové úsečce?
        {
            points[i--] = points[--n_points];              // Pak musí být odstraněn, tj. přepsán posledním.
        }
    for (i = 0; i < n_lines; i++)                         // Vyhledání a vyřešení překrytí úsečky s již existujícími.
    {
        if (lines[i].at(l.begin))
            if (lines[i].at(l.end)) return; // Nová je uvnitř existující => nedělat nic.
            else {
                l.begin = lines[i].begin; // Roztažení přidávané doleva, pak stávající
                lines[i--] = lines[--n_lines]; // odstranit, je uvnitř roztažené nové.
            }
        else if (lines[i].at(l.end)) {
            l.end = lines[i].end; // Roztažení přidávané doprava, pak stávající
            lines[i--] = lines[--n_lines]; // odstranit, je uvnitř roztažené nové.
        } else if (l.at(lines[i].begin)) lines[i--] = lines[--n_lines]; // Odstranit existující úsečku, je uvnitř nové.
    }
    lines[n_lines++] = l; // Vlastní přidání nové úsečky.
}

int main() {
    point p1(0.), p2 = 1.;  // dvě proměnné typu point
    line l1(1, 2), l2(3, 5);
    on_line ol1 = p2, ol2 = l2;
    on_line ol3 = ol1;
    cout << "ol1: " << ol1 << endl;
    cout << "ol2: " << ol2 << endl;
    cout << "ol3: " << ol3 << endl;
    cout << endl;
    ol1.add(p1);
    ol1.add(p2);
    cout << "ol1: " << ol1 << endl;
    cout << endl;
    ol2.add(p1);
    ol2.add(7);
    ol2.add(point(1));
    ol2.add(line(0, 2));
    ol2.add(line(0, 8));
    ol2.add(line(10, 18));
    ol2.add(9);
    cout << "ol2: " << ol2 << endl;
    return 0;
}
