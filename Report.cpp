#include "Report.h"
Report::Report(std::vector<std::string>& reports, std::mutex& report_mutex, 
           std::condition_variable& cv, std::atomic_bool& data_to_report, std::atomic_bool &reports_left_to_to){}

void Report::report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                    std::condition_variable& cv, std::atomic_bool& data_to_report, std::atomic_bool &reports_left_to_to)                    
{
    std::ofstream report_file("temp.txt");

    while (reports_left_to_to == true)
    {
    //std::cout << "report thread is running\n";
    std::unique_lock report_lock(report_mutex);
        cv.wait(report_lock, [&data_to_report]{ return &data_to_report; } );

        for (auto& report : reports) {
            std::cout << report;
            report_file << report;
        }
        reports.clear();
        data_to_report = false;
        report_lock.unlock();
    cv.notify_one();
    }
    
    

}