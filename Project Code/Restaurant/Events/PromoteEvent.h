#pragma once

#include "Event.h"

class PromoteEvent : public Event
{
	//info about the order related to promoted event   
		//order type: should be Normal to be promoted
	double extraOrdMoney;	//extra money for promation

public:
	PromoteEvent(int eTime, int oID, double EOM);
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

