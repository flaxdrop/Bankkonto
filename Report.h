#ifndef CHAS_BOILER1_BANKSYSTEM_REPORT
#define CHAS_BOILER1_BANKSYSTEM_REPORT

#include "Bank.h"
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <fstream>
#include <atomic>
#include <sstream>

namespace Report{
       void report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                   std::condition_variable& cv, std::atomic_bool &reports_left_to_do, const std::string& filename);
};

bool file_exists(const std::string& filename); 
std::string get_current_date_cstyle();
std::string generate_filename();


#endif