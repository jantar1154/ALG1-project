#ifndef H_TIMESTAMP
#define H_TIMESTAMP

#include <stdint.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

/**
 * @brief `Timestamp` class is used for working with IoT data and decoding a string into usable number format.
 *
 * Expected format of string to be decoded is "YYYY-MM-DDTHH:MM:SS".
 * 
 * Example:
 * Given the string "2024-04-12T20:28:09", class will decode it into:
 * > Year: 2024 (uint16_t) <br>
 * > Month: 4 (uint8_t) <br>
 * > Day: 12 (uint8_t) <br>
 * > Hours: 20 (uint8_t) <br>
 * > Minutes: 28 (uint8_t) <br>
 * > Seconds: 9 (uint8_t) <br>
 * Individual values can be accesed via getters (get_year(), get_minutes(), ...)
*/
class Timestamp {
private:
    uint16_t year;
    uint8_t month;
    uint8_t day;

    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    
public:
    /**
     * @brief Constructor for the `Timestamp` class.
     * @param input_string A string to be parsed into usable number values.
     *
     * Example:
     * @code
     *  #include "timestamp.h"
     *  Timestamp ts("1998-04-10T12:30:01");
     * @endcode
    */
    Timestamp(const std::string& input_string);
    
    /**
     * @brief Getter for years.
     * @return `uint16_t` representing year
    */
    uint16_t get_year() const;
    /**
     * @brief Getter for months.
     * @return `uint8_t` representing month
    */
    uint8_t get_month() const;
    /**
     * @brief Getter for days.
     * @return `uint8_t` representing day
    */
    uint8_t get_day() const;

    /**
     * @brief Getter for hours.
     * @return `uint8_t` representing hours
    */
    uint8_t get_hours() const;
    /**
     * @brief Getter for minutes.
     * @return `uint8_t` representing minutes
    */
    uint8_t get_minutes() const;
    /**
     * @brief Getter for seconds.
     * @return `uint8_t` representing seconds
    */
    uint8_t get_seconds() const;

    std::string to_string() const;

    /**
     * @brief Operator `<` compares two Timestamp values and finds out whether the first one is later than the second one, but not the same.
     * @param rhs right hand side
     * @return `bool` `false` if `lhs` is earlier or the same than `rhs` or `true` if the `lhs` is later than `rhs`
    */
    bool operator>(const Timestamp& rhs) const;
    /**
     * @brief Operator `==` compares two Timestamp values and finds out whether they are the same time.
     * @param rhs right hand side
     * @return `bool` `true` if the times are the same, otherwise `false`
    */
    bool operator==(const Timestamp& rhs) const;
};

#endif
