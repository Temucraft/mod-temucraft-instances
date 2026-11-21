/*
 * Copyright (C) 2008-2012 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
 * with this program. If not, see <https://www.gnu.org/licenses/>.
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

#include "CreatureGroups.h"
#include "CreatureTextMgr.h"
#include "GameObjectAI.h"
#include "ScriptedEscortAI.h"
#include "siege_of_orgrimmar.h"

// UPDATE `creature` SET `spawnMask` = '16632' WHERE map = 1136;
enum eSpells
{
    SPELL_SUBMERGE                  = 103742, //sha spawn
    SPELL_MANIFESTATION_SPAWN       = 144778, //Manifestation Spawn
    SPELL_SELF_REFLECTION_SPAWN     = 144784, //Self-Reflection
    SPELL_PRIDE                     = 144343,

    SPELL_CORRUPTED_PRISON_WEST     = 144574, //Corrupted Prison
    SPELL_CORRUPTED_PRISON_EAST     = 144636, //Corrupted Prison
    SPELL_CORRUPTED_PRISON_NORTH    = 144683, //Corrupted Prison 25ppl
    SPELL_CORRUPTED_PRISON_SOUTH    = 144684, //Corrupted Prison 25ppl
    SPELL_CORRUPTED_PRISON_KNOCK    = 144615, //Corrupted Prison

    SPELL_IMPRISON                  = 144563, //Imprison
    SPELL_MARK_OF_ARROGANCE         = 144351, //Mark of Arrogance
    SPELL_REACHING_ATTACK           = 144774, //Reaching Attack 119775
    SPELL_SELF_REFLECTION           = 144800, //Self-Reflection
    SPELL_WOUNDED_PRIDE             = 144358, //Wounded Pride

    SPELL_UNLEASHED                 = 144832, //Unleashed

    //Pride
    SPELL_SWELLING_PRIDE            = 144400, //Swelling Pride
    SPELL_BURSTING_PRIDE            = 144910, //Bursting Pride  25-49
    SPELL_BURSTING_PRIDE_DMG        = 144911,
    SPELL_PROJECTION                = 146822, //Projection      50-74
    SPELL_PROJECTION_MARKER         = 145066,
    SPELL_PROJECTION_DMG            = 145320,
    SPELL_AURA_OF_PRIDE             = 146817, //Aura of Pride   75-99
    SPELL_OVERCOME                  = 144843, //Overcome        100 
    SPELL_OVERCOME_MIND_CONTROL     = 144863,
    
    //Manifestation of Pride
    SPELL_MOCKING_BLAST             = 144379, //Mocking Blast + 5power
    SPELL_LAST_WORD                 = 144370, //Last Word     + 5power 2 nearest players

    //Norushen
    SPELL_DOOR_CHANNEL              = 145979, //Door Channel
    SPELL_FINAL_GIFT                = 144854, //Final Gift
    SPELL_GIFT_OF_THE_TITANS_BASE   = 146595,
    SPELL_GIFT_OF_THE_TITANS        = 144359, //Gift of the Titans
    SPELL_POWER_OF_THE_TITANS       = 144364, //Power of the Titans

    //Lingering Corruption
    SPELL_CORRUPTION_TOUCH          = 149207, //Corrupted Touch

    //Reflection
    SPELL_SELF_REFLECTION_CAST      = 144788, //Self-Reflection

    //Rift of Corruption
    SPELL_RIFT_OF_CORRUPTION        = 147199, //Rift of Corruption
    SPELL_UNSTABLE_CORRUPTION       = 147389, //Unstable Corruption
    SPELL_RIFT_OF_CORRUPTION_AT     = 147205,
    SPELL_RIFT_OF_CORRUPTION_DMG    = 147391,
    SPELL_RIFT_OF_CORRUPTION_TR_DMG = 147198,
    SPELL_WEAKENED_RESOLVE          = 147207, //Weakened Resolve

    //
    SPELL_ORB_OF_LIGHT              = 145345, //Orb of Light

    //�������� ���� �� ������       145215
    //�������� ����� ��� ���������  145299
    //������������ �������          72569 - ���� 145684 AnimKitID: 1615
    //����������� �������           73972 - ���� 149027
};

Position const Sha_of_pride_taranzhu  = {748.1805f, 1058.264f, 356.1557f, 5.566918f };
Position const Sha_of_pride_finish_jaina  = {765.6154f, 1050.112f, 357.0135f, 1.514341f };
Position const Sha_of_pride_finish_teron  = {756.955f, 1048.71f, 357.0236f, 1.68638f };

//Manifestation of Pride
Position const Sha_of_pride_manifestation[3]  =
{
    {735.12f, 1174.49f, 356.0720f, 4.8904f},
    {686.34f, 1099.86f, 356.0709f, 0.1859f},
    {809.97f, 1126.04f, 356.0724f, 3.3118f},
};

uint32 const prison[4] = { GO_CORRUPTED_PRISON_WEST, GO_CORRUPTED_PRISON_EAST, GO_CORRUPTED_PRISON_NORTH, GO_CORRUPTED_PRISON_SOUTH };
uint32 const prison_spell[4] = { SPELL_CORRUPTED_PRISON_WEST, SPELL_CORRUPTED_PRISON_EAST, SPELL_CORRUPTED_PRISON_NORTH, SPELL_CORRUPTED_PRISON_SOUTH };
uint32 const prisonbutton[12] = 
{ GO_CORRUPTED_BUTTON_WEST_1, GO_CORRUPTED_BUTTON_WEST_2, GO_CORRUPTED_BUTTON_WEST_3, GO_CORRUPTED_BUTTON_EAST_1, GO_CORRUPTED_BUTTON_EAST_2,
  GO_CORRUPTED_BUTTON_EAST_3, GO_CORRUPTED_BUTTON_NORTH_1, GO_CORRUPTED_BUTTON_NORTH_2, GO_CORRUPTED_BUTTON_NORTH_3, GO_CORRUPTED_BUTTON_SOUTH_1,
  GO_CORRUPTED_BUTTON_SOUTH_2, GO_CORRUPTED_BUTTON_SOUTH_3 };

enum PhaseEvents
{
    EVENT_SPELL_MARK_OF_ARROGANCE       = 1,    
    EVENT_SPELL_WOUNDED_PRIDE           = 2,
    EVENT_SUMMON_MANIFESTATION_OF_PRIDE = 3,
    EVENT_SPELL_SELF_REFLECTION         = 4,
    EVENT_SPELL_CORRUPTED_PRISON        = 5,
    EVENT_SPELL_GIFT_OF_THE_TITANS      = 7,
    EVENT_PRIDE_GENERATION              = 8,
    EVENT_RIFT_OF_CORRUPTION            = 10,
    EVENT_SPELL_RIFT_OF_CORRUPTION_AT   = 11,
    EVENT_SPELL_RIFT_OF_CORRUPTION_DMG  = 12,
};

enum Phases
{
    PHASE_BATTLE                        = 1,
};

enum SActions
{
    ACTION_CLOSE_RIFT_OF_CORRUPTION     = 1,
};

class TankFilter
{
public:
    bool operator()(WorldObject* unit)
    {
        if (Player* player = unit->ToPlayer())
            if (!player->HasTankSpec())
                return false;
        return true;
    }
};

uint32 corruptedprisonlist[4] =
{
    SPELL_CORRUPTED_PRISON_WEST,
    SPELL_CORRUPTED_PRISON_EAST,
    SPELL_CORRUPTED_PRISON_NORTH,
    SPELL_CORRUPTED_PRISON_SOUTH,
};

class RiftOfCorruptionFilter
{
public:
    bool operator()(WorldObject* unit)
    {
        if (Player* target = unit->ToPlayer())
            for (uint8 n = 0; n < 4; n++)
                if (target->HasAura(corruptedprisonlist[n]))
                    return true;
        return false;
    }
};

uint8 selfreflectionstage[4] =
{
    25,
    50,
    75,
    100,
};

class boss_sha_of_pride : public CreatureScript
{
    public:
        boss_sha_of_pride() : CreatureScript("boss_sha_of_pride") {}

        struct boss_sha_of_prideAI : public BossAI
        {
            boss_sha_of_prideAI(Creature* creature) : BossAI(creature, DATA_SHA_OF_PRIDE)
            {
                instance = creature->GetInstanceScript();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->SetCombatMovement(false);
            }

            InstanceScript* instance;
            uint32 checkvictim;
            bool bPhaseLowHp;

            void Reset()
            {
                _Reset();
                me->SetReactState(REACT_DEFENSIVE);
                //Debug
                /*me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->SetCombatMovement(false);
                me->AddAura(SPELL_SUBMERGE, me);
                me->SetVisible(true);
                DoCast(me, SPELL_SUBMERGE, false);*/
                checkvictim = 0;
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_PRIDE);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_OVERCOME);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MARK_OF_ARROGANCE);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_WEST);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_EAST);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_NORTH);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_SOUTH);
                me->RemoveAurasDueToSpell(SPELL_UNLEASHED);
                me->setPowerType(POWER_ENERGY);
                me->SetMaxPower(POWER_ENERGY, 100);
                me->SetPower(POWER_ENERGY, 0);
                bPhaseLowHp = false;
                if (Creature* norushen = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_NORUSHEN)))
                    norushen->Respawn();
                (void)0; // instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // no encounter frame in 3.3.5
                for (uint8 i = 0; i < 12; ++i)
                    if (GameObject* prisonGo = instance->instance->GetGameObject(instance->GetGuidData(prisonbutton[i])))
                        prisonGo->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
            }

            void SetData(uint32 id, uint32 value)
            {
                //event after killing all NPC_LINGERING_CORRUPTION. Appear of Sha.
                if (id == NPC_LINGERING_CORRUPTION)
                {
                    Talk(TEXT_GENERIC_0);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->SetCombatMovement(false);
                    //me->SetUnitMovementFlags(1536);
                    //me->AddExtraUnitMovementFlag(15);
                    //me->GetMotionMaster()->MoveLand(0, *me);
                    me->AddAura(SPELL_SUBMERGE, me);
                    me->SetVisible(true);
                    DoCast(me, SPELL_SUBMERGE, false);
                }
            }

            void KilledUnit(Unit* who) 
            {
                if (who->ToPlayer())
                    Talk(urand(TEXT_GENERIC_9, TEXT_GENERIC_10));
            }

            void JustEngagedWith(Unit* who)
            {
                _JustEngagedWith();
                (void)0; // instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // no encounter frame in 3.3.5
                Talk(TEXT_GENERIC_1);
                events.SetPhase(PHASE_BATTLE);
                checkvictim = 1500;
                if (IsHeroic())
                    events.RescheduleEvent(EVENT_RIFT_OF_CORRUPTION, 8000ms, 0, PHASE_BATTLE);
                events.RescheduleEvent(EVENT_SPELL_GIFT_OF_THE_TITANS, 1000ms, 0, PHASE_BATTLE);
                events.RescheduleEvent(EVENT_SPELL_WOUNDED_PRIDE, 3000ms, 0, PHASE_BATTLE);
                events.RescheduleEvent(EVENT_SPELL_MARK_OF_ARROGANCE, 2000ms, 0, PHASE_BATTLE);
                events.RescheduleEvent(EVENT_SPELL_SELF_REFLECTION, 20000ms, 0, PHASE_BATTLE);
                events.RescheduleEvent(EVENT_SPELL_CORRUPTED_PRISON, 45000ms, 0, PHASE_BATTLE);
                events.RescheduleEvent(EVENT_SUMMON_MANIFESTATION_OF_PRIDE, 60000ms, 0, PHASE_BATTLE);
                events.RescheduleEvent(EVENT_PRIDE_GENERATION, 4000ms);
                Map::PlayerList const& PlayerList = instance->instance->GetPlayers();
                if (!PlayerList.IsEmpty())
                    for (Map::PlayerList::const_iterator Itr = PlayerList.begin(); Itr != PlayerList.end(); ++Itr)
                        if (Player* player = Itr->GetSource())
                            if (player->IsAlive())
                                DoCast(player, SPELL_PRIDE, true);
            }

            void DamageTaken(Unit* attacker, uint32 &damage, DamageEffectType dmgType)
            {
                if (me->HealthBelowPct(30) && !bPhaseLowHp)
                {
                    bPhaseLowHp = true;
                    me->InterruptNonMeleeSpells(true);
                    events.CancelEvent(EVENT_SPELL_GIFT_OF_THE_TITANS);
                    if (Creature* nor = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_SHA_NORUSHEN)))
                    {
                        Talk(TEXT_GENERIC_8);
                        DoCast(nor, SPELL_UNLEASHED);
                    }
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                (void)0; // instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // no encounter frame in 3.3.5
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_PRIDE);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_OVERCOME);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MARK_OF_ARROGANCE);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_WEST);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_EAST);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_NORTH);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_PRISON_SOUTH);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (checkvictim)
                {
                    if (checkvictim <= diff)
                    {
                        if (me->GetVictim() && !me->IsWithinMeleeRange(me->GetVictim()))
                            DoCastVictim(SPELL_REACHING_ATTACK, true);
                        checkvictim = 1500;
                    }
                    else
                        checkvictim -= diff;
                }
                
                (CheckEvadeIfOutOfCombatArea() ? (EnterEvadeMode(), true) : false);
                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_SPELL_MARK_OF_ARROGANCE:
                            DoCast(me, SPELL_MARK_OF_ARROGANCE);
                            events.RescheduleEvent(EVENT_SPELL_MARK_OF_ARROGANCE, 20000ms, 0, PHASE_BATTLE);
                            break;
                        case EVENT_PRIDE_GENERATION:
                            me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 5);
                            if (me->GetPower(POWER_ENERGY) == 100)
                            {
                                Talk(TEXT_GENERIC_12);
                                Talk(urand(TEXT_GENERIC_5, TEXT_GENERIC_6));
                                DoCast(me, SPELL_SWELLING_PRIDE, false);
                            }
                            events.RescheduleEvent(EVENT_PRIDE_GENERATION, 4000ms);
                            break;
                        case EVENT_SPELL_WOUNDED_PRIDE:
                            DoCastVictim(SPELL_WOUNDED_PRIDE);
                            events.RescheduleEvent(EVENT_SPELL_WOUNDED_PRIDE, 30000ms, 0, PHASE_BATTLE);
                            break;
                        case EVENT_SPELL_SELF_REFLECTION:
                            Talk(TEXT_GENERIC_4);
                            DoCast(me, SPELL_SELF_REFLECTION, false);
                            events.RescheduleEvent(EVENT_SPELL_SELF_REFLECTION, 60000ms, 0, PHASE_BATTLE);
                            break;
                        case EVENT_SPELL_CORRUPTED_PRISON:
                        {
                            Talk(TEXT_GENERIC_11);
                            Talk(TEXT_GENERIC_3);
                            DoCast(me, SPELL_IMPRISON, true);
                            uint8 maxcount = Is25ManRaid() ? 3 : 1;
                            uint8 i = 0;
                            std::list<Player*> targetList;
                            targetList.clear();
                            GetPlayerListInGrid(targetList, me, 80.0f);
                            targetList.remove_if(TankFilter());
                            for (std::list<Player*>::iterator itr = targetList.begin(); itr != targetList.end(); itr++, i++)
                            {
                                if (GameObject* prisonGo = instance->instance->GetGameObject(instance->GetGuidData(prison[i])))
                                {
                                    me->CastSpell(prisonGo->GetPositionX(), prisonGo->GetPositionY(), prisonGo->GetPositionZ(), SPELL_CORRUPTED_PRISON_KNOCK, false);
                                    prisonGo->AI()->SetGUID((*itr)->GetGUID(), false);
                                    DoCast(*itr, prison_spell[i], true);
                                    if (i == maxcount)
                                        break;
                                }
                            }
                            events.RescheduleEvent(EVENT_SPELL_CORRUPTED_PRISON, 60000ms, 0, PHASE_BATTLE);
                            break;
                        }
                        case EVENT_SUMMON_MANIFESTATION_OF_PRIDE:
                        {
                            uint8 count = Is25ManRaid() ? 2 : 1;
                            if (count == 1)
                                me->SummonCreature(NPC_MANIFEST_OF_PRIDE, Sha_of_pride_manifestation[0], TEMPSUMMON_DEAD_DESPAWN);
                            else
                                for (uint8 i = 1; i <= count; i++)
                                    me->SummonCreature(NPC_MANIFEST_OF_PRIDE, Sha_of_pride_manifestation[i], TEMPSUMMON_DEAD_DESPAWN);
                            events.RescheduleEvent(EVENT_SUMMON_MANIFESTATION_OF_PRIDE, 60000ms, 0, PHASE_BATTLE);
                            break;
                        }
                        case EVENT_SPELL_GIFT_OF_THE_TITANS:
                            DoCast(me, SPELL_GIFT_OF_THE_TITANS_BASE);
                            events.RescheduleEvent(EVENT_SPELL_GIFT_OF_THE_TITANS, 25000ms, 0, PHASE_BATTLE);
                            break;
                        case EVENT_RIFT_OF_CORRUPTION:
                        {
                            float x, y;
                            GetPosInRadiusWithRandomOrientation(me, 55.0f, x, y);
                            me->SummonCreature(NPC_RIFT_OF_CORRUPTION, x, y, me->GetPositionZ(), 0.0f);
                            events.RescheduleEvent(EVENT_RIFT_OF_CORRUPTION, 8000ms, 0, PHASE_BATTLE);
                            break;
                        }
                    }
                }
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_sha_of_prideAI(creature);
        }
};

