-- mod-temucraft-vortex-pinnacle: script names for the converted creatures, objects, spells and area triggers (from the TrinityCore 4.3.4 world database)
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (657, 0, 'instance_vortex_pinnacle', 0) ON DUPLICATE KEY UPDATE `script` = VALUES(`script`);
UPDATE `creature_template` SET `ScriptName` = 'boss_altairus' WHERE `entry` = 43873;
UPDATE `creature_template` SET `ScriptName` = 'boss_asaad' WHERE `entry` = 43875;
UPDATE `creature_template` SET `ScriptName` = 'boss_grand_vizier_ertan' WHERE `entry` = 43878;
UPDATE `creature_template` SET `ScriptName` = 'npc_slipstream' WHERE `entry` = 45455;
UPDATE `creature_template` SET `ScriptName` = 'npc_slipstream_landing_zone' WHERE `entry` = 45504;
UPDATE `creature_template` SET `ScriptName` = 'npc_vp_howling_gale' WHERE `entry` = 45572;
UPDATE `creature_template` SET `ScriptName` = 'npc_lurking_tempest' WHERE `entry` = 45704;
UPDATE `creature_template` SET `ScriptName` = 'npc_vp_young_storm_dragon' WHERE `entry` = 45919;
UPDATE `creature_template` SET `ScriptName` = 'npc_skyfall_star' WHERE `entry` = 45932;
UPDATE `creature_template` SET `ScriptName` = 'npc_skyfall' WHERE `entry` = 45981;
UPDATE `creature_template` SET `ScriptName` = 'npc_ertan_ertans_vortex' WHERE `entry` = 46007;
UPDATE `creature_template` SET `ScriptName` = 'npc_asaad_unstable_grounding_field' WHERE `entry` = 46492;
UPDATE `creature_template` SET `ScriptName` = 'npc_grounding_field' WHERE `entry` = 47085;
UPDATE `creature_template` SET `ScriptName` = 'npc_vp_catch_fall' WHERE `entry` = 48165;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_altairus_call_the_wind','spell_altairus_call_the_wind_channel','spell_altairus_chilling_breath','spell_altairus_safe_area','spell_altairus_upwind_of_altairus','spell_asaad_grounding_field','spell_asaad_grounding_field_visual_beams','spell_asaad_sots_targeting','spell_asaad_sots_trigger','spell_asaad_static_cling','spell_asaad_storm_rune_beam','spell_asaad_supremacy_of_the_storm_damage','spell_asaad_supremacy_of_the_storm_visual','spell_ertan_storms_edge','spell_ertan_storms_edge_script','spell_grounding_field','spell_skyfall','spell_slipstream','spell_vp_catch_fall','spell_vp_feign_death','spell_vp_healing_well','spell_vp_howling_gale','spell_vp_howling_gale_knockback','spell_vp_lurk_ressurect','spell_vp_lurk_search','spell_vp_lurk_search_periodic');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84978, 'spell_slipstream'),
(84989, 'spell_slipstream'),
(85017, 'spell_slipstream'),
(85084, 'spell_vp_howling_gale'),
(85085, 'spell_vp_howling_gale_knockback'),
(85159, 'spell_vp_howling_gale_knockback'),
(85267, 'spell_vp_feign_death'),
(85281, 'spell_vp_lurk_ressurect'),
(85291, 'spell_vp_lurk_search'),
(85294, 'spell_vp_lurk_search_periodic'),
(85395, 'spell_slipstream'),
(85396, 'spell_slipstream'),
(86284, 'spell_ertan_storms_edge'),
(86299, 'spell_ertan_storms_edge_script'),
(86311, 'spell_ertan_storms_edge'),
(86456, 'spell_vp_lurk_search'),
(86493, 'spell_vp_lurk_search'),
(86632, 'spell_asaad_sots_targeting'),
(86715, 'spell_asaad_supremacy_of_the_storm_visual'),
(86921, 'spell_asaad_storm_rune_beam'),
(86923, 'spell_asaad_storm_rune_beam'),
(86925, 'spell_asaad_storm_rune_beam'),
(86926, 'spell_asaad_sots_trigger'),
(87474, 'spell_asaad_grounding_field'),
(87517, 'spell_asaad_grounding_field_visual_beams'),
(87553, 'spell_asaad_supremacy_of_the_storm_damage'),
(87618, 'spell_asaad_static_cling'),
(87726, 'spell_grounding_field'),
(87850, 'spell_skyfall'),
(88201, 'spell_vp_healing_well'),
(88276, 'spell_altairus_call_the_wind'),
(88282, 'spell_altairus_upwind_of_altairus'),
(88322, 'spell_altairus_chilling_breath'),
(88350, 'spell_altairus_safe_area'),
(88772, 'spell_altairus_call_the_wind_channel'),
(89522, 'spell_vp_catch_fall'),
(93994, 'spell_asaad_supremacy_of_the_storm_damage');
DELETE FROM `areatrigger_scripts` WHERE `entry` IN (6477,6651,6652,6660,6661,6663,6667);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6477, 'at_vp_catch_fall'),
(6651, 'at_vp_catch_fall'),
(6652, 'at_vp_catch_fall'),
(6660, 'at_vp_catch_fall'),
(6661, 'at_vp_catch_fall'),
(6663, 'at_vp_catch_fall'),
(6667, 'at_vp_catch_fall');
