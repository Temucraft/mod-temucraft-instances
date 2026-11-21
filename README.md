# mod-temucraft-instances

Boss, trash and instance scripts for the Cataclysm and Mists of Pandaria dungeons and raids on Temucraft, in one
module. Each instance has its own folder under `src/` and its own notes under `docs/`. The maps, creatures and items
these scripts use come from [mod-temucraft-world](https://github.com/Temucraft/mod-temucraft-world): install it first.

| Instance | Kind | Folder | Notes |
|---|---|---|---|
| The Deadmines (heroic, map 36) | Cataclysm dungeon | `src/deadmines` | [docs/deadmines.md](docs/deadmines.md) |
| Shadowfang Keep (heroic, map 33) | Cataclysm dungeon | `src/shadowfang_keep` | [docs/shadowfang_keep.md](docs/shadowfang_keep.md) |
| Halls of Origination | Cataclysm dungeon | `src/halls_of_origination` | [docs/halls_of_origination.md](docs/halls_of_origination.md) |
| Lost City of the Tol'vir | Cataclysm dungeon | `src/lost_city` | [docs/lost_city.md](docs/lost_city.md) |
| The Vortex Pinnacle | Cataclysm dungeon | `src/vortex_pinnacle` | [docs/vortex_pinnacle.md](docs/vortex_pinnacle.md) |
| Well of Eternity | Cataclysm dungeon | `src/well_of_eternity` | [docs/well_of_eternity.md](docs/well_of_eternity.md) |
| Throne of the Four Winds | Cataclysm raid | `src/throne_of_the_four_winds` | [docs/throne_of_the_four_winds.md](docs/throne_of_the_four_winds.md) |
| Firelands | Cataclysm raid | `src/firelands` | [docs/firelands.md](docs/firelands.md) |
| Temple of the Jade Serpent | Mists dungeon | `src/temple_of_the_jade_serpent` | [docs/temple_of_the_jade_serpent.md](docs/temple_of_the_jade_serpent.md) |
| Mogu'shan Vaults | Mists raid | `src/mogushan_vaults` | [docs/mogushan_vaults.md](docs/mogushan_vaults.md) |
| Siege of Orgrimmar | Mists raid | `src/siege_of_orgrimmar` | [docs/siege_of_orgrimmar.md](docs/siege_of_orgrimmar.md) |

The Deadmines and Shadowfang Keep keep the classic AzerothCore dungeon as the normal mode; the Cataclysm version is
the heroic mode (level 80).

## Install

1. Install mod-temucraft-world.
2. Put this folder in `modules/`, re-run CMake and build. Remove the old single-instance modules
   (mod-temucraft-deadmines, mod-temucraft-firelands, ...) from `modules/` if you had them: they are this module now.
3. The SQL in `data/sql/` is applied by the worldserver on its next start (same file names as before, so nothing is
   applied twice).

## Layout

- `src/mod_temucraft_instances_loader.cpp` calls each instance's own loader.
- Each folder keeps its own helper headers (`TemucraftTCCompat.h` and others); they are included from the same
  folder, so the copies don't mix.
- These scripts were ported from TrinityCore forks; the ported files keep their GNU GPL v2 licence and copyright
  notices (see each `docs/` file for where they come from).

Earlier these were eleven modules (mod-temucraft-deadmines, -shadowfang-keep, -firelands, -halls-of-origination,
-lost-city, -vortex-pinnacle, -throne-of-the-four-winds, -mogushan-vaults, -siege-of-orgrimmar,
-temple-of-the-jade-serpent, -well-of-eternity). Their repositories keep the history.
