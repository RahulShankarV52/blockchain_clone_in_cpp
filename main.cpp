#include "blockchain.h"

int main(){
  BlockChain B;
  std::cout << "[+] Mining blocks..." << std::endl;
  B.AddBlock(Block(1, "Block 1 Data", ""));
  B.AddBlock(Block(2, "Block 2 Data", ""));

  std::cout << "Is chain valid? " << B.isvalidChain() << std::endl;

  std::vector<Block>& chainRef = const_cast<std::vector<Block>&>(B.getChain());

  std::cout << "\n[!] Hacker changing Block 1 data..." << std::endl;
  chainRef[1]._data = "Someone paid me $1,000,000"; // Modifying history!

  std::cout << "Is chain valid? " << B.isvalidChain() << std::endl;
}
