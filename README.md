# CppChain: Persistent C++ Blockchain Engine
- Developed by Rahul Shankar V
---
A lightweight, compliant blockchain implementation built from scratch in C++. 
This project was built to explore system-level programming concepts, specifically focusing on manual memory management, binary serialization, and cryptographic data integrity without relying on heavy external libraries like OpenSSL or Boost.

## ⚡ Core Features
* **Proof-of-Work Consensus:** Implements a tunable difficulty mining algorithm (SHA-256 target validation).
* **Custom Binary Serialization:** Data is persisted to disk (`blockchain.dat`) using a custom Length-Value binary protocol, avoiding the overhead of JSON/XML parsers.
* **Immutable Ledger:** Tamper-evident architecture. Modifying a single byte in the binary file invalidates the entire chain upon the next validation check.
* **Mempool Management:** Transactions are queued in memory and flushed to storage only upon successful mining.
* **Zero-Dependency Cryptography:** Includes a standalone implementation of the SHA-256 algorithm.
## Build & Run
**Prerequisites**
* GCC/G++ (Supports C++11 or later)
* Standard Make tools (Optional, raw commands provided below)
**Compilation**
The project consists of the core engine, the SHA-256 module, and the CLI entry point.
```bash
g++ main.cpp sha256.cpp -o blockchain_node
```
Running the Node
```bash
./blockchain_node
```
## Usage
The application runs an interactive CLI (REPL).
- **Add Transaction:** Queues a transaction (Sender -> Receiver : Amount) into the local Mempool.
- **Mine Block:** Aggregates pending transactions, calculates the Merkle proof (simplified), and solves the Proof-of-Work puzzle.
- **Print Chain:** Displays the current state of the ledger and validates the cryptographic link of every block.
- **Exit:** Serializes the current state to blockchain.dat and terminates.
Note: If blockchain.dat exists, the node automatically loads and validates the chain on startup.

## Technical Architecture
Memory Layout & Serialization
Unlike standard implementations that dump structs to files, CppChain uses manual serialization to handle dynamic containers (std::vector and std::string).

Binary File Format:
```
[Header]
| Chain Size (size_t) |

[Block N]
| Index (4B) | Nonce (4B) | Timestamp (8B) |
| Hash Len (size_t) | Hash Bytes... |
| PrevHash Len (size_t) | PrevHash Bytes... |
| Tx Count (size_t) |
    [Transaction 1]
    | Sender Len | Sender Bytes | Receiver Len | Receiver Bytes | Amount (8B) |
```
## Safety Mechanisms
- Ghost File Prevention: The loader validates file headers before allocation to prevent segmentation faults from corrupted or zero-byte files.
- String Sanitization: Serialization logic checks for zero-length strings to prevent unsafe pointer access during read() operations.
## Roadmap
- Network Layer: P2P socket implementation for node-to-node block propagation.
- ChainWire: Currently refactoring the engine to serve as a File Integrity Monitor (FIM) for intrusion detection (Tripwire-style).

