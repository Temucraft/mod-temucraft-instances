/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// mod-temucraft-deadmines: AzerothCore's own (classic) Deadmines instance script, unchanged apart from the names.
// The module's instance_deadmines replaces AzerothCore's script of the same name and hands the normal mode to this
// copy, so the classic dungeon (Mr. Smite, the cannon, the doors) keeps working exactly as before.

#include "InstanceScript.h"
#include "GameObject.h"
#include "Map.h"
#include <sstream>

namespace TemucraftDeadminesClassic
{
// the values of AzerothCore's deadmines.h, which AzerothCore's own Deadmines scripts (Mr. Smite) still use
enum DataTypes
{
    TYPE_RHAHK_ZOR              = 0,
    TYPE_CANNON                 = 1,
    MAX_ENCOUNTERS              = 2
};

enum GameObjects
{
    GO_FACTORY_DOOR             = 13965,
    GO_HEAVY_DOOR_1             = 17153,
    GO_HEAVY_DOOR_2             = 17154,
    GO_IRON_CLAD_DOOR           = 16397,
    GO_DOOR_LEVER_1             = 101831,
    GO_DOOR_LEVER_2             = 101833,
    GO_DOOR_LEVER_3             = 101834,
    GO_CANNON                   = 16398,
    GO_FOUNDRY_DOOR             = 16399,
    GO_MAST_ROOM_DOOR           = 16400,
};

struct instance_deadmines_classic_InstanceMapScript : public InstanceScript
{
    instance_deadmines_classic_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetHeaders("DM");
    }

    void Initialize() override
    {
        memset(&_encounters, 0, sizeof(_encounters));
    }

    void OnGameObjectCreate(GameObject* gameobject) override
    {
        switch (gameobject->GetEntry())
        {
            case GO_HEAVY_DOOR_1:
            case GO_HEAVY_DOOR_2:
            case GO_DOOR_LEVER_1:
            case GO_DOOR_LEVER_2:
            case GO_DOOR_LEVER_3:
            case GO_CANNON:
            case GO_FOUNDRY_DOOR:
            case GO_MAST_ROOM_DOOR:
                gameobject->AllowSaveToDB(true);
                break;
            case GO_FACTORY_DOOR:
                gameobject->AllowSaveToDB(true);
                // GoState (Door opened) is restored during GO creation, but we need to set LootState to prevent Lever from closing it again
                if (_encounters[TYPE_RHAHK_ZOR] == DONE)
                    gameobject->SetLootState(GO_ACTIVATED);
                break;
            case GO_IRON_CLAD_DOOR:
                gameobject->AllowSaveToDB(true);
                if (GetStoredGameObjectState(gameobject->GetSpawnId()) == GO_STATE_ACTIVE)
                    gameobject->DespawnOrUnsummon();

                break;
        }
    }

    void SetData(uint32 type, uint32 data) override
    {
        switch (type)
        {
            case TYPE_RHAHK_ZOR:
            case TYPE_CANNON:
                _encounters[type] = data;
                break;
        }

        if (data == DONE)
            SaveToDB();
    }

    std::string GetSaveData() override
    {
        std::ostringstream saveStream;
        saveStream << "D E " << _encounters[0] << ' ' << _encounters[1];
        return saveStream.str();
    }

    void Load(char const* in) override
    {
        if (!in)
            return;

        char dataHead1, dataHead2;
        std::istringstream loadStream(in);
        loadStream >> dataHead1 >> dataHead2;
        if (dataHead1 == 'D' && dataHead2 == 'E')
        {
            for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            {
                loadStream >> _encounters[i];
                if (_encounters[i] == IN_PROGRESS)
                    _encounters[i] = NOT_STARTED;
            }
        }
    }

private:
    uint32 _encounters[MAX_ENCOUNTERS];
};

InstanceScript* CreateInstanceScript(InstanceMap* map)
{
    return new instance_deadmines_classic_InstanceMapScript(map);
}
}
