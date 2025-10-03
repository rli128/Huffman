#include <iostream>
#include <fstream>
#include <cstdint>
#include "Helper.hpp"
#include "HCTree.hpp"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
  vector<int> frequency = vector<int>(256, 0);
  FancyInputStream* input = new FancyInputStream(argv[1]);
  int filesize = input->filesize();
  for (int i = 0; i < input->filesize(); i++) {
    int ascii = input->read_byte();
    frequency[ascii] += 1;
  }
  HCTree Huffman;
  Huffman.build(frequency);

  //create new file
  input->reset();
  string filename = argv[2];
  std::ofstream outfile (filename);

  FancyOutputStream output(argv[2]);

  if (filesize == 0) {
    return 0;
  }

  //Put in the header
  output.write_int(filesize);
  for (int i :frequency) {
    output.write_int(int(i));
  }

  //Start encoding from the file
  for (int i = 0; i < filesize; i++) {
    unsigned int ascii = input->read_byte();
    Huffman.encode(ascii, output);
  }
  return 0;
}