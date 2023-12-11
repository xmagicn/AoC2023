#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <map>
#include <unordered_map>
#include <stack>
#include <set>
#include <algorithm>
#include <functional>

// Unused Param
#pragma warning( disable : 4100 )

int Year23Day1Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int CurrentSum = 0;
	int CurrentMax = 0;


	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );
		std::string FirstDigit, LastDigit;

		for (auto& Char : Line)
		{
			if (isdigit(Char))
			{
				if (FirstDigit.empty())
				{
					FirstDigit = Char;
				}
				LastDigit = Char;
			}
		}

		std::string LineSum = FirstDigit + LastDigit;
		if (!LineSum.empty())
		{
			CurrentSum += std::stoi(LineSum);
		}
	}

	myfile.close();

	return CurrentSum;
}

void ReadNumberFromLine(const std::string& Line, int& OutNumber)
{
	const std::string DigitNames[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	int FirstDigit = -1;
	int LastDigit = 0;
	int Idx = 0;

	while (Idx < Line.size())
	{
		auto& Char = Line[Idx];

		if (isdigit(Char))
		{
			if (FirstDigit < 0)
			{
				FirstDigit = static_cast<int>(Char) - 48;// std::stoi(&Char);
			}
			LastDigit = static_cast<int>(Char) - 48;// std::stoi(&Char);
		}
		else
		{
			for (int DigitIdx = 1; DigitIdx < 10; ++DigitIdx)
			{
				const auto& Name = DigitNames[DigitIdx];
				if (Idx + Name.size() - 1 < Line.size())
				{
					std::string SubStr = Line.substr(Idx, Name.size());
					size_t FoundIdx = SubStr.find(Name.c_str());
					if (std::string::npos != FoundIdx)
					{
						if (FirstDigit < 0)
						{
							FirstDigit = DigitIdx;
						}
						LastDigit = DigitIdx;
						//Idx += Name.size() - 1;
						break;
					}
				}
			}
		}

		++Idx;
	}

	OutNumber = (FirstDigit > -1 ? FirstDigit * 10 + LastDigit : 0);
}

// 0 Red, 1 Green, 2 Blue
void ReadGameEntry(const std::string& Line, int& Max, int& Color)
{
	if (Line.empty())
	{
		return;
	}

	std::string ColorStrs[3] = { "red", "green", "blue" };

	size_t ColorIdx;
	for (int Idx = 0; Idx < 3; ++Idx)
	{
		ColorIdx = Line.find(ColorStrs[Idx]);
		if (ColorIdx != std::string::npos)
		{
			Color = Idx;
			break;
		}
	}

	std::string Number = Line.substr(0, ColorIdx);

	Max = std::stoi(Number);
}

int ReadDay23Game(const std::string& Line, int& MaxBlue, int& MaxRed, int& MaxGreen)
{
	size_t CurrOffset = Line.find(':');
	int TestMax, TestColor;
	ReadGameEntry("3 blue", TestMax, TestColor);
	ReadGameEntry("1 red", TestMax, TestColor);
	ReadGameEntry("4 red", TestMax, TestColor);

	return 0;
}

int Year23Day1Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;
	int CurrentMax = 0;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		std::string FirstDigit, LastDigit;

		int FoundDigit;
		ReadNumberFromLine(Line, FoundDigit);
		CurrentSum += FoundDigit;
	}

	myfile.close();

	return CurrentSum;
}

bool ValidateGame(const std::string& GameLine, int* AllowedMaxes)
{
	// Parse to Games
	size_t Idx = GameLine.find(':');
	if (Idx == std::string::npos)
	{
		return false;
	}

	// Skip the space
	Idx += 2;

	// Split into games
	size_t StartIdx;
	int Maxes[3] = { 0, 0, 0 };
	int MaxColor, MaxVal;
	do
	{
		// Run each game
		StartIdx = Idx;
		Idx = GameLine.find(';', StartIdx);

		std::string FullGameStr = GameLine.substr(StartIdx, Idx - StartIdx);
		size_t GameIdx = 0;
		size_t GamePrevIdx = 0;
		do
		{
			GamePrevIdx = GameIdx;
			GameIdx = FullGameStr.find(',', GamePrevIdx);
			ReadGameEntry(FullGameStr.substr(GamePrevIdx, GameIdx - GamePrevIdx), MaxVal, MaxColor);
			Maxes[MaxColor] = std::max(MaxVal, Maxes[MaxColor]);
			if (GameIdx != std::string::npos)
			{
				GameIdx++;
			}
		} while (GameIdx != std::string::npos);

		if (Idx != std::string::npos)
		{
			Idx++;
		}

	} while (Idx != std::string::npos);

	// Validity check
	return (Maxes[0] <= AllowedMaxes[0]
		&& Maxes[1] <= AllowedMaxes[1]
		&& Maxes[2] <= AllowedMaxes[2]);
}

int CalculateGamePower(const std::string& GameLine)
{
	// Parse to Games
	size_t Idx = GameLine.find(':');
	if (Idx == std::string::npos)
	{
		return false;
	}

	// Skip the space
	Idx += 2;

	// Split into games
	size_t StartIdx;
	int Maxes[3] = { 0, 0, 0 };
	int MaxColor, MaxVal;
	do
	{
		// Run each game
		StartIdx = Idx;
		Idx = GameLine.find(';', StartIdx);

		std::string FullGameStr = GameLine.substr(StartIdx, Idx - StartIdx);
		size_t GameIdx = 0;
		size_t GamePrevIdx = 0;
		do
		{
			GamePrevIdx = GameIdx;
			GameIdx = FullGameStr.find(',', GamePrevIdx);
			ReadGameEntry(FullGameStr.substr(GamePrevIdx, GameIdx - GamePrevIdx), MaxVal, MaxColor);
			Maxes[MaxColor] = std::max(MaxVal, Maxes[MaxColor]);
			if (GameIdx != std::string::npos)
			{
				GameIdx++;
			}
		} while (GameIdx != std::string::npos);

		if (Idx != std::string::npos)
		{
			Idx++;
		}

	} while (Idx != std::string::npos);

	return Maxes[0] * Maxes[1] * Maxes[2];
}

int Year23Day2Part1(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;
	int CurrentGame = 1;
	int AllowedMaxes[3] = { 12, 13, 14 };

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		size_t Idx = 0;
		
		if (ValidateGame(Line, AllowedMaxes))
		{
			CurrentSum += CurrentGame;
		}

		++CurrentGame;
	}

	myfile.close();

	return CurrentSum;
}

int Year23Day2Part2(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		size_t Idx = 0;

		CurrentSum += CalculateGamePower(Line);
	}

	myfile.close();

	return CurrentSum;
}

struct EngineSchematics
{
	void AddLine(const std::string& Line)
	{
		Data.push_back(Line);
	}

	void PrintSchematics() const
	{
		for (const auto& Line : Data)
		{
			std::cout << Line << std::endl;
		}

		std::cout << std::endl;
	}

	std::vector<std::pair<int, int>> GetSymbolLocations() const
	{
		std::vector<std::pair<int, int>> Locations;
		for (int RowIdx = 0; RowIdx < Data.size(); ++RowIdx)
		{
			const auto& Line = Data[RowIdx];
			for (int ColIdx = 0; ColIdx < Line.size(); ++ColIdx)
			{
				const auto& Char = Line[ColIdx];
				if (!std::isdigit(Char) && (Char != '.'))
				{
					Locations.push_back(std::pair<int, int>(RowIdx, ColIdx));
				}
			}
		}

		return Locations;
	}

