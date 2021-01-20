#include "ScoreMachine.h"

void ScoreMachine::sortList()
{
    std::sort(scoreboardList.begin(), scoreboardList.end(), sortListFunction);
    if(scoreboardList.size()>10)
        scoreboardList.pop_back();
}

void ScoreMachine::saveList()
{
    std::fstream scoreboard("scoreboard.bin", std::ios::binary | std::ios::out | std::ios::trunc);
    
    for(auto &i: scoreboardList)
    {
        scoreboard.write(reinterpret_cast<char*>(&i), sizeof(ScoreDataLine));
    }
    scoreboard.close();
}

ScoreDataLine ScoreMachine::getTopScore()
{
    return scoreboardList.front();
}

void ScoreMachine::loadList()
{
    std::fstream scoreboard("scoreboard.bin", std::ios::binary | std::ios::in | std::ios::ate);
    int size = scoreboard.tellg();
    scoreboard.seekg(0);
    auto temp = new ScoreDataLine;
    while ((!scoreboard.eof())&&size)
    {
        scoreboard.read(reinterpret_cast<char*>(temp), sizeof(ScoreDataLine));
        scoreboardList.push_back(*(temp));      
    }

    scoreboard.close();
    while (scoreboardList.size() < 10)
        scoreboardList.push_back(ScoreDataLine{ 0,"---------------" });
}

void ScoreMachine::addScore(int sc)
{
    ScoreDataLine temp;
    temp.points = sc;

    time_t localTime;
    tm tm{};
    auto ptr = &tm;
    time(&localTime);
    localtime_s(ptr, &localTime);

    std::ostringstream oss;
    oss << std::put_time(ptr, "%d-%m-%Y");
   
    temp.date = oss.str();

    scoreboardList.push_back(temp);
}

std::string ScoreMachine::getScoreLine(unsigned n)
{
    std::string toReturn = "";

    if ((n-1 < scoreboardList.size())&&(n>0))
    {
        std::ostringstream oss;
        oss<< std::to_string(n)<<'.';
        oss << std::string((n>9) ? 4 : 5, ' ');
        oss << scoreboardList.at(n-1).date;
        oss << std::setw(6) <<scoreboardList.at(n-1).points;
        toReturn = oss.str();
    }

    return toReturn;
}

bool ScoreMachine::sortListFunction(ScoreDataLine& a, ScoreDataLine& b)
{
    return (a.points > b.points);
}

