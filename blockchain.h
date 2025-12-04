#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <iostream>
#include "Block.h"
#include "transactions.h" 

class Blockchain {
private:
    std::vector<Block> _chain;
    std::vector<Transaction> _pendingTransactions;
    uint32_t _difficulty;
    uint32_t _miningReward;

public:
    Blockchain() {
        _difficulty = 4;
        _miningReward = 100; 
        
        std::vector<Transaction> genesisTransactions;
        _chain.emplace_back(Block(0, genesisTransactions, "0000"));
    }

    void addTransaction(Transaction tx) {
        _pendingTransactions.push_back(tx);
    }

    void MinePendingTransactions(std::string minerAddress) {
        Transaction rewardTx;
        rewardTx.sender = "System";
        rewardTx.receiver = minerAddress;
        rewardTx.amount = _miningReward;
        
        _pendingTransactions.push_back(rewardTx);

        Block newBlock(static_cast<uint32_t>(_chain.size()), _pendingTransactions, _chain.back()._hash);
        newBlock.MineBlock(_difficulty);
        std::cout << "Block successfully mined!" << std::endl;
        _chain.push_back(newBlock);
        
        _pendingTransactions.clear(); 
    }

    const std::vector<Block>& getChain() const {
        return _chain;
    }

    bool isChainValid() const {
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
