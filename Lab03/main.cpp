#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
using namespace std;

int main()
{
    // ���� ������
    const auto input = read_input(cin);
    // ����� ������
    const auto bins = make_histogram(input);
   // show_histogram_text(bins, numbers, number_count, bin_count);
    show_histogram_svg(bins, input);

    return 0;
}
