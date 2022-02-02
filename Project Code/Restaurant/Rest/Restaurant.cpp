#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant()
{
	SimulatorMode = -1;
	AutoPromoteCounter = 0;
	pGUI = NULL;
	UrgentOrderCounter=0;
}
Queue<Order*> *Restaurant::GetNormalOrders()
{
	return &NormalOrders;
}
Queue<Order*> *Restaurant::GetVeganOrders()
{
	return &VeganOrders;
}
PriorityQueue<Order*> *Restaurant::GetVIPOrders()
{
	return &VIPOrders;
}
void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		SimulatorMode = 1;

		SimulatorFunction();
		break;
	case MODE_STEP:
		SimulatorMode = 2;

		SimulatorFunction();
		break;
	case MODE_SLNT:
		SimulatorMode = 3;

		SimulatorFunction();
		break;


	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

/*adds a new event to the queue of events*/
void Restaurant::AddEvent(Event* QE)
{
	EventsQueue.enqueue(QE);
}









Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	int size = 0;


	Order* a;
	Order** OrdList3 = FinishedOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		a = OrdList3[i];
		pGUI->AddToDrawingList(a);
	}

	Order* o;
	Order** OrdList2 = InServiceOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		o = OrdList2[i];
		pGUI->AddToDrawingList(o);
	}




	Order** OrdList = NormalOrders.toArray(size);
	Order* pOrd;
	for (int i = 0; i < size; i++)
	{
		pOrd = OrdList[i];
		pGUI->AddToDrawingList(pOrd);
	}
	OrdList = VeganOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = OrdList[i];
		pGUI->AddToDrawingList(pOrd);
	}
	OrdList = VIPOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = OrdList[i];
		pGUI->AddToDrawingList(pOrd);
	}
	OrdList = UrgentOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = OrdList[i];
		pGUI->AddToDrawingList(pOrd);
	}

	Cook* C;
	Cook** CookList = Normal.toArray(size);
	for (int i = 0; i < size; i++)
	{
		C = CookList[i];
		pGUI->AddToDrawingList(C);
	}
	CookList = Vegan.toArray(size);
	for (int i = 0; i < size; i++)
	{
		C = CookList[i];
		pGUI->AddToDrawingList(C);
	}
	CookList = VIP.toArray(size);
	for (int i = 0; i < size; i++)
	{
		C = CookList[i];
		pGUI->AddToDrawingList(C);
	}
	pGUI->UpdateInterface();
}







void Restaurant::LoadFile(ifstream& input)
{
	Event* pEv;
	Cook* pCook;

	int NormalCooks, VeganCooks, VIPCooks;
	int SN_min, SN_max, SG_min, SG_max, SV_min, SV_max;
	int BO, BN_min, BN_max, BG_min, BG_max, BV_min, BV_max;
	float InjProb;
	int RstPrd, AutoP, VIP_WT;
	int EventCount;

	if (input.is_open())
	{
		input >> NormalCooks >> VeganCooks >> VIPCooks >> SN_min >> SN_max >> SG_min >> SG_max >> SV_min >> SV_max >> BO >> BN_min >> BN_max >> BG_min >> BG_max >> BV_min >> BV_max >> InjProb >> RstPrd;
		InjPropSim = InjProb;
		for (int i = 0; i < NormalCooks; ++i)
		{
			pCook = new Cook(i + 1, TYPE_NRM, SN_min, SN_max, BN_min, BN_max, BO, RstPrd);
			Normal.enqueue(pCook);
		}
		for (int i = 0; i < VeganCooks; ++i)
		{
			pCook = new Cook(i + 100, TYPE_VGAN, SG_min, SG_max, BG_min, BG_max, BO, RstPrd);
			Vegan.enqueue(pCook);
		}
		for (int i = 0; i < VIPCooks; ++i)
		{
			pCook = new Cook(i + 200, TYPE_VIP, SV_min, SV_max, BV_min, BV_max, BO, RstPrd);
			VIP.enqueue(pCook);
		}

		input >> AutoP;
		AutoPromoteTimeStep = AutoP;
		input >> VIP_WT;
		VIPWait = VIP_WT;

		input >> EventCount;

		for (int i = 0; i < EventCount; ++i)
		{
			char eventType;
			char ordertype;
			int timestep;
			int ID;
			int SIZE;
			int Money;
			input >> eventType;

			if (eventType == 'R')
			{
				input >> ordertype >> timestep >> ID >> SIZE >> Money;
				if (ordertype == 'N')
				{
					pEv = new ArrivalEvent(timestep, ID, TYPE_NRM, Money, SIZE);
					EventsQueue.enqueue(pEv);

				}
				else if (ordertype == 'G')
				{
					pEv = new ArrivalEvent(timestep, ID, TYPE_VGAN, Money, SIZE);
					EventsQueue.enqueue(pEv);
				}
				else if (ordertype == 'V')
				{
					pEv = new ArrivalEvent(timestep, ID, TYPE_VIP, Money, SIZE);
					EventsQueue.enqueue(pEv);
				}
			}

			else if (eventType == 'X')
			{
				input >> timestep >> ID;
				pEv = new CancelEvent(timestep, ID);
				EventsQueue.enqueue(pEv);

			}
			else if (eventType == 'P')
			{
				input >> timestep >> ID >> Money;
				pEv = new PromoteEvent(timestep, ID, Money);
				EventsQueue.enqueue(pEv);
			}
		}
	}

}


