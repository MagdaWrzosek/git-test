//
// Created by lisik on 08/07/2021.
//
#include <iostream>
#include <iomanip>
#include <map>

struct Range {
public:
    int min;
    int max;
};

struct Date{
public:
    int day;
    int month;
    int year;
};

/**
 * Checks if given value is between given range.min and range.max inclusively
 * @param [in] range  Range object containing information about range
 * @param [in] value Integer value to be checked
 * @return true if value is less of equal to range.max and if value is more or equal range.min
 */
bool isInRange(const Range &range, const int &value) {
    return value >= range.min && value <= range.max;
}


 /**
  * Validate if given date has day, month and year in correct ranges.
  * Prints verbose error to 'std:cerr' if givan values are exceeding their rages.
  * @param date Date to be validated
  * @param dayRange Range value describing possible values for day
  * @param monthRange Range value describing possible values for day
  * @param yearRange Range value describing possible values for year
  * @return true if all three validation are passed `false` otherwise
  */
bool validateDate(const Date& date, Range dayRange, Range monthRange, Range yearRange) {
    bool isDayInRage = isInRange(dayRange, date.day);
    bool isMonthInRage = isInRange(monthRange, date.month);
    bool isYearInRange = isInRange(yearRange, date.year);

    if (!isDayInRage) {
        std::cerr << "Day out of range [" << dayRange.min << "," << dayRange.max << "]\n";
    }
    if (!isMonthInRage) {
        std::cerr << "Month out of range [" << monthRange.min << "," << monthRange.max << "]\n";
    }
    if (!isYearInRange) {
        std::cerr << "Year out of range [" << yearRange.min << "," << yearRange.max << "]\n";
    }

    return isDayInRage && isMonthInRage && isYearInRange;
}

/**
 * Checks if given number is leap year in gregorian calendar.
 * Year is leap is consider to leap if is divisible by 4.
 * Year is not leap if is divisible by 100 and not divisible by 400
 * @param year Integer value
 * @return true if given value is leap year, false otherwise
 */
bool isLeapYear(const int &year) {
    if (year % 100 == 0)
        return year % 400 != 0;
    return year % 4 == 0;
}

/**
 * Function that computes numbers of day in month. Leap year are taken into consideration.
 * This is version utilizes std::map
 * @param month Integers describing
 * @param year Integer value
 * @return numbers of day in month
 */
int getNumberOfDaysInMonthMap(const int &month, const int &year) {
    std::map<int, int> monthsToDays = {{1,  31},
                                       {2,  isLeapYear(year) ? 29 : 28},
                                       {3,  31},
                                       {4,  30},
                                       {5,  31},
                                       {6,  30},
                                       {7,  31},
                                       {8,  31},
                                       {9,  30},
                                       {10, 31},
                                       {11, 30},
                                       {12, 31}};
    return monthsToDays.at(month);
}
/**
 * Validates number od days in month.
 * Assumes that year and month is correct.
 * Prints error to 'std:cerr' if number of day is incorrect.
 * @param date Date object to be validated
 * @return true if date is correct in terms od papal Bull, false otherwise
 */
bool validateDatePapalBull(const Date& date) {
    int maxNumberOfDays = getNumberOfDaysInMonthMap(date.month, date.year);
    bool isNumberOfDaysCorrect = date.day <= maxNumberOfDays;
    if(!isNumberOfDaysCorrect) {
        std::cerr << "Given number of days is incorrect. Month " << date.month << " in year " << date.year << "has "
                  << maxNumberOfDays << "days";
    }
    return isNumberOfDaysCorrect;
}

/**
 * Function that computes date next day.
 * Function assume that date is correct
 * @param date Date to be consider start
 * @return Date that is one day ahead of given one
 */
Date computeDateNextDay(const Date& date){
    Date dateNextDay = Date(date);
    if(date.day== getNumberOfDaysInMonthMap(date.month,date.year)){
        dateNextDay.day = 1;
    } else{
        dateNextDay.day++;
    }
    // check for last month
    if(date.month==12){
        dateNextDay.month=1;
        dateNextDay.year++;
    }
    return dateNextDay;
}

/**
 * Prints given data to std:cout in YYYY-MM-DD format
 * @param date
 */
void printDate(Date date){
    std::cout<<std::setw(4)<<date.year
    <<"-"<<std::setw(2)<<std::setfill('0')<<date.month
    <<"-"<<std::setw(2)<<std::setfill('0')<<date.day;
}


int main() {
    const Range DAY_RANGE = Range{1, 31};
    const Range MOTH_RANGE = Range{1, 12};
    const Range YEAR_RANGE = Range{1538, 2300};

    int day, month, year;
    std::cin >> day >> month >> year;
    Date date = Date{day,month,year};

    //Exit if given numbers are not correct date
    if (!validateDate(date, DAY_RANGE, MOTH_RANGE, YEAR_RANGE)) {
        return 1;
    }
    if(!validateDatePapalBull(date)){
        return 2;
    }
    Date dateNextDay = computeDateNextDay(date);
    printDate(dateNextDay);

    return 0;
}
