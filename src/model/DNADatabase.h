#include <string>
#include <unordered_map>

using namespace std;

using dictionary_type = unordered_map<string, string>;

class DNADatabase {
 private:
  dictionary_type dictionary;

 public:
  dictionary_type get_dictionary() {
    return this->dictionary;
  }
  void add_item(const string& key, const string& value) {
    this->dictionary.insert({key, value});
  }
};
