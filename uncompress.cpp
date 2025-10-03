#include <iostream>
#include <fstream>
#include "Helper.hpp"
#include "HCTree.hpp"
#include <vector>
using namespace std;
using namespace std;


int main(int argc, char* argv[]) {
  FancyInputStream input(argv[1]);

  if (input.filesize() == 0) {
    FancyOutputStream output(argv[2]);
    return 0;

  }

  int filesize = input.read_int();


  vector<int> frequency = vector<int>(256, 0);
  for (int i = 0; i < 256; i++) {
    frequency[i] = input.read_int();
  }
  HCTree Huffman;
  Huffman.build(frequency);

  string filename = argv[2];
  std::ofstream outfile (filename);
  FancyOutputStream output(argv[2]);

  //int bit = Huffman.decode(input);
  //int count = 0;
  //int chars = input.read_int();
  for (int i = 0; i < filesize; i++) {
  //   unsigned char bit = Huffman.decode(input);
  //   output.write_byte(bit);
  // while (bit > 1) {
    unsigned char bit = Huffman.decode(input);
    output.write_byte(bit);
  }
  return 0;
}
