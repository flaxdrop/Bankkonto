#ifndef CHAS_BOILER1_BANKSYSTEM_CLIENT
#define CHAS_BOILER1_BANKSYSTEM_CLIENT

#include "Bank.h"

class Report{
    public:
    Report(std::vector<std::string>& reports, std::mutex& report_mutex, 
           std::condition_variable& cv, bool& data_to_report);
    static void report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                       std::condition_variable& cv, bool& data_to_report);
};


#endif