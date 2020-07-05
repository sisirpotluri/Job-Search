# Job-Search
A basic command-line job search program that returns Google jobs to apply for based on input such as category, location, and skills. It applies basic machine learning principles and uses data structures such as maps, sets and classes.

## Supervised Training 
I used a CSV file containing data about over 1700 past Google jobs, including job titles, category, location, and desired qualifications. After reading the data in the file and storing keyword-job combinations in several maps, the log likehlihood that each word of appears with a given job was calculated. This allows the program to estimate the chance that a keyword in a category, location, or skill would appear with a given job title. 

## Prediction
Here are the prompts and sample user inputs:

```bash

Please enter your job category. Here are the available options: {ACCOUNT, ADMINISTRATIVE, DATA CENTER, COMMUNICATIONS, CUSTOMER, DATA, DESIGN, DEVELOPER, SOFTWARE ENGINEERING, HARDWARE ENGINEERING, NETWORK ENGINEERING, REAL ESTATE, FINANCE, GOVERNMENT, HARDWARE, INFRASTRUCTURE, IT, LEGAL, MANUFACTURING, MARKETING, NETWORK, OPERATIONS, PARTNERSHIPS, PEOPLE, PRODUCT MANAGEMENT, PROGRAM, RELATIONS, SALES, SERVICES, SOFTWARE, SOLUTIONS, BUSINESS STRATEGY, SUPPLY CHAIN, TECHNICAL SUPPORT, USER EXPERIENCE, WORKPLACE, WRITING}
Please 'enter' after you're done entering the category

>>>Software Engineering

Please enter your preferred locations by city, and be sure to put a space between each word. Please 'enter' after you're done entering locations

>>>Sunnyvale CA

Please enter your key skills, and be sure to put a space between each word. Please 'enter' after you're done entering skills

>>>Java Cloud AWS Angular Testing

```

Based on user input, the program determines the log likelihood of every job title. This is done efficiently since a map was used to store combinations of job titles and keywords. If the user input is vague or irrelevant to any jobs at Google, the program gives the following message:

```bash
There are no good matches. Please try changing your search criteria next time.
```

This is determined by a minimum threshold for the maximum log likelihood, which is weighted based on the number of keywords entered (more keywords equates to a lower threshold since log likelihood decreases with increased specificity). The program then determines a difference threshold, which is a range of log likelihoods beneath the maximum one. All jobs titles in this range are included in the results. This range is also determined based on the number of keywords entered, and it narrows down as more keywords are entered to ensure only relevant results appear. If more than 50 jobs are returned, this message will be printed:

```bash
There are too many results to display. Please narrow your search criteria.
```

Otherwise, the program returns all jobs - in alphabetical order - that match the user's criteria. It also mentions whether each job is in a preferred location or not. This is how the job search results appear:

```bash

Job Search Results:

Job 1: Cloud Integration Software Engineer, Robotics Simulation, Google Cloud Platform
(This job is not in a location you prefer)

Job 2: Software Engineer (English)
(This job is not in a location you prefer)

Job 3: Software Engineer Manager, Tools and Infrastructure
(This job is not in a location you prefer)

Job 4: Software Engineering Manager, G Suite
(This job is in a location you prefer)

Job 5: Web Solutions Engineer, Product and Tools Operations
(This job is in a location you prefer)

```

## Licenses and Acknowledgments

The CSV file containing data about past Google jobs is under the [CC BY-NC-SA 4.0 license](https://creativecommons.org/licenses/by-nc-sa/4.0/). Credit for the entire file - which was not edited in any way - goes to Niyamat Ullah. A link to the source of the CSV file is provided [here](https://www.kaggle.com/niyamatalmass/google-job-skills). 

The csvstream.h file was written by Andrew DeOrio, and the link to the code is provided [here](https://github.com/awdeorio/csvstream). 

## Running the Program

The program can be cloned into a local repository and run from the command-line. After accessing the folder containing the program, run the following commands to use the job search:

```bash
g++ -Wall -Werror -pedantic --std=c++11 main.cpp -o main.exe
```
followed by

```bash
./main.exe
```

