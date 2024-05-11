#ifndef H_HISTOGRAM
#define H_HISTOGRAM

#include <vector>
#include <stdint.h>
#include <iostream>

using std::vector;

/**
 * @brief `Histogram` class is used to visually represent a vector of values.
 * Can be used independently of this project.
*/
class Histogram {
private:
    vector<int> data;
    uint16_t height;
    uint16_t width;
    int lowest;
    int highest;

public:
    /**
     *  @brief Contructor for the class `Histogram`. Used to initialize values.
     *  @param data Vector of floats to be represented using a histogram
     *  @param width Width of the histogram, in characters.
     *  Linux terminals usually have ~140 character width.
     *  @param height Height of the histogram, in characters.
     *
     *  Example:
     *  @code
     *  #include "histogram.h"
     *  Histogram hs({1,2,3}, 12, 6);
     *  @endcode
    */
    Histogram(const vector<int>& data, uint16_t width, uint16_t height);
    /**
     *  @brief Prints this histogram into an output stream.
     *  Histogram will be drawn in vertical position.
     *  @param ostream The output stream the histograph should be printed to.
     *
     *  Example:
     *  @code
     *  #include <iostream>
     *  #include "histogram.h"
     *  Histogram hs({1,2,3}, 12, 6);
     *  hs.hist_draw(std::cout);
     *  //       ####
     *  //       ####
     *  //   ########
     *  //   ########
     *  // ##########
     *  @endcode
    */
    void hist_draw(std::ostream& ostream) const;

    /**
     * @brief Divides possible values from `vec` and
     * finds frequency of each interval of values from `vec`.
     * @param vec A vector of data with values to be divided
     * @param parts A number of parts deciding
     * how many bars will the histogram have
     *
     * @return A vector where index is index of bar and value is the frequency
    */
    static vector<int> get_frequency(const vector<float>& vec, uint16_t parts);
};

#endif // H_HISTOGRAM
