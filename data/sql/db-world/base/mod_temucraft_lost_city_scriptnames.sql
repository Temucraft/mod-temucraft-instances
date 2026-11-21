-- mod-temucraft-lost-city: script names for the converted creatures, objects, spells and area triggers (from the TrinityCore 4.3.4 world database)
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (755, 0, 'instance_lost_city_of_the_tolvir', 0) ON DUPLICATE KEY UPDATE `script` = VALUES(`script`);
UPDATE `creature_template` SET `ScriptName` = 'boss_high_prophet_barim' WHERE `entry` = 43612;
UPDATE `creature_template` SET `ScriptName` = 'boss_lockmaw' WHERE `entry` = 43614;
UPDATE `creature_template` SET `ScriptName` = 'npc_lockmaw_frenzied_crocolisk' WHERE `entry` = 43658;
UPDATE `creature_template` SET `ScriptName` = 'npc_barim_repentance' WHERE `entry` = 43817;
UPDATE `creature_template` SET `ScriptName` = 'npc_barim_phoenix_summoner' WHERE `entry` = 43926;
UPDATE `creature_template` SET `ScriptName` = 'npc_barim_harbinger_of_darkness' WHERE `entry` = 43927;
UPDATE `creature_template` SET `ScriptName` = 'npc_barim_soul_fragment' WHERE `entry` = 43934;
UPDATE `creature_template` SET `ScriptName` = 'boss_general_husam' WHERE `entry` = 44577;
UPDATE `creature_template` SET `ScriptName` = 'npc_husam_bad_intentions_target' WHERE `entry` = 44586;
UPDATE `creature_template` SET `ScriptName` = 'npc_siamat_minion_of_siamat' WHERE `entry` = 44704;
UPDATE `creature_template` SET `ScriptName` = 'npc_husam_shockwave_visual' WHERE `entry` = 44712;
UPDATE `creature_template` SET `ScriptName` = 'npc_husam_tolvir_land_mine' WHERE `entry` = 44796;
UPDATE `creature_template` SET `ScriptName` = 'boss_siamat' WHERE `entry` = 44819;
UPDATE `creature_template` SET `ScriptName` = 'npc_siamat_servant_of_siamat' WHERE `entry` = 45259;
UPDATE `creature_template` SET `ScriptName` = 'npc_siamat_servant_of_siamat' WHERE `entry` = 45268;
UPDATE `creature_template` SET `ScriptName` = 'npc_siamat_servant_of_siamat' WHERE `entry` = 45269;
UPDATE `creature_template` SET `ScriptName` = 'npc_lct_augh' WHERE `entry` = 45377;
UPDATE `creature_template` SET `ScriptName` = 'npc_lockmaw_augh' WHERE `entry` = 45378;
UPDATE `creature_template` SET `ScriptName` = 'npc_lockmaw_augh' WHERE `entry` = 45379;
UPDATE `creature_template` SET `ScriptName` = 'npc_lct_wind_tunnel' WHERE `entry` = 48092;
UPDATE `creature_template` SET `ScriptName` = 'npc_lct_wind_tunnel_landing_zone' WHERE `entry` = 48097;
UPDATE `creature_template` SET `ScriptName` = 'npc_barim_phoenix_summoner' WHERE `entry` = 48904;
UPDATE `creature_template` SET `ScriptName` = 'npc_barim_blaze_of_the_heavens' WHERE `entry` = 48906;
UPDATE `creature_template` SET `ScriptName` = 'boss_augh' WHERE `entry` = 49045;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_barim_repentance_pull','spell_barim_repentance_script','spell_barim_repentance_stun','spell_husam_bad_intentions','spell_husam_detonate_traps','spell_husam_hammer_fist','spell_husam_hurl','spell_husam_land_mine_player_search_effect','spell_husam_mystic_trap','spell_husam_shockwave','spell_husam_shockwave_summon_search','spell_lockmaw_paralytic_blow_dart','spell_lockmaw_random_aggro_taunt','spell_lockmaw_scent_of_blood','spell_siamat_absorb_storms','spell_siamat_gathered_storms','spell_siamat_lightning_charge','spell_siamat_thunder_crash','spell_siamat_wailing_winds','spell_siamat_wailing_winds_knockback','spell_siamat_wailing_winds_player');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(50230, 'spell_lockmaw_random_aggro_taunt'),
(81690, 'spell_lockmaw_scent_of_blood'),
(81947, 'spell_barim_repentance_stun'),
(81960, 'spell_barim_repentance_script'),
(82009, 'spell_barim_repentance_script'),
(82168, 'spell_barim_repentance_pull'),
(82220, 'spell_barim_repentance_script'),
(83066, 'spell_siamat_wailing_winds'),
(83089, 'spell_siamat_wailing_winds_player'),
(83112, 'spell_husam_land_mine_player_search_effect'),
(83113, 'spell_husam_bad_intentions'),
(83151, 'spell_siamat_absorb_storms'),
(83236, 'spell_husam_hurl'),
(83445, 'spell_husam_shockwave'),
(83466, 'spell_husam_shockwave_summon_search'),
(83566, 'spell_siamat_wailing_winds_knockback'),
(83644, 'spell_husam_mystic_trap'),
(83654, 'spell_husam_hammer_fist'),
(84521, 'spell_siamat_thunder_crash'),
(84799, 'spell_lockmaw_paralytic_blow_dart'),
(84987, 'spell_siamat_gathered_storms'),
(89989, 'spell_lockmaw_paralytic_blow_dart'),
(89998, 'spell_lockmaw_scent_of_blood'),
(91252, 'spell_husam_mystic_trap'),
(91256, 'spell_husam_hammer_fist'),
(91257, 'spell_husam_shockwave'),
(91263, 'spell_husam_detonate_traps'),
(93959, 'spell_siamat_lightning_charge');