	std::vector<std::pair<int, int>> GetGearLocations() const
	{
		std::vector<std::pair<int, int>> Locations;
		for (int RowIdx = 0; RowIdx < Data.size(); ++RowIdx)
		{
			const auto& Line = Data[RowIdx];
			for (int ColIdx = 0; ColIdx < Line.size(); ++ColIdx)
			{
				const auto& Char = Line[ColIdx];
				if (Char == '*')
				{
					Locations.push_back(std::pair<int, int>(RowIdx, ColIdx));
				}
			}
		}

		return Locations;
	}

	char GetEntryUnchecked(int RowIdx, int ColIdx) const
	{
		return Data[RowIdx][ColIdx];
	}

	bool TryGetNumberAtLocation(int RowIdx, int ColIdx, int& OutNumber, std::pair<int, int>& OutStartPos, std::pair<int, int>& OutEndPos) const
	{
		if (
			Data.size() == 0
			|| RowIdx < 0 || RowIdx >= Data.size()
			|| ColIdx < 0 || ColIdx >= Data[0].size()
			)
		{
			return false;
		}

		int WorkingColIdx = ColIdx;
		char Entry = GetEntryUnchecked(RowIdx, WorkingColIdx);
		if (!std::isdigit(Entry))
		{
			return false;
		}

		// Get start and end pos
		int StartIdx = WorkingColIdx;
		int EndIdx = WorkingColIdx;

		while (WorkingColIdx - 1 >= 0)
		{
			Entry = GetEntryUnchecked(RowIdx, WorkingColIdx - 1);
			if (!std::isdigit(Entry))
			{
				break;
			}
			--WorkingColIdx;
		}
		StartIdx = WorkingColIdx;

		WorkingColIdx = ColIdx;
		while (WorkingColIdx + 1 < Data[0].size())
		{
			Entry = GetEntryUnchecked(RowIdx, WorkingColIdx + 1);
			if (!std::isdigit(Entry))
			{
				break;
			}
			++WorkingColIdx;
		}
		EndIdx = WorkingColIdx;

		const std::string& NumSubStr = Data[RowIdx].substr(StartIdx, EndIdx - StartIdx + 1);
		OutNumber = std::stoi(NumSubStr);
		OutStartPos = std::pair<int, int>(RowIdx, StartIdx);
		OutEndPos = std::pair<int, int>(RowIdx, EndIdx);

		return true;
	}

	std::vector<std::string> Data;
};

int Year23Day3Part1(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;
	EngineSchematics Schematics;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		Schematics.AddLine(Line);
	}

	myfile.close();

	//Schematics.PrintSchematics();
	std::vector<std::pair<int, int>> Locations = Schematics.GetSymbolLocations();

	for (const auto& Location : Locations)
	{
		std::deque<std::pair<int, int>> LocationDeque;

		LocationDeque.push_back(std::pair<int, int>(Location.first - 1, Location.second -1));
		LocationDeque.push_back(std::pair<int, int>(Location.first - 1, Location.second));
		LocationDeque.push_back(std::pair<int, int>(Location.first - 1, Location.second + 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first, Location.second - 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first, Location.second + 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first + 1, Location.second - 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first + 1, Location.second));
		LocationDeque.push_back(std::pair<int, int>(Location.first + 1, Location.second + 1));

		while (LocationDeque.size())
		{
			std::pair<int, int> CurrLoc = LocationDeque.front();
			LocationDeque.pop_front();

			int FoundNumber;
			std::pair<int, int> StartPos, EndPos;
			if (Schematics.TryGetNumberAtLocation(CurrLoc.first, CurrLoc.second, FoundNumber, StartPos, EndPos))
			{
				CurrentSum += FoundNumber;

				// Remove all processed entries
				for (int Idx = StartPos.second; Idx <= EndPos.second; ++Idx)
				{
					auto It = std::find(LocationDeque.begin(), LocationDeque.end(), std::pair<int, int>(CurrLoc.first, Idx));
					if (It != LocationDeque.end())
					{
						LocationDeque.erase(It);
					}
				}
			}
		}
	}

	return CurrentSum;
}

int Year23Day3Part2(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;
	EngineSchematics Schematics;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		Schematics.AddLine(Line);
	}

	myfile.close();

	//Schematics.PrintSchematics();
	std::vector<std::pair<int, int>> Locations = Schematics.GetGearLocations();

	for (const auto& Location : Locations)
	{
		constexpr int NUMS_NEEDED = 2;
		int NumCt = 0;
		int Nums[NUMS_NEEDED];
		bool bTooManyNums = false;
		std::deque<std::pair<int, int>> LocationDeque;

		LocationDeque.push_back(std::pair<int, int>(Location.first - 1, Location.second - 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first - 1, Location.second));
		LocationDeque.push_back(std::pair<int, int>(Location.first - 1, Location.second + 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first, Location.second - 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first, Location.second + 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first + 1, Location.second - 1));
		LocationDeque.push_back(std::pair<int, int>(Location.first + 1, Location.second));
		LocationDeque.push_back(std::pair<int, int>(Location.first + 1, Location.second + 1));

		while (LocationDeque.size())
		{
			std::pair<int, int> CurrLoc = LocationDeque.front();
			LocationDeque.pop_front();

			int FoundNumber;
			std::pair<int, int> StartPos, EndPos;
			if (Schematics.TryGetNumberAtLocation(CurrLoc.first, CurrLoc.second, FoundNumber, StartPos, EndPos))
			{
				if (NumCt < NUMS_NEEDED)
				{
					Nums[NumCt] = FoundNumber;
					++NumCt;
				}
				else
				{
					bTooManyNums = true;
					break;
				}

				// Remove all processed entries
				for (int Idx = StartPos.second; Idx <= EndPos.second; ++Idx)
				{
					auto It = std::find(LocationDeque.begin(), LocationDeque.end(), std::pair<int, int>(CurrLoc.first, Idx));
					if (It != LocationDeque.end())
					{
						LocationDeque.erase(It);
					}
				}
			}
		}

		if (!bTooManyNums && NumCt == NUMS_NEEDED)
		{
			CurrentSum += Nums[0] * Nums[1];
		}
	}

	return CurrentSum;
}

// Space separated sting of numbers
void ReadNumbersIntoArray(const std::string& Numbers, std::vector<int>& OutNumbers)
{
	std::string Temp;
	for (const auto& Char : Numbers)
	{
		if (isdigit(Char))
		{
			Temp += Char;
		}
		else if (!Temp.empty())
		{
			OutNumbers.push_back(std::stoi(Temp));
			Temp.clear();
		}
	}

	// Lazy: handle the last one
	if (!Temp.empty())
	{
		OutNumbers.push_back(std::stoi(Temp));
		Temp.clear();
	}
}
void ReadNumbersIntoArray(const std::string& Numbers, std::vector<long long>& OutNumbers)
{
	std::string Temp;
	for (const auto& Char : Numbers)
	{
		if (isdigit(Char))
		{
			Temp += Char;
		}
		else if (!Temp.empty())
		{
			OutNumbers.push_back(std::stoul(Temp));
			Temp.clear();
		}
	}

	// Lazy: handle the last one
	if (!Temp.empty())
	{
		OutNumbers.push_back(std::stoul(Temp));
		Temp.clear();
	}
}