class npc_sha_of_pride_norushen : public CreatureScript
{
public:
    npc_sha_of_pride_norushen() : CreatureScript("npc_sha_of_pride_norushen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sha_of_pride_norushenAI (creature);
    }

    struct npc_sha_of_pride_norushenAI : public npc_escortAI
    {
        npc_sha_of_pride_norushenAI(Creature* creature) : npc_escortAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        std::set<ObjectGuid> _gift;
        InstanceScript* instance;
        EventMap events;
        bool start;

        void Reset() override
        {
            start = false;
            _gift.clear();
        }
        
        void JustRespawned() override
        {
            start = true;
        }
        
        void MoveInLineOfSight(Unit* who) override
        {
            if (start)return;
            start = true;

            Talk(TEXT_GENERIC_0, me);
            Start(false);
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_UNLEASHED)
            {
                DoCast(me, SPELL_FINAL_GIFT, false);
                Talk(TEXT_GENERIC_4);
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell) override
        {
            if (target->GetTypeId() != TYPEID_PLAYER || spell->Id != SPELL_GIFT_OF_THE_TITANS)
                return;

            _gift.insert(target->GetGUID());
        }

        void SetGUID(ObjectGuid const& guid, int32 id) override
        {
            _gift.erase(guid);
        }

        void SetData(uint32 id, uint32 value) override
        {
            //event after killing all NPC_LINGERING_CORRUPTION. Appear of Sha.
            if (id == NPC_LINGERING_CORRUPTION)
            {
                instance->SetData(DATA_SHA_PRE_EVENT, DONE);
                Talk(TEXT_GENERIC_2);             //18:47:21.000 
                events.RescheduleEvent(EVENT_2, 11000ms);    //18:47:32.000
            }
            else if (id == SPELL_GIFT_OF_THE_TITANS)
            {
                Talk(TEXT_GENERIC_3);
                me->CastSpell(me, SPELL_GIFT_OF_THE_TITANS, true);
            }
            else if (id == EVENT_SPELL_GIFT_OF_THE_TITANS)
            {
                bool good = _gift.size() == value;
                for(std::set<ObjectGuid>::iterator itr = _gift.begin(); itr != _gift.end(); ++itr)
                {
                    Player* target = ObjectAccessor::FindPlayer(*itr);
                    if (!target)
                        continue;

                    if (good)
                        target->AddAura(SPELL_POWER_OF_THE_TITANS, target);
                    else
                        target->RemoveAura(SPELL_POWER_OF_THE_TITANS);
                }
            }
        }

