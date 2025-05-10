## The Drunken Master
The game is about the last user of almighty drunken fist technique. Fight you limitations and bring back peace with kung fu style

### Project description
Drunken master is a platform game with turn based fighting, as a fan of retro games, I want to create something similar to Mario 64 and Pokemon.

### Project features
- GameSave System
- Really simple level creation/load system

### Level system explained
Under `/levels` directory we have `.txt` files, those files are nothing more than instructions for map generator on what elements it should create and what properties they should have

**Level file naming rules**

Proper syntax is `level_<chapter>-<level>` for example **level_1-1**. Every chapter has 5 levels, for ex. **level-3-6** will not be loaded

**How to create my own level?**

This is how typical level file looks like:
```cpp
ground->0.0,0.0,0.0,0.0
platform->0.0,0.0,812.0,584.0
platform->300.0,0.0,300.0,584.0
start->0.0,0.0,0.0,658.0
```
Before `->` separator name of the element is provided, after the separator are 4 **float values** which represent
- size x
- size y
- position x
- position y

For some elements some values are not used, here's a cheat sheet

| Element | Size X | Size Y | Position X | Position Y |
| ------- | ----- | ----- | --------- | --------- |
| **ground** | ❌ | ✅ | ❌ | ❌ |
| **platform** | ✅ | ✅ | ✅ | ✅ |

### Legal & license
As im not a legal owner of some music/graphics i will put credits below

| Main Menu music                                      | Graphics        |
| ---------------------------------------------------- | --------------- |
| Pokemon Fire/Red Sound Track (Modified with effects) | Me (for now)    |

Going back to a license game is completely **open-source** and **free to use/download/remix** as long as the link to this repo is present on wherever you're posting your remix
