#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>

std::string formatdate(const std::tm& date) 
    {std::stringstream ss;
    ss << std::put_time(&date, "%Y-%m-%d");
    return ss.str();}

std::tm getfirstdayofweek(int year, int month, int week) 
    {std::tm date = {};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1; 
    date.tm_mday = 1;
    std::mktime(&date);
    date.tm_mday += (week - 1) * 7;
    std::mktime(&date);
    date.tm_mday -= date.tm_wday;
    std::mktime(&date);
    return date;}

std::string searchprompt(const std::string& userid, int year, int month, int weeki, int weekf) 
    {std::tm startdate = getfirstdayofweek(year, month, weeki);
    std::tm enddate = getfirstdayofweek(year, month, weekf);
    enddate.tm_mday += 6;
    std::mktime(&startdate); 
    std::mktime(&enddate); 
    std::string fromdate = formatdate(startdate);
    std::string todate = formatdate(enddate);
    std::stringstream searchprompt;
    searchprompt << "from: " << userid << " on: " << fromdate << " before: " << todate;
    return searchprompt.str();}

void getinitialinput(std::string& userid, int& month) 
    {std::cout << "userid: ";
    std::cin >> userid;
    std::cout << "month (1-12): ";
    std::cin >> month;}

void getweeklyinput(int& weeki, int& weekf) 
    {std::cout << "initial week: ";
    std::cin >> weeki;
    std::cout << "final week: ";
    std::cin >> weekf;}

void getmessagecount(int& messages) 
	{std::cout << "amount of messages during this week: ";
    std::cin >> messages;}

int main() 
    {std::string userid;
    int month, weeki, weekf;
    const int year = 2024;
    std::string retry;
    std::vector<int> messagecounts;

    do {messagecounts.clear();
        getinitialinput(userid, month);
        do {getweeklyinput(weeki, weekf);
            std::string prompt = searchprompt(userid, year, month, weeki, weekf);
            std::cout << "search prompt: " << prompt << std::endl;
            int messages;
            getmessagecount(messages);
            messagecounts.push_back(messages);
            std::cout << "try again or calculate average messages per week? (try/calc): ";
            std::cin >> retry;} 
			while (retry == "try");

        if (!messagecounts.empty()) 
            {int totalmessages = 0;
            for (int count : messagecounts) {
                totalmessages += count;}
            double average = static_cast<double>(totalmessages) / messagecounts.size();
            std::cout << "avg messages: " << average << std::endl;}
        std::cout << "restart? (y/n): ";
        std::cin >> retry;} 
	while (retry == "y" || retry == "Y");
    return 0;}
