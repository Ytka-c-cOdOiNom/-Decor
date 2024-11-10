#include <iostream>
#include <memory>
#include <string>
#include <windows.h>
using namespace std;

// Базовий інтерфейс для напоїв
class Beverage {
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() = default;
};

// Конкретний клас напою: Кава
class Coffee : public Beverage {
public:
    string getDescription() const override {
        return "Чорна кава";
    }

    double cost() const override {
        return 20.0;
    }
};

// Абстрактний клас декоратора для додаткових інгредієнтів
class BeverageDecorator : public Beverage {
protected:
    unique_ptr<Beverage> beverage; // Основний напій, який декорується

public:
    BeverageDecorator(unique_ptr<Beverage> bev) : beverage(move(bev)) {}
};

// Декоратор для додавання молока
class MilkDecorator : public BeverageDecorator {
public:
    MilkDecorator(unique_ptr<Beverage> bev) : BeverageDecorator(move(bev)) {}

    string getDescription() const override {
        return beverage->getDescription() + " з молоком";
    }

    double cost() const override {
        return beverage->cost() + 6.0; // Додаємо вартість молока
    }
};

// Декоратор для додавання цукру
class SugarDecorator : public BeverageDecorator {
public:
    SugarDecorator(unique_ptr<Beverage> bev) : BeverageDecorator(move(bev)) {}

    string getDescription() const override {
        return beverage->getDescription() + " з цукром";
    }

    double cost() const override {
        return beverage->cost() + 3.5; // Додаємо вартість цукру
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створення базового напою
    unique_ptr<Beverage> myCoffee = make_unique<Coffee>();

    // Додавання молока
    myCoffee = make_unique<MilkDecorator>(move(myCoffee));

    // Додавання цукру
    myCoffee = make_unique<SugarDecorator>(move(myCoffee));

    cout << "Ваш напій: " << myCoffee->getDescription() << endl;
    cout << "Ціна: " << myCoffee->cost() << " грн" << endl;

}

