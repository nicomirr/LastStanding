#pragma once

class IObserver
{
public:

	virtual ~IObserver();
	virtual void Update(bool newState) = 0;
};