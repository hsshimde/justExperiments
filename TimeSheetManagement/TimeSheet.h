#pragma once
#include <string>

namespace lab3
{
	class TimeSheet
	{
	public:

		TimeSheet(const char* name, unsigned int maxEntries);
		TimeSheet(const TimeSheet& rhs);
		~TimeSheet();
		void AddTime(int timeInHours);
		int GetTimeEntry(unsigned int index) const;
		int GetTotalTime() const;
		float GetAverageTime() const;
		float GetStandardDeviation() const;
		const std::string& GetName() const;

		TimeSheet& operator=(const TimeSheet& rhs);
		bool operator==(const TimeSheet& rhs) const;





	private:

		
		size_t getTableMaxLength() const;

		std::string mName;
		int* mTimeTable;
		size_t mTableMaxLength;
		size_t mTableIndex;

	};
}