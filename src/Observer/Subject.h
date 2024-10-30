#pragma once
#include <vector>;
#include "IObserver.h"

class Subject
{
private: 
	std::vector<IObserver*> observers;
	bool state;

public:
	Subject();
	void Attach(IObserver* observer);
	void Detach(IObserver* observer);
	void SetState(bool newState);
	bool GetState() const { return state; };
	void NotifyObservers();
};