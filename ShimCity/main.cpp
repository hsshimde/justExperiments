#include <cassert>

#include "Vehicle.h"
#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"
#include "Motorcycle.h"
#include "Sedan.h"
#include "Trailer.h"
#include "UBoat.h"
#include "ShimCity.h"
#include "Person.h"

using namespace assignment2;

int main()
{
	//simple test code
	Person* p = new Person("Bob", 85);

	assert(p->GetName() == std::string("Bob"));
	assert(p->GetWeight() == 85);

	Person* p2 = new Person("James", 75);
	Person* p3 = new Person("Tina", 52);

	Person* p4 = new Person("Peter", 78);
	Person* p5 = new Person("Jane", 48);
	Person* p6 = new Person("Steve", 88);

	Airplane a(5);
	a.AddPassenger(p);
	a.AddPassenger(p2);
	a.AddPassenger(p3);

	assert(a.GetMaxPassengersCount() == 5);
	assert(a.GetPassengersCount() == 3);
	assert(a.GetPassenger(1) == p2);
	assert(a.GetFlySpeed() == 648);
	assert(a.GetDriveSpeed() == 59);
	assert(a.GetMaxSpeed() == 648);

	Boat b(5);
	b.AddPassenger(p4);
	b.AddPassenger(p5);
	b.AddPassenger(p6);

	Boatplane bp = a + b;

	assert(bp.GetPassengersCount() == 6);
	assert(bp.GetMaxPassengersCount() == 10);

	assert(a.GetPassengersCount() == 0);
	assert(b.GetPassengersCount() == 0);

	ShimCity* ShimCity1 = ShimCity::GetInstance();
	ShimCity* ShimCity2 = ShimCity::GetInstance();

	bool bSame = ShimCity1 == ShimCity2;
	assert(bSame);

	Airplane* airplane = new Airplane(5);
	Boat* boat = new Boat(5);
	Boatplane* boatplane = new Boatplane(5);
	Motorcycle* motorcycle = new Motorcycle();
	Sedan* sedan = new Sedan();
	Sedan* sedan2 = new Sedan();
	UBoat* uboat = new UBoat();

	bool bAdded = sedan2->AddTrailer(new Trailer(50));
	assert(bAdded);

	bAdded = sedan2->AddTrailer(new Trailer(60));
	assert(!bAdded);

	bAdded = ShimCity1->AddVehicle(airplane);
	assert(bAdded);

	ShimCity1->AddVehicle(boat);
	ShimCity1->AddVehicle(boatplane);
	ShimCity1->AddVehicle(motorcycle);
	ShimCity1->AddVehicle(sedan);
	ShimCity1->AddVehicle(sedan2);
	ShimCity1->AddVehicle(uboat);
	ShimCity1->AddVehicle(new Airplane(5));
	ShimCity1->AddVehicle(new Airplane(5));
	ShimCity1->AddVehicle(new Airplane(5));

	bAdded = ShimCity1->AddVehicle(new Airplane(5));

	assert(!bAdded);

	ShimCity1->RemoveVehicle(9);
	ShimCity1->RemoveVehicle(8);
	bool bRemoved = ShimCity1->RemoveVehicle(7);
	assert(bRemoved);

	bRemoved = ShimCity1->RemoveVehicle(9);
	assert(!bRemoved);

	ShimCity1->Travel(); // ��� ��� ������ �̵�
	ShimCity1->Travel(); // Boat, Motorcycle, �� Sedan, UBoat�� �̵�
	ShimCity1->Travel(); // Motorcycle, �� Sedan�� �̵�
	ShimCity1->Travel(); // Boat, Motorcycle, �� Sedan�� �̵�
	ShimCity1->Travel(); // UBoat�� ���� ���� �̵�
	ShimCity1->Travel(); // � ��� ���ܵ� �������� ����
	ShimCity1->Travel(); // Boat, Motorcycle, Ʈ���Ϸ� �� �޸� Sedan, UBoat�� �̵�
	ShimCity1->Travel(); // Boat, Motorcycle, �� Sedan, UBoat�� �̵�
	ShimCity1->Travel(); // Airplane, Boatplane, Motorcycle, �� Sedan�� �̵�
	ShimCity1->Travel(); // Boat, Motorcycle, �� Sedan�� �̵�
	ShimCity1->Travel(); // Boat, Motorcycle, �� Sedan�� �̵�
	ShimCity1->Travel(); // Ʈ���Ϸ� �޸� Sedan�� �̵�

	assert(ShimCity1->GetFurthestTravelled() == boat);

	return 0;
}