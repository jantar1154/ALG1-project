#include "histogram.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_map>

using std::endl;
using std::cout;
using std::queue;
using std::unordered_map;

float get_max(const vector<float>& vector) {
    float max = vector.at(0);
    for (const float& f : vector) {
        if (f <= max) continue;
        max = f;
    }
    return max;
}

float get_min(const vector<float>& vector) {
    float min = vector.at(0);
    for (const float& f : vector) {
        if (f >= min) continue;
        min = f;
    }
    return min;
}

int find_lowest(const vector<int>& data) {
    int lowest = data.at(0);
    for (const int& i : data) {
        if (i >= lowest) continue;
        lowest = i;
    }
    return lowest;
}

int find_highest(const vector<int>& data) {
    float highest = data.at(0);
    for (const int& i : data) {
        if (i <= highest) continue;
        highest = i;
    }
    return highest;
}

vector<int> Histogram::get_frequency(const vector<float>& vec, uint16_t parts) {
    const float min = get_min(vec);
    const float max = get_max(vec);
    const float interval = (max-min) / parts;
    unordered_map<int, int> frequencies;
    vector<int> result(parts, 0);

    for (int i = 0; i < parts; ++i) frequencies[i] = 0;

    for (const float& value : vec) {
        int location = floorf((value-min)/interval);
        if (location >= parts) location = parts - 1;
        result.at(location) += 1;
    }

    // for (const std::pair<int,int> p : frequencies) {
    //     result.push_back(p.second);
    // }
    return result;
}


Histogram::Histogram(const vector<int>& data, uint16_t width, uint16_t height)
: data(data){
    this->data = data;
    this->width = width;
    this->height = height;
    this->lowest = find_lowest(data);
    this->highest = find_highest(data);
}

float map(float number, float min1, float max1, float min2, float max2) {
    return (number - min1) * (max2 - min2) / (max1 - min1) + min2;
}

void Histogram::hist_draw(std::ostream& ostream) const {
    const float space_between = (float)this->data.size() / (float)this->width;
    float data_index = 0;

    queue<float> treshold;

    // Populate height map
    while (floorf(data_index) < this->data.size()) {
        const float dist = map(this->data.at(floorf(data_index)), this->lowest, this->highest, 2, this->height);
        treshold.push(this->height - dist);
        data_index += space_between;
    } 

    // Print graph
    // y
    for (size_t i = 0; i < this->height; ++i) {
        queue<float> l_tres = treshold;
        size_t j = 0;
        // x 
        while (++j < treshold.size()) {
            ostream << (i > l_tres.front() ? '#' : ' ');
            l_tres.pop();
        }
        ostream << endl;
    }
}

