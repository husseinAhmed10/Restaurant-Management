#include "Cook.h"
#include "Order.h"

#include <iostream>
using namespace std;

Cook::Cook()
{
}

Cook::Cook(int IDnumber, ORD_TYPE t, int smin, int smax, int Bmin, int Bmax, int o, int RestP) {

	Availability = FREE;
	ID = IDnumber;
	srand(time(NULL));
	speed = ((rand()) % (smax - smin + 1)) + smin;
	type = t;
	BreakTime = ((rand()) % (Bmax - Bmin + 1)) + Bmin;
	Orders = o;
	RestPeriod = RestP;
	OrderCount = 0;
	Dishes = 0;
	Injury = false;

	OriginalSpeed = speed;
	BreakEndTimeStep = 0;
	RestPeriodEnd = 0;
}



Cook::~Cook()
{
}


int Cook::GetBreakTime() const
{
	return BreakTime;
}


int Cook::GetID() const
{
	return ID;
}

int Cook::GetOriginalSpeed() const {
	return OriginalSpeed;
}

ORD_TYPE Cook::GetType() const
{
	return type;
}

COOK_STATUS Cook::GetStatus() const {

	return Availability;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}


void Cook::setBreakTime(int t) {
	BreakTime = t;
}



void Cook::SetSpeed(int s)
{
	speed = s;
}
int Cook::GetSpeed() const
{
	return speed;
}

int Cook::GetRestPeriodEnd() const {
	return RestPeriodEnd;
}

bool Cook::incrementOrderCount()
{
	OrderCount++;
	if (OrderCount == Orders)
	{
		OrderCount = OrderCount % Orders;
		return true;
	}
	return false;
}
int Cook::GetOrderCount() const
{
	return OrderCount;
}

int Cook::GetBreakEndTimeStep() const {
	return BreakEndTimeStep;
}

void Cook::SetStatus(COOK_STATUS S)
{
	Availability = S;
}

void Cook::SetRestPeriodEnd(int a) {
	RestPeriodEnd = a;
}


void Cook::SetOrderCount(int OC) {
	OrderCount = OC;
}

bool Cook::isInjured() {
	if (Injury == false)
		return false;
	return true;
}


void Cook::SetHealthStat(bool HS) {
	Injury = HS;
}


void Cook::SetBreakEndTimeStep(int i) {
	BreakEndTimeStep = i;
}


int Cook::GetDishesNumber() const {
	return Dishes;
}


int Cook::GetRestPeriod() const {
	return RestPeriod;
}

bool operator== (const Cook& c1, const Cook& c2)
{
	if (c1.GetID() == c2.GetID())
		return true;
	return false;
}

bool Cook::MakeInjured() {

	if (isInjured() == false) {
		SetHealthStat(true);
		SetSpeed((GetSpeed()) / 2);
		return true;
	}
	return false;
}


int Cook::TimeExpectedToFinish(int currenttimestep) {
	int i = ceil(Dishes / speed);
	return (i + currenttimestep);
}

int Cook::TimeExpectedToReturnFromTheBreak(int CurrentTimeStep) {
	int i = CurrentTimeStep + BreakTime;
	return i;
}

int Cook::TimeExpectedToReturnFromRest(int CurrentTimeStep) {
	int i = CurrentTimeStep + RestPeriod;
	return i;
}
