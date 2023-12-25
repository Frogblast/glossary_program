#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    bool running = true;
    const int mapSize = 2;
    // Create hashmap with words
    // TODO: Read from a text-file
    // Create an unordered_map with int keys and string values
    unordered_map<string, string> glossaryMap;

    glossaryMap["Czesc"] = "Hej";
    glossaryMap["Slowo"] = "Ord";

    std::cout << "HashMap contents:" << std::endl;
    /*     for (const auto &pair : glossaryMap)
        {
            cout << "Key: " << pair.first << " Value: " << pair.second << endl;
        } */

    while (running)
    {
        string answer;

        // Show next word to be translated
        for (const auto &pair : glossaryMap)
        {
            cout << "The first word is: " << pair.first << endl;
            cout << "Enter the swedish translation" << endl;
            cin >> answer;

            if (answer == "q")
            {
                running = false;
                break;
            }

            // If correct (some % of correct letters) then congratulate, if not show the correct translation.
            if (answer == pair.second)
            {
                cout << "Good job" << endl;
            }
            else
            {
                cout << "The correct answer is: " << pair.second << endl;
            }
            // Go back to showing of the next word.
        }
    }
    return 0;
}