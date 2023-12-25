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

    /*    std::cout << "HashMap contents:" << std::endl;
   for (const auto &pair : glossaryMap)
       {
           cout << "Key: " << pair.first << " Value: " << pair.second << endl;
       } */

    while (running)
    {
        string answer;
        int correctLetters;
        bool accepted = false;

        // Show next word to be translated
        for (const auto &pair : glossaryMap)
        {
            cout << "The next word is: " << pair.first << endl;
            cout << "Enter the swedish translation \n"
                 << endl;
            cin >> answer;

            if (answer == "q")
            {
                running = false;
                break;
            }

            accepted = false;
            correctLetters = 0;

            int correctLength = pair.second.length();

            for (int i = 0; i < correctLength; i++)
            {
                bool equalLetters = pair.second[i] == answer[i];
                cout << "Equal letters? :" << equalLetters << endl;
                if (equalLetters)
                {
                    correctLetters++;
                }
            }
            float ratio = static_cast<float>(correctLetters) / correctLength;
            cout << "Ratio: " << ratio << " Correct letters: " << correctLetters << endl;

            if (ratio > 0.6f)
            {
                accepted = true;
            }

            // If correct (some % of correct letters) then congratulate, if not show the correct translation.
            if (accepted)
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