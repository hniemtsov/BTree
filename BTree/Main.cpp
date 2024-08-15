#include <iostream>
#include <string>
#include <algorithm>
#include "SymbolTable.h"

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