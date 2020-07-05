#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Machine.cpp"

using namespace std;

int main() {
    
    //bool conduct = false;
    
    Machine job_finder;
    
    job_finder.get_training_data();
    
    job_finder.request_skills();
    
    job_finder.get_result();
    
    /*
    while (conduct) {
        
        cout << "Training the Algorithm..." << endl;
        
        Machine job_finder;
        
        job_finder.get_training_data();
        
        job_finder.request_skills();
        
        job_finder.get_result();
        
        cout << "Enter either 'repeat' or 'done'." << endl;
        
        string go;
        
        cin >> go;
        
        if (go == "repeat" || go == "Repeat") {
            conduct = true;
        }
        else {
            conduct = false;
        }
        
    }
     */
    
    cout << "Job Search Complete." << endl << endl;
    
    return 0;
    
}



