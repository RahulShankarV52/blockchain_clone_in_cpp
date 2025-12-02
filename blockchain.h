#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>

class BlockChain{
  std::vector<Block> _chain;
  uint32_t difficulty;
  public:
    BlockChain(){
      _chain.emplace_back(Block(0,"Genesis Block","0000"));
      difficulty=4;
    }

    void AddBlock(Block B){
      std::string prev_hash=_chain.back()._hash;
      B._index=static_cast<uint32_t>(_chain.size());
      B._prevHash=prev_hash;
      B.MineBlock(difficulty);
      _chain.push_back(B);
    }
    
    const std::vector<Block>& getChain() const {
        return _chain;
    }

    bool isvalidChain(){
      for(size_t i = 1; i < _chain.size(); i++) {
        const Block& current = _chain[i];
        const Block& previous = _chain[i-1];

        if(current._hash != current.CalculateHash()) {
          std::cout << "Invalid Block Hash at index " << i << std::endl;
          return false;
        }

        if(current._prevHash != previous._hash) {
          std::cout << "Invalid Linkage at index " << i << std::endl;
          return false;
        }
      }
      return true;
    }
};
#endif  
