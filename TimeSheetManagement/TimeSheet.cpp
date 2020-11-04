#include "TimeSheet.h"

namespace lab3
{
	TimeSheet::TimeSheet(const char* name, unsigned int maxEntries)
		: mName{ name }
		, mTableMaxLength{ maxEntries }
		, mTableIndex{ 0 }
	{

		mTimeTable = new int[mTableMaxLength];
		for (size_t i{}; i < mTableMaxLength; i++)
		{
			mTimeTable[i] = 0;
		}

	}


	TimeSheet::TimeSheet(const TimeSheet& rhs)
		: mName{ rhs.mName }
		, mTableMaxLength{ rhs.mTableMaxLength }
		, mTableIndex{ rhs.mTableIndex }
	{

		mTimeTable = new int[mTableMaxLength];
		for (size_t i{}; i < mTableMaxLength; i++)
		{
			mTimeTable[i] = rhs.mTimeTable[i];
		}

	}




	TimeSheet::~TimeSheet()
	{
		delete[] mTimeTable;
	}




	void TimeSheet::AddTime(int timeInHours)
	{
		if (timeInHours < 1 || timeInHours > 10)
		{
			return;
		}

		if (mTableIndex >= mTableMaxLength)
		{
			return;
		}

		mTimeTable[mTableIndex++] = timeInHours;

	}



	int TimeSheet::GetTimeEntry(unsigned int index) const
	{
		if (index >= mTableIndex)
		{
			return -1;
		}

		return mTimeTable[index];
	}



	int TimeSheet::GetTotalTime() const
	{
		int totalTime{};

		for (size_t i{}; i < mTableIndex; i++)
		{
			totalTime += mTimeTable[i];
		}

		return totalTime;
	}




	float TimeSheet::GetAverageTime() const
	{
		if (mTableIndex == 0)
		{
			return 0.0f;
		}

		return static_cast<float>(GetTotalTime()) / mTableIndex;
	}




	float TimeSheet::GetStandardDeviation() const
	{
		if (mTableIndex == 0)
		{
			return 0.0f;
		}
		float averageTime{ GetAverageTime() };
		float deviationSquaredSum{ 0.0 };

		for (size_t i{}; i < mTableIndex; i++)
		{
			float deviation{ mTimeTable[i] - averageTime };
			float deviationSquared{ deviation * deviation };

			deviationSquaredSum += deviationSquared;

		}

		float variance{ deviationSquaredSum / mTableIndex };

		return static_cast<float>(sqrt(variance));
	}



	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}




	size_t TimeSheet::getTableMaxLength() const
	{
		return mTableMaxLength;
	}

	bool TimeSheet::operator==(const TimeSheet& rhs) const
	{
		if (mName != rhs.GetName())
		{
			return false;
		}

		if (mTableIndex != rhs.mTableIndex)
		{
			return false;
		}

		if (mTableMaxLength != rhs.mTableMaxLength)
		{
			return false;
		}

		for (size_t i{}; i < mTableMaxLength; ++i)
		{
			if (mTimeTable[i] != rhs.mTimeTable[i])
			{
				return false;
			}
		}

		return true;

	}



	TimeSheet& TimeSheet::operator=(const TimeSheet& rhs)
	{
		if (*this == rhs)
		{
			return *this;
		}

		mName = rhs.GetName();
		mTableMaxLength = rhs.getTableMaxLength();
		mTableIndex = rhs.mTableIndex;

		int* newTable = new int[mTableMaxLength];

		for (size_t i{}; i < mTableMaxLength; i++)
		{
			newTable[i] = rhs.mTimeTable[i];
		}

		delete[] mTimeTable;
		mTimeTable = newTable;

		return *this;

	}

}