        void WaypointReached(uint32 i) override
        {
            switch(i)
            {
                case 4:
                    SetEscortPaused(true);
                    DoCast(me, SPELL_DOOR_CHANNEL, false);
                    //
                    if (GameObject* door = instance->instance->GetGameObject(instance->GetGuidData(GO_NORUSHEN_EX_DOOR)))
                        door->SetGoState(GO_STATE_ACTIVE);
                    events.RescheduleEvent(EVENT_1, 2000ms);
                    break;
                case 5:
                    if (Creature* lo = instance->instance->GetCreature(instance->GetGuidData(NPC_LOREWALKER_CHO3)))
                        lo->AI()->DoAction(EVENT_1);
                    SetEscortPaused(true);
                    Talk(TEXT_GENERIC_1, me);
                    //Start pre-event 
                    instance->SetData(DATA_SHA_PRE_EVENT, IN_PROGRESS);

                    // WARNING!! T M P !!!!!!
                    //SetData(NPC_LINGERING_CORRUPTION, true);
                    break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            npc_escortAI::UpdateAI(diff);
            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_1:
                    SetEscortPaused(false);
                    break;
                case EVENT_2:
                    if (Creature* sha = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE)))
                        sha->AI()->SetData(NPC_LINGERING_CORRUPTION, DONE); 
                    break;
                }
            }
        }
    };
};

class npc_sha_of_pride_lowerwalker : public CreatureScript
{
public:
    npc_sha_of_pride_lowerwalker() : CreatureScript("npc_sha_of_pride_lowerwalker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sha_of_pride_lowerwalkerAI (creature);
    }

    struct npc_sha_of_pride_lowerwalkerAI : public npc_escortAI
    {
        npc_sha_of_pride_lowerwalkerAI(Creature* creature) : npc_escortAI(creature)
        {
            instance = creature->GetInstanceScript();
            (void)0; // group_member = sFormationMgr->CreateCustomFormation(me); // not in 3.3.5
            end = false;
        }

