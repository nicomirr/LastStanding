#include "IObserver.h"
#include <iostream>

class Observer : public IObserver {
public:
    void Update(bool newState) override 
    {
        std::cout << "Estado actualizado a: " << newState << std::endl;
    }
};