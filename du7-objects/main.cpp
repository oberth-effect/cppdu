#include <iostream>

class A {
public:
    char x;
};

A a_global = {'g'}, pole_a_global[] = {'0', '1'};


class B {
public:
    char x;

    B() {
        x = '?';
        std::cout << "B()" << x << std::endl;
    }

    B(char c) {
        x = c;
        std::cout << "B(char)" << x << std::endl;
    }

    B(const B &b) {
        x = b.x;
        std::cout << "B(B &b)" << x << std::endl;
    }

    ~B() {
        std::cout << "~B()" << x << std::endl;
    }
};

B b_global('G');

int main() {
    A a_local = {'l'}, pole_a_local[] = {'3', '4', '5'};

    std::cout << "Objekt A" << std::endl << "--------" << std::endl;
    std::cout << "a_global.x: " << a_global.x << " pole_a_global.x:";
    for (int i = 0; i < sizeof pole_a_global / sizeof *pole_a_global; i++) {
        std::cout << " [" << i << "]: " << pole_a_global[i].x;
    }
    std::cout << std::endl;

    std::cout << "Objekt A" << std::endl << "--------" << std::endl;
    std::cout << "a_local.x: " << a_local.x << " pole_a_local.x:";
    for (int i = 0; i < sizeof pole_a_local / sizeof *pole_a_local; i++) {
        std::cout << " [" << i << "]: " << pole_a_local[i].x;
    }
    std::cout << std::endl;

    std::cout << std::endl;
    {
        std::cout << "Block with instances of B" << std::endl << "-------" << std::endl;
        B a, b('b'), c(a), d = b;
        c.x = 'c';
        d.x = 'd';
        std::cout << "deallocation" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Heap allocated instances of B as pointers" << std::endl << "-------" << std::endl;
    B *p1B = new B('P');
    B *p2B = new B(*p1B);
    p2B->x = 'Q';
    std::cout << "Explicit deallocation using delete" << std::endl;
    delete (p1B);
    delete (p2B);
    std::cout << std::endl;

    std::cout << "Heap allocated instance of B as reference" << std::endl << "-------" << std::endl;
    B &rB = *new B('R');
// Otazka 1:
    delete(&rB);
//Otazka 2: Konstruktor probehne na zacatku a destruktor na konci programu
//Otazka 3:
    B pole_b[]={ 'x', 'y' };
    return 0;
}

