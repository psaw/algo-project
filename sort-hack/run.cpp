#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include "libcxx_v10_sort.cpp"

std::vector<int> readVector(size_t max_count)
{
    std::vector<int> result;
    result.reserve(max_count);
    for (size_t i = 0; i < max_count; ++i)
    {
        int elem;
        if (!(std::cin >> elem))
        {
            break;
        }
        result.push_back(elem);
    }
    std::cout << "read " << result.size() << " elements\n";
    return result;
}

int main()
{
    const size_t max_count = 32768u;
    auto data = readVector(max_count);
    auto start_time = std::clock();

    sort1(data.begin(), data.end(), [&](int x, int y)
          { return x < y; });

    auto end_time = std::clock();
    double spent = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    if (!std::is_sorted(data.begin(), data.end()))
    {
        std::cout << "10 \nmmmm...\n";
        std::cout << spent << " seconds\n";
        return 0;
    }

    if (spent > 0.04)
    {
        std::cout << "10 \noh...\n";
        std::cout << spent << " seconds\n";
        return 0;
    }
    std::cout << "no 0 (" << spent << " seconds)\n";
    return 1;
}
