-- mod-temucraft-throne-of-the-four-winds: script names for the converted creatures, objects, spells and area triggers (from the TrinityCore 4.3.4 world database)
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (754, 0, 'instance_throne_of_the_four_winds', 0) ON DUPLICATE KEY UPDATE `script` = VALUES(`script`);
UPDATE `creature_template` SET `ScriptName` = 'npc_totfw_fall_catcher' WHERE `entry` = 45710;
UPDATE `creature_template` SET `ScriptName` = 'npc_conclave_of_wind_ravenous_creeper' WHERE `entry` = 45812;
UPDATE `creature_template` SET `ScriptName` = 'npc_conclave_of_wind_ravenous_creeper_trigger' WHERE `entry` = 45813;
UPDATE `creature_template` SET `ScriptName` = 'boss_anshal' WHERE `entry` = 45870;
UPDATE `creature_template` SET `ScriptName` = 'boss_nezir' WHERE `entry` = 45871;
UPDATE `creature_template` SET `ScriptName` = 'boss_rohash' WHERE `entry` = 45872;
UPDATE `creature_template` SET `ScriptName` = 'npc_alakir_ice_storm' WHERE `entry` = 46734;
UPDATE `creature_template` SET `ScriptName` = 'boss_alakir' WHERE `entry` = 46753;
UPDATE `creature_template` SET `ScriptName` = 'npc_totfw_slipstream' WHERE `entry` = 47066;
UPDATE `creature_template` SET `ScriptName` = 'npc_alakir_stormling' WHERE `entry` = 47175;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_alakir_electrocute','spell_alakir_lightning_clouds_damage','spell_alakir_lightning_clouds_dummy','spell_alakir_lightning_clouds_periodic','spell_alakir_lightning_clouds_targeting','spell_alakir_lightning_rod_damage','spell_alakir_lightning_script','spell_alakir_lightning_strike_damage','spell_alakir_lightning_strike_periodic','spell_alakir_lightning_strike_script','spell_alakir_relentless_storm','spell_alakir_relentless_storm_initial_vehicle_ride','spell_alakir_relentless_storm_initial_vehicle_ride_trigger','spell_alakir_squall_line_pre_aura','spell_alakir_squall_line_script','spell_alakir_storm_distance_check','spell_alakir_wind_burst','spell_conclave_of_wind_hurricane','spell_conclave_of_wind_hurricane_ride_vehicle','spell_conclave_of_wind_sleet_storm','spell_conclave_of_wind_teleport_to_center','spell_conclave_of_wind_toxic_spores','spell_conclave_of_wind_wind_blast','spell_conclave_of_wind_wind_blast_effect','spell_conclave_of_wind_wind_blast_triggered','spell_conclave_of_wind_winds','spell_conclave_of_wind_winds_pre_effect_warning','spell_totfw_catch_fall_summon','spell_totfw_jet_stream');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84576, 'spell_totfw_jet_stream'),
(85269, 'spell_totfw_catch_fall_summon'),
(85480, 'spell_conclave_of_wind_wind_blast_triggered'),
(85483, 'spell_conclave_of_wind_wind_blast_effect'),
(85573, 'spell_conclave_of_wind_winds'),
(85576, 'spell_conclave_of_wind_winds'),
(85578, 'spell_conclave_of_wind_winds'),
(86193, 'spell_conclave_of_wind_wind_blast'),
(86290, 'spell_conclave_of_wind_toxic_spores'),
(86367, 'spell_conclave_of_wind_sleet_storm'),
(86481, 'spell_conclave_of_wind_hurricane_ride_vehicle'),
(86498, 'spell_conclave_of_wind_hurricane'),
(87652, 'spell_alakir_squall_line_pre_aura'),
(87855, 'spell_alakir_squall_line_script'),
(88214, 'spell_alakir_lightning_strike_damage'),
(88238, 'spell_alakir_lightning_strike_periodic'),
(88427, 'spell_alakir_electrocute'),
(88858, 'spell_alakir_wind_burst'),
(88903, 'spell_alakir_storm_distance_check'),
(89104, 'spell_alakir_relentless_storm'),
(89527, 'spell_alakir_relentless_storm_initial_vehicle_ride'),
(89528, 'spell_alakir_relentless_storm_initial_vehicle_ride_trigger'),
(89567, 'spell_alakir_lightning_clouds_periodic'),
(89583, 'spell_alakir_lightning_clouds_dummy'),
(89588, 'spell_alakir_lightning_clouds_damage'),
(89628, 'spell_alakir_lightning_clouds_targeting'),
(89642, 'spell_alakir_lightning_script'),
(89667, 'spell_alakir_lightning_rod_damage'),
(89843, 'spell_conclave_of_wind_teleport_to_center'),
(89844, 'spell_conclave_of_wind_teleport_to_center'),
(91326, 'spell_alakir_lightning_strike_script'),
(93135, 'spell_conclave_of_wind_sleet_storm'),
(93136, 'spell_conclave_of_wind_sleet_storm'),
(93137, 'spell_conclave_of_wind_sleet_storm'),
(93138, 'spell_conclave_of_wind_wind_blast_effect'),
(93139, 'spell_conclave_of_wind_wind_blast_effect'),
(93140, 'spell_conclave_of_wind_wind_blast_effect'),
(93147, 'spell_conclave_of_wind_winds'),
(93148, 'spell_conclave_of_wind_winds'),
(93149, 'spell_conclave_of_wind_winds'),
(93181, 'spell_conclave_of_wind_winds'),
(93182, 'spell_conclave_of_wind_winds'),
(93183, 'spell_conclave_of_wind_winds'),
(93190, 'spell_conclave_of_wind_winds'),
(93191, 'spell_conclave_of_wind_winds'),
(93192, 'spell_conclave_of_wind_winds'),
(93255, 'spell_alakir_lightning_strike_damage'),
(93286, 'spell_alakir_wind_burst'),
(93287, 'spell_alakir_wind_burst'),
(93288, 'spell_alakir_wind_burst'),
(93293, 'spell_alakir_lightning_rod_damage'),
(93294, 'spell_alakir_lightning_rod_damage'),
(93295, 'spell_alakir_lightning_rod_damage'),
(93297, 'spell_alakir_lightning_clouds_damage'),
(93298, 'spell_alakir_lightning_clouds_damage'),
(93299, 'spell_alakir_lightning_clouds_damage'),
(93854, 'spell_alakir_lightning_strike_periodic'),
(93855, 'spell_alakir_lightning_strike_periodic'),
(93856, 'spell_alakir_lightning_strike_periodic'),
(96508, 'spell_conclave_of_wind_winds_pre_effect_warning');
DELETE FROM `areatrigger_scripts` WHERE `entry` IN (6274,6275,6276,6277,6278,6279,6280,6281,6290);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6274, 'at_totfw_jet_stream'),
(6275, 'at_totfw_jet_stream'),
(6276, 'at_totfw_jet_stream'),
(6277, 'at_totfw_jet_stream'),
(6278, 'at_totfw_jet_stream'),
(6279, 'at_totfw_jet_stream'),
(6280, 'at_totfw_jet_stream'),
(6281, 'at_totfw_catch_fall'),
(6290, 'at_totfw_jet_stream');
