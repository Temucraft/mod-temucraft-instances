-- mod-temucraft-temple-of-the-jade-serpent: script names (from the LegionCore 7.3.5 world database the scripts come from)
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (960, 0, 'instance_temple_of_jade_serpent', 0) ON DUPLICATE KEY UPDATE `script` = VALUES(`script`);
UPDATE `creature_template` SET `ScriptName` = 'boss_sha_of_doubt' WHERE `entry` = 56439;
UPDATE `creature_template` SET `ScriptName` = 'boss_wase_mari' WHERE `entry` = 56448;
UPDATE `creature_template` SET `ScriptName` = 'boss_liu_flameheart' WHERE `entry` = 56732;
UPDATE `creature_template` SET `ScriptName` = 'boss_yu_lon' WHERE `entry` = 56762;
UPDATE `creature_template` SET `ScriptName` = 'mob_trigger_liu_flameheart' WHERE `entry` = 56789;
UPDATE `creature_template` SET `ScriptName` = 'mob_figment_of_doubt' WHERE `entry` = 56792;
UPDATE `creature_template` SET `ScriptName` = 'boss_lorewalker_stonestep' WHERE `entry` = 56843;
UPDATE `creature_template` SET `ScriptName` = 'mob_sun' WHERE `entry` = 56915;
UPDATE `creature_template` SET `ScriptName` = 'mob_minion_of_doubt' WHERE `entry` = 57109;
UPDATE `creature_template` SET `ScriptName` = 'mob_lesser_sha' WHERE `entry` = 58319;
UPDATE `creature_template` SET `ScriptName` = 'mob_zao' WHERE `entry` = 58826;
UPDATE `creature_template` SET `ScriptName` = 'mob_haunting_sha' WHERE `entry` = 58856;
UPDATE `creature_template` SET `ScriptName` = 'mob_strife' WHERE `entry` = 59051;
UPDATE `creature_template` SET `ScriptName` = 'mob_nodding_tiger' WHERE `entry` = 59544;
UPDATE `creature_template` SET `ScriptName` = 'mob_golden_beetle' WHERE `entry` = 59545;
UPDATE `creature_template` SET `ScriptName` = 'mob_songbird_queen' WHERE `entry` = 59546;
UPDATE `creature_template` SET `ScriptName` = 'mob_jiang_xiang' WHERE `entry` = 59547;
UPDATE `creature_template` SET `ScriptName` = 'mob_songbird_queen' WHERE `entry` = 59553;
UPDATE `creature_template` SET `ScriptName` = 'mob_lesser_sha' WHERE `entry` = 59598;
UPDATE `creature_template` SET `ScriptName` = 'mob_peril' WHERE `entry` = 59726;
UPDATE `creature_template` SET `ScriptName` = 'mob_jiang_xiang' WHERE `entry` = 65317;
-- not bound to anything in LegionCore's database either: mob_corrupt_living_water, mob_talking_fish
