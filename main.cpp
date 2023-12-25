#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{

    const int mapSize = 2;
    // Create hashmap with words
    // TODO: Read from a text-file
    // Create an unordered_map with int keys and string values
    unordered_map<string, string> glossaryMap;

    glossaryMap["Czesc"] = "Hej";
    glossaryMap["Slowo"] = "Ord";


    std::cout << "HashMap contents:" << std::endl;
    for (const auto &pair : glossaryMap)
    {
        cout << "Key: " << pair.first << " Value: " << pair.second << endl;
    }

    // Show next word to be translated

    // Get input

    // If correct (some % of correct letters) then congratulate, if not show the correct translation.

    // Go back to showing of the next word.

    return 0;
}