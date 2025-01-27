#include "Report.h"


void Report::report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                    std::condition_variable& cv, bool& data_to_report)
{
    std::unique_lock report_lock(report_mutex);
    cv.wait(report_lock, [&data_to_report]{ return data_to_report; } );

    while(reports.size() != 0) {
        // std::string local_report = reports.pop_back() ;
        // std::cout << repor

    }




    //


}