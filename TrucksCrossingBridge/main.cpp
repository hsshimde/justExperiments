#include <string>
#include <vector>
#include <iostream>


#include "Bridge.h"
#include "Trucks.h"

using namespace std;
using namespace codingpractice;

//int solution(int bridge_length, int weight, vector<int> truck_weights) {
//	int answer = 0;
//
//	size_t currentTruckInsertIndex{};
//	size_t truckCount{ truck_weights.size() };
//	Bridge* br = Bridge::GetBridge(static_cast<size_t>(weight), static_cast<size_t>(bridge_length), truckCount);
//	size_t time{ 1 };
//
//	while (br->GetTruckCrossedCount() != truckCount)
//	{
//		br->RemoveTruck(time);
//		if (currentTruckInsertIndex < truckCount)
//		{
//			if (br->HandleOneMore(static_cast<size_t>(truck_weights[currentTruckInsertIndex])))
//			{
//				br->AddTruck(new Truck{ static_cast<size_t>(truck_weights[currentTruckInsertIndex++]), time });
//			}
//		}
//		
//
//		//br->RemoveTruck(time);
//		time++;
//	}
//
//	answer = static_cast<int>(time);
//
//	return answer;
//}

int main()
{
	//100, 100, [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
	int answer = 0;
	int bridge_length{ 100};
	int weight{ 100 };
	vector<int>truck_weights(10, 10);
	//2	10	[7,4,5,6]	8

	size_t currentTruckInsertIndex{};
	size_t truckCount{ truck_weights.size() };
	Bridge* br = Bridge::GetBridge(static_cast<size_t>(weight), static_cast<size_t>(bridge_length), truckCount);
	size_t time{ 1 };

	while (true)
	{
		br->RemoveTruck(time);

		if (br->GetTruckCrossedCount() == truckCount)
		{
			break;
		}

		if (currentTruckInsertIndex < truckCount)
		{
			if (br->HandleOneMore(static_cast<size_t>(truck_weights[currentTruckInsertIndex])))
			{
				br->AddTruck(new Truck{ static_cast<size_t>(truck_weights[currentTruckInsertIndex++]), time });
			}

		}

		//br->RemoveTruck(time);
		time++;
	}

	answer = static_cast<int>(time);

	std::cout << answer << std::endl;
	return answer;

}