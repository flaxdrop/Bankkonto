#include "Report.h"


void Report::report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                    std::condition_variable& cv, bool& data_to_report)
{
    std::ofstream report_file("temp.json");

    std::unique_lock report_lock(report_mutex);
    
    cv.wait(report_lock, [&data_to_report]{ return data_to_report; } );

        for (auto& report : reports) {
            std::cout << report;
            report_file << report;
        }
        data_to_report = false;
        report_lock.unlock();
    cv.notify_one();
    
    //

}