#pragma once
#include <iostream>
#include "Payment.cpp"
using namespace std;

// Each subclass will implements the method which the user want to use.

class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "  [UPI] Rs." << amount << " paid successfully\n";
        return true;
    }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "  [Card] Rs." << amount << " paid successfully\n";
        return true;
    }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "  [Cash] Rs." << amount << " collected successfully\n";
        return true;
    }
};
