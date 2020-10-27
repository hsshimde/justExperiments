#pragma once

#include "Person.h"

namespace assignment2
{
	class Vehicle
	{
	public:
		Vehicle(unsigned int maxPassengersCount);
		Vehicle(const Vehicle& rhs);
		virtual ~Vehicle();
		Vehicle& operator=(const Vehicle& rhs);

		virtual unsigned int GetMaxSpeed() const = 0;

		bool AddPassenger(const Person* person);
		bool RemovePassenger(unsigned int i);
		const Person* GetPassenger(unsigned int i) const;
		unsigned int GetPassengersCount() const;
		unsigned int GetMaxPassengersCount() const;
		size_t GetTravelledDistance() const;
		size_t GetTravelCount() const;
		void Travel();

		virtual bool GoOnTravel() = 0;


	protected:
		void MakeVehicleEmpty();
		void IncreaseTravelCount();

	private:
		static constexpr size_t MAX_COUNT{ 100 };
		size_t mMaxPassengersCount;
		size_t mCurrentPassengersCount;
		size_t mTravelledDistance;
		size_t mTravelCount;
		const Person* mPeopleOnTheVehicle[MAX_COUNT];

	};
}