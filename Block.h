#ifndef BLOCK_H
#define BLOCK_H

#include<string>
#include <ctime>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include "sha256.h"
#include "transactions.h"

class Block{
  public:
    uint32_t _index;
    uint32_t _nonce;
    std::vector<Transaction> _transactions;
    std::string _hash;
    std::string _prevHash;
    time_t _time;

    Block(uint32_t index,const std::vector<Transaction> &transactions, const std::string &prevHash):_index(index),_transactions(transactions),_prevHash(prevHash),_nonce(0)
    {
      _time=std::time(nullptr);
      _hash=CalculateHash();
    }
    std::string CalculateHash() const{
      std::stringstream ss;
      ss<<_index<<_time;

      for(const auto tx: _transactions){
        ss<<tx.toString();
      }

      ss<<_prevHash<<_nonce;
      return sha256(ss.str());
    }
    void MineBlock(uint32_t difficulty){
      std::string target(difficulty,'0');

      do{
        _nonce++;
        _hash=CalculateHash();
      }while(_hash.substr(0,difficulty)!=target);
      std::cout<<"Block mined: "<<_hash<<std::endl;
    }
};

#endif 
