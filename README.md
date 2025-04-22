Mars Habitat Builder Bot Simulation

**Author:** Mohamed Nawfel M  
**Roll Number:** ME24B1072  
**Assignment Question 4 –** Mars Habitat Builder Bot  

---

## Overview

This project brings to life a **Mars Habitat Builder Bot** — a system designed to automate the construction and maintenance of habitat modules on the Martian surface.

Using C and some classic data structures, the simulation models how the bot handles part delivery, construction sequencing, storage management, damage tracking, and priority upgrades.

---

### Part A: Parts Delivery & Bot Construction

- Simulates parts arriving in a **Queue** (`Wall`, `Roof`, `Door`, `Window`, `Airlock`, `Vent`)
- Parts are then passed to a **Stack**, representing how bots build habitats in a last-in, first-out manner.
- Construction order is printed by popping the stack.

**Why LIFO?**  
Because the last component like the *Vent* needs to be sealed last—after the structure is built—making LIFO a natural fit!

---

### Part B: Habitat Storage Management

- A fixed-size **Array** (5 slots) stores finished habitats.
- As new habitats are built (`Hab1` to `Hab7`), older ones are replaced if storage is full.

**Design Insight:**  
The system assumes that older habitats can be reassigned or upgraded when new settlers arrive—so it's okay to overwrite the oldest ones.

---

### Part C: Damaged Habitat Tracker

- Uses a **Singly Linked List** to keep track of damaged habitats (`Hab3`, `Hab6`).
- Once repaired, `Hab3` is moved to a **Doubly Linked List** for inspection.
- The list can be traversed forward and backward.

**Repair Story:**  
*Hab3’s door cracked during a Martian dust storm. Builder bots sealed it with heat-resistant materials, and it's now up for inspection.*

---

### Part D: Priority Upgrades

- High-priority habitats like `Hab1` and `Hab4` are added to a **Circular Linked List** for continuous upgrade checks.
- Traversing the list simulates recurring upgrade cycles.

**Upgrade Idea:**  
*Hab4 is getting a greenhouse dome—supporting fresh oxygen and crops to boost colony sustainability!*

---
