# 🎮 QuattroRealm

![QuattroRealm Banner](assets/banner.png) 

> A fantasy strategy game built with **C++** and **SFML**, blending tactical combat and immersive gameplay in a vibrant pixelated realm.

---

## 🧠 About the Game

**QuattroRealm** is a turn-based, four-player strategy game where each player controls unique characters with distinct abilities. Inspired by classic board games and fantasy lore, it aims to combine tactical decision-making with a fun visual style powered by SFML.

- **Objective**: Reach the center of the board, eliminate the opposing **Commander**, or capture the opponent’s **headquarter** to win the game.
- **Board Layout**:  
  - The **9x9 grid** features each corner cell as a **headquarter**.
  - The **central cell** is the ultimate control point.
  - The cells immediately **up, down, left, and right** of the center are **blocked** (inaccessible).

- **Army Control**:
  - Each player controls a **commander-led army** consisting of specialized units.
  - On capturing a headquarter or killing the opposing **Commander**, the victorious player gains control of the defeated army's remaining pieces.

![3](assets/3.png) 

---

## 🚀 Features

- 🧙‍♂️ Multiple character classes with unique abilities
- 🗺️ Grid-based board system
- ⚔️ Attack, move, and use abilities during your turn
- 🎨 Pixel-art style graphics with **SFML**
- 💾 Object-oriented code structure in **C++**

![1](assets/1.png) 
![2](assets/2.png) 
---

## 🧬 Characters & Abilities

| Character | Image | Description |
|----------|-------|-------------|
| **Commander** | ![Commander](assets/Commander.png) |  The strategic centerpiece. <br>• Moves: 1 step diagonally only <br>• Captures: Any direction <br>• Loss: Losing this piece results in complete defeat. <br>• On defeat: Remaining army joins the attacker |
| **Rifleman** | ![Rifleman](assets/Rifleman.png) |  Basic infantry unit (3 per player). <br>• Moves: 1 step in any direction (up, down, left, right) <br>• Captures: Same as movement <br>• Vulnerable to all other pieces |
| **Sniper** | ![Sniper](assets/Sniper.png) |  Precision attacker (3 per player). <br>• Moves: 1 step in any direction <br>• Attack (without moving): Can eliminate any piece within **3 blocks diagonally** <br>• Fragile and killable by any unit |
| **Tank** | ![Tank](assets/Tank.png) |  Heavy unit (2 per player). <br>• Moves: 1 or 2 steps in a straight line (up, down, left, right) <br>• Attack (without moving): Can eliminate any unit within **2 cells in any direction** <br>• Can only be killed by another **Tank** |

---

> 🎮 Each character brings unique abilities to the board, making **QuattroRealm** a rich blend of chess-like planning and action-packed tactics.

### **Win Conditions**:
- Reach the **center cell**
- Capture the **enemy headquarter**
- Eliminate the **opposing Commander**

---

## Character Actions
> Blue highlight represents the positions where a character can move and grey highlight represents the position where a character can attack.

| Player Selection | Gameplay Board |
|------------------|----------------|
| ![Commander move and Attack](assets/Commander.png) | ![Board](assets/Commander_Move_Attack.png) | 
| ![Tank Attack](assets/Tank.png) | ![Board](assets/Tank_Attack.png) | 
| ![Tank Move](assets/Tank.png) | ![Board](assets/Tank_Move.png) | 
| ![Sniper Attack](assets/Sniper.png) | ![Board](assets/Sniper_Attack.png) | 
| ![Sniper Move](assets/Sniper.png) | ![Board](assets/Sniper_Move.png) | 
| ![RifleMan Attack and Move](assets/Rifleman.png) | ![Board](assets/Rifleman_Move_Attack.png) | 

---

## 🎬 Demo Video

> Click below to watch a gameplay demo!

[![Watch the Demo](https://img.youtube.com/vi/1s_1gz1ykmo/0.jpg)](https://www.youtube.com/watch?v=1s_1gz1ykmo)


---

## 🛠️ Getting Started

### 📋 Requirements

- C++17 or later
- [SFML 2.5+](https://www.sfml-dev.org/download.php)
- CMake (optional but helpful)
- A C++ compiler (G++, MSVC, or Clang)

### **Clone the repository**

   ```bash
   git clone https://github.com/yourusername/QuattroRealm.git
   cd QuattroRealm
```

## 🤝 Contributing
Pull requests are welcome! If you find bugs or have ideas to improve the game, feel free to open an issue or submit a PR.

## 📜 License
This project is licensed under the MIT License. 

---


# 🙌 Acknowledgments
## SFML Library

---

# ⭐ Show Your Support
If you enjoyed playing QuattroRealm, consider giving this repo a ⭐ and sharing it with your friends!
---

## ✨ Future Enhancements
1. Add AI for single-player mode
2. Implement undo/redo functionality
3. Add sound effects and background music
4. Improve animations and transitions

---
# 👨‍💻 Authors
1. Ananya Srivastava
2. Vishwajeet Singh (infiniper@gmail.com)
3. Nitish Kumar 
4. Shashwat Pandey

---