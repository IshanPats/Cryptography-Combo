Cryptographic Algorithms Implemented using Object-Oriented Programming (C++)

Project Overview
Cryptography is traditionally studied as a mathematical discipline, where algorithms are expressed through equations, modular arithmetic, and theoretical constructs. However, implementing these algorithms in real software systems requires translating those mathematical procedures into structured and maintainable code.

This project explores how classical cryptographic algorithms can be implemented and organized using Object-Oriented Programming (OOP) principles in C++.

Instead of writing isolated implementations, each cryptographic method is designed as a separate class, encapsulating its encryption logic and internal operations. These modules are integrated into a menu-driven application that allows users to choose between different cryptographic algorithms.

Core Concepts Connected
1.	Cryptographic theory
2.	Algorithmic thinking
3.	Object-Oriented Software Design

Project Objectives
The primary objective of this project was to explore how OOP can be used to organize and implement cryptographic algorithms in a structured way.

Key Goals
1.	Understand the internal working of classical cryptographic systems
2.	Implement encryption algorithms using C++ and OOP principles
3.	Translate mathematical encryption formulas into executable code
4.	Create a single program supporting multiple cryptographic methods
5.	Strengthen understanding of software architecture and algorithm design

Cryptographic Algorithms Implemented
Each team member implemented a different cryptographic system.
1) RSA Encryption
Implemented by: Aniket Patankar

Features:
1.	Generation of key parameters
2.	Encryption using public key
3.	Decryption using private key
4.	Modular exponentiation for efficient computation

2) Hill Cipher
Implemented by: Anannya Patil

Features:
1.	Plaintext converted into numerical vectors
2.	Matrix multiplication with key matrix
3.	Modular arithmetic operations
4.	Decryption using inverse matrix

3) Playfair Cipher
Implemented by: Parth Khadiwala

Features:
1.	5×5 key matrix construction
2.	Digraph (pair-wise) encryption
3.	Position-based encryption rules
4.	Reverse process for decryption

4) ElGamal Encryption
Implemented by: Ishan Amod Patankar

Features:
1.	Prime modulus verification
2.	Private key selection
3.	Public key generation
4.	Plaintext numeric conversion
5.	Ciphertext pair generation


Software Architecture and Design
The system uses a class-based modular architecture.

1.	Architectural Characteristics
2.	Modular class-based design
3.	Encapsulation of encryption logic
4.	Clear separation of algorithms
5.	Central menu-driven interface

The main program acts as the entry point and calls the selected algorithm class.

Technologies Used
1.	Programming Language
2.	C++
3.	Programming Paradigm
4.	Object-Oriented Programming (OOP)
5.	Core Concepts Applied
6.	Classes and Objects
7.	Encapsulation
8.	Inheritance
9.	Modular Design
10.	Modular Arithmetic

How the Program Works
When executed, the program displays:
Select Cryptographic Method
1. RSA
2. Hill Cipher
3. Playfair Cipher
4. ElGamal
The user selects an option and provides required inputs (plaintext, keys, parameters).
The selected algorithm performs encryption/decryption and displays the result.


Running the Project
Clone the Repository
git clone https://github.com/IshanPats/Cryptography-Combo.git

Compile the Program
g++ main.cpp -o cryptography

Run the Executable
./cryptography


Contributors
1.	Ishan Amod Patankar — ElGamal Encryption
2.	Aniket Patankar — RSA Implementation
3.	Anannya Patil — Hill Cipher
4.	Parth Khadiwala — Playfair Cipher


Future Improvements
1.	Implement modern encryption systems (AES, Diffie–Hellman)
2.	Improve modular arithmetic efficiency
3.	Implement secure random number generation
4.	Add graphical user interface (GUI)
5.	Expand into a cryptography learning toolkit
   

Educational Purpose
1.	This project was developed as part of an academic exploration of Object-Oriented Programming and cryptographic system implementation.
2.	The primary goal was to understand how theoretical encryption methods can be translated into practical software systems through structured design.
