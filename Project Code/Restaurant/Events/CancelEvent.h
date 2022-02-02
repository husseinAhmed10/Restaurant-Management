#ifndef __CANCEL_EVENT_H_
#define __CANCEL_EVENT_H_

#include "Event.h"


class CancelEvent : public Event
{
			//No data members for cancel event
public:
	CancelEvent(int eTime, int oID);
	
	virtual void Execute(Restaurant *pRest);	//override execute function
};

#endif

