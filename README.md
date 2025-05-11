## The Drunken Master
The game is about the last user of almighty drunken fist technique. Fight you limitations and bring back peace with kung fu style

### Project description
Drunken master is a platform game with turn based fighting, as a fan of retro games, I want to create something similar to Mario 64 and Pokemon.

## Project features
- GameSave System
- Really simple level creation/load system

---

### Level system
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
| **start** | ❌ | ❌ | ✅ | ✅ |

---

### Save system
Save system uses method similar to one used in **level system**. In `/saves` dir there are `.txt` files with this syntax `<character-name>.txt`. When you create new game **character name** is generated automatically and then displayed in level/game UI

**How to edit/create save files**

This could come in handy when you want to add custom name for your character, or when you just want to tweak statictics

Default freshly generated save file will look like this
```cpp
hp->100
ad->10
move_speed->300
name->test_player
exp_level->1
exp->0
current_chapter->1
current_level->1
```

| Key | Default Value | Max Value | What it does? |
| --- | ------------- | --------- | ------------- |
| **hp** | ` 100 ` | - | Health points of your character |
| **ad** | ` 10 ` | - | Attack damage of your character |
| **move_speed** | ` 300 ` | ` 600 ` | Horizontal movement speed |
| **exp_level** | ` 1 ` | - | Character level |
| **exp** | ` 0 ` | ` exp_level * 100 ` | Exp, used to level up |
| **current_chapter** | `1` | - | Current chapter that your character is on |
| **current_level** | ` 1 ` | ` 5 ` | Current level of chapter that your character is on |

---

## Legal & license
As im not a legal owner of some music/graphics i will put credits below

| Main Menu music                                      | Graphics        |
| ---------------------------------------------------- | --------------- |
| Pokemon Fire/Red Sound Track (Modified with effects) | Me (for now)    |

Going back to a license game is completely **open-source** and **free to use/download/remix** as long as the link to this repo is present on wherever you're posting your remix
