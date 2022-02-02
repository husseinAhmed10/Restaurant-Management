#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include "..\Rest\Cook.h"


class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant     
	double totalMoney;	//Total order money
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	Cook* AssignedCook;
	double Key;
	int Size;
	//
	// TODO: Add More Data Members As Needed
	//
	int WaitTime;

public:
	Order(int ID, ORD_TYPE r_Type);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//
	double GetTotalMoney();
	void SetTotalMoney(double i);

	void SetArrivalTime(int AT);
	int GetArrivalTime();
	void SetServeTime();
	int GetServeTime();
	void SetFinishTime(int FT);
	int GetFinishTime();
	int GetVIPKey();
	void SetOrderSize(int S);
	int GetOrderSize();
	void SetWaitTime(int currentTimeStep);
	int GetWaitTime();
	void SetOrderType(ORD_TYPE T);
	void SetAssignedCook(Cook* c);
	Cook* GetAssignedCook();
};

#endif