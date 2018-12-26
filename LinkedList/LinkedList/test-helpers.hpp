#pragma once

#include "list.hpp"
#include <vector>
#include <iterator>

#include <chrono>
#include <stdint.h>

void append_to_list(pjc::list& l, std::vector<double> elems);

auto rbegin(const pjc::list& l) -> std::reverse_iterator<pjc::list::const_iterator>;

auto rend(const pjc::list& l) -> std::reverse_iterator<pjc::list::const_iterator>;

bool list_equal(const pjc::list& l, const std::vector<double>& numbers);
int generate_int();
std::vector<double> generate_data(size_t sz);

struct cpu_clock {
    using rep = int64_t;
    using period = std::nano;
    using duration = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<cpu_clock>;
    static constexpr bool is_steady = true;
    static time_point now();
};
