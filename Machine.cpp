#ifndef MACHINE_CPP
#define MACHINE_CPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <cctype>
#include "csvstream.h"

using namespace std;

set<string> remove_duplicates(string & string_in);

class Machine {
public:
    
    void get_training_data() {
        
        csvstream train_file("job_skills.csv");
        
        map<string, string> input;
 
        while (train_file >> input) {
            
            string job_title;
            string location;
            string category;
            string job_min;
            string job_preferred;
            
            set<string> unique_category;
            set<string> unique_location;
            
            string complete_skills;
            set<string> unique_skills;
            
            for (auto it = input.begin(); it != input.end(); ++it) {
                
                if(it -> first == "Title") {
                    job_title = it -> second;
                }
                
                if(it -> first == "Category") {
                    category = it -> second;
                }
                
                if(it -> first == "Location") {
                    location = it -> second;
                }
                
                if(it -> first == "Minimum Qualifications") {
                    job_min = it -> second;
                }
                
                if(it -> first == "Preferred Qualifications") {
                    job_preferred = it -> second;
                }
                
            }
            
            unique_category = remove_duplicates(category);
            unique_location = remove_duplicates(location);
            
            complete_skills = job_min + job_preferred;
            unique_skills = remove_duplicates(complete_skills);
            
            for (auto it = unique_category.begin(); it != unique_category.end(); ++it) {
                title_category_count[{job_title, *it}] += 1;
                category_count[*it] += 1;
                all_categories.insert(*it);
                //cout << *it << endl;
            }
            
            for (auto it = unique_location.begin(); it != unique_location.end(); ++it) {
                title_location_count[{job_title, *it}] += 1;
                location_count[*it] += 1;
                all_locations.insert(*it);
            }
            
            for (auto it = unique_skills.begin(); it != unique_skills.end(); ++it) {
                title_skills_count[{job_title, *it}] += 1;
                keywords_count[*it] += 1;
                all_keywords.insert(*it);
            }
            
            titles_count[job_title] += 1;
 
            all_titles.insert(job_title);
            
            ++num_jobs;
            
        }
        
        num_categories = static_cast<int>(all_categories.size());
        num_locations = static_cast<int>(all_locations.size());
        num_keywords = static_cast<int>(all_keywords.size());
        
    }
    
    void request_skills() {
        
        /*
        cout << "cat" << endl;
        for (auto it = all_categories.begin(); it != all_categories.end(); ++it) {
            cout << *it << endl;
        }
        
        cout << "loc" << endl;
        for (auto it = all_locations.begin(); it != all_locations.end(); ++it) {
            cout << *it << endl;
        }
        cout << "skill" << endl;
        for (auto it = all_keywords.begin(); it != all_keywords.end(); ++it) {
            cout << *it << endl;
        }
        */
        
        cout << endl;
        
        cout << "Please enter your job category. Here are the available options: {ACCOUNT, ADMINISTRATIVE, DATA CENTER, COMMUNICATIONS, CUSTOMER, DATA, DESIGN, DEVELOPER, SOFTWARE ENGINEERING, HARDWARE ENGINEERING, NETWORK ENGINEERING, REAL ESTATE, FINANCE, GOVERNMENT, HARDWARE, INFRASTRUCTURE, IT, LEGAL, MANUFACTURING, MARKETING, NETWORK, OPERATIONS, PARTNERSHIPS, PEOPLE, PRODUCT MANAGEMENT, PROGRAM, RELATIONS, SALES, SERVICES, SOFTWARE, SOLUTIONS, BUSINESS STRATEGY, SUPPLY CHAIN, TECHNICAL SUPPORT, USER EXPERIENCE, WORKPLACE, WRITING}" << endl
            << " Please 'enter' after you're done entering the category" << endl << endl;
        
        getline(cin, user_category);
        
        cout << endl;
        cout << "Please enter your preferred locations by city, and be sure"
        << " to put a space between each word."
        << " Please 'enter' after you're done entering locations" << endl << endl;
        
        getline(cin, user_location);
        
        cout << endl;
        cout << "Please enter your key skills, and be sure to put a space between each word."
        << " Please 'enter' after you're done entering skills" << endl << endl;
        
        getline(cin, user_skills);
        
        user_category_sorted = remove_duplicates(user_category);
        user_location_sorted = remove_duplicates(user_location);
        user_skills_sorted = remove_duplicates(user_skills);
        
        num_user_categories = static_cast<int>(user_category_sorted.size());
        num_user_locations = static_cast<int>(user_location_sorted.size());
        num_user_skills = static_cast<int>(user_skills_sorted.size());
        
    }
    
