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
	state = newState;	//EL STATE SE LLENA CON LO QUE QUIERO. ACA PONEMOS EL ISDESTROYED DEL AUTO.
}

void Subject::NotifyObservers()
{
	for (IObserver* observer : observers)
	{
		observer->Update(state);
	}
}


