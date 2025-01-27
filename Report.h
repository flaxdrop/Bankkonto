#ifndef CHAS_BOILER1_BANKSYSTEM_REPORT
#define CHAS_BOILER1_BANKSYSTEM_REPORT

#include "Bank.h"
#include <fstream>

class Report{
    public:
    Report(std::vector<std::string>& reports, std::mutex& report_mutex, 
           std::condition_variable& cv, bool& data_to_report, std::atomic_bool &reports_left_to_to);
    static void report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                       std::condition_variable& cv, bool& data_to_report, std::atomic_bool &reports_left_to_to);
};


#endif