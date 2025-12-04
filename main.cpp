#include <iostream>
#include "blockchain.h"
#include "transactions.h"

void create_transaction(Blockchain& coin){
  std::cout << "Creating transactions..." << std::endl;
  Transaction tx;
  std::cout<<"enter sender name:";
  std::cin>>tx.sender;
  std::cout<<"enter receiver name:";
  std::cin>>tx.receiver;
  std::cout<<"enter amount:";
  std::cin>>tx.amount;
  coin.addTransaction(tx);
  std::cout << "Transactions Saved" << std::endl;
}

int main() {
    Blockchain myCoin;
    int value;
    while(true){
      std::cout<<"Choose an option."<<std::endl;
      std::cout<<"1. Add Transaction"<<std::endl;
      std::cout<<"2. Mine Block"<<std::endl;
      std::cout<<"3. Print Chain"<<std::endl;
      std::cout<<"4. Exit"<<std::endl;
      std::cin>>value;
      switch(value){
        case 1: 
          create_transaction(myCoin);
          break;
        case 2:
          std::cout << "\nStarting the miner..." << std::endl;
          myCoin.MinePendingTransactions("MyWalletAddress");
          std::cout << "\nValidity of chain: " << myCoin.isChainValid() << std::endl;
          break;
        case 3:{
                 const auto& chain = myCoin.getChain();
                 std::cout << "\n--- Ledger ---" << std::endl;
                 for(const auto& block : chain) {
                   std::cout << "Block #" << block._index << " [" << block._transactions.size() << " txs]" << std::endl;
                   for(const auto& tx : block._transactions) {
                     std::cout << "   " << tx.sender << " -> " << tx.receiver << ": " << tx.amount << std::endl;
                   }
                   std::cout << "   Hash: " << block._hash << "\n" << std::endl;
                 }
                 break;
               }
        case 4:
          std::cout<<"Exiting Program"<<std::endl;
          return 0;
      }

    }
}