void ReadCard(const std::string& CardString, std::vector<int>& OutCardNumbers, std::vector<int>& OutWinningNumbers)
{
	size_t CardStartPos = CardString.find(':');
	if (CardStartPos == std::string::npos)
	{
		return;
	}

	CardStartPos += 2;

	size_t WinningNumbersStartPos = CardString.find('|');
	if (CardStartPos == std::string::npos)
	{
		return;
	}

	ReadNumbersIntoArray(CardString.substr(CardStartPos, WinningNumbersStartPos - CardStartPos), OutCardNumbers);
	ReadNumbersIntoArray(CardString.substr(WinningNumbersStartPos), OutWinningNumbers);
}

int Year23Day4Part1(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);

		std::vector<int> CardNumbers, WinningNumbers;
		ReadCard(Line, CardNumbers, WinningNumbers);

		// Calculate the wins so we can use them later
		int WinCt = 0;
		for (int Number : CardNumbers)
		{
			if (std::find(WinningNumbers.begin(), WinningNumbers.end(), Number) != WinningNumbers.end())
			{
				++WinCt;
			}
		}

		// Apply grading metric (must be phrased as annoyingly as possible)
		CurrentSum += static_cast<int>(std::pow(2, WinCt - 1));
	}

	myfile.close();

	return CurrentSum;
}

int Year23Day4Part2(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;
	int GameCt = 1;
	std::unordered_map<int, int> GameToBonusMap;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);

		std::vector<int> CardNumbers, WinningNumbers;
		ReadCard(Line, CardNumbers, WinningNumbers);

		// Calculate the wins so we can use them later
		int WinCt = 0;
		for (int Number : CardNumbers)
		{
			if (std::find(WinningNumbers.begin(), WinningNumbers.end(), Number) != WinningNumbers.end())
			{
				++WinCt;
			}
		}

		// Apply grading metric (must be phrased as annoyingly as possible)
		int TotalCopiesOfThisCard = (1 + GameToBonusMap[GameCt]);
		CurrentSum += TotalCopiesOfThisCard;
		while (WinCt > 0)
		{
			GameToBonusMap[GameCt + WinCt] += TotalCopiesOfThisCard;
			--WinCt;
		}

		++GameCt;
	}

	myfile.close();

	return CurrentSum;
}

enum AlmanacMapTypes
{
	SeedToSoilMap,
	SoilToFertilizerMap,
	FertilizerToWaterMap,
	WaterToLightMap,
	LightToTempMap,
	TempToHumidityMap,
	HumidityToLocMap,

	Count
};

struct Almanac
{
private:
	std::map<long long, std::pair<long long, long long>> SeedToSoilMap;
	std::map<long long, std::pair<long long, long long>> SoilToFertilizerMap;
	std::map<long long, std::pair<long long, long long>> FertilizerToWaterMap;
	std::map<long long, std::pair<long long, long long>> WaterToLightMap;
	std::map<long long, std::pair<long long, long long>> LightToTempMap;
	std::map<long long, std::pair<long long, long long>> TempToHumidityMap;
	std::map<long long, std::pair<long long, long long>> HumidityToLocMap;

public:
	std::map<long long, std::pair<long long, long long>>& GetMap(AlmanacMapTypes MapType)
	{
		switch (MapType)
		{
		case AlmanacMapTypes::SeedToSoilMap:
			return SeedToSoilMap;
		case AlmanacMapTypes::SoilToFertilizerMap:
			return SoilToFertilizerMap;
		case AlmanacMapTypes::FertilizerToWaterMap:
			return FertilizerToWaterMap;
		case AlmanacMapTypes::WaterToLightMap:
			return WaterToLightMap;
		case AlmanacMapTypes::LightToTempMap:
			return LightToTempMap;
		case AlmanacMapTypes::TempToHumidityMap:
			return TempToHumidityMap;
		case AlmanacMapTypes::HumidityToLocMap:
			return HumidityToLocMap;
		default:
			//don't @ me
			return SeedToSoilMap;
		}
	}

private:
	void LoadMapEntry(std::map<long long, std::pair<long long, long long>>& Map, long long Key, long long RangeMin, long long RangeMax)
	{
		Map[Key] = std::pair<long long, long long>(RangeMin, RangeMax);
	}
	void LoadMapEntry(std::map<long long, std::pair<long long, long long>>& Map, const std::string& InLine)
	{
		std::string Temp;
		int ValIdx = 0;
		long long Vals[3] = { 0, 0, 0 };

		for (char Entry : InLine)
		{
			if (Entry != ' ')
			{
				Temp += Entry;
			}
			else
			{
				if (!Temp.empty())
				{
					Vals[ValIdx] = stoul(Temp);

					Temp.clear();
					++ValIdx;
					// Unsafe, relies on input being 3 entries
				}
			}
		}

		if (!Temp.empty())
		{
			// again, don't @ me
			Vals[ValIdx] = stoi(Temp);
		}

		Map[Vals[1]] = std::pair<long long, long long>(Vals[0], Vals[2]);
	}

	long long TransformId(AlmanacMapTypes MapType, long long InId)
	{
		std::map<long long, std::pair<long long, long long>>& CurrMap = GetMap(MapType);

		long long Offset = 0;
		for (const auto& It : CurrMap)
		{
			long long RangeStart = It.first;
			long long RangeEnd = It.first + It.second.second;
			if (InId >= RangeStart && InId < RangeEnd)
			{
				Offset = It.second.first - RangeStart;
				break;
			}
		}

		return InId + Offset;
	}

public:
	void LoadAlmanac(const std::string& Filename)
	{
		std::ifstream myfile;
		myfile.open(Filename);

		bool bSeedsSkipped = false;
		AlmanacMapTypes CurrMapType = static_cast<AlmanacMapTypes>(0);
		std::vector<std::string> CurrentEntries;

		while (myfile.good())
		{
			char line[512];
			myfile.getline(line, 512);
			std::string Line(line);

			if (!Line.empty())
			{
				if (isdigit(Line[0]))
				{
					CurrentEntries.push_back(Line);
				}
			}
			else
			{
				if (bSeedsSkipped)
				{
					for (const std::string& Entry : CurrentEntries)
					{
						LoadMapEntry(GetMap(CurrMapType), Entry);
					}

					CurrMapType = static_cast<AlmanacMapTypes>(static_cast<int>(CurrMapType) + 1);
					CurrentEntries.clear();
				}
				else
				{
					bSeedsSkipped = true;
				}
			}
		}

		// Once more!
		for (const std::string& Entry : CurrentEntries)
		{
			LoadMapEntry(GetMap(CurrMapType), Entry);
		}

		myfile.close();
	}

	long long GetSoilLocationForSeed(long long InSeed)
	{
		long long WorkingId = InSeed;
		for (int MapIdx = 0; MapIdx < static_cast<int>(AlmanacMapTypes::Count); ++MapIdx)
		{
			WorkingId = TransformId(static_cast<AlmanacMapTypes>(MapIdx), WorkingId);
		}
		return WorkingId;
	}

	long long GetMinSoilLocationForSeedRange(const std::map<long long, long long>& InRanges)
	{
		std::map<long long, long long> StartingRanges = InRanges;
		for (int MapIdx = 0; MapIdx < static_cast<int>(AlmanacMapTypes::Count); ++MapIdx)
		{
			auto CurrMap = GetMap(static_cast<AlmanacMapTypes>(MapIdx));
			auto It = CurrMap.begin();
			std::map<long long, long long> TransformedRanges;
			for (const auto& Range : StartingRanges)
			{
				long long RangeStart = Range.first;
				long long RangeEnd = Range.first + Range.second;
				std::pair<long long, long long> NewRange = {-1, -1};

				while (It != CurrMap.end())
				{
					long long TransformStart = It->first;
					long long TransformEnd = It->first + It->second.second;
					if (RangeStart >= TransformStart && RangeStart < TransformEnd) // RangeEnd is within TransformStart/End needs a special case
					{
						long long NewStart = RangeStart + It->second.first - TransformStart;
						long long NewEnd;
						if (RangeEnd < TransformEnd)
						{
							NewEnd = RangeEnd + It->second.first - TransformStart;
							NewRange.first = NewStart;
							NewRange.second = NewEnd;
							break;
						}
						else
						{
							NewEnd = TransformEnd + It->second.first - TransformStart;
						}

					}

					++It;
				}

				if (NewRange.first < 0)
				{
					NewRange = Range;
				}
				TransformedRanges[NewRange.first] = NewRange.second;
			}
			StartingRanges = TransformedRanges;
		}
		return 0;
	}
};

