#ifndef CHAS_BOILER1_BANKSYSTEM_REPORT
#define CHAS_BOILER1_BANKSYSTEM_REPORT

#include "Bank.h"
#include<chrono>
#include<ctime>
#include <fstream>

class Report{
    public:
    Report(std::vector<std::string>& reports, std::mutex& report_mutex, 
           std::condition_variable& cv, std::atomic_bool &reports_left_to_do, const std::string& filename);
    static void report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                       std::condition_variable& cv, std::atomic_bool &reports_left_to_do, const std::string& filename);
};

// checks if file exists in current directory
bool file_exists(const std::string& filename); 

// get current date in format suitable for a filename
std::string get_current_date_cstyle();

// Function generates a filename based on current date
std::string generate_filename();


#endif