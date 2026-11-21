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

#include "Object.h"

namespace Acore
{
    // true for objects more than `difference` yards above (or, with reverse, not above) the base object
    class HeightDifferenceCheck
    {
    public:
        HeightDifferenceCheck(WorldObject* base, float difference, bool reverse) : _base(base), _difference(difference), _reverse(reverse) { }
        bool operator()(WorldObject* object) const { return (object->GetPositionZ() - _base->GetPositionZ() > _difference) != _reverse; }
    private:
        WorldObject* _base;
        float _difference;
        bool _reverse;
    };
}

#endif
