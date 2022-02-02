#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Events\CancelEvent.h"
#include "Order.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Events\PromoteEvent.h"

// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	LinkedList<Cook*> BusyCook;
	Queue<Cook*> VIP, Vegan, Normal;
	LinkedList<Cook*> InBreakCooks;
	//
	// TODO: Add More Data Members As Needed
	//
	PriorityQueue<Order*> VIPOrders;
	Queue<Order*> NormalOrders, VeganOrders, UrgentOrders;
	Queue<Order*> InServiceOrders;
	Queue<Order*> FinishedOrders;
	Queue<Cook*> InjuredCooks;
	int SimulatorMode ;
	int AutoPromoteTimeStep;
	int VIPWait;
	int InjPropSim;
	int AutoPromoteCounter ;
	int UrgentOrderCounter;

public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void LoadFile(ifstream& input);
	Queue<Order*> *GetNormalOrders();
	Queue<Order*> *GetVeganOrders();
	PriorityQueue<Order*> *GetVIPOrders();

	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//

	/*adds a new event to the queue of events */
	void AddEvent(Event* pE);
	/*Member function:AddtoQueue used to add an order using arrival event*/
	/*return the order that the customer want to cancel it*/
	void fillUrgentOrders(int CurrentTimeStep); //

	void SimulatorFunction();

	void AutoPromotion(int CurrentTimeStep);
	void AssignOrders(int timestep);   //
	void FinishOrderEffect(int timestep);
	void ReturnFromBreak(int);
	void ReturnFromRestPeriod(int);
	void OutputFile();
};

#endif