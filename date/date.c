#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/// @brief Structure to save the program's output
typedef struct
{
    int m_TotalDays;
    int m_WorkDays;
} TResult;

/// @brief Function that checks whether the given year is a leap year.
/// @param year Year to check
/// @return Whether the provided year is a leap year
bool isLeapYear(int year)
{
    if (year % 4000 == 0)
    {
        return 0;
    }
    if (year % 400 == 0)
    {
        return 1;
    }
    if (year % 100 == 0)
    {
        return 0;
    }
    if (year % 4 == 0)
    {
        return 1;
    }

    return 0;
}

/// @brief Gets the century code for the given year with the DOTW algorithm.
/// @param year Year to get century code for.
/// @return Century code for the given year.
int getCenturyCode(int year) {
    const int results[4] = {6, 4, 2, 0};
    int century = year/100;
    int mod = century % 4;
    return results[mod];
}

/// @brief Gets the year code for DOTW algorithm.
/// @param year Year to get code for
/// @return Year code
int getYearCode(int year) {
    int digit1 = ((int)(year/10)) % 10;
    int digit2 = year % 10;
    int doubleDigit = (digit1 * 10) + digit2;
    return (doubleDigit + (doubleDigit / 4)) % 7;
}

/// @brief Returns the month code for the given month for the DOTW algorithm.
/// @param month Month to get the code for.
/// @return Month code for the given month.
int getMonthCode(int month) {
    const int months[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    return months[month-1];
}

/// @brief Gets the amount of days in the specified month.
/// @param isLeapYear Boolean whether the year is a leap year
/// @param month Month to get amount of days for
/// @return Amount of days in the specified month
int getCountDaysInMonth(bool isLeapYear, int month) {
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear && month == 2) {
        return 29;
    }

    return daysInMonth[month-1];
}

/// @brief Calculates the given day of the week from the provided input.
/// Utilizes the algorithm from this blog: https://artofmemory.com/blog/how-to-calculate-the-day-of-the-week/
/// @param year Input year
/// @param month Input month
/// @param day Input day
/// @return Day of the week from {0...6} where 0 -> sunday
int getDayOfTheWeek(int year, int month, int day) {
    int leapYearModifier = (isLeapYear(year) && (month == 1 || month == 2) ? -1 : 0);
    return (getYearCode(year) + getMonthCode(month) + getCenturyCode(year) + day + leapYearModifier) % 7;
}

/// @brief Gets whether the specified month and day are a holiday.
/// @param month Month to check for
/// @param day Day to check for
/// @return Whether the specified date is a holiday
bool isHoliday(int month, int day) {
    return (month == 1 && day == 1)
        || (month == 5 && day == 1)
        || (month == 5 && day == 8)
        || (month == 7 && day == 5)
        || (month == 7 && day == 6)
        || (month == 9 && day == 28)
        || (month == 10 && day == 28)
        || (month == 11 && day == 17)
        || (month == 12 && day >= 24 && day <= 26);
}

/// @brief Checks whether the given input is valid within the calendar.
/// @param year Input year
/// @param month Input month
/// @param day Input day
/// @return true if the input is valid, false otherwise.
bool isValidDate(int year, int month, int day) {
    // Handle years smaller than 2000.
    if(year < 2000) {
        return false;
    }

    // Handle incorrect months
    if(month < 1 || month > 12) {
        return false;
    }

    return (day > 0 && day <= getCountDaysInMonth(isLeapYear(year), month));
}

/// @brief Checks whether the second date is subsequent to the first one (date2 > date1)
/// @param year1 Year of date1
/// @param month1 Month of date1
/// @param day1 Day of date1
/// @param year2 Year of date2
/// @param month2 Month of date2
/// @param day2 Day of date2
/// @return Whether date2 is bigger than date1
bool isSubsequent(int year1, int month1, int day1, int year2, int month2, int day2) {
    if(year1 > year2) 
        return false;

    if(year2 > year1)
        return true;

    if(month1 > month2)
        return false;

    if(month2 > month1)
        return true;

    if(day1 > day2)
        return false;
    
    return true;
}

/// @brief Gets whether the specified date is a work day.
/// To be classied as work day, the date needs to be Monday - Friday and not be a holiday.
/// If the year, month or day are not valid (or valid within the given month/year), returns false.
/// @param year Input year
/// @param month Input month
/// @param day Input day
/// @return Whether the specified date is a work day
bool isWorkDay(int year, int month, int day)
{
    // Check input year, month and day.
    // If the input is not valid, return false.
    if(!isValidDate(year, month, day)) {
        return false;
    }

    int dayOfWeek = getDayOfTheWeek(year, month, day);
    return (dayOfWeek != 0 && dayOfWeek != 6 && !isHoliday(month, day));
}

TResult countDays(int year1, int month1, int day1, int year2, int month2, int day2)
{
    // Result struct
    TResult result;

    // Validate inputs - check each input entirely.
    // Also check whether the first date is smaller than the second date.
    if(!isValidDate(year1, month1, day1) || !isValidDate(year2, month2, day2) || !isSubsequent(year1, month1, day1, year2, month2, day2)) {
        result.m_TotalDays = -1;
        result.m_WorkDays = -1;
        return result;
    }

    // Instantly return if the dates are equal.
    if(year1 == year2 && month1 == month2 && day1 == day2) {
        result.m_TotalDays = 1;
        result.m_WorkDays = (isWorkDay(year1, month1, day1) ? 1 : 0);
        return result;
    }

    result.m_TotalDays = 1;
    result.m_WorkDays = (isWorkDay(year1, month1, day1) ? 1 : 0);

    // Main loop
    while(!(year1 == year2 && month1 == month2 && day1 == day2)) {
        day1++;
        if(!isValidDate(year1, month1, day1)) {
            day1 = 1;
            month1++;
            if(!isValidDate(year1, month1, day1)) {
                day1 = 1;
                month1 = 1;
                year1++;
            }
        }
        result.m_TotalDays++;
        if(isWorkDay(year1, month1, day1))
            result.m_WorkDays++;
    }

    return result;
}
