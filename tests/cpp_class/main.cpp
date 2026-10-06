#include <string.h>
#include <iostream>
using namespace std;
class A {
    public:
        char name[8];
        A(){}
        A(const char *name) {
            strcpy(this->name, name);
        }
        ~A() {}
};

class B: public A {
    public:
        B(const  char *name) : A(name) {};
};

class C: public A {
    public:
        using A::A;
};

int main() {
    char t[3][8];
    strcpy(t[0], (new A("toto"))->name);
    strcpy(t[1], (new B("titi"))->name);
    strcpy(t[2], (new C("tutu"))->name);

    cout << t[0] << '\n';
    cout << t[1] << '\n';
    cout << t[2] << '\n';

    return 0;
}
