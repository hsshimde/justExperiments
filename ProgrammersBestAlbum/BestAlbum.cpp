

#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

class Song
{
public:
	Song(string& genre, size_t uniqueNumber, int playsNumber) : mGenre{ genre }, mUniqueNumber{ uniqueNumber }, mPlaysNumber{ playsNumber}{}
	const std::string& GetGenre() const { return mGenre; }
	size_t GetUniqueNumber() const { return mUniqueNumber; }
	int GetPlaysNumber() const { return mPlaysNumber; }


private:
	string mGenre;
	size_t mUniqueNumber;
	int mPlaysNumber;

};



vector<int> solution(vector<string> genres, vector<int> plays) 
{

    vector<int> answer;

	unordered_map<string, int> playNumberMap{};
	unordered_map<string, vector<Song*>> genreSongVectorMap{};
	vector<Song> songVector{};

	for (size_t i{}; i < genres.size(); ++i)
	{
		songVector.emplace_back(Song{ genres[i], i, plays[i] });
	}

	for (size_t i{}; i < songVector.size(); ++i)
	{
		playNumberMap[songVector[i].GetGenre()] += songVector[i].GetPlaysNumber();
		genreSongVectorMap[songVector[i].GetGenre()].push_back(&songVector[i]);
	}

	
	vector<pair<string, int>> playNumberVector(begin(playNumberMap), end(playNumberMap));

	sort(begin(playNumberVector), end(playNumberVector), [](pair<string, int>&p1, pair<string, int>&p2) {return p1.second > p2.second; });


	for (const auto& i : playNumberVector)
	{
		vector<Song*> songVectorEachGenre = genreSongVectorMap[i.first];
		auto predicate = [](const Song* s1, const Song* s2)
		{
			return ((s1->GetPlaysNumber() > s2->GetPlaysNumber())
				|| (s1->GetPlaysNumber() == s2->GetPlaysNumber() && s1->GetUniqueNumber() < s2->GetUniqueNumber()));
		};

		sort(begin(songVectorEachGenre), end(songVectorEachGenre), predicate);

		if (songVectorEachGenre.size() >= 2)
		{
			answer.push_back(songVectorEachGenre[0]->GetUniqueNumber());
			answer.push_back(songVectorEachGenre[1]->GetUniqueNumber());
		}

		else
		{
			answer.push_back(songVectorEachGenre[0]->GetUniqueNumber());
		}
		
	}



	
    return answer;
}

int main()
{

	vector<string> genres{ "noyna", "noyna", "dami", "apinya", "apinya","noyna","dami","dami","aoomaam","aoomaam" };
	vector<int> plays{ 500,600,150,800,2500,320,1000,1111,12,123 };

	assert(genres.size() == plays.size());
	
	vector<int>answer = solution(genres, plays);

	for (const auto& i : answer)
	{
		std::cout << i << std::endl;
	}

	return 0;
}