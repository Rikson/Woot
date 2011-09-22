/**
 * Lower case transformer.
 */

#include <algorithm>
#include <string>
#include <cstring>
#include "../iTransformer.h"

using namespace std;

string LowerCaseTransformer::transform(string word) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    return word;
}
