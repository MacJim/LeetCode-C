//
// Created by Jim Shi on 5/27/21.
//

#ifndef LEETCODECACHE_TERMINAL_FORMAT_H
#define LEETCODECACHE_TERMINAL_FORMAT_H

namespace terminal_format {
    using namespace std::literals;

    inline constexpr auto HEADER = "\033[95m"sv;
    inline constexpr auto OK_BLUE = "\033[94m"sv;
    inline constexpr auto OK_CYAN = "\033[96m"sv;
    inline constexpr auto OK_GREEN = "\033[92m"sv;
    inline constexpr auto WARNING = "\033[93m"sv;
    inline constexpr auto FAIL = "\033[91m"sv;
    inline constexpr auto ENDC = "\033[0m"sv;
    inline constexpr auto BOLD = "\033[1m"sv;
    inline constexpr auto UNDERLINE = "\033[4m"sv;
}

#endif //LEETCODECACHE_TERMINAL_FORMAT_H
