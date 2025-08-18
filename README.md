# 🔒 CryptoVault: An Interactive Encryption Platform  

**CryptoVault** is a web-based educational and functional platform that lets users **learn, explore, and experiment** with both classical and modern cryptographic techniques.  
It combines an **OOP-based C++ backend** for cryptographic logic with a **clean, user-friendly web interface**, allowing real-time encryption and decryption.  

---

## 🚀 Overview  
CryptoVault helps users enter plaintext, choose an encryption algorithm, and instantly see the encrypted ciphertext — with an option to **decrypt back** and validate correctness.  
It’s not just a tool — it’s a learning platform that shows **step-by-step transformations** for better understanding.  

---

## ✨ Key Features  

- 🌐 **Web Interface** – Intuitive UI for text input and algorithm selection.  
- 🔑 **Multiple Encryption Techniques** – Supports both **classical** and **modern** methods:  
  1. **AES (Advanced Encryption Standard)** – secure modern block cipher.  
  2. **RSA** – public-key encryption based on prime factorization.  
  3. **ElGamal Cipher** – discrete logarithm-based system.  
  4. **Playfair Cipher** – digraph substitution cipher with a 5×5 matrix.  
  5. **Hill Cipher** – matrix-based cipher using linear algebra.  
  6. **Transposition Cipher** – rearranges characters to obscure order.  
  7. **McEliece Cryptosystem** – post-quantum, code-based encryption method.  
- 🔄 **Bidirectional Operations** – Encryption **and** decryption for every algorithm.  
- 🎓 **Educational Mode** – Step-by-step breakdown of transformations (substitution tables, matrix multiplication, key expansion, etc.).  
- ⚡ **OOP Backend** – Implemented in **C++ (classes & inheritance)** for modularity, extensibility, and clarity.  

---

## 🛠 Workflow  

1. User enters a **plaintext message**.  
2. Selects an **encryption algorithm**.  
3. Platform generates and displays the **ciphertext**.  
4. Option to **decrypt** the ciphertext back to plaintext.  
5. (Optional) Toggle **educational details** to view intermediate steps.  

---

## 🎯 Practical Applications  

- 📘 **Education:** Teaching cryptography concepts in CS courses.  
- 🔬 **Research:** Comparing methods for strength, speed, and complexity.  
- 🔐 **Prototype Security:** Basis for secure communication or post-quantum studies.  
- 🧑‍💻 **Hands-on Learning:** Bridges the gap between theory and real-world cryptography.  

---

## 🗂️ Tech Stack  

- **Backend (Cryptographic Logic):** C++ with OOP principles (inheritance, polymorphism).  
- **Frontend (Web Interface):** HTML, CSS, JavaScript.  
- **Integration:** C++ cryptographic classes exposed to the web UI (via APIs / WebAssembly if deployed).  

---

## 📖 Supported Algorithms Summary  

| Category            | Algorithms |
|---------------------|------------|
| 🔐 Modern Ciphers   | AES, RSA, ElGamal, McEliece |
| 🏛 Classical Ciphers| Playfair, Hill, Transposition |

---

## 📌 Roadmap  

### ✅ MVP (v1.0)  
- Plaintext → Ciphertext conversion for all listed ciphers  
- Decryption support  
- Web-based UI with text input + output panel  
- Educational mode for Playfair, Hill, and Transposition  

### 🚀 Future Enhancements  
- Add **visual animations** of steps (matrix ops, key expansion).  
- Support **more modern ciphers** (ChaCha20, ECC).  
- User accounts to **save encrypted logs**.  
- Deploy backend using **WebAssembly** for browser-native C++ execution.  

---

## 🎯 Final Take  

CryptoVault is **not just a cryptography demo**.  
It’s a **bridge between theory, coding, and practice**, letting users:  
- Learn algorithms interactively  
- Experiment with encryption/decryption  
- Understand mathematical underpinnings  

✨ *A classroom tool, a research companion, and a real-world encryption lab — all in one.*  