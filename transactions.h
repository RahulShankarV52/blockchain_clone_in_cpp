#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include <sstream>
struct Transaction{
  std::string sender;
  std::string receiver;
  double amount;
  std::string toString() const{
    std::stringstream ss;
    ss<<sender<<receiver<<amount;
    return ss.str();
  }
};
#endif
