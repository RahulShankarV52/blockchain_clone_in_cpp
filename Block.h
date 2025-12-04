#ifndef BLOCK_H
#define BLOCK_H

#include<string>
#include <ctime>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

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
    
    Block(){
      _nonce=0;
      _index=0;
      _time=0;
    }

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
    
    void serialize(std::ofstream& out) const {
      out.write((char*)&_index, sizeof(_index));
      out.write((char*)&_nonce, sizeof(_nonce));
      out.write((char*)&_time, sizeof(_time));

      size_t len = _hash.size();
      out.write((char*)&len, sizeof(len));
      out.write(_hash.c_str(), len); 

      len = _prevHash.size();
      out.write((char*)&len, sizeof(len));
      out.write(_prevHash.c_str(), len);

      size_t tx_count = _transactions.size();
      out.write((char*)&tx_count, sizeof(tx_count));

      for(const auto& tx: _transactions){
        tx.serialize(out);
      }
    }

    void deserialize(std::ifstream& in){
      in.read((char*)&_index, sizeof(_index));
      in.read((char*)&_nonce, sizeof(_nonce));
      in.read((char*)&_time, sizeof(_time));

      size_t len;
      in.read((char*)&len, sizeof(len));
      _hash.resize(len);
      if(len > 0) in.read(&_hash[0], len); 

      in.read((char*)&len, sizeof(len));
      _prevHash.resize(len);
      if(len > 0) in.read(&_prevHash[0], len); 

      size_t tx_count;
      in.read((char*)&tx_count, sizeof(tx_count));

      _transactions.resize(tx_count); 

      for(int i=0; i < tx_count; i++){
        _transactions[i].deserialize(in);
      }
    }
};

#endif 
