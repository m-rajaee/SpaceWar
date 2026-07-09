# Space War - Console Multiplayer Game

A two-player competitive space battle game developed in **C** and implemented for the **Windows Console Environment**.

The project features a complete local account system, database management, real-time gameplay mechanics, collision detection, physics-based interactions, and audio effects.

---

## Overview

Space War is a local multiplayer game where two players can create accounts, log in, customize their profiles, and compete against each other on the same device.

Each player's account information and game history are stored locally inside the game directory.

---

# Features

## User Account System

Players can:

- Create new accounts.
- Log in using existing accounts.
- Store account information in a local database.
- Update account details.
- View match history, including wins and losses.
- Return to the login page.

During account creation, several validations are performed, including:

- Valid email format checking.
- Password length requirements.
- Input validation.

---

## Multiplayer Gameplay

- Two players play on the same computer using separate accounts.
- Players can choose the starting amount of health before the match begins.

### Controls

**Left Side Player**
- Movement: `W A S D`
- Shooting: `C`
- Plant Bomb : `E`
**Right Side Player**
- Movement: `I J K L`
- Shooting: `N`
- Plant Bomb : `U`
---

# Game Mechanics

The game includes various gameplay systems:

- Real-time two-player combat.
- Physics-based collision detection.
- Obstacle interaction.
- Bullet collision and reflection mechanics.
- Special locations including:
  - Teleportation points
  - Death zones

---

## Bomb System

Inspired by tactical games such as Counter-Strike, the game includes:

- Bomb planting mechanics.
- Time-based bomb activation.
- Bomb defusing system.

---

## Audio System

Complete sound design was implemented, including:

- Shooting effects.
- Bomb planting and defusing sounds.
- Menu background music.
- Gameplay sound effects.

---

# Technologies Used

- **Programming Language:** C
- **Platform:** Windows Console
- **Database:** Local File-Based Storage
- **Game Systems:**
  - Collision Detection
  - Physics Simulation
  - Input Handling
  - Audio Management

---

# Course Information

Basic Programming course at Isfahan University of Technology

---