        InstanceScript* instance;
        EventMap events;
        FormationInfo* group_member;
        bool end;

        void Reset(){}

        void DoAction(int32 const action)
        {
            switch(action)
            {
                case EVENT_1:
                    SetEscortPaused(false);
                    break;
                case EVENT_2:
                    end = true;     //19:34:01
                    uint32 t = 0;
                    events.RescheduleEvent(EVENT_7, Milliseconds(t+= 2000));   //19:34:01
                    events.RescheduleEvent(EVENT_8, Milliseconds(t+= 11000));  //19:34:13.000
                    events.RescheduleEvent(EVENT_9, Milliseconds(t+= 10000));  //19:34:23.000
                    events.RescheduleEvent(EVENT_10, Milliseconds(t+= 4000));  //19:34:27.000
                    events.RescheduleEvent(EVENT_16, Milliseconds(t+= 3000));  //19:34:30.000
                    events.RescheduleEvent(EVENT_11, Milliseconds(t+= 4000));  //19:34:33.000
                    events.RescheduleEvent(EVENT_12, Milliseconds(t+= 9000));  //19:34:42.000
                    events.RescheduleEvent(EVENT_13, Milliseconds(t+= 5000));  //19:34:47.000
                    events.RescheduleEvent(EVENT_17, Milliseconds(t+= 12000));  //19:34:59.000
                    events.RescheduleEvent(EVENT_14, Milliseconds(t+= 5000)); //19:35:04.000
                    events.RescheduleEvent(EVENT_15, Milliseconds(t+= 20000)); //19:35:24.000
                    
                    if (Creature * c = instance->instance->SummonCreature(NPC_SHA_OF_PRIDE_END_LADY_JAINA, Sha_of_pride_finish_jaina))
                        c->GetMotionMaster()->MovePoint(c->GetGUID().GetCounter(), 756.9792f, 1093.34f, 356.0723f);
                    if (Creature * c = instance->instance->SummonCreature(NPC_SHA_OF_PRIDE_END_THERON, Sha_of_pride_finish_teron))
                        c->GetMotionMaster()->MovePoint(c->GetGUID().GetCounter(), 739.9184f, 1129.293f, 356.0723f);
                    break;
            }            
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!end)
                Start(false);
        }

        void WaypointReached(uint32 i)
        {
            switch(i)
            {
                case 5:
                    SetEscortPaused(true);
                    break;
                case 6:
                {
                    SetEscortPaused(true);
                    uint32 t = 0;
                    events.RescheduleEvent(EVENT_1, Milliseconds(t += 1000));    //18:45:18.000
                    events.RescheduleEvent(EVENT_3, Milliseconds(t += 5000));    //18:45:23.000 
                    events.RescheduleEvent(EVENT_2, Milliseconds(t += 1000));    //18:45:24.000
                    events.RescheduleEvent(EVENT_4, Milliseconds(t += 12000));   //18:45:36.000
                    events.RescheduleEvent(EVENT_5, Milliseconds(t += 11000));   //18:45:47.000
                    events.RescheduleEvent(EVENT_6, Milliseconds(t += 1));
                    //18:45:47.000
                    break;
                }
                case 16:
                    if (Creature* taran = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_TARAN_ZHU)))
                    {
                        if (CreatureGroup* f = me->GetFormation())
                        {
                            f->RemoveMember(taran);
                            f->RemoveMember(me);
                            delete group_member;
                        }
                        taran->DespawnOrUnsummon();
                    }
                    me->DespawnOrUnsummon();
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                    case EVENT_2:
                        if (Creature* taran = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_TARAN_ZHU)))
                            taran->AI()->Talk(eventId - 1, me);
                        break;
                    case EVENT_3:
                    case EVENT_4:
                    case EVENT_5:
                        if (Creature* taran = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_TARAN_ZHU)))
                            Talk(eventId - 3, taran);
                        break;
                    case EVENT_6:
                        me->SetWalk(true);
                        if (Creature* taran = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_TARAN_ZHU)))
                            if (CreatureGroup* f = me->GetFormation())
                                f->AddMember(taran);
                        SetEscortPaused(false);
                        break;
                    case EVENT_7:
                        Talk(TEXT_GENERIC_3);
                        //me->DespawnOrUnsummon(60000ms);
                        break;
                    case EVENT_8:
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                            jaina->AI()->Talk(TEXT_GENERIC_0);
                        break;
                    case EVENT_9:
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                            jaina->GetMotionMaster()->MovePoint(jaina->GetGUID().GetCounter(), 748.8203f, 1130.096f, 356.0723f);
                        if (Creature* teron = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_THERON)))
                            teron->AI()->Talk(TEXT_GENERIC_0);
                        break;
                    case EVENT_10:
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                            jaina->AI()->Talk(TEXT_GENERIC_1);
                        break;
                    case EVENT_11:
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                            jaina->AI()->Talk(TEXT_GENERIC_2);
                        break;
                    case EVENT_12:
                        if (Creature* teron = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_THERON)))
                            teron->AI()->Talk(TEXT_GENERIC_2);
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                            jaina->GetMotionMaster()->MovePoint(jaina->GetGUID().GetCounter(), 748.5174f, 1131.481f, 356.0723f);
                        break;
                    case EVENT_13:
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                            jaina->AI()->Talk(TEXT_GENERIC_3);
                        break;
                    case EVENT_17:
                        if (Creature* teron = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_THERON)))
                            teron->AI()->Talk(TEXT_GENERIC_3);
                        break;
                    case EVENT_14:
                        instance->SetData(DATA_SHA_OF_PRIDE, DONE);
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                        {
                            jaina->AI()->Talk(TEXT_GENERIC_4);
                            jaina->GetMotionMaster()->MovePoint(jaina->GetGUID().GetCounter(), 783.2882f, 1167.352f, 356.0717f);
                        }
                        if (Creature* teron = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_THERON)))
                        {
                            teron->GetMotionMaster()->MovePoint(teron->GetGUID().GetCounter(), 692.4531f, 1149.196f, 356.0718f);
                        }
                        break;
                    case EVENT_15:
                        if (Creature* jaina = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_LADY_JAINA)))
                        {
                            jaina->CastSpell(jaina, 51347, true);
                            jaina->DespawnOrUnsummon(5000ms);
                        }
                        if (Creature* teron = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_THERON)))
                        {
                            teron->CastSpell(teron, 51347, true);
                            teron->DespawnOrUnsummon(5000ms);
                        }
                        me->DespawnOrUnsummon(5000ms);
                        break;
                    case EVENT_16:
                        if (Creature* teron = instance->instance->GetCreature(instance->GetGuidData(NPC_SHA_OF_PRIDE_END_THERON)))
                            teron->AI()->Talk(TEXT_GENERIC_1);
                        break;
                }
            }
        }
    };
};

enum ACTION_CORUPTED_PRISON
{
    ACTION_CORUPTED_PRISON_ACTIVATE_KEY     = 1,
    ACTION_CORUPTED_PRISON_DEACTIVATE_KEY   = 2,
    ACTION_CORUPTED_PRISON_ENABLE           = 3,
};

class go_sha_of_pride_corupted_prison : public GameObjectScript
{
    public:
        go_sha_of_pride_corupted_prison() : GameObjectScript("go_sha_of_pride_corupted_prison") { }

