#include <string>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> jobData;

class CompareByStartTime
{
public:
	bool operator()(const tuple<int, int, int>& t1, const tuple<int, int, int>& t2)
	{
		return get<0>(t1) > get<0>(t2) || (get<0>(t1) == get<0>(t2) && get<1>(t1) > get<1>(t2));
	}
};

class CompareByWorkTime
{
public:
	bool operator()(const tuple<int, int, int>& t1, const tuple<int, int, int>& t2)
	{
		return get<1>(t1) > get<1>(t2) || (get<1>(t1) == get<1>(t2) && get<0>(t1) > get<0>(t2));
	}
};


int solution(vector<vector<int>> jobs) {

	int answer = 0;

	priority_queue<jobData, vector<jobData>, CompareByStartTime> qTime;
	priority_queue<jobData, vector<jobData>, CompareByWorkTime> qWork;

	for (const auto& i : jobs)
	{
		qTime.push(make_tuple(i[0], i[1], 0));
	}

	auto front = qTime.top();
	qTime.pop();

	int time = get<0>(front);
	get<2>(front) = time;

	while (true)
	{
		while (!qTime.empty() && time >= get<0>(qTime.top()))
		{
			qWork.push(qTime.top());
			qTime.pop();
		}

		if (time - get<1>(front) >= get<2>(front))
		{
			if (get<0>(front) != -1)
			{
				answer += (time - get<0>(front));
				get<0>(front) = -1;
			}

			if (!qWork.empty())
			{
				front = qWork.top();
				get<2>(front) = time;
				qWork.pop();
			}

		}

		/*while (!qTime.empty() && time >= get<0>(qTime.top()))
		{
			qWork.push(qTime.top());
			qTime.pop();
		}*/

		if (qTime.empty() && qWork.empty() && get<0>(front) == -1)
		{
			break;
		}

		time++;
	}


	return static_cast<int>(answer / jobs.size());
}

//int main()
//{
//	//[0, 3] , [1, 9], [2, 6]]	9
//
//	vector<vector<int>> jobs{ {0,3},{1,9},{2,6}/*,{2,9},{1,7}*/ };
//
//	int answer = solution(jobs);
//
//	return 0;
//}