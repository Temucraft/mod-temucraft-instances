-- mod-temucraft-deadmines: script names (from the TrinityCore 4.3.4 world database). The instance script keeps AzerothCore's
-- name `instance_deadmines`: the module's copy replaces AzerothCore's and runs the classic script in the normal mode.
UPDATE `creature_template` SET `ScriptName` = 'boss_foe_reaper_5000' WHERE `entry` = 43778;
UPDATE `creature_template` SET `ScriptName` = 'boss_glubtok' WHERE `entry` = 47162;
UPDATE `creature_template` SET `ScriptName` = 'boss_helix_gearbreaker' WHERE `entry` = 47296;
UPDATE `creature_template` SET `ScriptName` = 'npc_helix_lumbering_oaf' WHERE `entry` = 47297;
UPDATE `creature_template` SET `ScriptName` = 'npc_helix_sticky_bomb' WHERE `entry` = 47314;
UPDATE `creature_template` SET `ScriptName` = 'npc_deadmines_defias_watcher' WHERE `entry` = 47403;
UPDATE `creature_template` SET `ScriptName` = 'npc_deadmines_defias_watcher' WHERE `entry` = 47404;
UPDATE `creature_template` SET `ScriptName` = 'boss_admiral_ripsnarl' WHERE `entry` = 47626;
UPDATE `creature_template` SET `ScriptName` = 'npc_ripsnarl_vapor' WHERE `entry` = 47714;
UPDATE `creature_template` SET `ScriptName` = 'boss_captain_cookie' WHERE `entry` = 47739;
UPDATE `creature_template` SET `ScriptName` = 'npc_helix_crew' WHERE `entry` = 49139;
UPDATE `creature_template` SET `ScriptName` = 'npc_foe_reaper_5000_molten_slag' WHERE `entry` = 49229;
UPDATE `creature_template` SET `ScriptName` = 'npc_vanessa_vanessa_van_cleef' WHERE `entry` = 49429;
UPDATE `creature_template` SET `ScriptName` = 'npc_deadmines_vanessas_trap_bunny' WHERE `entry` = 49454;
UPDATE `creature_template` SET `ScriptName` = 'npc_deadmines_steam_valve' WHERE `entry` = 49457;
UPDATE `creature_template` SET `ScriptName` = 'boss_vanessa_van_cleef' WHERE `entry` = 49541;
UPDATE `creature_template` SET `ScriptName` = 'npc_vanessa_rope' WHERE `entry` = 49550;
UPDATE `creature_template` SET `ScriptName` = 'npc_vanessa_note_from_vanessa' WHERE `entry` = 49564;
UPDATE `creature_template` SET `ScriptName` = 'npc_deadmines_vanessa_van_cleef_nightmare' WHERE `entry` = 49671;
UPDATE `creature_template` SET `ScriptName` = 'npc_deadmines_helix_nightmare' WHERE `entry` = 49674;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_cookie_satiated','spell_cookie_throw_food_targeting','spell_deadmines_bloodbath','spell_deadmines_magma_trap_throw_to_location','spell_deadmines_on_fire','spell_deadmines_ride_magma_vehicle','spell_foe_reaper_5000_acquire_target','spell_foe_reaper_5000_fixate','spell_foe_reaper_5000_fixate_targeting','spell_glubtok_blossom_targeting','spell_helix_chest_bomb','spell_helix_chest_bomb_emote','spell_helix_force_player_to_ride_oaf','spell_helix_helix_ride','spell_helix_helix_ride_face_timer_aura','spell_helix_oaf_grab_targeting','spell_helix_oaf_smash','spell_helix_ride_face_targeting','spell_helix_ride_vehicle','spell_helix_sticky_bomb_periodic_trigger','spell_helix_throw_bomb_targeting','spell_ripsnarl_go_for_the_throat_targeting','spell_ripsnarl_summon_vapor_targeting','spell_vanessa_backslash_targeting');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89267, 'spell_cookie_satiated'),
(92834, 'spell_cookie_satiated'),
(89268, 'spell_cookie_throw_food_targeting'),
(89740, 'spell_cookie_throw_food_targeting'),
(90561, 'spell_cookie_throw_food_targeting'),
(90562, 'spell_cookie_throw_food_targeting'),
(90563, 'spell_cookie_throw_food_targeting'),
(90564, 'spell_cookie_throw_food_targeting'),
(90565, 'spell_cookie_throw_food_targeting'),
(90582, 'spell_cookie_throw_food_targeting'),
(90583, 'spell_cookie_throw_food_targeting'),
(90584, 'spell_cookie_throw_food_targeting'),
(90585, 'spell_cookie_throw_food_targeting'),
(90586, 'spell_cookie_throw_food_targeting'),
(90925, 'spell_deadmines_bloodbath'),
(92438, 'spell_deadmines_magma_trap_throw_to_location'),
(91737, 'spell_deadmines_on_fire'),
(92378, 'spell_deadmines_ride_magma_vehicle'),
(88492, 'spell_foe_reaper_5000_acquire_target'),
(91830, 'spell_foe_reaper_5000_fixate'),
(91831, 'spell_foe_reaper_5000_fixate_targeting'),
(88140, 'spell_glubtok_blossom_targeting'),
(88352, 'spell_helix_chest_bomb'),
(91572, 'spell_helix_chest_bomb_emote'),
(88278, 'spell_helix_force_player_to_ride_oaf'),
(88337, 'spell_helix_helix_ride'),
(88351, 'spell_helix_helix_ride_face_timer_aura'),
(88289, 'spell_helix_oaf_grab_targeting'),
(88300, 'spell_helix_oaf_smash'),
(91568, 'spell_helix_oaf_smash'),
(88349, 'spell_helix_ride_face_targeting'),
(88360, 'spell_helix_ride_vehicle'),
(88329, 'spell_helix_sticky_bomb_periodic_trigger'),
(88268, 'spell_helix_throw_bomb_targeting'),
(88838, 'spell_ripsnarl_go_for_the_throat_targeting'),
(88833, 'spell_ripsnarl_summon_vapor_targeting'),
(92620, 'spell_vanessa_backslash_targeting');