void Restaurant::SimulatorFunction()
{
	int max;
	Order* pOrd;
	Event* pEv;
	Cook* pCook;
	int CurrentTimestep = 1;
	pGUI->PrintMessage("Please enter the file name: ");
	string Input = pGUI->GetString();
	Input = Input + ".txt";
	ifstream InputFile(Input);
	LoadFile(InputFile);

	if (SimulatorMode == 1)
	{
		while (!EventsQueue.isEmpty() || !InServiceOrders.isEmpty() || !NormalOrders.isEmpty() || !VeganOrders.isEmpty() || !VIPOrders.isEmpty())
		{
			pGUI->waitForClick();

			pGUI->ResetDrawingList();
			srand(time(NULL));
			double R = (double)((rand() % 101)) / 100;
			string s = "the current timestep is " + to_string(CurrentTimestep) + ". CLICK to continue to next timestep";
			pGUI->PrintMessage(s);
			ExecuteEvents(CurrentTimestep);
			FinishOrderEffect(CurrentTimestep);
			ReturnFromBreak(CurrentTimestep);
			ReturnFromRestPeriod(CurrentTimestep);
			AutoPromotion(CurrentTimestep);
			AssignOrders(CurrentTimestep);
			if (R <= InjPropSim && BusyCook.isEmpty() == false)
			{
				pCook = BusyCook.FirstCooktoInjure();

			}
			FillDrawingList();
			pGUI->UpdateInterface();
			++CurrentTimestep;
		}

		OutputFile();
		pGUI->PrintMessage("All Orders have been fulfilled, click once more to exit");
		pGUI->waitForClick();
	}





	else if (SimulatorMode == 2)
	{
		while (!EventsQueue.isEmpty() || !InServiceOrders.isEmpty() || !NormalOrders.isEmpty() || !VeganOrders.isEmpty() || !VIPOrders.isEmpty())
		{
			Sleep(1000);
			pGUI->ResetDrawingList();
			srand(time(NULL));
			double R = (double)((rand() % 101)) / 100;
			string s = "the current timestep is " + to_string(CurrentTimestep);
			pGUI->PrintMessage(s);
			ExecuteEvents(CurrentTimestep);
			FinishOrderEffect(CurrentTimestep);
			ReturnFromBreak(CurrentTimestep);
			ReturnFromRestPeriod(CurrentTimestep);
			AutoPromotion(CurrentTimestep);
			AssignOrders(CurrentTimestep);
			if (R <= InjPropSim && BusyCook.isEmpty() == false)
			{
				pCook = BusyCook.FirstCooktoInjure();

			}
			FillDrawingList();
			pGUI->UpdateInterface();
			++CurrentTimestep;
		}

		OutputFile();
		pGUI->PrintMessage("All Orders have been fulfilled, click once more to exit");
		pGUI->waitForClick();
	}


	else if (SimulatorMode == 3) {
		{
			while (!EventsQueue.isEmpty() || !InServiceOrders.isEmpty() || !NormalOrders.isEmpty() || !VeganOrders.isEmpty() || !VIPOrders.isEmpty())
			{
				srand(time(NULL));
				double R = (double)((rand() % 101)) / 100;

				ExecuteEvents(CurrentTimestep);
				FinishOrderEffect(CurrentTimestep);
				ReturnFromBreak(CurrentTimestep);
				ReturnFromRestPeriod(CurrentTimestep);
				AutoPromotion(CurrentTimestep);
				AssignOrders(CurrentTimestep);
				if (R <= InjPropSim && BusyCook.isEmpty() == false)
				{
					pCook = BusyCook.FirstCooktoInjure();

				}
				++CurrentTimestep;
			}
			OutputFile();
		}
	}
}