        struct go_sha_of_pride_corupted_prisonAI : public GameObjectAI
        {
            go_sha_of_pride_corupted_prisonAI(GameObject* go) : GameObjectAI(go), _enableKeyCount(0)
            {
                instance = me->GetInstanceScript();

                switch(me->GetEntry())
                {
                    case GO_CORRUPTED_PRISON_WEST:
                        _key[0] = GO_CORRUPTED_BUTTON_WEST_1;
                        _key[2] = GO_CORRUPTED_BUTTON_WEST_3;
                        _key[1] = GO_CORRUPTED_BUTTON_WEST_2;
                        break;
                    case GO_CORRUPTED_PRISON_EAST:
                        _key[0] = GO_CORRUPTED_BUTTON_EAST_1;
                        _key[2] = GO_CORRUPTED_BUTTON_EAST_3;
                        _key[1] = GO_CORRUPTED_BUTTON_EAST_2;
                        break;
                    case GO_CORRUPTED_PRISON_NORTH:
                        _key[0] = GO_CORRUPTED_BUTTON_NORTH_1;
                        _key[2] = GO_CORRUPTED_BUTTON_NORTH_3;
                        _key[1] = GO_CORRUPTED_BUTTON_NORTH_2;
                        break;
                    case GO_CORRUPTED_PRISON_SOUTH:
                        _key[0] = GO_CORRUPTED_BUTTON_SOUTH_1;
                        _key[2] = GO_CORRUPTED_BUTTON_SOUTH_3;
                        _key[1] = GO_CORRUPTED_BUTTON_SOUTH_2;
                        break;
                }
            }

            void SetGUID(const ObjectGuid& guid, int32 /*id = 0 */)
            {
                _enableKeyCount = 0;
                _plrPrisonerGUID = guid;
                TemucraftEnableGo(me, true);
                if (me->GetMap()->Is25ManRaid())
                {
                    for (uint8 i = 0; i < 3; i++)
                        if (GameObject* buttons = instance->instance->GetGameObject(instance->GetGuidData(_key[i])))
                            buttons->AI()->DoAction(ACTION_CORUPTED_PRISON_ACTIVATE_KEY);
                }
                else
                {
                    for (uint8 i = 0; i < 2; ++i)
                        if (GameObject* buttons = instance->instance->GetGameObject(instance->GetGuidData(_key[i])))
                            buttons->AI()->DoAction(ACTION_CORUPTED_PRISON_ACTIVATE_KEY);
                    //last one should be activated
                    if (GameObject* buttons = instance->instance->GetGameObject(instance->GetGuidData(_key[2])))
                        buttons->AI()->DoAction(ACTION_CORUPTED_PRISON_ENABLE);
                }
            }

            void DoAction(const int32 param)
            {
                switch (param)
                {
                    case ACTION_CORUPTED_PRISON_DEACTIVATE_KEY:
                        --_enableKeyCount;
                        break;
                    case ACTION_CORUPTED_PRISON_ACTIVATE_KEY:
                        ++_enableKeyCount;
                        if (_enableKeyCount >= 3)
                        {
                            if (Player* player = ObjectAccessor::FindPlayer(_plrPrisonerGUID))
                            {
                                _plrPrisonerGUID.Clear();

                                player->RemoveAurasDueToSpell(SPELL_CORRUPTED_PRISON_WEST);
                                player->RemoveAurasDueToSpell(SPELL_CORRUPTED_PRISON_EAST);
                                player->RemoveAurasDueToSpell(SPELL_CORRUPTED_PRISON_NORTH);
                                player->RemoveAurasDueToSpell(SPELL_CORRUPTED_PRISON_SOUTH);
                                TemucraftEnableGo(me, false);
                                for(uint8 i = 0; i < 3; ++i)
                                {
                                    if (GameObject* buttons = instance->instance->GetGameObject(instance->GetGuidData(_key[i])))
                                        buttons->AI()->DoAction(ACTION_CORUPTED_PRISON_DEACTIVATE_KEY);
                                }
                            }
                        }
                        break;
                }
            }

        private:
            InstanceScript* instance;
            ObjectGuid _plrPrisonerGUID;
            uint32 _enableKeyCount;
            uint32 _key[3];
        };

        GameObjectAI* GetAI(GameObject* go) const
        {
            return new go_sha_of_pride_corupted_prisonAI(go);
        }
};

class go_sha_of_pride_corupted_prison_button : public GameObjectScript
{
    public:
        go_sha_of_pride_corupted_prison_button() : GameObjectScript("go_sha_of_pride_corupted_prison_button") { }

        struct go_sha_of_pride_corupted_prison_buttonAI : public GameObjectAI
        {
            go_sha_of_pride_corupted_prison_buttonAI(GameObject* go) : 
                GameObjectAI(me), ownerEntry(0)
            {
                TemucraftEnableGo(me, true);
                instance = me->GetInstanceScript();
                switch(me->GetEntry())
                {
                    case GO_CORRUPTED_BUTTON_WEST_1:
                    case GO_CORRUPTED_BUTTON_WEST_2:
                    case GO_CORRUPTED_BUTTON_WEST_3:
                        ownerEntry = GO_CORRUPTED_PRISON_WEST;
                        break;
                    case GO_CORRUPTED_BUTTON_EAST_1:
                    case GO_CORRUPTED_BUTTON_EAST_2:
                    case GO_CORRUPTED_BUTTON_EAST_3:
                        ownerEntry = GO_CORRUPTED_PRISON_EAST;
                        break;
                    case GO_CORRUPTED_BUTTON_NORTH_1:
                    case GO_CORRUPTED_BUTTON_NORTH_2:
                    case GO_CORRUPTED_BUTTON_NORTH_3:
                        ownerEntry = GO_CORRUPTED_PRISON_NORTH;
                        break;
                    case GO_CORRUPTED_BUTTON_SOUTH_1:
                    case GO_CORRUPTED_BUTTON_SOUTH_2:
                    case GO_CORRUPTED_BUTTON_SOUTH_3:
                        ownerEntry = GO_CORRUPTED_PRISON_SOUTH;
                        break;
                }

                //TMP
                //events.RescheduleEvent(ACTION_CORUPTED_PRISON_DEACTIVATE_KEY, 1000ms);
            }

            void DoAction(const int32 param)
            {
                switch (param)
                {
                    case ACTION_CORUPTED_PRISON_DEACTIVATE_KEY:
                        events.Reset();
                        break;
                    case ACTION_CORUPTED_PRISON_ACTIVATE_KEY:
                        events.RescheduleEvent(ACTION_CORUPTED_PRISON_DEACTIVATE_KEY, 1000ms);
                        break;
                    case ACTION_CORUPTED_PRISON_ENABLE:
                        if (me->GetGoState() == GO_STATE_ACTIVE_ALTERNATIVE)
                        {
                            TemucraftEnableGo(me, false);
                            if (GameObject* pris = instance->instance->GetGameObject(instance->GetGuidData(ownerEntry)))
                                pris->AI()->DoAction(ACTION_CORUPTED_PRISON_ACTIVATE_KEY);
                            return;
                        }
                        break;
                }

                if (me->GetGoState() != GO_STATE_ACTIVE_ALTERNATIVE)
                    TemucraftEnableGo(me, true);
            }

