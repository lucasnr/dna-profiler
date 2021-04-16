#include <string.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./lib/Color.h"
#include "./model/DNADatabase.h"
#include "./model/Profiler.h"

using namespace std;
using namespace Color;

vector<string> split(string& str) {
  vector<string> substrings;

  string token;
  size_t position{0};
  string delimiter{","};

  while ((position = str.find(delimiter)) != string::npos) {
    token = str.substr(0, position);
    substrings.push_back(token);
    str.erase(0, position + delimiter.length());
  }
  token = str.substr(0, position);
  substrings.push_back(token);

  return substrings;
}

int main(int argc, char** argv) {
  bool has_database{false}, has_sequence{false};
  for (int i = 0; i < argc; i++)
    if (strcmp(argv[i], "-d") == 0)
      has_database = true;
    else if (strcmp(argv[i], "-s") == 0)
      has_sequence = true;

  if (!has_database) {
    cout << tcolor("The database filename was not provided. Use the flag -d to provide it", RED);
    return 1;
  }

  if (!has_sequence) {
    cout << tcolor("The dna sequence filename was not provided. Use the flag -s to provide it", RED);
    return 1;
  }

  if (argc < 5) {
    cout << tcolor("Invalid arguments", RED);
    return 1;
  }

  string database_filename, dna_sequence_filename;
  for (int i{1}; i < argc; i++)
    if (i % 2 != 0)
      if (strcmp(argv[i], "-d") == 0)
        database_filename = argv[i + 1];
      else if (strcmp(argv[i], "-s") == 0)
        dna_sequence_filename = argv[i + 1];

  ifstream database_file(database_filename);
  if (!database_file.good()) {
    cout << tcolor("No database file was found with the provided filename", RED) << endl;
    database_file.close();
    return 1;
  }

  ifstream dna_sequence_file(dna_sequence_filename);
  if (!dna_sequence_file.good()) {
    cout << tcolor("No dna sequence file was found with the provided filename", RED) << endl;
    dna_sequence_file.close();
    return 1;
  }

  DNADatabase database;
  string name;
  stringstream key;
  vector<string> substrings;

  string line;
  getline(database_file, line);
  while (getline(database_file, line)) {
    substrings = split(line);

    key << substrings[1] << " " << substrings[2] << " " << substrings[3];
    name = substrings[0];

    database.add_item(key.str(), name);
    key.str(string());
  }
  database_file.close();

  string dna_sequence;
  getline(dna_sequence_file, dna_sequence);
  dna_sequence_file.close();

  Profiler profiler;
  auto profile = profiler.generate_profile(dna_sequence);
  auto found = database.get_dictionary()[profile];

  if (found.length() == 0) {
    cout << tcolor("No match", RED) << endl;
    return 1;
  }

  cout << "The subject is: " << tcolor(found, BLUE) << " [" << tcolor(profile, BLUE, BOLD) << "]" << endl;

  return 0;
}