void Restaurant::OutputFile()
{

	pGUI->PrintMessage("Please enter the output file's name: ");
	string Output = pGUI->GetString();
	Output = Output + ".txt";
	ofstream OutputFile(Output);
	if (OutputFile.is_open())
	{
		int size = 0;
		int UrgSize = 0;
		double avgwait = 0;
		double avgserve = 0;
		OutputFile << "FT" << "\t" << "ID" << "\t" << "AT" << "\t" << "WT" << "\t" << "ST" << endl;


		int OrdN = 0, OrdG = 0, OrdVIP = 0;
		Order* a;
		Order** OrdList3 = FinishedOrders.toArray(size);
		Order* Urg;
		Order** UrgList = UrgentOrders.toArray(UrgSize);

		for (int i = 0; i < size; i++)
		{
			a = OrdList3[i];
			OutputFile << a->GetFinishTime() << "\t" << a->GetID() << "\t" << a->GetArrivalTime() << "\t" << a->GetWaitTime() << "\t" << a->GetServeTime() << endl;
			if (a->GetType() == TYPE_NRM)
				OrdN++;
			else if (a->GetType() == TYPE_VGAN)
				OrdG++;
			else if (a->GetType() == TYPE_VIP)
				OrdVIP++;
			avgwait = avgwait + a->GetWaitTime();
			avgserve = avgserve + a->GetServeTime();
		}
		avgwait = avgwait / size;
		avgserve = avgserve / size;
		int TotalOrders = OrdN + OrdG + OrdVIP;
		OutputFile << "Orders: " << TotalOrders << "  " << "[Norm:" << OrdN << ", Veg:" << OrdG << ", VIP:" << OrdVIP << "]" << endl;



		int sizeN = 0, sizeG = 0, sizeVIP = 0, sizeInjured = 0;
		Cook* c;
		Cook** CookList;
		CookList = Normal.toArray(sizeN);
		CookList = Vegan.toArray(sizeG);
		CookList = VIP.toArray(sizeVIP);

		while (InjuredCooks.isEmpty() == false) {
			InjuredCooks.dequeue(c);
			sizeInjured++;
		}

		double AutoPromotePercentage = 0;
		if ( (OrdN + AutoPromoteCounter) != 0) {
			AutoPromotePercentage = ((double)AutoPromoteCounter / (OrdN+ AutoPromoteCounter)) * 100;
		}

		int Totalsize = sizeN + sizeG + sizeVIP + sizeInjured;
		OutputFile << "cooks: " << Totalsize << "   " << "[Norm:" << sizeN << ", Veg:" << sizeG << ", VIP:" << sizeVIP << " injured:" << sizeInjured << "]" << endl;
		OutputFile << "Avg Wait: " << avgwait << "   " << "Avg Serve: " << avgserve << endl;
		OutputFile << "Urgent Orders: " << UrgentOrderCounter << ",   "<<"AutoPromoted= "<<AutoPromotePercentage<<"%" ;


	}
}







void Restaurant::AutoPromotion(int CurrentTimeStep)
{
	Queue<Order*> RemainingOrders;
	Order* traverse;
	Order* orderAutoPromoted = nullptr;

	while (NormalOrders.dequeue(traverse))
	{
		if ((CurrentTimeStep - traverse->GetArrivalTime()) >= AutoPromoteTimeStep)
		{
			orderAutoPromoted = traverse;
			AutoPromoteCounter++;			//Number of Autopromoted Orders
			orderAutoPromoted->SetOrderType(TYPE_VIP);
			VIPOrders.enqueue(orderAutoPromoted, orderAutoPromoted->GetVIPKey());
		}
		else
			RemainingOrders.enqueue(traverse);
	}

	while (RemainingOrders.dequeue(traverse))
	{
		NormalOrders.enqueue(traverse);
	}
}



