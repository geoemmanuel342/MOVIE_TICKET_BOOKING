#pragma once

// Payment: the payment contract only. Abstraction - subclasses
// decide HOW payment happens; callers only ever see this contract.
class Payment {
public:
    virtual bool pay(double amount) = 0;   // pure virtual
    virtual ~Payment() {}
};
