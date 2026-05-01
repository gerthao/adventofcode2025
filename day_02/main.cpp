#include <fstream>
#include <string>
#include <print>
#include <ranges>
#include <string_view>

bool is_invalid_id(const long long id) {
    const auto id_text = std::to_string(id);
    const auto id_size = id_text.size();
    const size_t mid = id_size / 2;

    for (size_t chunk_size = 1; chunk_size <= mid; chunk_size++) {
        if (id_size % chunk_size != 0)
            continue;

        bool is_repeated = true;

        for (size_t i = chunk_size; i < id_size; i++) {
            if (id_text[i] != id_text[i % chunk_size]) {
                is_repeated = false;
                break;
            }
        }

        if (is_repeated)
            return true;
    }

    return false;
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

        auto invalid_ids = std::views::iota(min_id, max_id + 1)
                           | std::views::filter(is_invalid_id);

        for (const auto invalid_id: invalid_ids)
            sum += invalid_id;
    }

    std::println("Sum of invalid IDs: {}", sum);

    return 0;
}
