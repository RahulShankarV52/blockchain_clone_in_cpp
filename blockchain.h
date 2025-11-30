#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>

class BlockChain{
  std::vector<Block> _chain;

  public:
    BlockChain(){
      _chain.emplace_back(Block(0,"Genesis Block","0000"));
    }

    void AddBlock(Block B){
      std::string prev_hash=_chain.back()._data;
      B._index=static_cast<uint32_t>(_chain.size());
      B._prevHash=prev_hash;
      _chain.push_back(B);
    }
    
    const std::vector<Block>& getChain() const {
        return _chain;
    }

    bool isvalidChain(){
      for(uint32_t i=1;i<_chain.size();i++){
        if(_chain[i]._prevHash!=_chain[i-1]._data){
          return false;
        }
      }
      return true;
    }
};
#endif  