long long Year23Day5Part1(const std::string& Filename)
{
	long long CurrentSum = LLONG_MAX;

	Almanac Records;
	Records.LoadAlmanac(Filename);

	// Get the Seeds
	std::vector<long long> Seeds;
	std::ifstream myfile;

	myfile.open(Filename);
	std::string Line;
	if (myfile.good())
	{
		char line[1024];
		myfile.getline(line, 1024);
		Line += line;
	}
	myfile.close();

	ReadNumbersIntoArray(Line, Seeds);

	for (long long Seed : Seeds)
	{
		CurrentSum = std::min(CurrentSum, Records.GetSoilLocationForSeed(Seed));
	}

	return CurrentSum;
}

long long Year23Day5Part2(const std::string& Filename)
{
	long long CurrentSum = LLONG_MAX;

	Almanac Records;
	Records.LoadAlmanac(Filename);

	// Get the Seeds
	std::vector<long long> Seeds;
	std::ifstream myfile;

	myfile.open(Filename);
	std::string Line;
	if (myfile.good())
	{
		char line[1024];
		myfile.getline(line, 1024);
		Line += line;
	}
	myfile.close();

	ReadNumbersIntoArray(Line, Seeds);
	std::map<long long, long long> SeedRanges;
	for (int Idx = 0; Idx < Seeds.size() - 1; Idx += 2)
	{
		SeedRanges[Seeds[Idx]] = Seeds[Idx + 1];
	}
	//long long Val = Records.GetMinSoilLocationForSeedRange(SeedRanges);

	for (const auto& Range : SeedRanges)
	{

		for (long long Idx = Range.first; Idx < Range.first + Range.second; ++Idx)
		{
			CurrentSum = std::min(CurrentSum, Records.GetSoilLocationForSeed(Idx));
		}
	}

	return CurrentSum;
}

unsigned long long CalcMaxRaceDistance(unsigned long long Time, unsigned long long Distance)
{
	unsigned long long RaceDistance = 0;
	unsigned long long CurrHoldTime = 0;
	do
	{
		++CurrHoldTime;
		RaceDistance = ((Time - CurrHoldTime) * CurrHoldTime);
	} while (RaceDistance <= Distance);
	unsigned long long FirstWinTime = CurrHoldTime;

	CurrHoldTime = Time;
	do
	{
		--CurrHoldTime;
		RaceDistance = ((Time - CurrHoldTime) * CurrHoldTime);
	} while (RaceDistance <= Distance && CurrHoldTime > 0);

	unsigned long long Final = Time - (FirstWinTime) - (Time - CurrHoldTime) + 1;
	//std::cout << Final << std::endl;
	return Final;
}

unsigned long long Year23Day6Part1(const std::unordered_map<long, long>& Input)
{
	unsigned long long CurrentSum = 0;

	CurrentSum = 1;

	for (const auto& Race : Input)
	{
		CurrentSum *= CalcMaxRaceDistance(Race.first, Race.second);
	}

	return CurrentSum;
}

enum class CCWinningHandType
{
	HighCard,
	OnePair,
	TwoPair,
	ThreeOfAKind,
	FullHouse,
	FourOfAKind,
	FiveOfAKind,

	Count
};

CCWinningHandType AddJoker(CCWinningHandType InType, int JokerCt = 1, bool bFlag1 = false, bool bFlag2 = false)
{
	CCWinningHandType CurrType = InType;
	while (JokerCt > 0)
	{
		switch (CurrType)
		{
		case CCWinningHandType::HighCard:
			CurrType = CCWinningHandType::OnePair;
			break;
		case CCWinningHandType::OnePair:
			CurrType = CCWinningHandType::ThreeOfAKind;
			--JokerCt;
			break;
		case CCWinningHandType::TwoPair:
			// If we have a joker in either pair, we only bump to Three
			CurrType = bFlag1 || bFlag2 ? CCWinningHandType::FourOfAKind : CCWinningHandType::FullHouse;
			--JokerCt;
			break;
		case CCWinningHandType::ThreeOfAKind:
			CurrType = CCWinningHandType::FourOfAKind;
			if (bFlag1)
			{
				JokerCt -= 2;
			}
			break;
		case CCWinningHandType::FullHouse:
		case CCWinningHandType::FourOfAKind:
		case CCWinningHandType::FiveOfAKind:
			CurrType = CCWinningHandType::FiveOfAKind;
			break;
		default:
			break;
		}

		if (CurrType == CCWinningHandType::FiveOfAKind)
		{
			break;
		}
		--JokerCt;
	}

	return CurrType;
}

CCWinningHandType GetHandScore(const std::string& InHand, bool bJokersWild = false)
{
	CCWinningHandType Output = CCWinningHandType::HighCard;
	std::unordered_map<char, int> Cards;
	if (InHand.empty())
	{
		return Output;
	}

	// aggregate
	for (char InCard : InHand)
	{
		++Cards[InCard];
	}

	// switch 'em
	std::multimap<char, int, std::greater<int>> OrderedCards;
	for (const auto& Card : Cards)
	{
		OrderedCards.insert({ Card.second, Card.first });
	}

	bool bJokerSlot1 = false;
	bool bJokerSlot2 = false;
	auto It = OrderedCards.begin();
	if (It ->first == 5)
	{
		Output = CCWinningHandType::FiveOfAKind;
	}
	else if (It->first == 4)
	{
		Output = CCWinningHandType::FourOfAKind;
	}
	else if (It->first == 3)
	{
		bJokerSlot1 = It->second == '.';
		++It;
		if (It->first == 2)
		{
			Output = CCWinningHandType::FullHouse;
		}
		else
		{
			Output = CCWinningHandType::ThreeOfAKind;
		}
	}
	else if (It->first == 2)
	{
		bJokerSlot1 |= It->second == '.';
		++It;
		if (It->first == 2)
		{
			Output = CCWinningHandType::TwoPair;
			bJokerSlot2 |= It->second == '.';
		}
		else
		{
			Output = CCWinningHandType::OnePair;
		}
	}

	int JokerCt = Cards['.'];
	if (bJokersWild && JokerCt > 0)
	{
		Output = AddJoker(Output, JokerCt, bJokerSlot1, bJokerSlot2);
	}

	return Output;
}

struct CamelCardHand
{
	CamelCardHand(const std::string& InHand, int InWager, bool bInJokersWild = false)
		: Cards(InHand), Wager(InWager), bJokersWild(bInJokersWild)
	{
		if (Cards.empty())
		{
			// bad
		}

		for (char& Card : Cards)
		{
			if (Card == 'T')
			{
				// right above 9 in ascii
				Card = ':';
			}
			else if (Card == 'J')
			{
				Card = bJokersWild ? '.' : '<';
			}
			else if (Card == 'Q')
			{
				Card = '=';
			}
			else if (Card == 'K')
			{
				Card = '>';
			}
		}
		HandType = GetHandScore(Cards, bJokersWild);
	}

