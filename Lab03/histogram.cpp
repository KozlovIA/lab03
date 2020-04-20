#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
using namespace std;

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
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}
vector<size_t>
make_histogram(const vector<double> numbers, size_t number_count, size_t bin_count) {
    double min, max;
    find_minmax(numbers, number_count, min, max);
    vector<size_t> bins(bin_count);
    for (int i = 0; i < number_count; i++)
    {
        size_t bin = (size_t)((numbers[i] - min) / (max - min) * bin_count);
        if (bin == bin_count)
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
void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_end() {
    cout << "</svg>\n";
}
void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}
void
svg_text(double left, double baseline, string text) {
     cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";

}
double sred_visota(vector<size_t> bins, size_t bin_count)                // изменения к Д/З вариваент 7. Добавлена функция sred_visota
{
    double sred_visota;
    for(int i=0; i < bin_count; i++){
        sred_visota=sred_visota+bins[i];
    }
    return sred_visota/bin_count;
}
void
show_histogram_svg(const vector<size_t>& bins, size_t bin_count) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top=0;
    for (size_t i=0; i < bin_count; i++)
    {
        const double bin_width = BLOCK_WIDTH * bins[i];
        svg_text(TEXT_LEFT, top+TEXT_BASELINE, to_string(bins[i]));
        cout << endl;
        if (bins[i] > sred_visota(bins, bin_count))                                          // изменения к Д/З вариваент 7. добавлено if
        {
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "red");
            cout << endl;
        }
        else
        {
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "green");
            cout << endl;
        }

        top+=BIN_HEIGHT;
    }
    svg_end();
}
