/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

// Names LegionCore's scripts use that AzerothCore doesn't have: its generic EVENT_n / ACTION_n ids and a few helpers.
#pragma once

#include "InstanceScript.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include <cmath>
#include <list>

enum TemucraftLegionEvents
{
    EVENT_1 = 1, EVENT_2, EVENT_3, EVENT_4, EVENT_5, EVENT_6, EVENT_7, EVENT_8, EVENT_9, EVENT_10,
    EVENT_11, EVENT_12, EVENT_13, EVENT_14, EVENT_15, EVENT_16, EVENT_17, EVENT_18, EVENT_19, EVENT_20,
    EVENT_21, EVENT_22, EVENT_23, EVENT_24, EVENT_25, EVENT_26, EVENT_27, EVENT_28, EVENT_29, EVENT_30,
    EVENT_31, EVENT_32, EVENT_33, EVENT_34, EVENT_35, EVENT_36, EVENT_37, EVENT_38, EVENT_39, EVENT_40
};

enum TemucraftLegionActions
{
    ACTION_1 = 1, ACTION_2, ACTION_3, ACTION_4, ACTION_5, ACTION_6, ACTION_7, ACTION_8, ACTION_9, ACTION_10,
    ACTION_11, ACTION_12, ACTION_13, ACTION_14, ACTION_15, ACTION_16, ACTION_17, ACTION_18, ACTION_19, ACTION_20
};

// true when nobody alive (game masters aside) is left in the instance
inline bool TemucraftIsWipe(Map* map)
{
    for (auto const& ref : map->GetPlayers())
        if (Player* player = ref.GetSource())
            if (player->IsAlive() && !player->IsGameMaster())
                return false;
    return true;
}

inline bool TemucraftIsWipe(InstanceScript* instance) { return instance && TemucraftIsWipe(instance->instance); }

// creature that never moves to its target
struct Scripted_NoMovementAI : public ScriptedAI
{
    explicit Scripted_NoMovementAI(Creature* creature) : ScriptedAI(creature) { }

    void AttackStart(Unit* target) override
    {
        if (target && me->Attack(target, true))
            DoStartNoMovement(target);
    }
};

inline void GetPlayerListInGrid(std::list<Player*>& list, WorldObject const* source, float range)
{
    for (auto const& ref : source->GetMap()->GetPlayers())
        if (Player* player = ref.GetSource())
            if (source->GetDistance(player) <= range)
                list.push_back(player);
}

inline void GetRandPosFromCenterInDist(float centerX, float centerY, float dist, float& x, float& y)
{
    float angle = frand(0.0f, 2.0f * float(M_PI));
    x = centerX + dist * std::cos(angle);
    y = centerY + dist * std::sin(angle);
}

inline void GetPositionWithDistInOrientation(WorldObject const* source, float dist, float orientation, float& x, float& y)
{
    x = source->GetPositionX() + dist * std::cos(orientation);
    y = source->GetPositionY() + dist * std::sin(orientation);
}

// LegionCore difficulty ids as the 3.3.5 ones (looking-for-raid and challenge modes don't exist here)
constexpr Difficulty DIFFICULTY_NORMAL = DUNGEON_DIFFICULTY_NORMAL;
constexpr Difficulty DIFFICULTY_HEROIC = DUNGEON_DIFFICULTY_HEROIC;
constexpr Difficulty DIFFICULTY_10_N = RAID_DIFFICULTY_10MAN_NORMAL;
constexpr Difficulty DIFFICULTY_25_N = RAID_DIFFICULTY_25MAN_NORMAL;
constexpr Difficulty DIFFICULTY_10_HC = RAID_DIFFICULTY_10MAN_HEROIC;
constexpr Difficulty DIFFICULTY_25_HC = RAID_DIFFICULTY_25MAN_HEROIC;
constexpr Difficulty DIFFICULTY_LFR = Difficulty(250);
constexpr Difficulty DIFFICULTY_CHALLENGE = Difficulty(251);

// CastCustomSpell with a float base point 0, as LegionCore passes it
inline void TemucraftCastBp0(Unit* caster, Unit* target, uint32 spellId, float bp0, bool triggered)
{
    int32 bp = int32(bp0);
    caster->CastCustomSpell(target, spellId, &bp, nullptr, nullptr, triggered);
}

enum TemucraftLegionTexts
{
    TEXT_GENERIC_0 = 0, TEXT_GENERIC_1, TEXT_GENERIC_2, TEXT_GENERIC_3, TEXT_GENERIC_4, TEXT_GENERIC_5, TEXT_GENERIC_6,
    TEXT_GENERIC_7, TEXT_GENERIC_8, TEXT_GENERIC_9, TEXT_GENERIC_10, TEXT_GENERIC_11, TEXT_GENERIC_12, TEXT_GENERIC_13,
    TEXT_GENERIC_14, TEXT_GENERIC_15, TEXT_GENERIC_16, TEXT_GENERIC_17, TEXT_GENERIC_18, TEXT_GENERIC_19, TEXT_GENERIC_20
};

// LegionCore's group roles, worked out from the 3.3.5 talent specs
enum TemucraftLegionRoles { ROLES_DEFAULT = 0, ROLES_TANK = 1, ROLES_HEALER = 2, ROLES_DPS = 3 };
inline uint8 TemucraftRole(Player const* constPlayer)
{
    Player* player = const_cast<Player*>(constPlayer);
    if (!player) return ROLES_DPS;
    if (player->HasTankSpec()) return ROLES_TANK;
    if (player->HasHealSpec()) return ROLES_HEALER;
    return ROLES_DPS;
}

