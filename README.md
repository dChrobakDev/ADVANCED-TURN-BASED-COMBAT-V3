# ⚔️ ADVANCED TURN-BASED COMBAT V3 | EXPANDED DEMO

An even more advanced turn-based combat simulator written in C++.  
This version includes AI behavior, attack logic conditioning, and refined cooldowns.

---

## 📜 Description

The player can:

- Perform normal and piercing attacks (with crit chance and buffs)
- Use a DMG buff (+15% for next round, 5-round cooldown)
- Use a DEF buff (-15% enemy attack next round, 4-round cooldown)
- Heal (+20 HP, 6-round cooldown)
- Dodge (avoid attack, 3-round cooldown)
- Skip round to observe enemy behavior

**New additions in this version:**

- 🧠 Enemy AI that uses buff → attack logic flow
- 💡 Condition-based enemy decisions
- 🔄 Enhanced cooldown timers per skill
- 🔍 Cleaner debug/stat tracking

---

## 🧪 Features demonstrated

- ✅ Turn-based logic with enemy decision state
- ✅ Player/enemy HP & armor management
- ✅ Buff/debuff logic affecting attack outcome
- ✅ Enemy behavior based on previous actions
- ✅ Use of `switch-case`, `rand()`, `srand()`, and `max()`
- ✅ Cooldown & conditional checks per action

---

## ▶️ How to run

1. Compile using C++11 or later (e.g. Visual Studio 2022)
2. Run the executable and follow instructions

---

## 👤 Author

**Dawid Chrobak**  
Aspiring Game Developer  
[GitHub – dChrobakDev](https://github.com/dChrobakDev) • [LinkedIn – Dawid Chrobak](https://www.linkedin.com/in/dawid-chrobak-9511a0373/)

---

## 🖥️ Example Output
```
--- Round #1 ---

Choose Action (1–6)

1. Attack                        4. Dash [ CD 5 ]
2. Attack buff [ 15% CD 5 ]      5. Defense buff [ 15% CD 5 ]
3. Pearcing Attack  [ CD 3 ]     6. Skip round
7. Heal potion [ +20 HP CD 3 ]

[Player chooses 2]
Player used DMG Buff!

[Enemy uses Buff]
Enemy used attack buff!

--- Round #2 ---

[Player chooses 1]
Critical hit with buff! [22 DMG]

Enemy critical strike with buff! [26 DMG]

Player HP [74]     Enemy HP [78]

...

[[ --- VICTORY! --- ]]
```

