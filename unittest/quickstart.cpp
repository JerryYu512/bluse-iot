#include <iostream>
#include "simdjson.h"
using namespace simdjson;
// int main(void) {
//     ondemand::parser parser;
//     padded_string json = padded_string::load("twitter.json");
//     ondemand::document tweets = parser.iterate(json);
//     simdjson::dom::element elm;
//     tweets.get(elm);
//     std::cout << uint64_t(tweets["search_metadata"]["count"]) << " results." << std::endl;
// }

int main(void) {
  simdjson::dom::parser parser;
  simdjson::dom::element tweets;
  auto error = parser.load("twitter.json").get(tweets);
  if (error) { std::cerr << error << std::endl; return EXIT_FAILURE; }
  simdjson::dom::element res;

  if ((error = tweets["search_metadata"]["count"].get(res))) {
    std::cerr << "could not access keys" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << res << " results." << std::endl;
}