#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include <sstream>
#include <fstream>

struct Transaction{
  std::string sender;
  std::string receiver;
  double amount;

  std::string toString() const{
    std::stringstream ss;
    ss<<sender<<receiver<<amount;
    return ss.str();
  }

  void serialize(std::ofstream& out) const{
    size_t len;

    len=sender.size();
    out.write((char*)&len,sizeof(len));
    out.write(sender.c_str(),len);

    len=receiver.size();
    out.write((char*)&len,sizeof(len));
    out.write(receiver.c_str(),len);

    out.write((char*)&amount,sizeof(amount));
  }

  void deserialize(std::ifstream& in) {
    size_t len = 0;

    in.read((char*)&len, sizeof(len));
    sender.resize(len);
    if(len > 0) in.read(&sender[0], len); // <--- Add check: if(len > 0)

    in.read((char*)&len, sizeof(len));
    receiver.resize(len);
    if(len > 0) in.read(&receiver[0], len); // <--- Add check

    in.read((char*)&amount, sizeof(amount));
  }
};
#endif
