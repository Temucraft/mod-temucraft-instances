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
  than intended.
- Spells: 52 spells the creatures use aren't in Temucraft's `Spell.dbc`. 42 of them are the heroic copies of a
  normal-mode spell (from the 4.3.4 `SpellDifficulty.dbc`) and use that normal spell instead, which is in `Spell.dbc`
  (`SPELL_MAP` in `tools/heroic_convert.py`). The three Goblin Teleporter spells are a SmartAI teleport to the same
  spot, and the teleporter's gossip menu (12691) is in. Ripsnarl's cannon kill is done in the script. Left out, as no
  3.3.5 spell does the same job: the Defias Cannon's stun cannonball (95494), Vanessa's heroic buff Vengeance of
  VanCleef (95542), the vapor's Steam Aura look (95503), the rope's CLICK ME aura (95527) and the two achievement
  spells (95650, 95654). The scripts only cast these when `Spell.dbc` has them.
- Vehicles: the one-seat Cataclysm vehicles use a stock 3.3.5 vehicle with the same seat (Defias Watcher and Reaper
  227, Cookie's Cauldron and James Harrington 586, Ogre Henchman 294, Defias Cannon 554, Rope 477). The ones with many
  seats, where the seat spots are part of the fight (the Lumbering Oaf, the mine carts, Glubtok's fire wall platters,
  Vanessa's trap and lightning rings), keep their Cataclysm vehicle id: the server gets them in `vehicle_dbc` and
  `vehicleseat_dbc`, and the client in patch-T's `Vehicle.dbc` and `VehicleSeat.dbc`. The vehicle passengers and the
  spell clicks (riding the reapers, cannons and ropes) are in.
- The entrance quest givers of each faction (Lieutenant Horatio Laine, Kagtha and their groups) are left out: their
  quests don't exist here and both factions would see both.
- 9 creature models the client doesn't have use the closest 3.3.5 model (monkeys, hobgoblins, a goblin, the mystery
  meat).
- Loot: all of it is in. The bosses' own Cataclysm items (33) come from mod-temucraft-world (`item_template`, and
  `item_dbc` for the server plus patch-T's `Item.dbc` for the client).
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
| world | `vehicle_template_accessory`, `npc_spellclick_spells` | vehicle passengers and riding |
| world | `vehicle_dbc`, `vehicleseat_dbc` | the 8 Cataclysm vehicles that keep their id (1259, 1322, 1365, 1366, 1371, 1372, 1396, 1397) |
| world | `gossip_menu`, `gossip_menu_option` | the Goblin Teleporter (menu 12691) |
| world | `mapdifficulty_dbc` | heroic mode of map 36 (ID 758) |
| world | `dungeon_access_template` | level 80 for the heroic mode (ID 200) |

## Works with other modules

- Needs [mod-temucraft-world](https://github.com/Temucraft/mod-temucraft-world). Nothing else.
- [mod-temucraft-instances](https://github.com/Temucraft/mod-temucraft-instances) does the same for
  Shadowfang Keep.

Part of the Temucraft modules for AzerothCore 3.3.5a.
