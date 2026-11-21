/*
 * This file is part of the LegionCore project (TrinityCore-based), ported to AzerothCore.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "InstanceMapScript.h"
#include "InstanceScript.h"
#include "SpellScript.h"
#include "SpellScriptLoader.h"
#include "CreatureScript.h"
#include "GameObjectScript.h"
#include "AreaTriggerScript.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "Player.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "ObjectAccessor.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "MotionMaster.h"
#include "MoveSplineInit.h"
#include "Vehicle.h"
#include "TemporarySummon.h"
#include "Group.h"
#include "Map.h"
#include "PassiveAI.h"
#include "TemucraftTCCompat.h"
#include "TemucraftLegionCompat.h"

#include "CreatureTextMgr.h"

#define TYPE_SET_SUNS_SELECTABLE 2
#define TYPE_NUMBER_SUN_DEFEATED 1
#define TYPE_ZAO_ENTER_COMBAT    1
#define TYPE_ZAO_TALK            2
#define TYPE_LOREWALKTER_STONESTEP 0
#define TYPE_LOREWALKER_STONESTEP_TALK_AFTER_ZAO 3
#define TYPE_GET_EVENT_LOREWALKER_STONESTEP 5
 
enum eBoss
{
    BOSS_LOREWALKER_STONESTEP   = 1,
    BOSS_SUN                    = 2,
    BOSS_ZAO_SUNSEEKER          = 3,

    BOSS_STRIFE                 = 4,
    BOSS_PERIL                  = 5
};

enum eSpells
{
    SPELL_MEDITATION            = 122715,
    SPELL_ROOT_SELF             = 106822,
    SPELL_SUNFIRE_RAYS          = 111853,
    SPELL_SUN                   = 107349,
    SPELL_GROW_LOW              = 104921,
    SPELL_EXTRACT_SHA_3         = 111807,
    SPELL_EXTRACT_SHA_4         = 111768,
    SPELL_SHOOT_SUN             = 112084,
    SPELL_HELLFIRE_ARROW        = 113017,
    SPELL_SHA_CORRUPTION_2      = 120000,
    SPELL_EXTRACT_SHA           = 111764,

    SPELL_AGONY                 = 114571,
    SPELL_DISSIPATION           = 113379,
    SPELL_INTENSITY             = 113315,
    SPELL_ULTIMATE_POWER        = 113309,
    SPELL_LOREWALKER_ALACRITY   = 122714
};

enum eEvents
{
    EVENT_INTRO_0 = 1,
    EVENT_INTRO_1 = 2,
    EVENT_INTRO_2 = 3,
    EVENT_INTRO_3 = 4,

    EVENT_SUN_0 = 5,
    EVENT_SUN_1 = 6,
    EVENT_SUN_2 = 7,
    EVENT_SUN_3 = 8,
    EVENT_SUN_4 = 9,

    EVENT_ZAO_ENTER_COMBAT_1 = 10,
    EVENT_ZAO_ENTER_COMBAT_2 = 11,
    EVENT_ZAO_ATTACK         = 12,

    EVENT_TALK_LOREWALKER_DESPAWN = 13,

    EVENT_STRIFE_0 = 14,
    EVENT_STRIFE_1 = 15,
    EVENT_STRIFE_2 = 16,
    EVENT_STRIFE_3 = 17,
    EVENT_STRIFE_4 = 18
};

enum eTexts
{
    EVENT_TALK_INTRO_0 = 0,
    EVENT_TALK_INTRO_1 = 1,
    EVENT_TALK_INTRO_2 = 2,
    EVENT_TALK_INTRO_3 = 3,

    EVENT_TALK_ZAO_APPEARS_0 = 4,
    EVENT_TALK_ZAO_APPEARS_1 = 5,
    EVENT_TALK_ZAO_APPEARS_2 = 6,
    EVENT_TALK_ZAO_APPEARS_3 = 7,
    EVENT_TALK_ZAO_APPEARS_4 = 8,

    EVENT_TALK_ZAO_ENTERS_COMBAT_0 = 9,

    EVENT_TALK_STRIFE_0 = 10,
    EVENT_TALK_STRIFE_1 = 11,
    EVENT_TALK_STRIFE_2 = 12,
    EVENT_TALK_STRIFE_3 = 13,
    EVENT_TALK_STRIFE_4 = 14
};

enum eCreatures
{
    CREATURE_SCROLL                 = 57080,
    CREATURE_ZAO_SUNSEEKER          = 58826,
    CREATURE_HAUNTING_SHA_1         = 58865,
    CREATURE_HAUNTING_SHA_2         = 58856,
    CREATURE_SUN                    = 56915,
    CREATURE_OSONG                  = 56872,
    CREATURE_STRIFE                 = 59726,
    CREATURE_PERIL                  = 59051,
    CREATURE_SUN_TRIGGER            = 56861
};

struct boss_lorewalker_stonestep : public BossAI
{
    explicit boss_lorewalker_stonestep(Creature* creature) : BossAI(creature, BOSS_LOREWALKER_STONESTEP)
    {
        event_go = false;
        ended = false;
    }

    bool event_go;
    bool ended;
    ObjectGuid scrollGUID;
    ObjectGuid strifeGUID;
    ObjectGuid perilGUID;
    ObjectGuid osongGUID;
    ObjectGuid zaoGUID;
    std::list<ObjectGuid> suntriggerList;
    std::list<ObjectGuid> sunList;
    std::list<ObjectGuid> tornadoList;

    void Reset() override
    {
        me->GetMotionMaster()->MoveTargetedHome();
        _Reset();
    }

    void CompleteEncounter()
    {
        (void)0; // instance->DoUpdateAchievementCriteria(CRITERIA_TYPE_SCRIPT_EVENT_2, 30729); // no scenario criteria in 3.3.5
        instance->instance->DoForAllPlayers([&](Player* player) { player->CastSpell(player, SPELL_LOREWALKER_ALACRITY, false); });

        std::list<Creature*> creaList;
        GetCreatureListWithEntryInGrid(creaList, me, CREATURE_SCROLL, 100.0f);
        GetCreatureListWithEntryInGrid(creaList, me, CREATURE_HAUNTING_SHA_1, 100.0f);
        GetCreatureListWithEntryInGrid(creaList, me, CREATURE_HAUNTING_SHA_2, 100.0f);
        GetCreatureListWithEntryInGrid(creaList, me, CREATURE_SUN, 100.0f);
        GetCreatureListWithEntryInGrid(creaList, me, CREATURE_OSONG, 100.0f);
        GetCreatureListWithEntryInGrid(creaList, me, CREATURE_SUN_TRIGGER, 100.0f);
        GetCreatureListWithEntryInGrid(creaList, me, 58815, 100.0f);
        for (auto const& spawns : creaList)
            if (!creaList.empty())
                spawns->DespawnOrUnsummon(500ms);
    }

    void DoAction(int32 const action) override
    {
        switch (action)
        {
        case ACTION_1:
            CancelIntro();
            events.RescheduleEvent(EVENT_STRIFE_0, 7000ms);
            break;
        case ACTION_2:
            CancelIntro();
            events.RescheduleEvent(EVENT_SUN_0, 3000ms);
            break;
        case ACTION_4:
            if (!ended)
            {
                ended = true;
                CompleteEncounter();
                CancelIntro();
                events.RescheduleEvent(EVENT_19, 6000ms);

                if (auto osong = ObjectAccessor::GetCreature(*me, osongGUID))
                    osong->DespawnOrUnsummon();

                if (auto strife = ObjectAccessor::GetCreature(*me, strifeGUID))
                {
                    if (strife->IsAlive())
                        Unit::Kill(me, strife);
                }

                if (auto peril = ObjectAccessor::GetCreature(*me, perilGUID))
                {
                    if (peril->IsAlive())
                        Unit::Kill(me, peril);
                }
            }
            break;
        case ACTION_5:
            CompleteEncounter();
            Talk(18);
            me->GetMotionMaster()->MovePoint(4, 840.0646f, -2468.283f, 175.5254f);
            events.RescheduleEvent(EVENT_21, 9000ms);
            break;
        case ACTION_6:
            me->m_Events.AddEventAtOffset([=]() -> void { Talk(EVENT_SUN_4); }, Milliseconds(6000));
            break;
        }
    }

    void MovementInform(uint32 type, uint32 data) override
    {
        if (type == POINT_MOTION_TYPE)
        {
            switch (data)
            {
            case 1:
                if (auto strife = ObjectAccessor::GetCreature(*me, strifeGUID))
                {
                    strife->SetReactState(REACT_AGGRESSIVE);
                    strife->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);

                    if (auto player = strife->SelectNearestPlayer(50.0f))
                        if (auto player = strife->SelectNearestPlayer(50.0f))
                            strife->AI()->AttackStart(player);
                }

                if (auto peril = ObjectAccessor::GetCreature(*me, perilGUID))
                {
                    peril->SetReactState(REACT_AGGRESSIVE);
                    peril->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);

                    if (auto player = peril->SelectNearestPlayer(50.0f))
                        peril->AI()->AttackStart(player);
                }

                if (auto osong = ObjectAccessor::GetCreature(*me, osongGUID))
                {
                    osong->AI()->Talk(0);
                    osong->SetReactState(REACT_AGGRESSIVE);
                }

                me->SetFacingTo(5.986479f);
                events.RescheduleEvent(EVENT_STRIFE_3, 16000ms);
                break;
            case 2:
                me->SetFacingTo(1.256637f);
                break;
            case 3:
                me->SetFacingTo(1.239184f);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 510);
                break;
            }
        }
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!event_go && who && who->IsPlayer())
        {
            event_go = true;
            events.RescheduleEvent(EVENT_INTRO_0, 500ms);

            if (instance)
                instance->SetData(TYPE_LOREWALKTER_STONESTEP, 1);
        }
    }

    void JustSummoned(Creature* sum) override
    {
        summons.Summon(sum);

        switch (sum->GetEntry())
        {
        case CREATURE_STRIFE:
            strifeGUID.Clear();
            strifeGUID = sum->GetGUID();
            sum->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            sum->CastSpell(sum, 115086, false);
            sum->SetReactState(REACT_PASSIVE);
            break;
        case CREATURE_PERIL:
            perilGUID.Clear();
            perilGUID = sum->GetGUID();
            sum->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            sum->CastSpell(sum, 115086, false);
            sum->SetReactState(REACT_PASSIVE);
            break;
        case CREATURE_OSONG:
            osongGUID.Clear();
            osongGUID = sum->GetGUID();
            break;
        case CREATURE_SUN:
            suntriggerList.clear();
            sunList.push_back(sum->GetGUID());
            sum->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            sum->SetReactState(REACT_PASSIVE);
            break;
        case CREATURE_ZAO_SUNSEEKER:
            zaoGUID.Clear();
            zaoGUID = sum->GetGUID();
            sum->SetControlled(true, UNIT_STATE_ROOT);
            break;
        case CREATURE_SUN_TRIGGER:
            suntriggerList.clear();
            suntriggerList.push_back(sum->GetGUID());
            sum->SetFaction(14);
            sum->SetDisplayId(11686);
            sum->SetReactState(REACT_PASSIVE);
            break;
        case 58815:
            tornadoList.clear();
            tornadoList.push_back(sum->GetGUID());
            sum->SetReactState(REACT_PASSIVE);
            sum->CastSpell(sum, 111683, false);
            break;
        default:
            break;
        }
    }

    void CancelIntro()
    {
        me->RemoveAura(107048);
        events.CancelEvent(EVENT_INTRO_0);
        events.CancelEvent(EVENT_INTRO_1);
        events.CancelEvent(EVENT_INTRO_2);
        events.CancelEvent(EVENT_INTRO_3);
        events.CancelEvent(EVENT_STRIFE_3);
        events.CancelEvent(EVENT_STRIFE_4);
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_INTRO_0:
                Talk(EVENT_TALK_INTRO_0);
                events.RescheduleEvent(EVENT_INTRO_1, 10000ms);
                break;
            case EVENT_INTRO_1:
                Talk(EVENT_TALK_INTRO_1);
                events.RescheduleEvent(EVENT_INTRO_2, 10000ms);
                break;
            case EVENT_INTRO_2:
                Talk(EVENT_TALK_INTRO_2);
                events.RescheduleEvent(EVENT_INTRO_3, 8000ms);
                break;
            case EVENT_INTRO_3:
                Talk(EVENT_TALK_INTRO_3);
                break;
            case EVENT_SUN_0:
                me->SummonCreature(CREATURE_SUN, 830.067f, -2466.660f, 179.240f, 1.239f);
                me->SummonCreature(CREATURE_SUN, 836.632f, -2467.159f, 178.139f, 1.239f);
                me->SummonCreature(CREATURE_SUN, 839.659f, -2469.159f, 182.496f, 1.239f);
                me->SummonCreature(CREATURE_SUN, 845.263f, -2469.179f, 178.209f, 1.239f);
                me->SummonCreature(CREATURE_SUN, 850.361f, -2474.320f, 178.196f, 1.239f);
                me->SummonCreature(CREATURE_SUN_TRIGGER, 830.067f, -2466.660f, 176.320f);
                me->SummonCreature(CREATURE_SUN_TRIGGER, 836.632f, -2467.159f, 176.320f);
                me->SummonCreature(CREATURE_SUN_TRIGGER, 839.659f, -2469.159f, 176.320f);
                me->SummonCreature(CREATURE_SUN_TRIGGER, 845.263f, -2469.179f, 176.320f);
                me->SummonCreature(CREATURE_SUN_TRIGGER, 850.361f, -2474.320f, 176.320f);
                me->SummonCreature(CREATURE_ZAO_SUNSEEKER, 846.877f, -2449.110f, 175.044f, 4.43956f);

                me->SetFacingTo(1.23726f);
                Talk(EVENT_TALK_ZAO_APPEARS_0);
                events.RescheduleEvent(EVENT_SUN_1, 10000ms);
                break;
            case EVENT_SUN_1:
                Talk(EVENT_TALK_ZAO_APPEARS_1);
                events.RescheduleEvent(EVENT_SUN_2, 12000ms);
                break;
            case EVENT_SUN_2:
                Talk(EVENT_TALK_ZAO_APPEARS_2);
                events.RescheduleEvent(EVENT_SUN_3, 10000ms);
                break;
            case EVENT_SUN_3:
                instance->SetData(TYPE_SET_SUNS_SELECTABLE, 0);
                events.RescheduleEvent(EVENT_SUN_4, 4000ms);

                for (auto& guid : sunList)
                {
                    if (auto sun = ObjectAccessor::GetCreature(*me, guid))
                    {
                        sun->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        sun->CastSpell(sun, 111737, false);
                        sun->SetReactState(REACT_AGGRESSIVE);
                    }
                }

                if (auto zao = ObjectAccessor::GetCreature(*me, zaoGUID))
                    zao->AI()->Talk(1);
                break;
            case EVENT_SUN_4:
                me->SummonCreature(58815, 869.842f, -2454.816f, 179.6329f, 3.281219f);
                me->SummonCreature(58815, 865.658f, -2465.134f, 185.978f, 3.281219f);
                me->SummonCreature(58815, 859.8316f, -2483.79f, 176.3861f, 0.0f);
                me->SummonCreature(58815, 860.3246f, -2438.941f, 176.3861f, 3.281219f);
                me->SummonCreature(58815, 825.2917f, -2453.651f, 176.3861f, 3.281219f);

                me->SetWalk(false);
                me->GetMotionMaster()->MovePoint(3, 833.096f, -2494.71f, 179.9889f, FORCED_MOVEMENT_NONE, 0.f, 8.0f, false);
                Talk(EVENT_TALK_ZAO_APPEARS_4);
                break;
            case EVENT_STRIFE_0:
                me->SetFacingTo(1.23726f);
                me->SummonCreature(CREATURE_OSONG, 847.9601f, -2450.481f, 175.0443f, 4.409542f);
                me->SummonCreature(CREATURE_STRIFE, 847.530f, -2469.184f, 174.960f, 1.525f);
                me->SummonCreature(CREATURE_PERIL, 836.906f, -2465.859f, 174.960f, 1.014f);
                events.RescheduleEvent(EVENT_STRIFE_1, 11000ms);
                break;
            case EVENT_STRIFE_1:
                Talk(EVENT_TALK_STRIFE_0);
                events.RescheduleEvent(EVENT_STRIFE_2, 9000ms);
                break;
            case EVENT_STRIFE_2:
                Talk(EVENT_TALK_STRIFE_1);
                me->GetMotionMaster()->MovePoint(1, 827.9868f, -2456.078f, 176.6194f);
                break;
            case EVENT_STRIFE_3:
                Talk(EVENT_TALK_STRIFE_2);
                events.RescheduleEvent(EVENT_STRIFE_4, 9000ms);
                break;
            case EVENT_STRIFE_4:
                Talk(EVENT_TALK_STRIFE_3);
                break;
            case EVENT_19:
                Talk(15);
                me->GetMotionMaster()->MoveTargetedHome();
                events.RescheduleEvent(EVENT_20, 11000ms);
                break;
            case EVENT_20:
                Talk(16);
                events.RescheduleEvent(EVENT_21, 6000ms);
                break;
            case EVENT_21:
                Talk(17);
                DoCast(122715);
                me->DespawnOrUnsummon(10000ms);
                break;
            }
        }
    }
};

struct mob_sun : public BossAI
{
    explicit mob_sun(Creature* creature) : BossAI(creature, BOSS_SUN)
    {
        DoCast(SPELL_SUN);
        DoCast(SPELL_GROW_LOW);
        me->AddUnitState(UNIT_STATE_ROOT);
        me->SetDisableGravity(true);
    }

    void DoAction(int32 const action) override
    {
        switch (action)
        {
        case TYPE_SET_SUNS_SELECTABLE:
            events.RescheduleEvent(EVENT_1, 2000ms);
            break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        (void)0; // instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // no encounter frame in 3.3.5
        instance->SetData(TYPE_NUMBER_SUN_DEFEATED, 1);
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                DoCast(SPELL_SUNFIRE_RAYS);
                events.RescheduleEvent(EVENT_1, 5000ms);
                break;
            }
        }
    }
};

struct mob_zao : public BossAI
{
    explicit mob_zao(Creature* creature) : BossAI(creature, BOSS_ZAO_SUNSEEKER)
    {
        isCorrupted = false;
        eventDone = false;
    }

    GuidList suns;
    bool isCorrupted;
    bool eventDone;

    void Reset() override
    {
        _Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        _JustEngagedWith();
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();

        if (auto owner = me->GetCharmerOrOwner())
            owner->GetAI()->DoAction(ACTION_5);
    }

    void DoAction(int32 const action) override
    {
        switch (action)
        {
        case TYPE_ZAO_ENTER_COMBAT:
            events.RescheduleEvent(EVENT_ZAO_ATTACK, 1000ms);
            break;
        case ACTION_3:
            if (!eventDone)
            {
                Talk(0);
                eventDone = true;
                me->SetFaction(14);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                DoCast(SPELL_SHA_CORRUPTION_2);
                events.RescheduleEvent(EVENT_3, 2000ms);
                me->SetControlled(false, UNIT_STATE_ROOT);

                if (auto owner = me->GetCharmerOrOwner())
                    owner->GetAI()->DoAction(ACTION_6);

                if (auto player = me->SelectNearestPlayer(50.0f))
                    AttackStart(player);
            }
            break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (suns.empty())
        {
            std::list<Creature*> searcher;
            GetCreatureListWithEntryInGrid(searcher, me, CREATURE_SUN, 50.0f);

            if (searcher.empty())
                return;

            for (auto& cre : searcher)
                suns.push_back(cre->GetGUID());

            events.RescheduleEvent(EVENT_ZAO_ATTACK, 15000ms);
        }

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_ZAO_ENTER_COMBAT_2:
                events.RescheduleEvent(EVENT_ZAO_ATTACK, 1000ms);
                break;
            case EVENT_ZAO_ATTACK:
                if (!suns.empty())
                {
                    uint32 rand = urand(0, suns.size());
                    ObjectGuid guid_target;
                    for (GuidList::const_iterator guid = suns.begin(); guid != suns.end(); ++guid)
                    {
                        if (rand == 0)
                        {
                            guid_target = *guid;
                            break;
                        }
                        --rand;
                    }
                    if (auto target = me->GetInstanceScript()->instance->GetCreature(guid_target))
                        DoCast(target, SPELL_SHOOT_SUN, false);
                    else
                        suns.remove(guid_target);

                    events.RescheduleEvent(EVENT_ZAO_ATTACK, 3000ms);
                }
                break;
                case EVENT_3:
                    if (auto target = SelectTarget(SelectTargetMethod::Random, 0, 100.0f, true))
                        DoCast(target, 113017, false);

                    events.RescheduleEvent(EVENT_3, 1200ms);
                    break;
            }
        }
    }
};

struct mob_haunting_sha : public BossAI
{
    explicit mob_haunting_sha(Creature* creature) : BossAI(creature, BOSS_ZAO_SUNSEEKER)
    {
        me->SetFaction(14);
    }

    void JustEngagedWith(Unit* /*unit*/) override
    {
        events.RescheduleEvent(EVENT_1, 1000ms);
    }

    void DoAction(int32 const action) override
    {
        if (action == 0)
        {
            if (ObjectGuid guid = me->GetInstanceScript()->GetGuidData(CREATURE_ZAO_SUNSEEKER))
                if (auto zao = me->GetMap()->GetCreature(guid))
                    me->GetMotionMaster()->MoveFollow(zao, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        }
    }

    void MovementInform(uint32 type, uint32 data) override
    {
        if (type == FOLLOW_MOTION_TYPE)
        {
            if (ObjectGuid guid = me->GetInstanceScript()->GetGuidData(CREATURE_ZAO_SUNSEEKER))
            {
                if (auto zao = me->GetMap()->GetCreature(guid))
                {
                    me->DespawnOrUnsummon();
                    zao->AI()->DoAction(ACTION_3);
                }
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 114646, false);

                events.RescheduleEvent(EVENT_1, 2000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

struct mob_strife : public BossAI
{
    explicit mob_strife(Creature* creature) : BossAI(creature, BOSS_STRIFE)
    {
        timer_intensity = 2000;
        timer_dissipation = 2000;
        countIntensity = 0;
        hasBeenHit = false;
    }

    uint32 timer_dissipation;
    uint32 timer_intensity;
    int32 countIntensity;
    bool hasBeenHit;

    void Reset() override
    {
        _Reset();
    }

    void DamageTaken(Unit* /*unit*/, uint32& /*damage*/, DamageEffectType /*dmgType*/, SpellSchoolMask) override
    {
        timer_dissipation = 2000;
        hasBeenHit = true;
    }

    void JustEngagedWith(Unit* /*unit*/) override
    {
        _JustEngagedWith();
        events.RescheduleEvent(EVENT_1, 1000ms);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();

        if (auto owner = me->GetCharmerOrOwner())
            owner->GetAI()->DoAction(ACTION_4);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (timer_dissipation <= diff)
        {
            me->RemoveAuraFromStack(SPELL_INTENSITY);

            if (!me->HasAura(SPELL_INTENSITY))
                me->AddAura(SPELL_DISSIPATION, me);

            timer_dissipation = 2000;
            --countIntensity;

            if (countIntensity == -10)
                countIntensity = -10;
        }
        else
            timer_dissipation -= diff;

        if (timer_intensity <= diff)
        {
            if (hasBeenHit)
            {
                me->RemoveAuraFromStack(SPELL_DISSIPATION);

                if (!me->HasAura(SPELL_DISSIPATION))
                    me->AddAura(SPELL_INTENSITY, me);

                ++countIntensity;

                if (countIntensity == 10)
                {
                    DoCast(SPELL_ULTIMATE_POWER);
                    me->RemoveAura(SPELL_INTENSITY);
                }

                if (countIntensity > 10)
                    countIntensity = 10;
            }

            hasBeenHit = false;
            timer_intensity = 2000;
        }
        else
            timer_intensity -= diff;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, SPELL_AGONY, false);

                events.RescheduleEvent(EVENT_1, 2000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

struct mob_peril : public BossAI
{
    explicit mob_peril(Creature* creature) : BossAI(creature, BOSS_PERIL)
    {
        me->SetFaction(14);
        timer_intensity = 2000;
        timer_dissipation = 2000;
        countIntensity = 0;
        hasBeenHit = false;
    }

    uint32 timer_dissipation;
    uint32 timer_intensity;
    int32 countIntensity;
    bool hasBeenHit;

    void Reset() override
    {
        _Reset();
    }

    void DamageTaken(Unit* /*unit*/, uint32& /*damage*/, DamageEffectType /*dmgType*/, SpellSchoolMask) override
    {
        timer_dissipation = 2000;
        hasBeenHit = true;
    }

    void JustEngagedWith(Unit* /*unit*/) override
    {
        _JustEngagedWith();
        events.RescheduleEvent(EVENT_1, 1000ms);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();

        if (auto owner = me->GetCharmerOrOwner())
            owner->GetAI()->DoAction(ACTION_4);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (timer_dissipation <= diff)
        {
            me->RemoveAuraFromStack(SPELL_INTENSITY);

            if (!me->HasAura(SPELL_INTENSITY))
                me->AddAura(SPELL_DISSIPATION, me);

            timer_dissipation = 2000;
            --countIntensity;

            if (countIntensity == -10)
                countIntensity = -10;
        }
        else
            timer_dissipation -= diff;

        if (timer_intensity <= diff)
        {
            if (hasBeenHit)
            {
                me->RemoveAuraFromStack(SPELL_DISSIPATION);

                if (!me->HasAura(SPELL_DISSIPATION))
                    me->AddAura(SPELL_INTENSITY, me);

                ++countIntensity;

                if (countIntensity == 10)
                {
                    DoCast(SPELL_ULTIMATE_POWER);
                    me->RemoveAura(SPELL_INTENSITY);
                }

                if (countIntensity > 10)
                    countIntensity = 10;
            }

            hasBeenHit = false;
            timer_intensity = 2000;
        }
        else
            timer_intensity -= diff;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, SPELL_AGONY, false);

                events.RescheduleEvent(EVENT_1, 2000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

struct mob_nodding_tiger : public ScriptedAI
{
    explicit mob_nodding_tiger(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void JustEngagedWith(Unit* /*unit*/) override
    {
        events.RescheduleEvent(EVENT_1, 2000ms);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 31289, false);

                events.RescheduleEvent(EVENT_1, 3000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

struct mob_golden_beetle : public ScriptedAI
{
    explicit mob_golden_beetle(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void JustEngagedWith(Unit* /*unit*/) override
    {
        events.RescheduleEvent(EVENT_1, 2000ms);
        events.RescheduleEvent(EVENT_2, 4000ms);
        events.RescheduleEvent(EVENT_3, 6000ms);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 128051, false);

                events.RescheduleEvent(EVENT_1, 10000ms);
                break;
            case EVENT_2:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 88023, false);

                events.RescheduleEvent(EVENT_2, 5000ms);
                break;
            case EVENT_3:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 31589, false);

                events.RescheduleEvent(EVENT_3, 15000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

struct mob_jiang_xiang : public ScriptedAI
{
    explicit mob_jiang_xiang(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void JustEngagedWith(Unit* /*unit*/) override
    {
        events.RescheduleEvent(EVENT_1, 2000ms);
        events.RescheduleEvent(EVENT_2, 4000ms);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 114805, false);

                events.RescheduleEvent(EVENT_1, 10000ms);
                break;
            case EVENT_2:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 114803, false);

                events.RescheduleEvent(EVENT_2, 5000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

struct mob_songbird_queen : public ScriptedAI
{
    explicit mob_songbird_queen(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void JustEngagedWith(Unit* /*unit*/) override
    {
        events.RescheduleEvent(EVENT_1, 2000ms);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 114826, false);

                events.RescheduleEvent(EVENT_1, 10000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

struct mob_talking_fish : public ScriptedAI
{
    explicit mob_talking_fish(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void JustEngagedWith(Unit* /*unit*/) override
    {
        Talk(urand(0, 3));
        events.RescheduleEvent(EVENT_1, 2000ms);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_1:
                if (auto victim = me->GetVictim())
                    DoCast(victim, 114811, false);

                events.RescheduleEvent(EVENT_1, 10000ms);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }
};

void AddSC_boss_lorewalker_stonestep()
{
    RegisterCreatureAI(boss_lorewalker_stonestep);
    RegisterCreatureAI(mob_zao);
    RegisterCreatureAI(mob_sun);
    RegisterCreatureAI(mob_haunting_sha);
    RegisterCreatureAI(mob_strife);
    RegisterCreatureAI(mob_peril);
    RegisterCreatureAI(mob_nodding_tiger);
    RegisterCreatureAI(mob_golden_beetle);
    RegisterCreatureAI(mob_jiang_xiang);
    RegisterCreatureAI(mob_songbird_queen);
    //RegisterCreatureAI(mob_talking_fish);
}