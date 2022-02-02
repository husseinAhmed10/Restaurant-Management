#include "CancelEvent.h"

#include "../Rest/Restaurant.h"

CancelEvent::CancelEvent(int eTime, int oID ):Event(eTime,oID)
{
	
}



void CancelEvent::Execute(Restaurant *pRest )
{
	//Order* pOrd = pRest->getcancelled_order(OrderID);			//return the order that the customer want to cancel it
	//pRest->Cancel_therequired_order(pOrd);				//Cancel_therequired_order used to cancel order  
	Queue<Order*> RemainingOrders;
	Order* traverse;
	Order* cancel = nullptr;
	while (pRest->GetNormalOrders()->dequeue(traverse))
	{
		if (traverse->GetID() == OrderID)
			cancel = traverse;
		else
			RemainingOrders.enqueue(traverse);
	}
	while (RemainingOrders.dequeue(traverse))
		pRest->GetNormalOrders()->enqueue(traverse);
	delete cancel;
}