            void UpdateAI(uint32 diff) 
            {
                events.Update(diff);
                if (uint32 eventId = events.ExecuteEvent())
                {
                    //should be first
                    events.RescheduleEvent(ACTION_CORUPTED_PRISON_DEACTIVATE_KEY, 100ms);

                    // Possible Blizard do check like this
                    std::list<Player*> playerList;
                    GetPlayerListInGrid(playerList, me, 20.0f);

                    bool find = false;
                    for(std::list<Player*>::iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    {
                        if (me->GetDistance(*itr) > 5.5f && me->GetDistance(*itr) < 7.5f 
                            && TemucraftInDegreesRange(me, (*itr)->GetPositionX(), (*itr)->GetPositionY(), 170.0f, 250.0f, true))
                            find = true;
                    }

                    if (find)
                    {
                        if (me->GetGoState() == GO_STATE_ACTIVE_ALTERNATIVE)
                        {
                            TemucraftEnableGo(me, false);
                            if (GameObject* pris = instance->instance->GetGameObject(instance->GetGuidData(ownerEntry)))
                                pris->AI()->DoAction(ACTION_CORUPTED_PRISON_ACTIVATE_KEY);
                        }
                    }
                    else if (me->GetGoState() == GO_STATE_READY)
                    {
                        TemucraftEnableGo(me, true);
                        if (GameObject* pris = instance->instance->GetGameObject(instance->GetGuidData(ownerEntry)))
                            pris->AI()->DoAction(ACTION_CORUPTED_PRISON_DEACTIVATE_KEY);
                    }
                }
            }

        private:
            InstanceScript* instance;
            uint32 ownerEntry;
            EventMap events;
        };

        GameObjectAI* GetAI(GameObject* go) const
        {
            return new go_sha_of_pride_corupted_prison_buttonAI(go);
        }
};

//71946
class npc_sha_of_pride_manifest_of_pride : public CreatureScript
{
public:
    npc_sha_of_pride_manifest_of_pride() : CreatureScript("npc_sha_of_pride_manifest_of_pride") { }

    enum localEvent
    {
        EVENT_SPAWN                 = 1,
        EVENT_SPELL_MOCKING_BLAST   = 2,
    };

    struct npc_sha_of_pride_manifest_of_prideAI : public ScriptedAI
    {
        npc_sha_of_pride_manifest_of_prideAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            onSpawn = true;
        }

        bool onSpawn;
        EventMap events;
        InstanceScript* instance;

        void Reset()
        {
            events.RescheduleEvent(EVENT_SPAWN, 1000ms);
            events.RescheduleEvent(EVENT_SPELL_MOCKING_BLAST, 6000ms);
            me->AddAura(SPELL_MANIFESTATION_SPAWN, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            DoCast(me, SPELL_LAST_WORD, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (!onSpawn && !UpdateVictim())
                return;

            (CheckEvadeIfOutOfCombatArea() ? (EnterEvadeMode(), true) : false);
            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SPAWN:
                        me->RemoveAurasDueToSpell(SPELL_MANIFESTATION_SPAWN);
                        me->SetInCombatWithZone();
                        onSpawn = false;
                        break;
                    case EVENT_SPELL_MOCKING_BLAST:
                        DoCastVictim(SPELL_MOCKING_BLAST);
                        events.RescheduleEvent(EVENT_SPELL_MOCKING_BLAST, 6000ms);
                        break;
                }
            }         
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sha_of_pride_manifest_of_prideAI(creature);
    }
};

//72172
class npc_sha_of_pride_reflection : public CreatureScript
{
public:
    npc_sha_of_pride_reflection() : CreatureScript("npc_sha_of_pride_reflection") { }

    enum localEvent
    {
        EVENT_SPAWN                        = 1,
        EVENT_SPELL_SELF_REFLECTION_CAST   = 2,
    };

    struct npc_sha_of_pride_reflectionAI : public ScriptedAI
    {
        npc_sha_of_pride_reflectionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            onSpawn = true;
            me->SetCombatMovement(false);
        }

        bool onSpawn;
        EventMap events;
        InstanceScript* instance;

        void Reset()
        {
            events.RescheduleEvent(EVENT_SPAWN, 2000ms);
            events.RescheduleEvent(EVENT_SPELL_SELF_REFLECTION_CAST, 6000ms);
            me->AddAura(SPELL_SELF_REFLECTION_SPAWN, me);
        }

        void UpdateAI(uint32 diff)
        {
            if (!onSpawn && !UpdateVictim())
                return;

            (CheckEvadeIfOutOfCombatArea() ? (EnterEvadeMode(), true) : false);
            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                if (eventId == EVENT_SPAWN)
                {
                    me->RemoveAurasDueToSpell(SPELL_SELF_REFLECTION_SPAWN);
                    me->SetInCombatWithZone();
                    DoCastVictim(SPELL_SELF_REFLECTION_CAST);
                    onSpawn = false;
                    me->SetCombatMovement(true);
                }
            }
            if (!onSpawn)
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sha_of_pride_reflectionAI(creature);
    }
};

//72846
class npc_sha_of_pride_rift_of_corruption : public CreatureScript
{
public:
    npc_sha_of_pride_rift_of_corruption() : CreatureScript("npc_sha_of_pride_rift_of_corruption") { }

    struct npc_sha_of_pride_rift_of_corruptionAI : public ScriptedAI
    {
        npc_sha_of_pride_rift_of_corruptionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
        }
        EventMap events;
        InstanceScript* instance;

        void Reset()
        {
            DoCast(me, SPELL_UNSTABLE_CORRUPTION, true);
            events.RescheduleEvent(EVENT_SPELL_RIFT_OF_CORRUPTION_AT, 2000ms);
        }

        void JustEngagedWith(Unit* who){}

        void EnterEvadeMode(EvadeReason why = EVADE_REASON_OTHER){}

        void DoAction(int32 const action)
        {
            if (action == ACTION_CLOSE_RIFT_OF_CORRUPTION)
            {
                events.Reset();
                me->RemoveAurasDueToSpell(SPELL_RIFT_OF_CORRUPTION);
                me->RemoveAurasDueToSpell(SPELL_UNSTABLE_CORRUPTION);
                DoCast(me, SPELL_RIFT_OF_CORRUPTION, true);
                me->DespawnOrUnsummon();
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_SPELL_RIFT_OF_CORRUPTION_AT:
                    DoCast(me, SPELL_RIFT_OF_CORRUPTION_AT, true);
                    events.RescheduleEvent(EVENT_SPELL_RIFT_OF_CORRUPTION_DMG, 3000ms);
                    break;
                case EVENT_SPELL_RIFT_OF_CORRUPTION_DMG:
                {
                    std::list<Player*> pllist;
                    pllist.clear();
                    GetPlayerListInGrid(pllist, me, 150.0f);
                    pllist.remove_if(RiftOfCorruptionFilter());
                    if (!pllist.empty())
                    {
                        for (std::list<Player*>::const_iterator itr = pllist.begin(); itr != pllist.end(); ++itr)
                        {
                            if (!(*itr)->HasTankSpec())
                            {
                                DoCast(*itr, SPELL_RIFT_OF_CORRUPTION_DMG);
                                break;
                            }
                        }
                    }
                    events.RescheduleEvent(EVENT_SPELL_RIFT_OF_CORRUPTION_DMG, 8000ms);
                }
                break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sha_of_pride_rift_of_corruptionAI(creature);
    }
};

//144800
class spell_sha_of_pride_self_reflection : public SpellScriptLoader
{
public:
    spell_sha_of_pride_self_reflection() : SpellScriptLoader("spell_sha_of_pride_self_reflection") { }
    
