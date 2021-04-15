#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using count_type = unsigned int;

class Profiler {
 private:
  count_type erase_and_count(string& str, const string& toErase) {
    vector<count_type> ocurrences;
    count_type count{0};

    size_t position = string::npos;
    size_t previous = string::npos;

    // Search for the substring in string in a loop untill nothing is found
    while ((position = str.find(toErase)) != string::npos) {
      // If found, then erase
      str.erase(position, toErase.length());

      if (count == 0)
        previous = position;

      if (position == previous)
        count++;
      else {
        ocurrences.push_back(count);
        count = 0;
      }
    }

    if (ocurrences.size() == 0)
      return count;

    return *max_element(begin(ocurrences), end(ocurrences));
  }

 public:
  string generate_profile(const string& dna_sequence) {
    stringstream profile;
    string sequence{dna_sequence};

    auto agat{erase_and_count(sequence, "AGAT")};
    auto aatg{erase_and_count(sequence, "AATG")};
    auto tatc{erase_and_count(sequence, "TATC")};

    profile << agat << " " << aatg << " " << tatc;
    return profile.str();
  }
};
