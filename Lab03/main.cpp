#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>

using namespace std;

int main(int argc, char* argv[])
{
    input inp;
    //curl_global_init(CURL_GLOBAL_ALL);
    if(argc > 1)
    {
        inp = download(argv[1]);
    }
    else
    {
        inp = read_input(cin, true);
    }
    // Вывод данных
    const auto bins = make_histogram(inp);
   // show_histogram_text(bins, numbers, number_count, bin_count);
    show_histogram_svg(bins, inp);

    return 0;
}
