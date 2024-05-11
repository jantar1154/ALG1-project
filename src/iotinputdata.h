#ifndef H_IOTINPUTDATA
#define H_IOTINPUTDATA

#include "timestamp.h"
#include "payload.h"

#include <vector>

using std::vector;

/**
 * @brief A wrapper class around `Timestamp` and `Payload` classes.
*/
class iot_t {
private:

public:
    Timestamp timestamp;
    Payload payload;

    /**
     * @brief Loads data from `stream` into a vector of `iot_t`'s.
     * Please note that the file **must** exist!
     * @param stream Input stream to load from. For example `std::cin` or `std::ifstream`
     * @return `std::vector<iot_t>` loaded from `stream`
     *
     * **Example:**
     *
     * This will read contents of a file:
     * @code
     *  #include <fstream>
     *  #include "iotinputdata.h"
     *  std::ifstream is("input.txt");
     *  std::vector<iot_t> = iot_t::iot_load(is);
     * @endcode
     * 
     * This will load from standard input:
     * @code
     *  #include <iostream>
     *  #include "iotinputdata.h"
     *  std::vector<iot_t> = iot_t::iot_load(std::cin);
     * @endcode
    */
    static vector<iot_t> iot_load(std::istream& stream);
    /**
     * @brief Does the opposite of `iot_load`, writing data from `iot_t` vector into a file.
     * @param o_stream An output stream where the data should be written to. Can be for example `std::cout` or `std::ofstream`
     * @param data_vec Vector of `iot_t` data type with data to be written to `stream`
     *
     * **Example:**
     * @code
     * #include <fstream>
     * #include "iotinputdata.h"
     * std::ofstream os("result.txt");
     * std::vector<iot_t> data;
     * // ... populate `data` ...
     * iot_t::iot_write_data(os, data);
     * @endcode
    */
    static void iot_write_data(std::ostream& o_stream, const vector<iot_t>& data_vec);

    /**
     * @brief Finds `iot_t` with the lowest temperature in `data`.
     * @param data A vector of `iot_t` to search through
     * @return A reference to one of `iot_t` with the lowest temperature from `data`
     *
     * **Example:**
     * @code
     *  #include <vector>
     *  #include "iotinputdata.h"
     *  std::vector<iot_t> data;
     *  // ... populate data ...
     *  iot_t& lowest = iot_t::iot_min_temp(data);
     * @endcode
    */
    static iot_t& iot_min_temp(vector<iot_t>& data);      
    /**
     * @brief Finds `iot_t` with the highest temperature in `data`.
     * @param data A vector of `iot_t` to search through
     * @return A reference to one of `iot_t` with the highest temperature from `data`
     *
     * **Example:**
     * @code
     *  #include <vector>
     *  #include "iotinputdata.h"
     *  std::vector<iot_t> data;
     *  // ... populate data ...
     *  iot_t& lowest = iot_t::iot_max_temp(data);
     * @endcode
    */
    static iot_t& iot_max_temp(vector<iot_t>& data);      
    /**
     * @brief Finds `iot_t` with the lowest humidity in `data`.
     * @param data A vector of `iot_t` to search through
     * @return A reference to one of `iot_t` with the lowest humidity from `data`
     *
     * **Example:**
     * @code
     *  #include <vector>
     *  #include "iotinputdata.h"
     *  std::vector<iot_t> data;
     *  // ... populate data ...
     *  iot_t& lowest = iot_t::iot_min_humidity(data);
     * @endcode
    */
    static iot_t& iot_min_humidity(vector<iot_t>& data);  
    /**
     * @brief Finds `iot_t` with the highest humidity in `data`.
     * @param data A vector of `iot_t` to search through
     * @return A reference to one of `iot_t` with the highest humidity from `data`
     *
     * **Example:**
     * @code
     *  #include <vector>
     *  #include "iotinputdata.h"
     *  std::vector<iot_t> data;
     *  // ... populate data ...
     *  iot_t& lowest = iot_t::iot_max_humidity(data);
     * @endcode
    */
    static iot_t& iot_max_humidity(vector<iot_t>& data);  

    /**
     * @brief Mutates `data_vector` and removes duplicate elements from it.
     * @param data_vector input vector of `iot_t` data type to go through and sanitize
     * 
     * Example:
     * @code
     *  #include <vector>
     *  #include "iotinputdata"
     *  std::vector<iot_t> data;
     *  // ... populate vector ...
     *  iot_t::iot_remove_duplicates(data);
     * @endcode
    */
    static void iot_remove_duplicates(vector<iot_t>& data_vector);
    /**
     * @brief Mutates `data_vector` by sorting all its contents by `Timestamp`.
     * @param data_vector The vector which shall be sorted
    */
    static void iot_sort_by_date(vector<iot_t>& data_vector);

    /**
     * @brief Finds a reference to `iot_t`, if its timestamp is found in `data_vector`.
     * @param timestamp The timestamp to look for
     * @param data_vector Which vector shall be looked through
    */
    static iot_t& iot_find_by_timestamp(const Timestamp& timestamp, vector<iot_t>& data_vector);

    inline bool operator<(const iot_t& rhs) const;
};

#endif // H_IOTINPUTDATA
