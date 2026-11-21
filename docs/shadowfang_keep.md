# shadowfang-keep (part of mod-temucraft-instances)

Shadowfang Keep as it was rebuilt in Cataclysm, as the heroic mode of the classic dungeon (map 33): Baron Ashbury,
Baron Silverlaine, Commander Springvale, Lord Walden and Lord Godfrey, with the trash and the Alliance or Horde troops
that follow the group in. The normal mode stays the classic Shadowfang Keep of AzerothCore, untouched, with the Love
is in the Air event (Apothecary Hummel).

The scripts are the Cataclysm (4.3.4) scripts of the Cataclysm Preservation Project's TrinityCore fork for
Shadowfang Keep, ported to AzerothCore 3.3.5a. The creatures, objects, texts, waypoints, SmartAI, spawn groups and
loot come from the TrinityCore 4.3.4 world database (TDB 434.22011). The ported files keep TrinityCore's GNU GPL v2
licence and copyright notice; `instance_shadowfang_keep_classic.cpp` is AzerothCore's own classic script (GNU GPL v2,
AzerothCore's notice). The Cataclysm Apothecary Hummel script isn't ported: AzerothCore's own runs the event.

## How it works

- Every Cataclysm creature and object is spawned for the heroic mode only (`spawnMask` 2). AzerothCore's classic
  spawns are normal mode only, so the two versions never meet.
- Classic creatures that Cataclysm kept (Baron Silverlaine, Commander Springvale, the gargoyles, guardsmen, servitors
  and horses) get the Cataclysm heroic creature as their heroic difficulty; their normal mode doesn't change. The
  Cataclysm boss scripts of Silverlaine and Springvale are set on their heroic spawns only.
- The levels are 5 lower than in Cataclysm (80 to 82) and health and damage are scaled the same way as the other
  Cataclysm maps of [mod-temucraft-world](https://github.com/Temucraft/mod-temucraft-world).
- The instance script keeps AzerothCore's name, `instance_shadowfang_keep`, so it replaces AzerothCore's. In the normal
  mode it runs a copy of AzerothCore's classic script; in the heroic mode it runs the Cataclysm one. The area trigger
  scripts only act in the heroic mode.
- The Alliance and Horde troops are spawn groups 7350 to 7370, spawned by the instance script for the faction of the
  first player in.
- The heroic mode needs level 80. The server gets the heroic row of `MapDifficulty.dbc` (ID 756, the same row as the
  client's in Temucraft's patch-T).

## What to expect

- Built against AzerothCore's script API with the same encounter logic as the original.
- Some Cataclysm spell effects and auras don't exist in the 3.3.5 core, so a few abilities can do nothing or less
  than intended.
- Spells: 10 spells the creatures use aren't in Temucraft's `Spell.dbc`. Six are heroic copies of a normal-mode spell
  and use that spell (Pustulant Spit, Conjure Poisonous Mixture, Asphyxiate, Pain and Suffering, Unholy Power, Cursed
  Bullets); the Mystery Toxin's Shrink uses the 3.3.5 Shrink aura (35179). Springvale's Shield of the Perfidious dummy
  isn't in 4.3.4 either: the script summons the Shield Focus itself. The two Bullet Time achievement spells are left
  out (no achievement in 3.3.5).
- The four Cataclysm area triggers (6422, 6424, 6425, 6431: talk before Springvale, the troops outside, Ivar's talk
  and Godfrey's intro) are in: the server gets them in the `areatrigger` table, the client in patch-T's
  `AreaTrigger.dbc`.
- Baron Ashbury's vehicle uses the stock 3.3.5 vehicle 586 (one seat, for his wings).
- The Wailing Guardsmen and Tormented Officers Springvale calls are new creatures and are scripted; the ones spawned
  in the halls are the classic creatures with the Cataclysm stats.
- 7 creature models the client doesn't have use the closest 3.3.5 model (the Forsaken Blightspreader and the Rabid
  Mastiff).
- Loot: all of it is in. The bosses' own Cataclysm items (37) come from mod-temucraft-world (`item_template`, and
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
| world | `creature_template` and its `_model`, `_addon`, `_movement`, `_resistance`, `_spell` tables, `creature_equip_template`, `creature_text`, `creature_immunities` (IDs 73500 to 73999) | the Cataclysm creatures |
| world | `creature_template` | `difficulty_entry_1` of 9 classic creatures (only when it was empty) |
| world | `creature`, `creature_addon`, `creature_formations`, `waypoint_data` | heroic spawns, GUIDs 7350000 to 7399999 |
| world | `gameobject_template`, `gameobject_template_addon`, `gameobject` | heroic objects, GUIDs 7350000 to 7399999 |
| world | `spawn_group_template`, `spawn_group` | groups 7350 to 7370 (troops and disease clouds) |
| world | `creature_loot_template`, `gameobject_loot_template`, `reference_loot_template`, `skinning_loot_template`, `pickpocketing_loot_template`, `smart_scripts` | loot and SmartAI of the new creatures |
| world | `spell_script_names`, `areatrigger_scripts` | the spell and area trigger scripts |
| world | `areatrigger` | the four Cataclysm area triggers (6422, 6424, 6425, 6431) |
| world | `vehicle_template_accessory`, `npc_spellclick_spells` | Baron Ashbury's wings |
| world | `mapdifficulty_dbc` | heroic mode of map 33 (ID 756) |
| world | `dungeon_access_template` | level 80 for the heroic mode (ID 201) |

## Works with other modules

- Needs [mod-temucraft-world](https://github.com/Temucraft/mod-temucraft-world). Nothing else.
- [mod-temucraft-instances](https://github.com/Temucraft/mod-temucraft-instances) does the same for The Deadmines.

Part of the Temucraft modules for AzerothCore 3.3.5a.
