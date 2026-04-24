#include <string>
#include <print>
#include <fstream>

int add_to_range(const int current, const int value) {
    const auto new_value = (current + value) % 100;

    if (new_value < 0) {
        return 100 + new_value;
    }

    return new_value;
}

int turn_dial(const int dial_value, const std::string &move) {
    const auto direction = move[0];
    const auto value = std::stoi(move.substr(1));
    auto new_dial_value = dial_value;

    if (direction == 'L') {
        new_dial_value = add_to_range(dial_value, -value);
    } else if (direction == 'R') {
        new_dial_value = add_to_range(dial_value, value);
    }

    return new_dial_value;
}

int main() {
    std::ifstream file("../day_01/input.txt");
    if (!file.is_open()) {
        std::println("Error opening file\n");
        return 1;
    }

    constexpr auto DIAL_START = 50;
    auto current_dial_value = DIAL_START;
    auto zero_counter = 0;

    std::string move;
    while (std::getline(file, move)) {
        current_dial_value = turn_dial(current_dial_value, move);
        if (current_dial_value == 0) {
            zero_counter++;
        }
    }

    std::println("Password is {}", zero_counter);

    return 0;
}