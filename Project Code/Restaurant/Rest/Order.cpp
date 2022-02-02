#include "Order.h"
#include "Cook.h"
Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	AssignedCook = nullptr;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}



ORD_STATUS Order::getStatus() const
{
	return status;
}


void Order::SetTotalMoney(double X)
{
	totalMoney = X;
}
double Order::GetTotalMoney()
{
	return totalMoney;
}
void Order::SetArrivalTime(int AT)
{
	ArrTime = AT;
}
int Order::GetArrivalTime()
{
	return ArrTime;
}
void Order::SetServeTime()
{
	if (Size % AssignedCook->GetSpeed() == 0)
		ServTime = Size / AssignedCook->GetSpeed();
	else
		ServTime = (Size / AssignedCook->GetSpeed()) + 1;
}

int Order::GetServeTime()
{
	return ServTime;
}
void Order::SetFinishTime(int FT)
{
	FinishTime = FT;
}
int Order::GetFinishTime()
{
	return FinishTime;
}
void Order::SetOrderSize(int S)
{
	Size = S;
}
int Order::GetOrderSize()
{
	return Size;
}
int Order::GetVIPKey()
{
	Key = (totalMoney / 10) - (ArrTime * 5) - (Size * 3);
	return Key;
}

void Order::SetWaitTime(int currentTimeStep)
{
	WaitTime = currentTimeStep-ArrTime;
}
int Order::GetWaitTime()
{
	return WaitTime;
}

void Order::SetOrderType(ORD_TYPE T)
{
	type = T;
}

void Order::SetAssignedCook(Cook* c)
{
	AssignedCook = c;
}
Cook* Order::GetAssignedCook()
{
	return AssignedCook;
}
