#include <iostream>
#include <cmath>
#include <string>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// клас "Фігура"
class Figure {
public:
    virtual void printInfo() const = 0;  //  метод для друку інформації
    virtual double surfaceArea() const = 0;  // метод для обчислення площі поверхні
    virtual ~Figure() {}  // Віртуальний деструктор
};

// Клас-нащадок "Циліндр"
class Cylinder : public Figure {
private:
    double radius;
    double height;

public:
    Cylinder(double r, double h) : radius(r), height(h) {}

    void printInfo() const override {
        cout << "Figure: Cylinder" << endl;
        cout << "Radius: " << radius << ", Height: " << height << endl;
    }

    double surfaceArea() const override {
        return 2 * M_PI * radius * (radius + height);
    }
};

// Клас-нащадок "Куб"
class Cube : public Figure {
private:
    double side;

public:
    Cube(double s) : side(s) {}

    void printInfo() const override {
        cout << "Figure: Cube" << endl;
        cout << "Side: " << side << endl;
    }

    double surfaceArea() const override {
        return 6 * side * side;
    }
};


void printFigureInfo(const Figure& figure) {
    figure.printInfo();
    cout << "Surface area: " << figure.surfaceArea() << endl;
    cout << "-----------------------------" << endl;
}

int main() {
    Cylinder cylinder(3.0, 5.0);  
    Cube cube(4.0);              

    printFigureInfo(cylinder);  // Виведення інформації про циліндр
    printFigureInfo(cube);      // Виведення інформації про куб

    return 0;
}
