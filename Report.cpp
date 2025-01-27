#include "Report.h"
Report::Report(std::vector<std::string>& reports, std::mutex& report_mutex, 
           std::condition_variable& cv, std::atomic_bool &reports_left_to_do, const std::string& filename){}

void Report::report(std::vector<std::string>& reports, std::mutex& report_mutex, 
                    std::condition_variable& cv, std::atomic_bool &reports_left_to_do, const std::string& filename)                    
{
    std::ofstream report_file(filename);

    while (reports_left_to_do)
    {
        std::unique_lock report_lock(report_mutex);
        cv.wait(report_lock);

        // print reports to file and stdout
        for (auto& report : reports) {
            std::cout << report;
            report_file << report;
        }
        // clear vector
        reports.clear();
        report_lock.unlock();
    }
    
    

}


bool file_exists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string get_current_date_cstyle() {
    std::time_t t = std::time(nullptr);
    char time_string[100]; 
    if (std::strftime(time_string, sizeof(time_string), "%d%b%Y", std::localtime(&t))){
        return time_string;
    }
    else return "date_error";
}

std::string generate_filename() {
    const std::string namebase { "Transactions-" + get_current_date_cstyle() };
    std::string name_to_check { namebase + ".txt" };
    int suffix { 0 };
    while (1) {
        if (!file_exists(name_to_check)) return name_to_check;
        suffix++;
        name_to_check = namebase + "-" + std::to_string(suffix) + ".txt";
    }
    return " ";    
}