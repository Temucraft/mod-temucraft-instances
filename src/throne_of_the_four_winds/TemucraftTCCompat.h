/*
 * Small helpers for scripts ported from TrinityCore 4.3.4 to AzerothCore 3.3.5: names TrinityCore has and
 * AzerothCore doesn't, kept here so the ported scripts stay close to the original.
 */
#ifndef TEMUCRAFT_TC_COMPAT_H
#define TEMUCRAFT_TC_COMPAT_H

#include "Position.h"
#include <G3D/Vector3.h>

enum SpellFinishReason : uint8
{
    SPELL_FINISHED_SUCCESSFUL_CAST     = 0,   // AzerothCore: CreatureAI::OnSpellCast
    SPELL_FINISHED_CANCELED            = 1,   // AzerothCore: CreatureAI::OnSpellFailed
    SPELL_FINISHED_CHANNELING_COMPLETE = 2    // AzerothCore: CreatureAI::OnChannelFinished
};

inline G3D::Vector3 PositionToVector3(Position const& p) { return { p.GetPositionX(), p.GetPositionY(), p.GetPositionZ() }; }
inline G3D::Vector3 PositionToVector3(Position const* p) { return PositionToVector3(*p); }

#endif
