#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
using namespace std;

int main()
{
    // Ввод данных
    const auto input = read_input(cin);
    // Вывод данных
    const auto bins = make_histogram(input);
   // show_histogram_text(bins, numbers, number_count, bin_count);
    show_histogram_svg(bins, input);

    return 0;
}