	bool operator<(const CamelCardHand& Other) const
	{
		if (static_cast<int>(HandType) != static_cast<int>(Other.HandType))
		{
			return static_cast<int>(HandType) < static_cast<int>(Other.HandType);
		}

		for (int Idx = 0; Idx < Cards.size() && Idx < Other.Cards.size(); ++Idx)
		{
			if (Cards[Idx] != Other.Cards[Idx])
			{
				return Cards[Idx] < Other.Cards[Idx];
			}
		}

		return std::min(Cards.size(), Other.Cards.size());
	}

	std::string Cards;
	int32_t Wager;
	CCWinningHandType HandType;
	bool bJokersWild;
};

int Year23Day7Part1(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	std::multiset<CamelCardHand> Hands;
	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);

		size_t SpacePos = Line.find(' ');
		if (SpacePos != std::string::npos)
		{
			Hands.insert(CamelCardHand(Line.substr(0, SpacePos), std::stoi(Line.substr(SpacePos + 1))));
		}
	}

	myfile.close();

	int Rank = 1;
	for (const auto& Hand : Hands)
	{
		int Score = Hand.Wager * Rank++;
		CurrentSum += Score;
	}

	return CurrentSum;
}

int Year23Day7Part2(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	std::multiset<CamelCardHand> Hands;
	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);

		size_t SpacePos = Line.find(' ');
		if (SpacePos != std::string::npos)
		{
			Hands.insert(CamelCardHand(Line.substr(0, SpacePos), std::stoi(Line.substr(SpacePos + 1)), true));
		}
	}

	myfile.close();

	int Rank = 1;
	for (const auto& Hand : Hands)
	{
		int Score = Hand.Wager * Rank++;
		CurrentSum += Score;
	}

	return CurrentSum;
}

void AddCamelNode(const std::string& InLine, std::unordered_map < std::string, std::pair<std::string, std::string>>& OutNetwork)
{
	if (InLine.size() == 0)
	{
		return;
	}

	const int STRING_SIZE = 3;
	std::string Key, Left, Right;

	Key = InLine.substr(0, 3);
	Left = InLine.substr(7, 3);
	Right = InLine.substr(12, 3);

	OutNetwork[Key] = std::pair<std::string, std::string>(Left, Right);
}

int RunCamelSimulation(const std::string& Instructions, std::unordered_map<std::string, std::pair<std::string, std::string>>& Network, const std::string& StartingKey, bool bHaunted = false)
{
	int CurrentSum = 0;
	std::string CurrKey(StartingKey);
	int InstructionOffset = 0;


	while (bHaunted ? (CurrKey[2] != 'Z') : (CurrKey != "ZZZ"))
	{
		char Dir = Instructions[InstructionOffset]; // should check for validity
		if (Dir == 'L')
		{
			CurrKey = Network[CurrKey].first;
		}
		else // should be else if
		{
			CurrKey = Network[CurrKey].second;
		}

		InstructionOffset++;
		if (InstructionOffset >= Instructions.size())
		{
			InstructionOffset = 0;
		}

		CurrentSum++;
	}

	return CurrentSum;
}

int Year23Day8Part1(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	std::string Instructions;
	if (myfile.good())
	{
		char line[512];
		myfile.getline(line, 512);
		Instructions += line;

		// Skip the space
		myfile.getline(line, 512);
	}

	std::unordered_map<std::string, std::pair<std::string, std::string>> Network;
	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		AddCamelNode(Line, Network);
	}

	myfile.close();

	CurrentSum = RunCamelSimulation(Instructions, Network, "AAA");

	return CurrentSum;
}

int GetCompletedKeys(const std::vector<std::string>& InKeys)
{
	int NumZs = 0;
	for (const std::string& Key : InKeys)
	{
		if (Key[2] == 'Z')
		{
			++NumZs;
		}
	}
	return NumZs;
}

// [START] - Shamelessly 'borrowed' since i apparently can't have std::lcm
// Modified to handle ungodly-large numbers
// Utility function to find
// GCD of 'a' and 'b'
unsigned long long int gcd(unsigned long long int a, unsigned long long int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

// Returns LCM of array elements
unsigned long long int findlcm(int arr[], int n)
{
	// Initialize result
	long long int ans = arr[0];

	// ans contains LCM of arr[0], ..arr[i]
	// after i'th iteration,
	for (int i = 1; i < n; i++)
		ans = (((arr[i] * ans)) /
			(gcd(arr[i], ans)));

	return ans;
}
// [END] - Shamelessly 'borrowed' since i apparently can't have std::lcm

unsigned long long Year23Day8Part2(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	unsigned long long CurrentSum = 0;

	std::string Instructions;
	if (myfile.good())
	{
		char line[512];
		myfile.getline(line, 512);
		Instructions += line;

		// Skip the space
		myfile.getline(line, 512);
	}

	std::unordered_map<std::string, std::pair<std::string, std::string>> Network;
	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		AddCamelNode(Line, Network);
	}

	myfile.close();

	std::vector<std::string> CurrKeys;
	for (const auto& Entry : Network)
	{
		if (Entry.first[2] == 'A')
		{
			CurrKeys.push_back(Entry.first);
		}
	}

	std::vector<int> MinPaths;
	for (const auto& Key : CurrKeys)
	{
		MinPaths.push_back(RunCamelSimulation(Instructions, Network, Key, true));
	}
	CurrentSum = findlcm(MinPaths.data(), static_cast<int>(MinPaths.size()));

	return CurrentSum;
}

struct SandInstabilitySensor
{
private:
	std::vector<std::deque<int>> History;

public:
	void AddLine(const std::string& InLine)
	{
		std::deque<int> NewLine;
		size_t Start = 0;
		size_t End = InLine.find(' ');
		while (End != std::string::npos)
		{
			std::string NextNum = InLine.substr(Start, End - Start);
			NewLine.push_back(std::stoi(NextNum));

			Start = End + 1;
			End = InLine.find(' ', End + 1);
		}
		std::string NextNum = InLine.substr(Start, End - Start);
		NewLine.push_back(std::stoi(NextNum));

		History.push_back(NewLine);
	}

	bool IsLineAllZeros(const std::deque<int>& InLine) const
	{
		for (int Entry : InLine)
		{
			if (Entry != 0)
			{
				return false;
			}
		}
		return true;
	}

	int GetNextEntry()
	{
		int CurrIdx = 0;
		if (History.size() == 1)
		{
			std::deque<int> NewLine;
			do
			{
				std::deque<int>& CurrLine = History[CurrIdx];
				for (int LineIdx = 1; LineIdx < CurrLine.size(); ++LineIdx)
				{
					NewLine.push_back(CurrLine[LineIdx] - CurrLine[LineIdx - 1]);
				}

				History.push_back(NewLine);
				NewLine.clear();
				++CurrIdx;
			} while (!IsLineAllZeros(History[CurrIdx]));

			History[CurrIdx].push_back(0);
		}

		CurrIdx = static_cast<int>(History.size()) - 1;
		do
		{
			std::deque<int>& CurrLine = History[CurrIdx];
			std::deque<int>& PrevLine = History[CurrIdx - 1];
			int NewEntry = CurrLine[CurrLine.size() - 1] + PrevLine[PrevLine.size() - 1];
			PrevLine.push_back(NewEntry);
			--CurrIdx;
		} while (CurrIdx > 0);
	
		return History[0][History[0].size() - 1];
	}

