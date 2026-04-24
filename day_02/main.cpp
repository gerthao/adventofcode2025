#include <fstream>
#include <string>
#include <print>
#include <ranges>
#include <string_view>

bool is_invalid_id(const long long id) {
    const auto id_str = std::to_string(id);

    if (id_str.size() / 2 == 0) return false;

    const auto mid = id_str.size() / 2;

    return id_str.substr(0, mid) == id_str.substr(mid);
}

int main() {
    std::ifstream file("../day_02/input.txt");
    if (!file.is_open()) {
        std::println("Error opening file\n");
        return 1;
    }

    std::string line;
    std::getline(file, line);

    long long sum = 0;

    for (auto part: line | std::views::split(',')) {
        auto id_range = std::string_view(part);
        const size_t position = id_range.find_first_of('-');
        const auto min_id = std::stoll(std::string(id_range.substr(0, position)));
        const auto max_id = std::stoll(std::string(id_range.substr(position + 1)));

        auto invalid_ids
            = std::views::iota(min_id, max_id + 1)
            | std::views::filter(is_invalid_id);

        for (const auto invalid_id: invalid_ids)
            sum += invalid_id;
    }

    std::println("Sum of invalid IDs: {}", sum);

    return 0;
}