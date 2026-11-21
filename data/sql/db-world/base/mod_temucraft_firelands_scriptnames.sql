-- mod-temucraft-firelands: script names for the converted creatures, objects, spells and area triggers (from the TrinityCore 4.3.4 world database)
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (720, 0, 'instance_firelands', 0) ON DUPLICATE KEY UPDATE `script` = VALUES(`script`);
UPDATE `creature_template` SET `ScriptName` = 'boss_lord_rhyolith' WHERE `entry` = 52558;
UPDATE `creature_template` SET `ScriptName` = 'boss_majordomo_staghelm' WHERE `entry` = 52571;
UPDATE `creature_template` SET `ScriptName` = 'npc_rhyolith_foot' WHERE `entry` = 52577;
UPDATE `creature_template` SET `ScriptName` = 'npc_rhyolith_volcano' WHERE `entry` = 52582;
UPDATE `creature_template` SET `ScriptName` = 'npc_rhyolith_liquid_obsidian' WHERE `entry` = 52619;
UPDATE `creature_template` SET `ScriptName` = 'npc_rhyolith_movement_controller_lord_rhyolith' WHERE `entry` = 52659;
UPDATE `creature_template` SET `ScriptName` = 'npc_rhyolith_foot' WHERE `entry` = 53087;
UPDATE `creature_template` SET `ScriptName` = 'boss_baleroc' WHERE `entry` = 53494;
UPDATE `creature_template` SET `ScriptName` = 'npc_shard_of_torment' WHERE `entry` = 53495;
UPDATE `creature_template` SET `ScriptName` = 'npc_blazing_monstrosity' WHERE `entry` = 53786;
UPDATE `creature_template` SET `ScriptName` = 'npc_molten_barrage' WHERE `entry` = 53787;
UPDATE `creature_template` SET `ScriptName` = 'npc_molten_barrage' WHERE `entry` = 53788;
UPDATE `creature_template` SET `ScriptName` = 'npc_blazing_monstrosity' WHERE `entry` = 53791;
UPDATE `creature_template` SET `ScriptName` = 'npc_harbinger_of_flame' WHERE `entry` = 53793;
UPDATE `creature_template` SET `ScriptName` = 'npc_egg_pile' WHERE `entry` = 53795;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_alysrazor_aggro_closest','spell_alysrazor_cosmetic_egg_xplosion','spell_alysrazor_fieroblast','spell_alysrazor_turn_monstrosity','spell_baleroc_torment','spell_baleroc_tormented','spell_baleroc_tormented_debuff','spell_baleroc_tormented_heroic','spell_countdown_p1','spell_countdown_p2','spell_countdown_p3','spell_decimating_strike','spell_majordomo_staghelm_burning_orbs','spell_majordomo_staghelm_clump_check','spell_majordomo_staghelm_concentration','spell_majordomo_staghelm_form_controller','spell_majordomo_staghelm_leaping_flames','spell_majordomo_staghelm_leaping_flames_targeting','spell_majordomo_staghelm_searing_seeds','spell_rhyolith_concussive_stomp','spell_rhyolith_drink_magma','spell_rhyolith_heated_volcano','spell_rhyolith_immolation','spell_rhyolith_lava_line','spell_rhyolith_lava_strike','spell_rhyolith_lava_strike_visual','spell_rhyolith_magma_flow','spell_rhyolith_meltdown','spell_rhyolith_summon_rock_elementals','spell_shards_of_torment');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(97225, 'spell_rhyolith_magma_flow'),
(98034, 'spell_rhyolith_drink_magma'),
(98146, 'spell_rhyolith_summon_rock_elementals'),
(98229, 'spell_majordomo_staghelm_concentration'),
(98276, 'spell_rhyolith_lava_strike'),
(98386, 'spell_majordomo_staghelm_form_controller'),
(98399, 'spell_majordomo_staghelm_clump_check'),
(98450, 'spell_majordomo_staghelm_searing_seeds'),
(98451, 'spell_majordomo_staghelm_burning_orbs'),
(98476, 'spell_majordomo_staghelm_leaping_flames'),
(98489, 'spell_rhyolith_lava_strike_visual'),
(98493, 'spell_rhyolith_heated_volcano'),
(98597, 'spell_rhyolith_immolation'),
(98649, 'spell_rhyolith_meltdown'),
(99253, 'spell_baleroc_torment'),
(99256, 'spell_baleroc_tormented'),
(99257, 'spell_baleroc_tormented_debuff'),
(99259, 'spell_shards_of_torment'),
(99353, 'spell_decimating_strike'),
(99402, 'spell_baleroc_tormented_debuff'),
(99403, 'spell_baleroc_tormented_debuff'),
(99404, 'spell_baleroc_tormented_debuff'),
(99489, 'spell_baleroc_tormented_heroic'),
(99515, 'spell_countdown_p1'),
(99516, 'spell_countdown_p2'),
(99517, 'spell_countdown_p3'),
(100076, 'spell_alysrazor_turn_monstrosity'),
(100078, 'spell_alysrazor_turn_monstrosity'),
(100080, 'spell_alysrazor_turn_monstrosity'),
(100082, 'spell_alysrazor_turn_monstrosity'),
(100089, 'spell_alysrazor_turn_monstrosity'),
(100090, 'spell_alysrazor_turn_monstrosity'),
(100091, 'spell_alysrazor_turn_monstrosity'),
(100092, 'spell_alysrazor_turn_monstrosity'),
(100094, 'spell_alysrazor_fieroblast'),
(100099, 'spell_alysrazor_cosmetic_egg_xplosion'),
(100230, 'spell_baleroc_tormented'),
(100231, 'spell_baleroc_tormented'),
(100232, 'spell_baleroc_tormented'),
(100462, 'spell_alysrazor_aggro_closest'),
(100650, 'spell_rhyolith_lava_line'),
(100943, 'spell_majordomo_staghelm_clump_check'),
(101165, 'spell_majordomo_staghelm_leaping_flames_targeting'),
(101223, 'spell_alysrazor_fieroblast'),
(101294, 'spell_alysrazor_fieroblast'),
(101295, 'spell_alysrazor_fieroblast'),
(101296, 'spell_alysrazor_fieroblast'),
(101646, 'spell_rhyolith_meltdown'),
(101647, 'spell_rhyolith_meltdown'),
(101648, 'spell_rhyolith_meltdown'),
(102306, 'spell_rhyolith_concussive_stomp'),
(102307, 'spell_rhyolith_concussive_stomp'),
(102308, 'spell_rhyolith_concussive_stomp'),
(102309, 'spell_rhyolith_concussive_stomp');
