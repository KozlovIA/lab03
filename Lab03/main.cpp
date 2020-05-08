#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>

using namespace std;

int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    if(argc > 1)
    {
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        for(int i=0; i < argc; i++)
        {
            cout << "argc[" << i << "]=" << argv[i] << '/n';
        }
    }
    // Ввод данных
    const auto input = read_input(cin, true);
    // Вывод данных
    const auto bins = make_histogram(input);
   // show_histogram_text(bins, numbers, number_count, bin_count);
    show_histogram_svg(bins, input);

    return 0;
}
