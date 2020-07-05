#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Machine.cpp"

using namespace std;

int main() {
    
    Machine job_finder;
    
    job_finder.get_training_data();
    
    job_finder.request_skills();
    
    job_finder.get_result();
    
    cout << "Job Search Complete." << endl << endl;
    
    return 0;
    
}



