#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include "SymbolTable.h"
#include <cassert>

constexpr std::string_view Usage = "Usage: main.exe <min len word>\n";


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << Usage;
        return EXIT_FAILURE;
    }
    auto arg1 = std::string{ argv[1] };
    if (!std::all_of(arg1.begin(), arg1.end(), ::isdigit))
    {
        std::cout << Usage;
        return EXIT_FAILURE;
    }

    int minlen = std::stoi(arg1);

    gnem::SymbolTable st;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << "Read line: " << line << std::endl;
        if (line.length() < minlen)
            continue;
        if (!st.contains(line))
            st.put(line, 1);
        else
            st.put(line, st.get(line).value_or(0) + 1);
    }
    {
        gnem::SymbolTable st1 = std::move(st);
    }
    gnem::SymbolTable st2;
    st2 = st;

    std::string key_floor = st.floor("B");
    assert("A" == key_floor);

    size_t rank = st.rank("A");
    assert(0 == rank);
    assert(st.rank("C") == 1);
    assert(st.rank("E") == 2);
    assert(st.rank("G") == 3);
    assert(st.rank("H") == 3);
    assert(st.rank("M") == 4);
    assert(st.rank("R") == 5);
    assert(st.rank("S") == 6);
    assert(st.rank("X") == 7);
    assert(st.rank("U") == 7);

    std::string max = "";
    st.put(max, 0);
    for (auto const& word : st.keys())
    {
        if (st.get(word) > st.get(max))
            max = word;
    }
    std::cout << max << " " << st.get(max).value() << std::endl;

	return 0;
}