#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType) :Event(eTime, oID)
{
	OrdType = oType;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, double TMoney, int OrderSize) : Event(eTime, oID)
{
	OrdType = oType;
	OrdMoney = TMoney;
	OrdSize = OrderSize;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	Order* newOrder = new Order(OrderID, OrdType);
	newOrder->SetArrivalTime(EventTime);
	newOrder->SetOrderSize(OrdSize);
	newOrder->SetTotalMoney(OrdMoney);
	if (OrdType == TYPE_NRM)
		pRest->GetNormalOrders()->enqueue(newOrder);
	else if (OrdType == TYPE_VGAN)
		pRest->GetVeganOrders()->enqueue(newOrder);
	else if (OrdType == TYPE_VIP)
		pRest->GetVIPOrders()->enqueue(newOrder, newOrder->GetVIPKey());

	///For the sake of demo, this function will just create an order and add it to DemoQueue
		///Remove the next code lines in phases 1&2
		//Order* pOrd = new Order(OrderID,OrdType);
		//pRest->AddtoDemoQueue(pOrd);
}
