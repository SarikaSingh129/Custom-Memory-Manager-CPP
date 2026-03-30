# High-Performance Custom Memory Pool Manager (C++)

## 🚀 Overview
Standard `new` and `delete` operators in C++ carry significant overhead due to system calls and heap fragmentation. This project implements a **Fixed-Size Memory Pool Allocator** that achieves **O(1) allocation and deallocation** time by pre-allocating a large memory block and managing it manually.

## ✨ Key Features
- **O(1) Performance:** Constant time complexity for both allocation and deallocation.
- **Zero Fragmentation:** Prevents external fragmentation by using fixed-size blocks.
- **Free List Management:** Uses a linked-list based approach (Free List) to track available memory blocks.
- **Resource Efficient:** Ideal for high-frequency systems like Game Engines or Real-time Trading platforms.

## 🛠 Technical Concepts Used
- **Pointer Arithmetic:** Manual navigation through the memory pool.
- **Reinterpret Cast:** Safe type conversion for block linking.
- **Resource Acquisition Is Initialization (RAII):** Ensuring memory is freed in the destructor.

## 📦 How to Run
1. Clone the repository: `git clone https://github.com/SarikaSingh129/Custom-Memory-Manager-CPP.git`
2. Compile: `g++ MemoryPool.cpp -o MemoryPool`
3. Execute: `./MemoryPool`