void Restaurant::AssignOrders(int timestep)     //the current timestep
{
	Cook* cook = nullptr;
	Order* order = nullptr;
	fillUrgentOrders(timestep);
	while ((VIP.isEmpty() == false || Normal.isEmpty() == false || Vegan.isEmpty() == false || InBreakCooks.isEmpty() == false || InjuredCooks.isEmpty() == false) && UrgentOrders.isEmpty() == false)
	{
		if (VIP.isEmpty() == false)
		{
			VIP.dequeue(cook);
			BusyCook.InsertEnd(cook);
			UrgentOrders.dequeue(order);
			order->setStatus(SRV);
		}
		else if (Normal.isEmpty() == false)
		{
			Normal.dequeue(cook);
			BusyCook.InsertEnd(cook);
			UrgentOrders.dequeue(order);
			order->setStatus(SRV);
		}
		else if (Vegan.isEmpty() == false)
		{
			Vegan.dequeue(cook);
			BusyCook.InsertEnd(cook);
			UrgentOrders.dequeue(order);
			order->setStatus(SRV);
		}
		else if (InBreakCooks.isEmpty() == false)
		{
			cook = InBreakCooks.RemoveAndReturnfirstNode();
			if (cook->GetType() == TYPE_VIP)
				BusyCook.InsertEnd(cook);
			UrgentOrders.dequeue(order);
			order->setStatus(SRV);
		}
		else if (InjuredCooks.isEmpty() == false)
		{
			InjuredCooks.dequeue(cook);
			if (cook->GetType() == TYPE_VIP)
				BusyCook.InsertEnd(cook);
			UrgentOrders.dequeue(order);
			order->setStatus(SRV);
		}
		order->SetAssignedCook(cook);
		//cook->SetAssignedOrder(order);
		cook->SetStatus(BUSY);
		InServiceOrders.enqueue(order);
		/* The following 3 lines are intializing the waiting , serving and finishing time of the order */
		order->SetWaitTime(timestep);
		order->SetServeTime();
		order->SetFinishTime(order->GetArrivalTime() + order->GetWaitTime() + order->GetServeTime());
	}

	while ((VIP.isEmpty() == false || Normal.isEmpty() == false || Vegan.isEmpty() == false) && VIPOrders.isEmpty() == false)
	{
		if (VIP.isEmpty() == false)
		{
			VIP.dequeue(cook);
			BusyCook.InsertEnd(cook);
			VIPOrders.dequeue(order);
			order->setStatus(SRV);
		}
		else if (Normal.isEmpty() == false)
		{
			Normal.dequeue(cook);
			BusyCook.InsertEnd(cook);
			VIPOrders.dequeue(order);
			order->setStatus(SRV);
		}
		else if (Vegan.isEmpty() == false)
		{
			Vegan.dequeue(cook);
			BusyCook.InsertEnd(cook);
			VIPOrders.dequeue(order);
			order->setStatus(SRV);
		}
		order->SetAssignedCook(cook);
		//cook->SetAssignedOrder(order);
		cook->SetStatus(BUSY);
		InServiceOrders.enqueue(order);
		/* The following 3 lines are intializing the waiting , serving and finishing time of the order */
		order->SetWaitTime(timestep);
		order->SetServeTime();
		order->SetFinishTime(order->GetArrivalTime() + order->GetWaitTime() + order->GetServeTime());
	}

	while (Vegan.isEmpty() == false && VeganOrders.isEmpty() == false)
	{

		Vegan.dequeue(cook);
		BusyCook.InsertEnd(cook);
		VeganOrders.dequeue(order);
		order->setStatus(SRV);
		order->SetAssignedCook(cook);
		//cook->SetAssignedOrder(order);
		cook->SetStatus(BUSY);
		InServiceOrders.enqueue(order);
		/* The following 3 lines are intializing the waiting , serving and finishing time of the order */
		order->SetWaitTime(timestep);
		order->SetServeTime();
		order->SetFinishTime(order->GetArrivalTime() + order->GetWaitTime() + order->GetServeTime());
	}
	while ((VIP.isEmpty() == false || Normal.isEmpty() == false) && NormalOrders.isEmpty() == false)
	{
		if (Normal.isEmpty() == false)
		{
			Normal.dequeue(cook);
			BusyCook.InsertEnd(cook);
			NormalOrders.dequeue(order);
			order->setStatus(SRV);
		}
		else if (VIP.isEmpty() == false)
		{
			VIP.dequeue(cook);
			BusyCook.InsertEnd(cook);
			NormalOrders.dequeue(order);
			order->setStatus(SRV);
		}

		order->SetAssignedCook(cook);
		//cook->SetAssignedOrder(order);
		cook->SetStatus(BUSY);
		InServiceOrders.enqueue(order);
		/* The following 3 lines are intializing the waiting , serving and finishing time of the order */
		order->SetWaitTime(timestep);
		order->SetServeTime();
		order->SetFinishTime(order->GetArrivalTime() + order->GetWaitTime() + order->GetServeTime());
	}
}


