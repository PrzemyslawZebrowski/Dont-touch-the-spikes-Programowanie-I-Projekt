#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

struct ScoreDataLine
{
	unsigned points = 0;
	std::string date="";
};
class ScoreMachine
{
public:
	void sortList();
	void saveList();
	ScoreDataLine getTopScore();
	void loadList();
	void addScore(int);
	std::string getScoreLine(unsigned);
private:
	std::vector<ScoreDataLine>scoreboardList;
	static bool sortListFunction(ScoreDataLine&, ScoreDataLine&);
};