    double log_prior (const string & job_title) {
        
        double numerator;
        if (titles_count.find(job_title) != titles_count.end()) {
            numerator = titles_count.find(job_title) -> second;
        }
        else {
            numerator = 0;
        }
        double denominator = num_jobs;
        return log(numerator/denominator);
        
    }
    
    double log_likelihood_category(const string & job_title, const string & category) {
        
        pair<string, string> current_combination(job_title, category);
        
        if(title_category_count.find(current_combination) != title_category_count.end()) {
            
            double numerator = title_category_count.find(current_combination) -> second;
            double denominator = title_category_count.find(current_combination) -> second;
            return log((numerator / denominator) * 10);
            
        }
        
        else if (all_categories.find(category) != all_categories.end()) {
            
            double numerator = category_count.find(category) -> second;
            double denominator = num_jobs;
            return log((numerator / denominator) * 10);
            
        }
        
        else {
            
            double denominator = num_jobs;
            return log((1.0 / denominator));
            
        }
        
    }
    
    double log_likelihood_location(const string & job_title, const string & location) {
        
        pair<string, string> current_combination(job_title, location);
        
        if(title_location_count.find(current_combination) != title_location_count.end()) {
            
            location_match = true;
            
            double numerator = title_location_count.find(current_combination) -> second;
            double denominator = title_location_count.find(current_combination) -> second;
            return log((numerator / denominator) * 2);
            
        }
        
        else if (all_locations.find(location) != all_locations.end()) {
            
            double numerator = location_count.find(location) -> second;
            double denominator = num_jobs;
            return log((numerator / denominator) * 2);
            
        }
        
        else {
            
            double denominator = num_jobs;
            return log((1.0 / denominator));
            
        }
        
    }
    
    double log_likelihood_skills(const string & job_title, const string & skill) {
        
        pair<string, string> current_combination(job_title, skill);
       
        if(title_skills_count.find(current_combination) != title_skills_count.end()) {
            
            double numerator = title_skills_count.find(current_combination) -> second;
            double denominator = title_skills_count.find(current_combination) -> second;
            return log(numerator / denominator);
            
        }
        
        else if (all_keywords.find(skill) != all_keywords.end()) {
            
            double numerator = keywords_count.find(skill) -> second;
            double denominator = num_jobs;
            return log(numerator / denominator);
            
        }
       
        else {
            
            double denominator = num_jobs;
            return log((1.0 / denominator));
            
        }
        
    }
    
    
    void find_probability() {
        
        double category_prob= 0;
        double location_prob= 0;
        double keyword_prob= 0;
        
        map<string, double> all_probs;
        
        for (auto it = all_titles.begin(); it != all_titles.end(); ++it) {
            
            for (auto it_cat = user_category_sorted.begin();
                it_cat != user_category_sorted.end(); ++it_cat) {
                
                category_prob = log_likelihood_category(*it, *it_cat);
                
                all_probs[*it] += category_prob;
                
            }
            
            //cout << "Category prob is " << category_prob << endl;
            
            for (auto it_loc = user_location_sorted.begin();
                it_loc != user_location_sorted.end(); ++it_loc) {
                
                location_prob = log_likelihood_location(*it, *it_loc);
                
                all_probs[*it] += location_prob;
                
            }
            
            //cout << "Location prob is " << location_prob << endl;
            
            for (auto it_skills = user_skills_sorted.begin();
                it_skills != user_skills_sorted.end(); ++it_skills) {
                
                keyword_prob = log_likelihood_skills(*it, *it_skills);
                
                all_probs[*it] += keyword_prob;
                
            }
            
            //cout << "Skills prob is " << keyword_prob << endl;
            
        }
        
        /*
        for (auto it = all_probs.begin(); it != all_probs.end(); ++it) {
            cout << it -> first << " " << it -> second << endl;
        }
         */
    
        pair<string, double> best_match = *all_probs.begin();
        
        for (auto it_choose = all_probs.begin();
             it_choose != all_probs.end(); ++it_choose) {
            
            if(it_choose -> second > best_match.second) {
                best_match = *it_choose;
            }
            
        }
        
        double match_threshold = -1.5 * (num_user_categories + num_user_locations + num_user_skills);
        double difference_threshold = .6 * (num_user_categories + num_user_locations + num_user_skills);
        
        if (best_match.second < match_threshold) {
            bad_criteria = true;
        }
        
        for (auto it_get_all = all_probs.begin();
             it_get_all != all_probs.end(); ++it_get_all) {
            
            if(abs(it_get_all -> second - best_match.second) < difference_threshold) {
                best_matches.insert(*it_get_all);
            }
            
        }
        
    }
    
