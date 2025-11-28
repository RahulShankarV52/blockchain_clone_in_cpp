#ifdef BLOCK
#define BLOCK

#include<string>
#include <ctime>
#include <cstdint>
#include <iostream>

class Block{
  public:
    uint32_t _index;
    uint32_t _nonce;
    std::string _data;
    std::string _hash;
    std::string _prevHash;
    time_t _time;

    Block(uint32_t index,const std::string &data, std::string prevHash):_index(index),_data(data),_prevHash(prevHash),_nonce(0)
    {
      this._time=time(nullptr);
    }
};

#endif 