    class spell_sha_of_pride_self_reflection_SpellScript : public SpellScript
    {
    PrepareSpellScript(spell_sha_of_pride_self_reflection_SpellScript);


        std::set<ObjectGuid> TargetListGUIDs;

        void HandleAfterCast()
        {
            if (GetCaster())
            {
                bool havetarget;
                TargetListGUIDs.clear();
                std::vector<ThreatReference*> const &threatlist = GetCaster()->GetThreatMgr().GetModifiableThreatList();

                if (threatlist.empty())
                    return;

                std::list<Player*> pllist;
                pllist.clear();
                for (std::vector<ThreatReference*>::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                    if (Unit* target = (*itr)->GetVictim())
                        if (target->ToPlayer())
                            pllist.push_back(target->ToPlayer());

                if (pllist.empty())
                    return;

                std::list<Player*>::iterator itr = pllist.begin();
                std::advance(itr, urand(0, pllist.size() - 1));
                TargetListGUIDs.insert((*itr)->GetGUID());
                pllist.erase(itr);

                for (uint8 n = 0; n < 4; n++)
                {
                    if (pllist.empty())
                        break;

                    havetarget = false;
                    for (std::list<Player*>::iterator Itr = pllist.begin(); Itr != pllist.end();)
                    {
                        if (TemucraftAltPower::Get((*Itr)) != selfreflectionstage[n])
                            ++Itr;
                        else
                        {
                            havetarget = true;
                            TargetListGUIDs.insert((*Itr)->GetGUID());
                            pllist.erase(Itr);
                            break;
                        }
                    }

                    if (!havetarget && !pllist.empty())
                    {
                        std::list<Player*>::iterator itr = pllist.begin();
                        std::advance(itr, urand(0, pllist.size() - 1));
                        TargetListGUIDs.insert((*itr)->GetGUID());
                        pllist.erase(itr);
                    }
                }

                if (!TargetListGUIDs.empty())
                {
                    for (std::set<ObjectGuid>::iterator _itr = TargetListGUIDs.begin(); _itr != TargetListGUIDs.end(); ++_itr)
                    {
                        if (Player* plr = ObjectAccessor::GetPlayer(*GetCaster(), *_itr))
                        {
                            Position pos;
                            pos = plr->GetPosition();
                            GetCaster()->SummonCreature(NPC_REFLECTION, pos, TEMPSUMMON_DEAD_DESPAWN);
                        }
                    }
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_sha_of_pride_self_reflection_SpellScript::HandleAfterCast);
        }
    };
    
    SpellScript* GetSpellScript() const
    {
        return new spell_sha_of_pride_self_reflection_SpellScript();
    }
};

//146822
class spell_sha_of_pride_projection : public SpellScriptLoader
{
    public:
        spell_sha_of_pride_projection() : SpellScriptLoader("spell_sha_of_pride_projection") { }

        class spell_sha_of_pride_projection_AuraScript : public AuraScript
        {
    PrepareAuraScript(spell_sha_of_pride_projection_AuraScript);


            float x, y ,z;

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->GetTypeId() != TYPEID_PLAYER)
                    return;

                GetTarget()->GetRandomPoint(*GetTarget(), 15.0f, x, y, z);
                GetTarget()->CastSpell(x, y, z, SPELL_PROJECTION_MARKER, false);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->GetDistance(x, y, z) > 2.0f)
                    GetTarget()->CastSpell(x, y, z, SPELL_PROJECTION_DMG, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_sha_of_pride_projection_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_sha_of_pride_projection_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_of_pride_projection_AuraScript();
        }
};

//146595
class spell_gift_of_titans : public SpellScriptLoader
{
public:
    spell_gift_of_titans() : SpellScriptLoader("spell_gift_of_titans") { }

    class spell_gift_of_titans_SpellScript : public SpellScript
    {
    PrepareSpellScript(spell_gift_of_titans_SpellScript);


