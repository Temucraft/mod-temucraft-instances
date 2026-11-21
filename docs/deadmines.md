# deadmines (part of mod-temucraft-instances)

The Deadmines as it was rebuilt in Cataclysm, as the heroic mode of the classic dungeon (map 36): Glubtok, Helix
Gearbreaker, Foe Reaper 5000, Admiral Ripsnarl, "Captain" Cookie and Vanessa VanCleef with her nightmare event, with
the trash. The normal mode stays the classic Deadmines of AzerothCore, untouched.

The scripts are the Cataclysm (4.3.4) scripts of the Cataclysm Preservation Project's TrinityCore fork for The
Deadmines, ported to AzerothCore 3.3.5a. The creatures, objects, texts, waypoints, SmartAI and loot come from the
TrinityCore 4.3.4 world database (TDB 434.22011). The ported files keep TrinityCore's GNU GPL v2 licence and copyright
notice; `instance_deadmines_classic.cpp` is AzerothCore's own classic script (GNU GPL v2, AzerothCore's notice).

## How it works

- Every Cataclysm creature and object is spawned for the heroic mode only (`spawnMask` 2). AzerothCore's classic
  spawns are normal mode only, so the two versions never meet.
- The levels are 5 lower than in Cataclysm (80 to 82) and health and damage are scaled the same way as the other
  Cataclysm maps of [mod-temucraft-world](https://github.com/Temucraft/mod-temucraft-world).
- The instance script keeps AzerothCore's name, `instance_deadmines`, so it replaces AzerothCore's. In the normal mode
  it runs a copy of AzerothCore's classic script, so Mr. Smite, the doors and the cannon work as before; in the
  heroic mode it runs the Cataclysm one.
- The heroic mode needs level 80. The server gets the heroic row of `MapDifficulty.dbc` (ID 758, the same row as the
  client's in Temucraft's patch-T).

## What to expect

- Built against AzerothCore's script API with the same encounter logic as the original.
- Some Cataclysm spell effects and auras don't exist in the 3.3.5 core, so a few abilities can do nothing or less
  than intended. 52 spells the creatures use (mostly the heroic versions of Cataclysm spells) aren't in Temucraft's
  `Spell.dbc` and do nothing.
- The vehicles (Helix riding the Lumbering Oaf, the magma trap, the Defias cannon) use Cataclysm vehicle ids that the
  3.3.5 `Vehicle.dbc` doesn't have, so riding parts of these fights may not work.
- The entrance quest givers of each faction (Lieutenant Horatio Laine, Kagtha and their groups) are left out: their
  quests don't exist here and both factions would see both.
- 9 creature models the client doesn't have use the closest 3.3.5 model (monkeys, hobgoblins, a goblin, the mystery
  meat).
- Loot: the world drops and the items AzerothCore or mod-temucraft-world have are in. The bosses' own Cataclysm
  items (33 items) aren't: they need `item_template` rows and Item.dbc rows on the server and client first
  (`tools/items.py` in mod-temucraft-world), then this module's SQL can be made again with `tools/heroic_convert.py`.
- `TemucraftTCCompat.h` holds the few TrinityCore names the scripts use that AzerothCore doesn't have.

## Install

1. Install [mod-temucraft-world](https://github.com/Temucraft/mod-temucraft-world) first (some shared Cataclysm
   creatures and the Cataclysm items come from it).
2. Put this folder in `modules/`, re-run CMake and build.
3. The SQL in `data/sql/` is applied by the worldserver on its next start.

## What it changes

| Database | Table | What |
|---|---|---|
| world | `creature_template` and its `_model`, `_addon`, `_movement`, `_resistance`, `_spell` tables, `creature_equip_template`, `creature_text`, `creature_immunities` (IDs 73000 to 73499) | the Cataclysm creatures |
| world | `creature`, `creature_addon`, `creature_formations`, `waypoint_data` | heroic spawns, GUIDs 7300000 to 7349999 |
| world | `gameobject_template`, `gameobject_template_addon`, `gameobject` | heroic objects, GUIDs 7300000 to 7349999 |
| world | `spawn_group_template`, `spawn_group` | group 7300 (the goblin event) |
| world | `creature_loot_template`, `gameobject_loot_template`, `reference_loot_template`, `skinning_loot_template`, `pickpocketing_loot_template`, `smart_scripts`, `conditions` | loot, SmartAI and spell targets of the new creatures |
| world | `spell_script_names` | the spell scripts |
| world | `mapdifficulty_dbc` | heroic mode of map 36 (ID 758) |
| world | `dungeon_access_template` | level 80 for the heroic mode (ID 200) |

## Works with other modules

- Needs [mod-temucraft-world](https://github.com/Temucraft/mod-temucraft-world). Nothing else.
- [mod-temucraft-shadowfang-keep](https://github.com/Temucraft/mod-temucraft-shadowfang-keep) does the same for
  Shadowfang Keep.

Part of the Temucraft modules for AzerothCore 3.3.5a.