	int GetPrevEntry()
	{
		int CurrIdx = 0;
		if (History.size() == 1)
		{
			std::deque<int> NewLine;
			do
			{
				std::deque<int>& CurrLine = History[CurrIdx];
				for (int LineIdx = 1; LineIdx < CurrLine.size(); ++LineIdx)
				{
					NewLine.push_back(CurrLine[LineIdx] - CurrLine[LineIdx - 1]);
				}

				History.push_back(NewLine);
				NewLine.clear();
				++CurrIdx;
			} while (!IsLineAllZeros(History[CurrIdx]));

			History[CurrIdx].push_front(0);
		}

		CurrIdx = static_cast<int>(History.size()) - 1;
		do
		{
			std::deque<int>& CurrLine = History[CurrIdx];
			std::deque<int>& PrevLine = History[CurrIdx - 1];
			int NewEntry = PrevLine[0] - CurrLine[0];
			PrevLine.push_front(NewEntry);
			--CurrIdx;
		} while (CurrIdx > 0);

		return History[0][0];
	}
};

int Year23Day9Part1(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);

		SandInstabilitySensor Sensor;
		Sensor.AddLine(Line);
		CurrentSum += Sensor.GetNextEntry();
	}

	myfile.close();

	return CurrentSum;
}

int Year23Day9Part2(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);

		SandInstabilitySensor Sensor;
		Sensor.AddLine(Line);
		CurrentSum += Sensor.GetPrevEntry();
	}

	myfile.close();

	return CurrentSum;
}

struct PipeMap
{
private:
	std::vector<std::vector<char>> Data;

	enum class Directions
	{
		N,
		E,
		S,
		W
	};

public:
	void Print() const
	{
		for (int RowIdx = 0; RowIdx < Data.size(); ++RowIdx)
		{
			for (int ColIdx = 0; ColIdx < Data[RowIdx].size(); ++ColIdx)
			{
				std::cout << Data[RowIdx][ColIdx] << ' ';
			}
			std::cout << std::endl;
		}
	}

	void AddRow(const std::string& InRow)
	{
		std::vector<char> NewRow;
		for (char Entry : InRow)
		{
			NewRow.push_back(Entry);
		}
		Data.push_back(NewRow);
	}

	bool FindStart(int& OutRow, int& OutCol) const
	{
		for (int RowIdx = 0; RowIdx < Data.size(); ++RowIdx)
		{
			for (int ColIdx = 0; ColIdx < Data[RowIdx].size(); ++ColIdx)
			{
				if (Data[RowIdx][ColIdx] == 'S')
				{
					OutRow = RowIdx;
					OutCol = ColIdx;
					return true;
				}
			}
		}
		return false;
	}

	bool IsPipeValid(const std::pair<int, int>& InPos) const
	{
		return InPos.first >= 0
			&& InPos.first < Data.size()
			&& InPos.second >= 0
			&& InPos.second < Data[0].size();
	}
	char GetPipe(const std::pair<int, int>& InPos) const { return IsPipeValid(InPos) ? Data[InPos.first][InPos.second] : ' '; }

	void AppendStartAdjacencies(const std::pair<int, int>& StartPos, std::vector<std::pair<int, int>>& NewPositions) const
	{
		std::pair<int, int> North({StartPos.first + 1, StartPos.second });
		std::pair<int, int> East({ StartPos.first, StartPos.second + 1 });
		std::pair<int, int> South({ StartPos.first - 1, StartPos.second });
		std::pair<int, int> West({ StartPos.first, StartPos.second - 1 });

		if (IsPipeValid(North))
		{
			char NorthPipe = GetPipe(North);
			if (NorthPipe == '|' || NorthPipe == '7' || NorthPipe == 'F')
			{
				NewPositions.push_back(North);
			}
		}

		if (IsPipeValid(East))
		{
			char EastPipe = GetPipe(East);
			if (EastPipe == '-' || EastPipe == '7' || EastPipe == 'J')
			{
				NewPositions.push_back(East);
			}
		}

		if (IsPipeValid(South))
		{
			char SouthPipe = GetPipe(South);
			if (SouthPipe == '|' || SouthPipe == 'L' || SouthPipe == 'J')
			{
				NewPositions.push_back(South);
			}
		}

		if (IsPipeValid(West))
		{
			char WestPipe = GetPipe(West);
			if (WestPipe == '-' || WestPipe == 'F' || WestPipe == 'L')
			{
				NewPositions.push_back(West);
			}
		}
	}
	
	// [START] Lovingly borrowed from https://stackoverflow.com/questions/32685540/why-cant-i-compile-an-unordered-map-with-a-pair-as-key
	struct PipeHash
	{
		template <class T1, class T2>
		std::size_t operator () (const std::pair<T1, T2>& p) const {
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);

			// Mainly for demonstration purposes, i.e. works but is overly simple
			// In the real world, use sth. like boost.hash_combine
			// Yes I saw this comment, yes i ignored it
			return h1 ^ h2;
		}
	};
	// [END]

	int FindLoopLength(int RowStart, int ColStart) const
	{
		PipeMap DebugMap = *this;

		std::stack<std::pair<int, int>> Stack;
		Stack.push({ RowStart, ColStart });

		std::set<std::pair<int, int>> VisitedPositions;
		VisitedPositions.insert({ RowStart, ColStart });

		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> FinalMapping;
		//std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, PipeHash> FinalMapping;

		while (Stack.size())
		{
			std::pair<int, int> CurrPos = Stack.top();
			Stack.pop();
			VisitedPositions.insert(CurrPos);

			char CurrPipe = GetPipe(CurrPos);

			std::vector<std::pair<int, int>> NewPositions;
			switch (CurrPipe)
			{
			case '-':
				NewPositions.push_back({ CurrPos.first, CurrPos.second + 1 });
				NewPositions.push_back({ CurrPos.first, CurrPos.second - 1 });
				break;
			case '|':
				NewPositions.push_back({ CurrPos.first + 1, CurrPos.second });
				NewPositions.push_back({ CurrPos.first - 1, CurrPos.second });
				break;
			case '7':
				NewPositions.push_back({ CurrPos.first, CurrPos.second - 1 });
				NewPositions.push_back({ CurrPos.first + 1, CurrPos.second });
				break;
			case 'F':
				NewPositions.push_back({ CurrPos.first + 1, CurrPos.second });
				NewPositions.push_back({ CurrPos.first, CurrPos.second + 1 });
				break;
			case 'L':
				NewPositions.push_back({ CurrPos.first - 1, CurrPos.second });
				NewPositions.push_back({ CurrPos.first, CurrPos.second + 1 });
				break;
			case 'J':
				NewPositions.push_back({ CurrPos.first - 1, CurrPos.second });
				NewPositions.push_back({ CurrPos.first, CurrPos.second - 1 });
				break;
			case 'S':
				AppendStartAdjacencies(CurrPos, NewPositions);
				break;
			default:
				break;
			}

			for (const auto& Pos : NewPositions)
			{
				if (0 == VisitedPositions.count(Pos))
				{
					Stack.push(Pos);
					FinalMapping.push_back({ Pos, CurrPos });
					//FinalMapping.insert(Pos, CurrPos);
				}
			}
		}
		return static_cast<int>(FinalMapping.size()) / 2;
	}
};

int Year23Day10Part1(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;
	PipeMap Map;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
		Map.AddRow(Line);
	}

	myfile.close();

	//Map.Print();

	int StartRow, StartCol;
	if (Map.FindStart(StartRow, StartCol))
	{
		CurrentSum = Map.FindLoopLength(StartRow, StartCol);
	}

	return CurrentSum;
}

