#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int main() {
    std::string welcome= "hello, World";
    std::transform(welcome.begin(), welcome.end(), welcome.begin(), [](char ch) ->char {
        return std::tolower(ch);
    });
    return 0;
}