        void HandleAfterCast()
        {
            if (GetCaster())
            {
                std::list<Player*>pllist;
                pllist.clear();
                GetPlayerListInGrid(pllist, GetCaster(), 150.0f);
                uint8 maxcount = GetCaster()->GetMap()->Is25ManRaid() ? 8 : 3;
                uint8 count = 0;
                if (!pllist.empty())
                {
                    for (std::list<Player*>::const_iterator itr = pllist.begin(); itr != pllist.end(); itr++)
                    {
                        if (!(*itr)->HasTankSpec())
                        {
                            (*itr)->AddAura(SPELL_GIFT_OF_THE_TITANS, *itr);
                            if (++count == maxcount)
                                break;
                        }
                    }
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_gift_of_titans_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gift_of_titans_SpellScript();
    }
};

class ValidTargetCheck
{
public:
    bool operator()(WorldObject* unit)
    {
        if (Unit* target = unit->ToUnit())
            if (target->HasAura(SPELL_GIFT_OF_THE_TITANS))
                return false;
        return true;
    }
};

//144359
class spell_gift_of_titans_aura : public SpellScriptLoader
{
public:
    spell_gift_of_titans_aura() : SpellScriptLoader("spell_gift_of_titans_aura") { }

    class spell_gift_of_titans_aura_AuraScript : public AuraScript
    {
    PrepareAuraScript(spell_gift_of_titans_aura_AuraScript);


        void OnPeriodic(AuraEffect const*aurEff)
        {
            if (GetCaster())
            {
                std::list<Player*> pllist;
                pllist.clear();
                GetPlayerListInGrid(pllist, GetCaster(), 8.0f);
                pllist.remove_if(ValidTargetCheck());
                uint8 maxcount = GetCaster()->GetMap()->Is25ManRaid() ? 8 : 3;
                if (pllist.size() >= maxcount)
                {
                    for (std::list<Player*>::const_iterator itr = pllist.begin(); itr != pllist.end(); ++itr)
                    {
                        if (Player* pl = (*itr)->ToPlayer())
                        {
                            pl->RemoveAurasDueToSpell(SPELL_GIFT_OF_THE_TITANS);
                            pl->CastSpell(pl, SPELL_POWER_OF_THE_TITANS, true);
                        }
                    }
                    GetCaster()->RemoveAurasDueToSpell(SPELL_GIFT_OF_THE_TITANS);
                    GetCaster()->CastSpell(GetCaster(), SPELL_POWER_OF_THE_TITANS, true);
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_gift_of_titans_aura_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_gift_of_titans_aura_AuraScript();
    }
};

//144351
class spell_sha_of_pride_mark_of_arrogance : public SpellScriptLoader
{
public:
    spell_sha_of_pride_mark_of_arrogance() : SpellScriptLoader("spell_sha_of_pride_mark_of_arrogance") { }
    
    class spell_sha_of_pride_mark_of_arrogance_AuraScript : public AuraScript
    {
    PrepareAuraScript(spell_sha_of_pride_mark_of_arrogance_AuraScript);


        void HandleDispel(DispelInfo* dispelInfo)
        {
            if (Unit* dispeller = dispelInfo->GetDispeller())
                if (!dispeller->HasAura(SPELL_GIFT_OF_THE_TITANS) && dispeller->HasAura(SPELL_PRIDE))
                    if (TemucraftAltPower::Get(dispeller) <= 95)
                        TemucraftAltPower::Set(dispeller, TemucraftAltPower::Get(dispeller) + 5);
        }

        void Register()
        {
            AfterDispel += AuraDispelFn(spell_sha_of_pride_mark_of_arrogance_AuraScript::HandleDispel);
        }
    };
    
    AuraScript* GetAuraScript() const
    {
        return new spell_sha_of_pride_mark_of_arrogance_AuraScript();
    }
};

//144843
class spell_sha_of_pride_overcome : public SpellScriptLoader
{
public:
    spell_sha_of_pride_overcome() : SpellScriptLoader("spell_sha_of_pride_overcome") { }

    class spell_sha_of_pride_overcome_AuraScript : public AuraScript
    {
    PrepareAuraScript(spell_sha_of_pride_overcome_AuraScript);


        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget())
            {
                if (Creature* sha = GetTarget()->FindNearestCreature(NPC_SHA_OF_PRIDE, 150.0f, true))
                    sha->CastSpell(GetTarget(), SPELL_OVERCOME_MIND_CONTROL, true);
            }
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
                Unit::Kill(GetTarget(), GetTarget(), true);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_sha_of_pride_overcome_AuraScript::OnApply, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_sha_of_pride_overcome_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_of_pride_overcome_AuraScript();
    }
};

//144400
class spell_swelling_pride : public SpellScriptLoader
{
public:
    spell_swelling_pride() : SpellScriptLoader("spell_swelling_pride") { }

    class spell_swelling_pride_SpellScript : public SpellScript
    {
    PrepareSpellScript(spell_swelling_pride_SpellScript);


        void HitHandler()
        {
            if (GetCaster() && GetHitUnit()->ToPlayer())
            {
                if (GetHitUnit()->HasAura(SPELL_PRIDE))
                {
                    uint32 power = TemucraftAltPower::Get(GetHitUnit());
                    if (power >= 25 && power <= 49)
                        GetCaster()->CastSpell(GetHitUnit(), SPELL_BURSTING_PRIDE, true);
                    else if (power >= 50 && power <= 74)
                        GetCaster()->CastSpell(GetHitUnit(), SPELL_PROJECTION, true);
                    else if (power >= 75 && power <= 99)
                        GetCaster()->CastSpell(GetHitUnit(), SPELL_AURA_OF_PRIDE, true);
                    else if (power == 100)
                        GetHitUnit()->CastSpell(GetHitUnit(), SPELL_OVERCOME, true);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_swelling_pride_SpellScript::HitHandler);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_swelling_pride_SpellScript();
    }
};

//144774, 144379, 144788, 147198, 144911, 146818, 144836, 145320, 147207
class spell_generic_modifier_pride : public SpellScriptLoader
{
public:
    spell_generic_modifier_pride() : SpellScriptLoader("spell_generic_modifier_pride") { }

    class spell_generic_modifier_pride_SpellScript : public SpellScript
    {
    PrepareSpellScript(spell_generic_modifier_pride_SpellScript);


        void HitHandler()
        {
            if (GetHitUnit()->ToPlayer())
                if (!GetHitUnit()->HasAura(SPELL_GIFT_OF_THE_TITANS) && GetHitUnit()->HasAura(SPELL_PRIDE))
                    if (TemucraftAltPower::Get(GetHitUnit()) <= 95)
                        TemucraftAltPower::Set(GetHitUnit(), TemucraftAltPower::Get(GetHitUnit()) + 5);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_generic_modifier_pride_SpellScript::HitHandler);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_generic_modifier_pride_SpellScript();
    }
};

//144370
class spell_last_word : public SpellScriptLoader
{
public:
    spell_last_word() : SpellScriptLoader("spell_last_word") { }

    class spell_last_word_SpellScript : public SpellScript
    {
    PrepareSpellScript(spell_last_word_SpellScript);


        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!targets.empty() && GetCaster())
            {
                std::vector<ObjectGuid> pllist;
                pllist.clear();
                float dist = 5.0f;
                for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if (Player* pl = (*itr)->ToPlayer())
                    {
                        if (GetCaster()->GetExactDist2d(pl) <= dist && !pl->HasAura(SPELL_GIFT_OF_THE_TITANS) && pl->HasAura(SPELL_PRIDE))
                        {
                            if (pllist.empty())
                                pllist.push_back((*itr)->GetGUID());
                            else
                            {
                                if (pllist[0] != pl->GetGUID())
                                {
                                    pllist.push_back(pl->GetGUID());
                                    break;
                                }
                            }
                        }
                        else
                            dist = dist + 10;
                    }
                }
                if (!pllist.empty())
                    for (std::vector<ObjectGuid>::const_iterator itr = pllist.begin(); itr != pllist.end(); ++itr)
                        if (Player* pl = ObjectAccessor::GetPlayer(*GetCaster(), *itr))
                            if (TemucraftAltPower::Get(pl) <= 95)
                                TemucraftAltPower::Set(pl, TemucraftAltPower::Get(pl) + 5);
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_last_word_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_last_word_SpellScript();
    }
};

//144574, 144636,  144683,  144684
class spell_corrupted_prison : public SpellScriptLoader
{
public:
    spell_corrupted_prison() : SpellScriptLoader("spell_corrupted_prison") { }

    class spell_corrupted_prison_AuraScript : public AuraScript
    {
    PrepareAuraScript(spell_corrupted_prison_AuraScript);


        void OnPeriodic(AuraEffect const*aurEff)
        {
            if (GetTarget())
                if (GetTarget()->HasAura(SPELL_PRIDE))
                    if (TemucraftAltPower::Get(GetTarget()) <= 95)
                        TemucraftAltPower::Set(GetTarget(), TemucraftAltPower::Get(GetTarget()) + 5);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_corrupted_prison_AuraScript::OnPeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_corrupted_prison_AuraScript();
    }
};

//147207
class spell_weakened_resolve : public SpellScriptLoader
{
public:
    spell_weakened_resolve() : SpellScriptLoader("spell_weakened_resolve") { }

    class spell_weakened_resolve_AuraScript : public AuraScript
    {
    PrepareAuraScript(spell_weakened_resolve_AuraScript);


        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetCaster() && GetCaster()->ToCreature())
                GetCaster()->ToCreature()->AI()->DoAction(ACTION_CLOSE_RIFT_OF_CORRUPTION);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_weakened_resolve_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_weakened_resolve_AuraScript();
    }
};

void AddSC_boss_sha_of_pride()
{
    new boss_sha_of_pride();
    new npc_sha_of_pride_norushen();
    new npc_sha_of_pride_lowerwalker();
    new go_sha_of_pride_corupted_prison();
    new go_sha_of_pride_corupted_prison_button();
    new npc_sha_of_pride_manifest_of_pride();
    new npc_sha_of_pride_reflection();
    new npc_sha_of_pride_rift_of_corruption();
    new spell_sha_of_pride_self_reflection();
    new spell_sha_of_pride_projection();
    new spell_gift_of_titans();
    new spell_gift_of_titans_aura();
    new spell_sha_of_pride_mark_of_arrogance();
    new spell_sha_of_pride_overcome();
    new spell_swelling_pride();
    new spell_generic_modifier_pride();
    new spell_last_word();
    new spell_corrupted_prison();
    new spell_weakened_resolve();
}