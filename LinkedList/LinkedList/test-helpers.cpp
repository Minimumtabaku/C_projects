#include "test-helpers.hpp"

#include <random>
#include <algorithm>

using pjc::list;

void append_to_list(list& l, std::vector<double> elems) {
    for (auto elem : elems) {
        l.push_back(elem);
    }
}

auto rbegin(const list& l) -> std::reverse_iterator<list::const_iterator> {
    return std::make_reverse_iterator(l.end());
}

auto rend(const list& l) -> std::reverse_iterator<list::const_iterator> {
    return std::make_reverse_iterator(l.begin());
}


bool list_equal(const list& l, const std::vector<double>& numbers) {
    if (l.size() != numbers.size()) {
        return false;
    }

    // Check the list from both sides to verify that the list is connected properly.
    return std::equal(l.begin(), l.end(), begin(numbers), end(numbers)) &&
        std::equal(rbegin(l), rend(l), rbegin(numbers), rend(numbers));
}

int generate_int() {
    // Note: This inits the generator to a deterministic state,
    //       so that all runs of the tests will produce roughly the same
    //       output.
    static std::mt19937 gen;
    static std::uniform_int_distribution<> dist(0, 3000);
    return dist(gen);
}

std::vector<double> generate_data(size_t sz) {
    std::vector<double> res;
    res.reserve(sz);
    std::generate_n(std::back_inserter(res), sz, generate_int);
    return res;
}

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
void throw_windows_error(std::string msg)
{
    DWORD dwErrVal = GetLastError();
    std::error_code ec (dwErrVal, std::system_category());
    throw std::system_error(ec, std::move(msg));
}

cpu_clock::time_point cpu_clock::now()
{
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;

    if (!GetProcessTimes(GetCurrentProcess(),
        &createTime, &exitTime, &kernelTime, &userTime))
        throw_windows_error("GetProcessTimes failed");

    uint64_t d = (static_cast<uint64_t>(userTime.dwHighDateTime) << 32)
                 | userTime.dwLowDateTime;
    duration res { std::chrono::duration<uint64_t, std::ratio<1, 100'000>>(d) }; // 100ns
    return time_point(res);
}
#else // -> POSIX systems
#include <time.h>
cpu_clock::time_point cpu_clock::now()
{
    struct timespec ts;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) == -1)
        throw std::system_error(errno, std::generic_category());
    using namespace std::chrono;
    duration res = duration(seconds(ts.tv_sec)) +
                   duration_cast<duration>(nanoseconds(ts.tv_nsec));
    return time_point(res);
}
#endif
