#include "iotinputdata.h"
#include "timestamp.h"
#include "histogram.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;

vector<int> get_temp_histogram(const vector<iot_t>& data, uint16_t parts) {
    vector<float> temps;
    for (const iot_t& i : data) {
        temps.push_back(i.payload.get_temperature());
    }
    vector<int> frequencies = Histogram::get_frequency(temps, parts);
    return frequencies;
}

vector<int> get_humidity_histogram(const vector<iot_t>& data, uint16_t parts) {
    vector<float> humis;
    for (const iot_t& i : data) {
        humis.push_back(i.payload.get_humidity());
    }
    vector<int> frequencies = Histogram::get_frequency(humis, parts);
    return frequencies;
}

int main(int argc, const char *argv[]) {
    // output file name argument
    if (argc < 2) {
        cout << "Please define input and output file paths" << endl;
        cout << "Example: ./main Input.txt Result.txt" << endl;
        exit(1);
    }

    const string input_filename = argv[1];
    const string output_filename = argv[2];

    // Load data from file into custom structs
    std::ifstream input_file(input_filename);
    vector<iot_t> data = iot_t::iot_load(input_file);
    input_file.close();
    cout << "Loading done" << endl;

    // Remove duplicate entries in vector
    iot_t::iot_remove_duplicates(data);
    cout << "Removed duplicates" << endl;

    // Sort the list by date
    iot_t::iot_sort_by_date(data);
    cout << "List sorted" << endl;

    // Write to the output file
    std::ofstream output_file(output_filename);
    iot_t::iot_write_data(output_file, data);
    output_file.close();
    cout << "Data written to " << output_filename << endl;

    // Print lowest and highest temperatures and humidities
    const float min_temp = iot_t::iot_min_temp(data).payload.get_temperature();
    const float max_temp = iot_t::iot_max_temp(data).payload.get_temperature();
    const float min_humidity = iot_t::iot_min_humidity(data).payload.get_humidity();
    const float max_humidity = iot_t::iot_max_humidity(data).payload.get_humidity();
    cout << "Temperature range: " << min_temp << 'C';
    cout << " - " << max_temp << 'C' << endl;
    cout << "Humidity range: " << min_humidity << '%';
    cout << " - " << max_humidity << '%' << endl;

    // Histogram
    const vector<int> temps = get_temp_histogram(data, 8);
    const vector<int> humidities = get_humidity_histogram(data, 8);
    cout << "humi freqs: " << humidities.size() << endl;
    Histogram *temp_hist = new Histogram(temps, 140, 30);
    temp_hist->hist_draw(cout);
    Histogram *humidity_hist = new Histogram(humidities, 140, 30);
    humidity_hist->hist_draw(cout);

    delete temp_hist;
    delete humidity_hist;

    // Find by timestamp
    const iot_t& find = iot_t::iot_find_by_timestamp(Timestamp("2024-03-09T12:00:00"), data);
    cout << "Found!" << endl;
    cout << "Temp: " << find.payload.get_temperature() << 'C' << endl;
    cout << "Humidity: " << find.payload.get_humidity() << '%' << endl;

    return 0;
}
