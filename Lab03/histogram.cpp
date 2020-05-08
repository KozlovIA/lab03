#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include <istream>
using namespace std;

input read_input(istream& in, bool prompt) {
    input data;
    if (prompt == true)
    {
       cerr << "Enter number_count: ";
    }
    in >> data.number_count;
     if (prompt == true)
    {
        cerr << "Enter numbers: ";

    }
    data.numbers = input_numbers(in, data.number_count);
     if (prompt == true)
    {
        cerr << "Enter column count: ";
    }
    in >> data.bin_count;
    return data;
}
void find_minmax(const vector<double>& numbers, size_t count, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (int i=0; i < count; i++)
    {
        if (numbers[i] < min)
        {
            min = numbers[i];
        }
        if (numbers[i] > max)
        {
            max = numbers[i];
        }
    }
}
vector<double>
input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
vector<size_t>
make_histogram(struct input data) {
    double min, max;
    find_minmax(data.numbers, data.number_count, min, max);
    vector<size_t> bins(data.bin_count);
    for (int i = 0; i < data.number_count; i++)
    {
        size_t bin = (size_t)((data.numbers[i] - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}
void
show_histogram_text(vector<size_t> bins, const vector<double> numbers, size_t number_count, size_t bin_count) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (int i=0; i < bin_count; i++)
    {
        if (bins[i] > max_count)
        {
            max_count = bins[i];
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (int i=0; i < bin_count; i++)
    {
        if (bins[i] < 100)
        {
            cout << ' ';
        }
        if (bins[i] < 10)
        {
            cout << ' ';
        }
        cout << bins[i] << "|";

        size_t height = bins[i];
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bins[i] * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }
}