// 3.3.5 has no fixate aura; HasAuraType(SPELL_AURA_NONE) is always false
constexpr AuraType SPELL_AURA_FIXATE = SPELL_AURA_NONE;

// LegionCore's spell area triggers (pools, beams, walls) don't exist in 3.3.5. This stand-in keeps the code that looks
// them up compiling; the lookups never find one, so those effects simply don't happen.
class TemucraftAreaObject : public Position
{
public:
    void RemoveFromWorld() { }
    void Remove() { }
    void Despawn() { }
    void SetDuration(int32) { }
    int32 GetDuration() const { return 0; }
    uint32 GetEntry() const { return 0; }
    uint32 GetSpellId() const { return 0; }
    float GetRadius() const { return 0.0f; }
    Unit* GetCaster() const { return nullptr; }
    ObjectGuid GetGUID() const { return ObjectGuid::Empty; }
    ObjectGuid GetCasterGUID() const { return ObjectGuid::Empty; }
    template<typename... Args> bool CreateAreaTrigger(Args&&...) { return false; }
    void SetSpellId(uint32) { }
    void SetRadius(float) { }
    void SetCasterGUID(ObjectGuid) { }
    void SetTargetGUID(ObjectGuid) { }
};
template<typename L, typename... Args> inline void TemucraftNoAreaObjects(L&, Args&&...) { }
inline TemucraftAreaObject* TemucraftNoAreaObject() { return nullptr; }

inline float TemucraftHealthPctWithHeal(Unit const* unit, uint32 heal)
{
    return unit->GetMaxHealth() ? float(std::min<uint64>(uint64(unit->GetHealth()) + heal, unit->GetMaxHealth())) * 100.0f / float(unit->GetMaxHealth()) : 0.0f;
}

inline void GetPosInRadiusWithRandomOrientation(WorldObject const* source, float dist, float& x, float& y)
{
    GetPositionWithDistInOrientation(source, dist, frand(0.0f, 2.0f * float(M_PI)), x, y);
}

// crowd control states LegionCore checks with IsInDisable / IsInControl
inline bool TemucraftIsInDisable(Unit const* unit)
{
    return unit->HasUnitState(UNIT_STATE_STUNNED | UNIT_STATE_CONFUSED | UNIT_STATE_FLEEING) || unit->HasAuraType(SPELL_AURA_MOD_PACIFY_SILENCE);
}
inline bool TemucraftIsInControl(Unit const* unit)
{
    return unit->HasUnitState(UNIT_STATE_STUNNED | UNIT_STATE_CONFUSED | UNIT_STATE_FLEEING | UNIT_STATE_ROOT);
}

// LegionCore's EnableOrDisableGo: an activated object is open/used, a disabled one is back to ready
inline void TemucraftEnableGo(GameObject* go, bool activate)
{
    if (go)
        go->SetGoState(activate ? GO_STATE_ACTIVE : GO_STATE_READY);
}

// LegionCore's specialization ids, as class * 100 + talent tab (0-2) of the 3.3.5 primary tree
constexpr uint8 CLASS_MONK = 10;           // no monks in 3.3.5
constexpr uint8 CLASS_DEMON_HUNTER = 12;   // no demon hunters in 3.3.5
enum TemucraftLegionSpecs : uint32
{
    SPEC_WARRIOR_ARMS = 100, SPEC_WARRIOR_FURY, SPEC_WARRIOR_PROTECTION,
    SPEC_PALADIN_HOLY = 200, SPEC_PALADIN_PROTECTION, SPEC_PALADIN_RETRIBUTION,
    SPEC_HUNTER_BEASTMASTER = 300, SPEC_HUNTER_MARKSMAN, SPEC_HUNTER_SURVIVAL,
    SPEC_ROGUE_ASSASSINATION = 400, SPEC_ROGUE_COMBAT, SPEC_ROGUE_SUBTLETY,
    SPEC_PRIEST_DISCIPLINE = 500, SPEC_PRIEST_HOLY, SPEC_PRIEST_SHADOW,
    SPEC_DK_BLOOD = 600, SPEC_DK_FROST, SPEC_DK_UNHOLY,
    SPEC_SHAMAN_ELEMENTAL = 700, SPEC_SHAMAN_ENHANCEMENT, SPEC_SHAMAN_RESTORATION,
    SPEC_MAGE_ARCANE = 800, SPEC_MAGE_FIRE, SPEC_MAGE_FROST,
    SPEC_WARLOCK_AFFLICTION = 900, SPEC_WARLOCK_DEMONOLOGY, SPEC_WARLOCK_DESTRUCTION,
    SPEC_MONK_BREWMASTER = 1000, SPEC_MONK_MISTWEAVER, SPEC_MONK_WINDWALKER,
    SPEC_DRUID_BALANCE = 1100, SPEC_DRUID_FERAL, SPEC_DRUID_RESTORATION, SPEC_DRUID_GUARDIAN = 1101
};
inline uint32 TemucraftCurrentSpec(Player const* player)
{
    return player ? player->getClass() * 100 + TemucraftPrimaryTalentTab(player) : 0;
}

// LegionCore's WorldObject::IsInDegreesRange: is (x, y) between two angles (degrees) seen from the object,
// measured from its facing when relative is set
inline bool TemucraftInDegreesRange(WorldObject const* source, float x, float y, float degreesA, float degreesB, bool relative = false)
{
    float angle = source->GetAngle(x, y);
    if (relative)
        angle = Position::NormalizeOrientation(angle - source->GetOrientation());
    float degrees = angle * 180.0f / float(M_PI);
    return degreesA <= degreesB ? (degrees >= degreesA && degrees <= degreesB) : (degrees >= degreesA || degrees <= degreesB);
}
