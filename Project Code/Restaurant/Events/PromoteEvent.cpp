#include "PromoteEvent.h"
#include "../Rest/Restaurant.h"

PromoteEvent::PromoteEvent(int eTime, int oID, double EOM):Event(eTime,oID)
{
	extraOrdMoney = EOM;
}

void PromoteEvent::Execute(Restaurant *pRest)
{
	Queue<Order*> RemainingOrders;
	Order* traverse;
	Order* orderPromoted = nullptr;
	while (pRest->GetNormalOrders()->dequeue(traverse))
	{
		if (traverse->GetID() == OrderID)
			orderPromoted = traverse;
		else
			RemainingOrders.enqueue(traverse);
	}
	while (RemainingOrders.dequeue(traverse))
		pRest->GetNormalOrders()->enqueue(traverse);

	if(orderPromoted != nullptr)
	{
		orderPromoted->SetOrderType(TYPE_VIP);
		orderPromoted->SetTotalMoney(orderPromoted->GetTotalMoney()+extraOrdMoney);
		pRest->GetVIPOrders()->enqueue(orderPromoted,orderPromoted->GetVIPKey());

	}

	/*There is a function added in order.h and order.cpp */
	/*In order.h class add:  void SetOrderType(ORD_TYPE T); */
	/* void Order:: SetOrderType(ORD_TYPE T)	{ type=T;  }  */


}

