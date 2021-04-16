#include <iostream>
#include <string>

#include "./lib/Color.h"
#include "./model/DNADatabase.h"
#include "./model/Profiler.h"

using namespace std;
using namespace Color;

#define ALICE "AGACGGGTTACCATGACTATCTATCTATCTATCTATCTATCTATCTATCACGTACGTACGTATCGAGATAGATAGATAGATAGATCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA"
#define BOB "AACCCTGCGCGCGCGCGATCTATCTATCTATCTATCCAGCATTAGCTAGCATCAAGATAGATAGATGAATTTCGAAATGAATGAATGAATGAATGAATGAATG"
#define CHARLIE "CCAGATAGATAGATAGATAGATAGATGTCACAGGGATGCTGAGGGCTGCTTCGTACGTACTCCTGATTTCGGGGATCGCTGACACTAATGCGTGCGAGCGGATCGATCTCTATCTATCTATCTATCTATCCTATAGCATAGACATCCAGATAGATAGATC"
#define NO_MATCH "GGTACAGATGCAAAGATAGATAGATGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGAATGAATGACACACGTCGATGCTAGCGGCGGATCGTATATCTATCTATCTATCTATCAACCCCTAG"

int main() {
  DNADatabase database;
  database.add_item("5 2 8", "Alice");
  database.add_item("3 7 4", "Bob");
  database.add_item("6 1 5", "Charlie");

  Profiler profiler;
  auto key = profiler.generate_profile(CHARLIE);
  auto name = database.get_dictionary()[key];

  if (name.length() == 0) {
    cout << tcolor("No match", RED) << endl;
    return 1;
  }

  cout << tcolor("The subject is: ", BLUE) << tcolor(name, WHITE, BOLD) << endl;

  return 0;
}