int Year23Day10Part2(const std::string& Filename)
{
	std::ifstream myfile;
	myfile.open(Filename);

	int CurrentSum = 0;

	while (myfile.good())
	{
		char line[256];
		myfile.getline(line, 256);
		std::string Line(line);
	}

	myfile.close();

	return CurrentSum;
}

int main()
{
	/*
	std::string Day1Sample( "..\\Input\\Day1Sample.txt" );
	std::string Day1Input("..\\Input\\Day1Input.txt" );
	std::cout << "Day1Part1Sample: " << Year23Day1Part1( Day1Sample ) << std::endl;
	std::cout << "Day1Part1: " << Year23Day1Part1(Day1Input) << std::endl;
	std::cout << "Day1Part2Sample: " << Year23Day1Part2( Day1Sample ) << std::endl;
	std::cout << "Day1Part2: " << Year23Day1Part2( Day1Input ) << std::endl;



	std::string Day2Sample( "..\\Input\\Day2Sample.txt" );
	std::string Day2Input( "..\\Input\\Day2Input.txt" );
	std::cout << "Day2Part1Sample: " << Year23Day2Part1( Day2Sample ) << std::endl;
	std::cout << "Day2Part1: " << Year23Day2Part1( Day2Input ) << std::endl;
	std::cout << "Day2Part2Sample: " << Year23Day2Part2( Day2Sample ) << std::endl;
	std::cout << "Day2Part2: " << Year23Day2Part2( Day2Input ) << std::endl;



	std::string Day3Sample( "..\\Input\\Day3Sample.txt" );
	std::string Day3Input( "..\\Input\\Day3Input.txt" );
	std::cout << "Day3Part1Sample: " << Year23Day3Part1( Day3Sample ) << std::endl;
	std::cout << "Day3Part1: " << Year23Day3Part1( Day3Input ) << std::endl;
	std::cout << "Day3Part2Sample: " << Year23Day3Part2( Day3Sample ) << std::endl;
	std::cout << "Day3Part2: " << Year23Day3Part2( Day3Input ) << std::endl;

	std::string Day4Sample( "..\\Input\\Day4Sample.txt" );
	std::string Day4Input( "..\\Input\\Day4Input.txt" );
	std::cout << "Day4Part1Sample: " << Year23Day4Part1( Day4Sample ) << std::endl;
	std::cout << "Day4Part1: " << Year23Day4Part1( Day4Input ) << std::endl;
	std::cout << "Day4Part2Sample: " << Year23Day4Part2( Day4Sample ) << std::endl;
	std::cout << "Day4Part2: " << Year23Day4Part2( Day4Input ) << std::endl;

	std::string Day5Sample( "..\\Input\\Day5Sample.txt" );
	std::string Day5Input("..\\Input\\Day5Input.txt" );
	std::cout << "Day5Part1Sample: " << Year23Day5Part1( Day5Sample ) << std::endl;
	std::cout << "Day5Part1: " << Year23Day5Part1( Day5Input ) << std::endl;
	std::cout << "Day5Part2Sample: " << Year23Day5Part2( Day5Sample ) << std::endl;
	std::cout << "Day5Part2: " << Year23Day5Part2( Day5Input ) << std::endl;

	std::unordered_map<long, long> Day6Sample{ {7, 9}, {15, 40}, {30, 200} };
	std::unordered_map<long, long> Day6Input{ {48, 296}, {93, 1928}, {85, 1236}, {95, 1391} };
	std::cout << "Day6Part1Sample: " << Year23Day6Part1( Day6Sample ) << std::endl;
	std::cout << "Day6Part1: " << Year23Day6Part1( Day6Input ) << std::endl;
	std::cout << "Day6Part2Sample: " << CalcMaxRaceDistance(71530, 940200) << std::endl;
	std::cout << "Day6Part2: " << CalcMaxRaceDistance(48938595, 296192812361391) << std::endl;


	std::string Day7Sample( "..\\Input\\Day7Sample.txt" );
	std::string Day7Input("..\\Input\\Day7Input.txt" );
	std::cout << "Day7Part1Sample: " << Year23Day7Part1( Day7Sample ) << std::endl;
	std::cout << "Day7Part1: " << Year23Day7Part1( Day7Input ) << std::endl;
	std::cout << "Day7Part2Sample: " << Year23Day7Part2( Day7Sample ) << std::endl;
	std::cout << "Day7Part2: " << Year23Day7Part2( Day7Input ) << std::endl;

	std::string Day8Sample( "..\\Input\\Day8Sample.txt" );
	std::string Day8Sample2( "..\\Input\\Day8Sample2.txt" );
	std::string Day8Input("..\\Input\\Day8Input.txt" );
	std::cout << "Day8Part1Sample: " << Year23Day8Part1( Day8Sample ) << std::endl;
	std::cout << "Day8Part1: " << Year23Day8Part1( Day8Input ) << std::endl;
	std::cout << "Day8Part2Sample: " << Year23Day8Part2( Day8Sample2 ) << std::endl;
	std::cout << "Day8Part2: " << Year23Day8Part2( Day8Input ) << std::endl;

	std::string Day9Sample( "..\\Input\\Day9Sample.txt" );
	std::string Day9Input("..\\Input\\Day9Input.txt" );
	std::cout << "Day9Part1Sample: " << Year23Day9Part1( Day9Sample ) << std::endl;
	std::cout << "Day9Part1: " << Year23Day9Part1( Day9Input ) << std::endl;
	std::cout << "Day9Part2Sample: " << Year23Day9Part2( Day9Sample ) << std::endl;
	std::cout << "Day9Part2: " << Year23Day9Part2( Day9Input ) << std::endl;

	*/
	std::string Day10Sample( "..\\Input\\Day10Sample.txt" );
	std::string Day10Sample2( "..\\Input\\Day10Sample2.txt" );
	std::string Day10Input("..\\Input\\Day10Input.txt" );
	std::cout << "Day10Part1Sample: " << Year23Day10Part1( Day10Sample ) << std::endl;
	std::cout << "Day10Part1Sample2: " << Year23Day10Part1( Day10Sample2 ) << std::endl;
	std::cout << "Day10Part1: " << Year23Day10Part1( Day10Input ) << std::endl;
	std::cout << "Day10Part2Sample: " << Year23Day10Part2( Day10Sample ) << std::endl;
	std::cout << "Day10Part2Sample2: " << Year23Day10Part2( Day10Sample2 ) << std::endl;
	std::cout << "Day10Part2: " << Year23Day10Part2( Day10Input ) << std::endl;

	/*
	std::string Day11Sample( "..\\Input\\Day11Sample.txt" );
	std::string Day11Input("..\\Input\\Day11Input.txt" );
	std::cout << "Day11Part1Sample: " << Year23Day11Part1( Day11Sample ) << std::endl;
	std::cout << "Day11Part1: " << Year23Day11Part1( Day11Input ) << std::endl;
	std::cout << "Day11Part2Sample: " << Year23Day11Part2( Day11Sample ) << std::endl;
	std::cout << "Day11Part2: " << Year23Day11Part2( Day11Input ) << std::endl;

	std::string Day12Sample( "..\\Input\\Day12Sample.txt" );
	std::string Day12Input("..\\Input\\Day12Input.txt" );
	std::cout << "Day12Part1Sample: " << Year23Day12Part1( Day12Sample, true ) << std::endl;
	std::cout << "Day12Part1: " << Year23Day12Part1( Day12Input, true ) << std::endl;
	std::cout << "Day12Part2Sample: " << Year23Day12Part2( Day12Sample ) << std::endl;
	std::cout << "Day12Part2: " << Year23Day12Part2( Day12Input ) << std::endl;

	std::string Day13Sample( "..\\Input\\Day13Sample.txt" );
	std::string Day13Input("..\\Input\\Day13Input.txt" );
	std::cout << "Day13Part1Sample: " << Year23Day13Part1( Day13Sample ) << std::endl;
	std::cout << "Day13Part1: " << Year23Day13Part1( Day13Input) << std::endl;
	std::cout << "Day13Part2Sample: " << Year23Day13Part2( Day13Sample, true ) << std::endl;
	std::cout << "Day13Part2: " << Year23Day13Part2( Day13Input ) << std::endl;

	std::string Day14Sample( "..\\Input\\Day14Sample.txt" );
	std::string Day14Input("..\\Input\\Day14Input.txt" );
	std::cout << "Day14Part1Sample: " << Year23Day14Part1( Day14Sample ) << std::endl;
	std::cout << "Day14Part1: " << Year23Day14Part1( Day14Input ) << std::endl;
	std::cout << "Day14Part2Sample: " << Year23Day14Part2( Day14Sample, true ) << std::endl;
	std::cout << "Day14Part2: " << Year23Day14Part2( Day14Input ) << std::endl;

	std::string Day15Sample( "..\\Input\\Day15Sample.txt" );
	std::string Day15Input("..\\Input\\Day15Input.txt" );
	std::cout << "Day15Part1Sample: " << Year23Day15Part1( Day15Sample, 10, true ) << std::endl;
	std::cout << "Day15Part1: " << Year23Day15Part1( Day15Input, 2000000 ) << std::endl;
	std::cout << "Day15Part2Sample: " << Year23Day15Part2( Day15Sample, 20, true ) << std::endl;
	std::cout << "Day15Part2: " << Year23Day15Part2( Day15Input, 4000000 ) << std::endl;

	std::string Day16Sample( "..\\Input\\Day16Sample.txt" );
	std::string Day16Input("..\\Input\\Day16Input.txt" );
	std::cout << "Day16Part1Sample: " << Year23Day16Part1( Day16Sample ) << std::endl;
	std::cout << "Day16Part1: " << Year23Day16Part1( Day16Input ) << std::endl;
	std::cout << "Day16Part2Sample: " << Year23Day16Part2( Day16Sample, true ) << std::endl;
	std::cout << "Day16Part2: " << Year23Day16Part2( Day16Input ) << std::endl;

	std::string Day17Sample("..\\Input\\Day17Sample.txt");
	std::string Day17Input("..\\Input\\Day17Input.txt");
	std::cout << "Day17Part1Sample: " << Year23Day17Part1(Day17Sample) << std::endl;
	std::cout << "Day17Part1: " << Year23Day17Part1(Day17Input) << std::endl;
	std::cout << "Day17Part2Sample: " << Year23Day17Part2(Day17Sample, true) << std::endl;
	std::cout << "Day17Part2: " << Year23Day17Part2(Day17Input) << std::endl;

	std::string Day18Sample("..\\Input\\Day18Sample.txt");
	std::string Day18Input("..\\Input\\Day18Input.txt");
	std::cout << "Day18Part1Sample: " << Year23Day18Part1(Day18Sample) << std::endl;
	std::cout << "Day18Part1: " << Year23Day18Part1(Day18Input) << std::endl;
	std::cout << "Day18Part2Sample: " << Year23Day18Part2(Day18Sample, true) << std::endl;
	std::cout << "Day18Part2: " << Year23Day18Part2(Day18Input) << std::endl;

	std::string Day19Sample("..\\Input\\Day19Sample.txt");
	std::string Day19Input("..\\Input\\Day19Input.txt");
	std::cout << "Day19Part1Sample: " << Year23Day19Part1(Day19Sample) << std::endl;
	std::cout << "Day19Part1: " << Year23Day19Part1(Day19Input) << std::endl;
	std::cout << "Day19Part2Sample: " << Year23Day19Part2(Day19Sample, true) << std::endl;
	std::cout << "Day19Part2: " << Year23Day19Part2(Day19Input) << std::endl;

	std::string Day20Sample("..\\Input\\Day20Sample.txt");
	std::string Day20Input("..\\Input\\Day20Input.txt");
	std::cout << "Day20Part1Sample: " << Year23Day20Part1(Day20Sample) << std::endl;
	std::cout << "Day20Part1: " << Year23Day20Part1(Day20Input) << std::endl;
	std::cout << "Day20Part2Sample: " << Year23Day20Part2(Day20Sample, true) << std::endl;
	std::cout << "Day20Part2: " << Year23Day20Part2(Day20Input) << std::endl;

	std::string Day21Sample("..\\Input\\Day21Sample.txt");
	std::string Day21Input("..\\Input\\Day21Input.txt");
	std::cout << "Day21Part1Sample: " << Year23Day21Part1(Day21Sample) << std::endl;
	std::cout << "Day21Part1: " << Year23Day21Part1(Day21Input) << std::endl;
	std::cout << "Day21Part2Sample: " << Year23Day21Part2(Day21Sample, true) << std::endl;
	std::cout << "Day21Part2: " << Year23Day21Part2(Day21Input) << std::endl;

	std::string Day22Sample("..\\Input\\Day22Sample.txt");
	std::string Day22Input("..\\Input\\Day22Input.txt");
	std::cout << "Day22Part1Sample: " << Year23Day22Part1(Day22Sample) << std::endl;
	std::cout << "Day22Part1: " << Year23Day22Part1(Day22Input) << std::endl;
	std::cout << "Day22Part2Sample: " << Year23Day22Part2(Day22Sample, true) << std::endl;
	std::cout << "Day22Part2: " << Year23Day22Part2(Day22Input) << std::endl;

	std::string Day23Sample("..\\Input\\Day23Sample.txt");
	std::string Day23Input("..\\Input\\Day23Input.txt");
	std::cout << "Day23Part1Sample: " << Year23Day23Part1(Day23Sample) << std::endl;
	std::cout << "Day23Part1: " << Year23Day23Part1(Day23Input) << std::endl;
	std::cout << "Day23Part2Sample: " << Year23Day23Part2(Day23Sample, true) << std::endl;
	std::cout << "Day23Part2: " << Year23Day23Part2(Day23Input) << std::endl;

	std::string Day24Sample("..\\Input\\Day24Sample.txt");
	std::string Day24Input("..\\Input\\Day24Input.txt");
	std::cout << "Day24Part1Sample: " << Year23Day24Part1(Day24Sample) << std::endl;
	std::cout << "Day24Part1: " << Year23Day24Part1(Day24Input) << std::endl;
	std::cout << "Day24Part2Sample: " << Year23Day24Part2(Day24Sample, true) << std::endl;
	std::cout << "Day24Part2: " << Year23Day24Part2(Day24Input) << std::endl;

	std::string Day25Sample("..\\Input\\Day25Sample.txt");
	std::string Day25Input("..\\Input\\Day25Input.txt");
	std::cout << "Day25Part1Sample: " << Year23Day25Part1(Day25Sample) << std::endl;
	std::cout << "Day25Part1: " << Year23Day25Part1(Day25Input) << std::endl;
	std::cout << "Day25Part2Sample: " << Year23Day25Part2(Day25Sample, true) << std::endl;
	std::cout << "Day25Part2: " << Year23Day25Part2(Day25Input) << std::endl;
	//*/

	std::cin.get();

	return 0;
}