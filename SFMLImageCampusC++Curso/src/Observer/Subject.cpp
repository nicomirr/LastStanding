#include "Subject.h"

Subject::Subject(){}

void Subject::Attach(IObserver* observer)
{
	observers.push_back(observer);
}

void Subject::Detach(IObserver* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::SetState(bool newState)
{
	state = newState;	
}

void Subject::NotifyObservers()
{
	for (IObserver* observer : observers)
	{
		observer->Update(state);
	}
}