void Restaurant::fillUrgentOrders(int CurrentTimeStep)
{
	Order* traverse = nullptr;
	Queue<Order*> remainingVIP;
	while (VIPOrders.dequeue(traverse))
	{
		traverse->SetWaitTime(CurrentTimeStep);
		if (traverse->GetWaitTime() >= VIPWait)
		{
			UrgentOrderCounter++;
			UrgentOrders.enqueue(traverse);
		}
		else
			remainingVIP.enqueue(traverse);
	}
	while (remainingVIP.dequeue(traverse))
		VIPOrders.enqueue(traverse, traverse->GetVIPKey());
}
void Restaurant::FinishOrderEffect(int timestep)
{
	Order* order = nullptr;
	Cook* cook = nullptr;
	Queue<Order*> remaininginservice;
	while (InServiceOrders.dequeue(order))
	{
		if (order->GetFinishTime() <= timestep)
		{
			FinishedOrders.enqueue(order);
			order->setStatus(DONE);
			cook = order->GetAssignedCook();

			if (cook->incrementOrderCount()) {
				cook->SetStatus(INBREAK);
				int i = cook->TimeExpectedToReturnFromTheBreak(timestep);
				cook->SetBreakEndTimeStep(i);
				BusyCook.Remove(cook);
				InBreakCooks.InsertEnd(cook);
			}
			else if (cook->isInjured() == true) {
				cook->SetStatus(INREST);
				int i = cook->TimeExpectedToReturnFromRest(timestep);
				cook->SetRestPeriodEnd(i);
				BusyCook.Remove(cook);
				InjuredCooks.enqueue(cook);
			}
			else
			{
				cook->SetStatus(FREE);
				if (cook->GetType() == TYPE_NRM)
					BusyCook.RemoveAndAddNodes(Normal, cook);
				else if (cook->GetType() == TYPE_VGAN)
					BusyCook.RemoveAndAddNodes(Vegan, cook);
				else if (cook->GetType() == TYPE_VIP)
					BusyCook.RemoveAndAddNodes(VIP, cook);
			}

		}
		else
			remaininginservice.enqueue(order);
	}
	while (remaininginservice.dequeue(order))
		InServiceOrders.enqueue(order);
}



void Restaurant::ReturnFromBreak(int timestep)
{
	Cook* cook = nullptr;
	Queue<Cook*> temp;

	while (InBreakCooks.isEmpty() == false)
	{
		int flag = 0;
		cook = InBreakCooks.RemoveAndReturnfirstNode();
		if (cook->GetBreakEndTimeStep() == timestep) {
			if (cook->GetType() == TYPE_NRM) {
				cook->SetStatus(FREE);
				Normal.enqueue(cook);
				flag = 1;
			}
			else if (cook->GetType() == TYPE_VGAN) {
				cook->SetStatus(FREE);
				Vegan.enqueue(cook);
				flag = 1;
			}
			else if (cook->GetType() == TYPE_VIP) {
				cook->SetStatus(FREE);
				VIP.enqueue(cook);
				flag = 1;
			}
		}
		if (flag == 0) {
			temp.enqueue(cook);
		}
	}

	while (temp.isEmpty() == false) {
		temp.dequeue(cook);
		InBreakCooks.InsertEnd(cook);
	}

}


void Restaurant::ReturnFromRestPeriod(int timestep)
{
	Cook* cook = nullptr;
	Queue<Cook*> temp;

	while (InjuredCooks.isEmpty() == false) {
		InjuredCooks.dequeue(cook);
		int flag = 0;

		if (cook->GetRestPeriodEnd() == timestep) {
			if (cook->GetType() == TYPE_NRM) {
				cook->SetStatus(FREE);
				cook->SetSpeed(cook->GetOriginalSpeed());
				Normal.enqueue(cook);
				flag = 1;
			}
			else if (cook->GetType() == TYPE_VGAN) {
				cook->SetStatus(FREE);
				cook->SetSpeed(cook->GetOriginalSpeed());
				Vegan.enqueue(cook);
				flag = 1;
			}
			else if (cook->GetType() == TYPE_VIP) {
				cook->SetStatus(FREE);
				cook->SetSpeed(cook->GetOriginalSpeed());
				VIP.enqueue(cook);
				flag = 1;
			}
		}
		if (flag == 0) {
			temp.enqueue(cook);
		}
	}

	while (temp.isEmpty() == false) {
		temp.dequeue(cook);
		InjuredCooks.enqueue(cook);
	}
	return;
}







