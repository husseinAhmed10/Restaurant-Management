#pragma once

#include "..\Defs.h"
#include "time.h"
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;	//dishes it can prepare in one clock tick (in one timestep)
	COOK_STATUS Availability;
	int BreakTime;
	int Orders;        // number of order to do before break
	int RestPeriod;
	int OrderCount;    //number of orders done already

	int OriginalSpeed;
	int BreakEndTimeStep;
	int RestPeriodEnd;
	bool Injury;
	int Dishes;    //numbr of dishes

public:
	Cook();
	Cook(int, ORD_TYPE, int, int, int, int, int, int);
	virtual ~Cook();

	//   **GETTERS**   // 
	int GetID() const;
	int GetBreakTime() const;
	int GetSpeed() const;
	int GetOrderCount() const;
	ORD_TYPE GetType() const;
	COOK_STATUS GetStatus() const;

	int GetRestPeriod() const;
	int GetDishesNumber() const;
	int GetBreakEndTimeStep() const;
	int GetRestPeriodEnd() const;
	int GetOriginalSpeed() const;

	


	//   **SETTERS**   // 
	void setID(int);
	void setType(ORD_TYPE);
	void setBreakTime(int);
	void SetSpeed(int );
	void SetStatus(COOK_STATUS );
	void SetOrderCount(int);

	void SetBreakEndTimeStep(int);
	void SetRestPeriodEnd(int);
	void SetHealthStat(bool);
	


	//   **FUNCTIONS**   // 
	bool incrementOrderCount();

	int TimeExpectedToReturnFromTheBreak(int);
	int TimeExpectedToReturnFromRest(int);
	bool isInjured();
	bool MakeInjured();
	int TimeExpectedToFinish(int);
	friend bool operator== (const Cook& c1, const Cook& c2);

};

