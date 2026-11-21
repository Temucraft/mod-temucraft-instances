-- mod-temucraft-halls-of-origination: script names for the converted creatures, objects, spells and area triggers (from the TrinityCore 4.3.4 world database)
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (644, 0, 'instance_halls_of_origination', 0) ON DUPLICATE KEY UPDATE `script` = VALUES(`script`);
UPDATE `creature_template` SET `ScriptName` = 'npc_sun_touched_servant' WHERE `entry` = 39366;
UPDATE `creature_template` SET `ScriptName` = 'npc_sun_touched_servant' WHERE `entry` = 39369;
UPDATE `creature_template` SET `ScriptName` = 'npc_sun_touched_servant' WHERE `entry` = 39370;
UPDATE `creature_template` SET `ScriptName` = 'boss_rajh' WHERE `entry` = 39378;
UPDATE `creature_template` SET `ScriptName` = 'boss_temple_guardian_anhuur' WHERE `entry` = 39425;
UPDATE `creature_template` SET `ScriptName` = 'boss_earthrager_ptah' WHERE `entry` = 39428;
UPDATE `creature_template` SET `ScriptName` = 'npc_rajh_solar_winds' WHERE `entry` = 39635;
UPDATE `creature_template` SET `ScriptName` = 'boss_ammunae' WHERE `entry` = 39731;
UPDATE `creature_template` SET `ScriptName` = 'boss_anraphet' WHERE `entry` = 39788;
UPDATE `creature_template` SET `ScriptName` = 'npc_hoo_flame_warden' WHERE `entry` = 39800;
UPDATE `creature_template` SET `ScriptName` = 'npc_hoo_earth_warden' WHERE `entry` = 39801;
UPDATE `creature_template` SET `ScriptName` = 'npc_hoo_water_warden' WHERE `entry` = 39802;
UPDATE `creature_template` SET `ScriptName` = 'npc_hoo_air_warden' WHERE `entry` = 39803;
UPDATE `creature_template` SET `ScriptName` = 'npc_hoo_brann_bronzebeard' WHERE `entry` = 39908;
UPDATE `creature_template` SET `ScriptName` = 'npc_ptah_beetle_stalker' WHERE `entry` = 40459;
UPDATE `creature_template` SET `ScriptName` = 'npc_ammunae_seedling_pod' WHERE `entry` = 40550;
UPDATE `creature_template` SET `ScriptName` = 'npc_ammunae_spore' WHERE `entry` = 40585;
UPDATE `creature_template` SET `ScriptName` = 'npc_ammunae_bloodpetal_blossom' WHERE `entry` = 40620;
UPDATE `creature_template` SET `ScriptName` = 'npc_ammunae_bloodpetal_sprout' WHERE `entry` = 40630;
UPDATE `creature_template` SET `ScriptName` = 'npc_rajh_orb_of_the_sun' WHERE `entry` = 40835;
UPDATE `creature_template` SET `ScriptName` = 'npc_alpha_beam' WHERE `entry` = 41144;
UPDATE `creature_template` SET `ScriptName` = 'npc_omega_stance' WHERE `entry` = 41194;
UPDATE `creature_template` SET `ScriptName` = 'npc_hoo_whirling_winds' WHERE `entry` = 41245;
UPDATE `creature_template` SET `ScriptName` = 'npc_hoo_aqua_bubble' WHERE `entry` = 41257;
UPDATE `creature_template` SET `ScriptName` = 'npc_ammunae_seedling_pod' WHERE `entry` = 51329;
UPDATE `creature` SET `ScriptName` = 'npc_hoo_aggro_stalker_1' WHERE `guid` = 7000092;
UPDATE `creature` SET `ScriptName` = 'npc_hoo_aggro_stalker_2' WHERE `guid` = 7000093;
UPDATE `creature` SET `ScriptName` = 'npc_hoo_aggro_stalker_3' WHERE `guid` = 7000094;
UPDATE `gameobject_template` SET `ScriptName` = 'go_anhuur_beacon_of_light' WHERE `entry` = 203133;
UPDATE `gameobject_template` SET `ScriptName` = 'go_anhuur_beacon_of_light' WHERE `entry` = 203136;
UPDATE `gameobject_template` SET `ScriptName` = 'go_anhuur_beacon_of_light' WHERE `entry` = 207218;
UPDATE `gameobject_template` SET `ScriptName` = 'go_anhuur_beacon_of_light' WHERE `entry` = 207219;
UPDATE `gameobject_template` SET `ScriptName` = 'go_hoo_the_makers_lift_controller' WHERE `entry` = 207669;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_ammunae_consume_life_energy','spell_ammunae_fixate','spell_ammunae_rampant_growth','spell_ammunae_summon_bloodpetal_blossom','spell_anhuur_burning_light_forcecast','spell_anhuur_disable_beacon_beams','spell_anhuur_divine_reckoning','spell_anhuur_reverberating_hymn','spell_anhuur_shield_of_light','spell_anraphet_alpha_beams','spell_anraphet_destruction_protocol','spell_anraphet_omega_stance','spell_anraphet_omega_stance_summon','spell_earthrager_ptah_consume','spell_earthrager_ptah_explosion','spell_earthrager_ptah_flame_bolt','spell_earthrager_ptah_sandstorm','spell_hoo_bubble_bound','spell_hoo_bubble_bound_periodic','spell_hoo_bubble_bound_script','spell_hoo_disperse','spell_hoo_flame_ring_visual','spell_hoo_submerge','spell_rajh_summon_meteor','spell_rajh_summon_sun_orb','spell_rajh_summon_sun_orb_power_cost');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73686, 'spell_ammunae_fixate'),
(74632, 'spell_hoo_flame_ring_visual'),
(74930, 'spell_anhuur_shield_of_light'),
(75115, 'spell_anhuur_burning_light_forcecast'),
(75322, 'spell_anhuur_reverberating_hymn'),
(75378, 'spell_earthrager_ptah_consume'),
(75491, 'spell_earthrager_ptah_sandstorm'),
(75519, 'spell_earthrager_ptah_explosion'),
(75540, 'spell_earthrager_ptah_flame_bolt'),
(75592, 'spell_anhuur_divine_reckoning'),
(75622, 'spell_anraphet_omega_stance'),
(75725, 'spell_ammunae_consume_life_energy'),
(75774, 'spell_ammunae_summon_bloodpetal_blossom'),
(75790, 'spell_ammunae_rampant_growth'),
(76084, 'spell_hoo_submerge'),
(76338, 'spell_rajh_summon_sun_orb'),
(76375, 'spell_rajh_summon_meteor'),
(76573, 'spell_anhuur_shield_of_light'),
(76606, 'spell_anhuur_disable_beacon_beams'),
(76608, 'spell_anhuur_disable_beacon_beams'),
(76904, 'spell_anraphet_alpha_beams'),
(77106, 'spell_anraphet_omega_stance_summon'),
(77335, 'spell_hoo_bubble_bound'),
(77336, 'spell_hoo_bubble_bound_periodic'),
(77339, 'spell_hoo_bubble_bound_script'),
(77437, 'spell_anraphet_destruction_protocol'),
(80352, 'spell_rajh_summon_sun_orb_power_cost'),
(88097, 'spell_hoo_disperse'),
(88100, 'spell_hoo_disperse'),
(89881, 'spell_earthrager_ptah_flame_bolt'),
(89888, 'spell_ammunae_rampant_growth'),
(91158, 'spell_hoo_bubble_bound_periodic'),
(91176, 'spell_anraphet_omega_stance_summon'),
(91208, 'spell_anraphet_omega_stance'),
(94949, 'spell_anhuur_divine_reckoning');
DELETE FROM `areatrigger_scripts` WHERE `entry` IN (5811);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5811, 'at_hoo_brann_idle_emote');
