#include "iotinputdata.h"
#include <set>
#include <iomanip>

inline bool iot_t::operator<(const iot_t& rhs) const {
    if (this->payload.get_bytes() < rhs.payload.get_bytes()) return true;
    return !(this->timestamp > rhs.timestamp);

    return false;
}

vector<iot_t> iot_t::iot_load(std::istream& stream) {
    vector<iot_t> data_vec;

    for (string buf; getline(stream, buf);) {
        const int space_loc = buf.find(' ');
        const string timestamp_str = buf.substr(0, space_loc);
        const string payload_str = buf.substr(space_loc + 1, 10);
        data_vec.push_back({ Timestamp(timestamp_str), Payload(payload_str) });
    }

    return data_vec;
}

void iot_t::iot_write_data(std::ostream& o_stream, const vector<iot_t>& data_vec) {
    for (const iot_t& d : data_vec) {
        o_stream << d.timestamp.to_string() << ' ';
        o_stream << std::hex << std::uppercase;
        o_stream << d.payload.get_bytes() << endl;
        o_stream << std::dec;
    }
}

iot_t& iot_t::iot_min_temp(vector<iot_t>& data) {
    float min_temp = data.at(0).payload.get_temperature();
    size_t ref_i = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        const Payload& pl = data.at(i).payload;
        if (pl.get_temperature() >= min_temp) continue;
        min_temp = pl.get_temperature();
        ref_i = i;
    }
    return data.at(ref_i);
}

iot_t& iot_t::iot_max_temp(vector<iot_t>& data) {
    float max_temp = data.at(0).payload.get_temperature();
    size_t ref_i = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        const Payload& pl = data.at(i).payload;
        if (pl.get_temperature() <= max_temp) continue;
        max_temp = pl.get_temperature();
        ref_i = i;
    }
    return data.at(ref_i);
}

iot_t& iot_t::iot_min_humidity(vector<iot_t>& data) {
    float min_humidity = data.at(0).payload.get_humidity();
    size_t ref_i = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        const Payload& pl = data.at(i).payload;
        if (pl.get_humidity() >= min_humidity) continue;
        min_humidity = pl.get_humidity();
        ref_i = i;
    }
    return data.at(ref_i);
}

iot_t& iot_t::iot_max_humidity(vector<iot_t>& data) {
    float max_humidity = data.at(0).payload.get_humidity();
    size_t ref_i = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        const Payload& pl = data.at(i).payload;
        if (pl.get_humidity() <= max_humidity) continue;
        max_humidity = pl.get_humidity();
        ref_i = i;
    }
    return data.at(ref_i);
}

void iot_t::iot_remove_duplicates(vector<iot_t>& data_vector) {
    std::set<iot_t> nodup;
    
    for (iot_t& data : data_vector) {
        if (nodup.find(data) != nodup.end()) continue;
        nodup.insert(data);
    }

    data_vector.clear();

    for (const iot_t& data : nodup) {
        data_vector.push_back(data);
    }
}

// Insertion sort
void iot_t::iot_sort_by_date(vector<iot_t>& data_vector) {
    for (size_t i = 1; i < data_vector.size(); ++i) {
        iot_t v = data_vector.at(i);
        size_t j = i - 1;
        while (0 < j && data_vector.at(j).timestamp > v.timestamp) {
            data_vector.at(j+1) = data_vector.at(j);
            j --;
        }
        data_vector.at(j+1) = v;
    }
}

iot_t& iot_t::iot_find_by_timestamp(const Timestamp& timestamp, vector<iot_t>& data_vector) {
    for (iot_t& i : data_vector) {
        if (i.timestamp == timestamp) {
            return i;
        }
    }
    cout << "did not find any iot_t by timestamp" << endl;
    exit(1);
}
