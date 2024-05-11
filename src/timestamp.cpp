#include "timestamp.h"
#include <sstream>
#include <iomanip>

using std::stoi;

Timestamp::Timestamp(const std::string& input_string) {
    this->year = stoi(input_string.substr(0, 4));
    this->month = stoi(input_string.substr(5, 2));
    this->day = stoi(input_string.substr(8, 2));
    this->hours = stoi(input_string.substr(11, 2));
    this->minutes = stoi(input_string.substr(14, 2));
    this->seconds = stoi(input_string.substr(17, 2));
}

uint16_t Timestamp::get_year() const {
    return this->year;
}

uint8_t Timestamp::get_month() const {
    return this->month;
}

uint8_t Timestamp::get_day() const {
    return this->day;
}

uint8_t Timestamp::get_hours() const {
    return this->hours;
}

uint8_t Timestamp::get_minutes() const {
    return this->minutes;
}

uint8_t Timestamp::get_seconds() const {
    return this->seconds;
}

std::string Timestamp::to_string() const {
    std::stringstream ss;
    ss << this->year << '-';
    ss << std::setfill('0') << std::setw(2);
    ss << unsigned(this->month) << '-';
    ss << std::setfill('0') << std::setw(2);
    ss << unsigned(this->day) << 'T';
    ss << std::setfill('0') << std::setw(2);
    ss << unsigned(this->hours) << ':';
    ss << std::setfill('0') << std::setw(2);
    ss << unsigned(this->minutes) << ':';
    ss << std::setfill('0') << std::setw(2);
    ss << unsigned(this->seconds);
    return ss.str();
}

bool Timestamp::operator>(const Timestamp& rhs) const {
    return
        this->get_year() < rhs.get_year() ? false :
        this->get_year() > rhs.get_year() ? true :
        this->get_month() < rhs.get_month() ? false :
        this->get_month() > rhs.get_month() ? true :
        this->get_day() < rhs.get_day() ? false :
        this->get_day() > rhs.get_day() ? true :
        this->get_hours() < rhs.get_hours() ? false :
        this->get_hours() > rhs.get_hours() ? true :
        this->get_minutes() < rhs.get_minutes() ? false :
        this->get_minutes() > rhs.get_minutes() ? true :
        this->get_seconds() < rhs.get_seconds() ? false :
        this->get_seconds() > rhs.get_seconds() ? true :
        false;
}

bool Timestamp::operator==(const Timestamp& rhs) const {
    return
        this->get_year() != rhs.get_year() ? false :
        this->get_month() != rhs.get_month() ? false :
        this->get_day() != rhs.get_day() ? false :
        this->get_hours() != rhs.get_hours() ? false :
        this->get_minutes() != rhs.get_minutes() ? false :
        this->get_seconds() != rhs.get_seconds() ? false :
        true;
}