    void get_result() {
        
        cout << endl;
        cout << "Job Search Results:" << endl << endl;
        
        int index = 1;
        
        find_probability();
        
        if (bad_criteria) {
            cout << "There are no good matches. Please try changing your"
            << " search criteria next time." << endl << endl;
            return;
        }
        
        if (best_matches.size() > 50) {
            cout << "There are too many results to display. Please narrow your search criteria."
            << endl << endl;
            return;
        }
        
        for (auto it = best_matches.begin(); it != best_matches.end(); ++it) {
            cout << "Job " << index << ": " << it -> first << endl;
            for (auto it_words = user_location_sorted.begin();
                 it_words != user_location_sorted.end(); ++it_words) {
                if (title_location_count[{it -> first, *it_words}] != 0) {
                    cout << "(This job is in a location you prefer)" << endl << endl;
                    break;
                }
                else {
                    cout << "(This job is not in a location you prefer)" << endl << endl;
                    break;
                }
            }
            
            ++index;
        }
        
        cout << endl;
        
    }
    
    
private:
    
    map<string, int> keywords_count;
    map<string, int> titles_count;
    map<string, int> category_count;
    map<string, int> location_count;
    
    set<string> all_keywords;
    set<string> all_titles;
    set<string> all_categories;
    set<string> all_locations;
    
    map<pair<string, string>, int> title_skills_count;
    map<pair<string, string>, int> title_category_count;
    map<pair<string, string>, int> title_location_count;
    
    int num_jobs = 0;
    int num_keywords = 0;
    int num_categories = 0;
    int num_locations = 0;
    
    string user_category;
    set<string> user_category_sorted;
    int num_user_categories;
    
    string user_location;
    set<string> user_location_sorted;
    int num_user_locations;
    
    string user_skills;
    set<string> user_skills_sorted;
    int num_user_skills;
    
    map<string, double> best_matches;
    
    bool location_match = false;
    bool bad_criteria = false;
    
};


set<string> remove_duplicates(string & string_in) {
    
    for (int i = 0, len = static_cast<int>(string_in.size()); i < len; i++) {
        if (ispunct(string_in[i]))
        {
            string_in.erase(i--, 1);
            len = static_cast<int>(string_in.size());
        }
        else {
            string_in[i] = toupper(string_in[i]);
        }
    }
    
    //string_in.erase(remove_if(string_in.begin(), string_in.begin(), ispunct));
    istringstream input_content{string_in};
    set<string> result = {istream_iterator<string>{input_content}, istream_iterator<string>{}};
    return result;
    
}


#endif
