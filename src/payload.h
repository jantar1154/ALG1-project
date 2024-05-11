#ifndef H_PAYLOAD
#define H_PAYLOAD

#include <string>
#include <vector>
#include <stdint.h>

using std::string;
using std::vector;

/**
 * <h1>Payload</h1>
 * @brief A payload class. Contains bytes of data and functions to decode the bytes into usable values.
 * @brief Used for working with encoded payload data from input.
 * <h2>Expected string details: </h2>
 * sex
*/
class Payload {
private:
    uint64_t payload_bytes: 40;
    
public:
    /**
     * @brief Empty constructor for `Payload`. Initializes bytes to zeroes.
     * This constructor is not very useful and should only be used in initialisation and is expected to be later overwritten.
     * 
     * Example of wrong usage:
     * @code
     *  Payload p = Payload();
     *  std::cout << p.get_temperature() << std::endl; // will be zero
     * @endcode
     * Example of intended usage:
     * @code
     * Payload p();
     * // ... something something ...
     * p = Payload("7300E301EA");
     * std::cout << p.get_temperature() << std::endl; // will be good value
     * @endcode
    */
    Payload();

    /**
     * @brief Contructor for `Payload` class. Parses `input_string` into bytes
     * @param input_string String to be parsed into bytes. String should contain a 10-byte long hexadecimal number.
     * 
     * Example:
     * @code
     *  Payload p("7300E301EA");
     * @endcode
     * @code
     *  Payload *p = new Payload("7300E301EA");
     * @endcode
     * Putting zeroes before the 10-byte value is not allowed
     * @code
     *  Payload p("0000007300E301EA"); // This will parse very wrong
     * @endcode
     * Putting zeroes (or anything to that matter) **behind** the ten byte sequence is okay!
    */
    Payload(const string& input_string);

    /**
     * @brief Function to decode bytes into a battery voltage.
     * @return Integer representing battery voltage in millivolts.
     * Please note the function returns number in millivolts, therefore would you want volts you must multiply x1 000.
     * 
     * Example:
     * @code
     *  Payload p("7300E301EA");
     *  assert(p.get_battery_voltage() == 3450);
     * @endcode
    */
    uint16_t get_battery_voltage() const;
    /**
     * @brief Decodes bytes into a temperature in degrees C.
     * @return Float representing temperature in degrees celcius with one decimal digit.
     * @return Format: `xx.x`
     * 
     * Example:
     * @code
     *  Payload p("7300E301EA");
     *  assert(p.get_temperature() == (float)22.7);
     * @endcode
    */
    float get_temperature() const;
    /**
     * @brief Decodes bytes into a humidity value in percent.
     * @return Float value representing humidity in percent with one decimal digit.
     * 
     * Example:
     * @code
     *  Payload p("7300E301EA");
     *  assert(p.get_humidity() == (float)49);
     * @endcode
    */
    float get_humidity() const;
    /**
     * @brief Function returning bytes inputted into contructor but as a `uint32_t`
     * @return Bytes formatted as `uint32_t` number.
     * First 3 bytes will always be `0x00` as allowed input is only 10 bytes.
     * 
     * Example:
     * @code
     *  Payload p("7300E301EA");
     *  assert(p.get_bytes() == 0x7300E301EA);
     * @endcode
    */
    uint64_t get_bytes() const; 
};

#endif // H_PAYLOAD
