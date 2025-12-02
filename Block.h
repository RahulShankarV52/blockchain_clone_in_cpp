#ifndef BLOCK_H
#define BLOCK_H

#include<string>
#include <ctime>
#include <cstdint>
#include <iostream>
#include <sstream>

#include "sha256.h"

class Block{
  public:
    uint32_t _index;
    uint32_t _nonce;
    std::string _data;
    std::string _hash;
    std::string _prevHash;
    time_t _time;

    Block(uint32_t index,const std::string &data, std::string &prevHash):_index(index),_data(data),_prevHash(prevHash),_nonce(0)
    {
      _hash=CalculateHash();
      _time=time(nullptr);
    }
    std::string CalculateHash() const{
      std::stringstream ss;
      ss<<_index<<_time<<_data<<_prevHash<<_nonce;
      return sha256(ss.str());
    }
};

#endif 
