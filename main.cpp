#include <iostream>
#include "blockchain.h"

int main(){
  BlockChain B;
  std::cout << "Mining block 1..." << std::endl;
  B.AddBlock(Block(1, "Block 1 Data", ""));

  std::cout << "Mining block 2..." << std::endl;
  B.AddBlock(Block(2, "Block 2 Data", ""));

  std::cout << "Mining block 3..." << std::endl;
  B.AddBlock(Block(3, "Block 3 Data", ""));

  std::cout << "\nBlockchain is valid: " << B.isvalidChain() << std::endl;
  return 0;
}
