-- mod-temucraft-siege-of-orgrimmar: script names (from the LegionCore 7.3.5 world database the scripts come from)
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (1136, 0, 'instance_siege_of_orgrimmar', 0) ON DUPLICATE KEY UPDATE `script` = VALUES(`script`);
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_of_pride_lowerwalker' WHERE `entry` = 61348;
UPDATE `creature_template` SET `ScriptName` = 'npc_essence_of_yshaarj' WHERE `entry` = 63420;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71152;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71153;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71154;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71155;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71156;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71157;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71158;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71160;
UPDATE `creature_template` SET `ScriptName` = 'boss_paragons_of_the_klaxxi' WHERE `entry` = 71161;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71378;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71380;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71382;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71383;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71385;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71388;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71392;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71393;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71395;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71397;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71405;
UPDATE `creature_template` SET `ScriptName` = 'npc_amber' WHERE `entry` = 71407;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71408;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 71409;
UPDATE `creature_template` SET `ScriptName` = 'npc_kunchong' WHERE `entry` = 71420;
UPDATE `creature_template` SET `ScriptName` = 'npc_spark_of_life' WHERE `entry` = 71433;
UPDATE `creature_template` SET `ScriptName` = 'npc_eerie_fog' WHERE `entry` = 71453;
UPDATE `creature_template` SET `ScriptName` = 'boss_malkorok' WHERE `entry` = 71454;
UPDATE `creature_template` SET `ScriptName` = 'npc_arcing_smash' WHERE `entry` = 71455;
UPDATE `creature_template` SET `ScriptName` = 'boss_iron_juggernaut' WHERE `entry` = 71466;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_iron_juggernaut_passenger' WHERE `entry` = 71468;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_iron_juggernaut_passenger' WHERE `entry` = 71469;
UPDATE `creature_template` SET `ScriptName` = 'npc_implosion' WHERE `entry` = 71470;
UPDATE `creature_template` SET `ScriptName` = 'npc_measure_of_sun' WHERE `entry` = 71474;
UPDATE `creature_template` SET `ScriptName` = 'boss_rook_stonetoe' WHERE `entry` = 71475;
UPDATE `creature_template` SET `ScriptName` = 'npc_measure_of_rook' WHERE `entry` = 71476;
UPDATE `creature_template` SET `ScriptName` = 'npc_measure_of_rook' WHERE `entry` = 71477;
UPDATE `creature_template` SET `ScriptName` = 'npc_measure_of_he' WHERE `entry` = 71478;
UPDATE `creature_template` SET `ScriptName` = 'boss_he_softfoot' WHERE `entry` = 71479;
UPDATE `creature_template` SET `ScriptName` = 'boss_sun_tenderheart' WHERE `entry` = 71480;
UPDATE `creature_template` SET `ScriptName` = 'npc_measure_of_rook' WHERE `entry` = 71481;
UPDATE `creature_template` SET `ScriptName` = 'npc_measure_of_sun' WHERE `entry` = 71482;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_iron_juggernaut_passenger' WHERE `entry` = 71484;
UPDATE `creature_template` SET `ScriptName` = 'boss_siegecrafter_blackfuse' WHERE `entry` = 71504;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_spoil' WHERE `entry` = 71512;
UPDATE `creature_template` SET `ScriptName` = 'npc_ancient_miasma' WHERE `entry` = 71513;
UPDATE `creature_template` SET `ScriptName` = 'boss_general_nazgrim' WHERE `entry` = 71515;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_assasin' WHERE `entry` = 71518;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_trigger' WHERE `entry` = 71520;
UPDATE `creature_template` SET `ScriptName` = 'boss_thok_the_bloodthirsty' WHERE `entry` = 71529;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_passenger' WHERE `entry` = 71532;
UPDATE `creature_template` SET `ScriptName` = 'npc_klaxxi_blood' WHERE `entry` = 71542;
UPDATE `creature_template` SET `ScriptName` = 'boss_immerseus' WHERE `entry` = 71543;
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_pool' WHERE `entry` = 71544;
UPDATE `creature_template` SET `ScriptName` = 'npc_swirl_trigger' WHERE `entry` = 71548;
UPDATE `creature_template` SET `ScriptName` = 'npc_swirl_target' WHERE `entry` = 71550;
UPDATE `creature_template` SET `ScriptName` = 'npc_amber_parasite' WHERE `entry` = 71578;
UPDATE `creature_template` SET `ScriptName` = 'npc_automated_shredder' WHERE `entry` = 71591;
UPDATE `creature_template` SET `ScriptName` = 'npc_klaxxi_controller' WHERE `entry` = 71592;
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_puddle' WHERE `entry` = 71603;
UPDATE `creature_template` SET `ScriptName` = 'npc_contaminated_puddle' WHERE `entry` = 71604;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71606;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_banner' WHERE `entry` = 71626;
UPDATE `creature_template` SET `ScriptName` = 'npc_amber_piece' WHERE `entry` = 71628;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71638;
UPDATE `creature_template` SET `ScriptName` = 'npc_shock_collar' WHERE `entry` = 71645;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_sniper' WHERE `entry` = 71656;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_jailer' WHERE `entry` = 71658;
UPDATE `creature_template` SET `ScriptName` = 'npc_golden_lotus_control' WHERE `entry` = 71683;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71694;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71696;
UPDATE `creature_template` SET `ScriptName` = 'npc_after_shock' WHERE `entry` = 71697;
UPDATE `creature_template` SET `ScriptName` = 'boss_sha_of_pride' WHERE `entry` = 71734;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_trigger' WHERE `entry` = 71740;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_prisoner' WHERE `entry` = 71742;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_prisoner' WHERE `entry` = 71749;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71751;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71752;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_prisoner' WHERE `entry` = 71763;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_ironblade' WHERE `entry` = 71770;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_archweaver' WHERE `entry` = 71771;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_warshaman' WHERE `entry` = 71773;
UPDATE `creature_template` SET `ScriptName` = 'npc_body_stalker' WHERE `entry` = 71787;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71788;
UPDATE `creature_template` SET `ScriptName` = 'npc_falling_ash' WHERE `entry` = 71789;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_weapon' WHERE `entry` = 71790;
UPDATE `creature_template` SET `ScriptName` = 'npc_ash_elemental' WHERE `entry` = 71827;
UPDATE `creature_template` SET `ScriptName` = 'boss_korkron_dark_shaman' WHERE `entry` = 71858;
UPDATE `creature_template` SET `ScriptName` = 'boss_korkron_dark_shaman' WHERE `entry` = 71859;
UPDATE `creature_template` SET `ScriptName` = 'boss_garrosh_hellscream' WHERE `entry` = 71865;
UPDATE `creature_template` SET `ScriptName` = 'npc_ssop_spoils' WHERE `entry` = 71889;
UPDATE `creature_template` SET `ScriptName` = 'npc_borer_drill' WHERE `entry` = 71906;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_trigger' WHERE `entry` = 71910;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_iron_juggernaut_passenger' WHERE `entry` = 71914;
UPDATE `creature_template` SET `ScriptName` = 'npc_wolf_maunt' WHERE `entry` = 71921;
UPDATE `creature_template` SET `ScriptName` = 'npc_wolf_maunt' WHERE `entry` = 71923;
UPDATE `creature_template` SET `ScriptName` = 'npc_iron_tomb' WHERE `entry` = 71941;
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_of_pride_manifest_of_pride' WHERE `entry` = 71946;
UPDATE `creature_template` SET `ScriptName` = 'npc_explosive_tar' WHERE `entry` = 71950;
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_of_pride_norushen' WHERE `entry` = 71965;
UPDATE `creature_template` SET `ScriptName` = 'boss_norushen' WHERE `entry` = 71967;
UPDATE `creature_template` SET `ScriptName` = 'npc_essence_of_corruption_challenge' WHERE `entry` = 71976;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_manifestation_of_corruption_challenge' WHERE `entry` = 71977;
UPDATE `creature_template` SET `ScriptName` = 'npc_garrosh_soldier' WHERE `entry` = 71979;
UPDATE `creature_template` SET `ScriptName` = 'npc_garrosh_soldier' WHERE `entry` = 71983;
UPDATE `creature_template` SET `ScriptName` = 'npc_garrosh_soldier' WHERE `entry` = 71984;
UPDATE `creature_template` SET `ScriptName` = 'npc_iron_star' WHERE `entry` = 71985;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_heal_ch_guardian' WHERE `entry` = 71995;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_heal_ch_melee_combtant' WHERE `entry` = 71996;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_heal_ch_caster' WHERE `entry` = 72000;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_heal_ch_greater_corruption' WHERE `entry` = 72001;
UPDATE `creature_template` SET `ScriptName` = 'npc_cutter_laser' WHERE `entry` = 72026;
UPDATE `creature_template` SET `ScriptName` = 'npc_crawler_mine' WHERE `entry` = 72050;
UPDATE `creature_template` SET `ScriptName` = 'npc_titanic_corruption' WHERE `entry` = 72051;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_trigger' WHERE `entry` = 72052;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_purifying_light' WHERE `entry` = 72065;
UPDATE `creature_template` SET `ScriptName` = 'npc_desecrated_weapon' WHERE `entry` = 72154;
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_of_pride_reflection' WHERE `entry` = 72172;
UPDATE `creature_template` SET `ScriptName` = 'npc_empowered_desecrated_weapon' WHERE `entry` = 72198;
UPDATE `creature_template` SET `ScriptName` = 'npc_heart_of_yshaarj' WHERE `entry` = 72215;
UPDATE `creature_template` SET `ScriptName` = 'npc_heart_of_yshaarj_realm' WHERE `entry` = 72228;
UPDATE `creature_template` SET `ScriptName` = 'npc_garrosh_soldier' WHERE `entry` = 72236;
UPDATE `creature_template` SET `ScriptName` = 'npc_garrosh_soldier' WHERE `entry` = 72238;
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_vortex' WHERE `entry` = 72239;
UPDATE `creature_template` SET `ScriptName` = 'boss_galakras' WHERE `entry` = 72249;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_elite_sniper' WHERE `entry` = 72261;
UPDATE `creature_template` SET `ScriptName` = 'npc_essence_of_corruption_released' WHERE `entry` = 72263;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_manifestation_of_corruption_released' WHERE `entry` = 72264;
UPDATE `creature_template` SET `ScriptName` = 'npc_garrosh_soldier' WHERE `entry` = 72272;
UPDATE `creature_template` SET `ScriptName` = 'boss_amalgam_of_corruption' WHERE `entry` = 72276;
UPDATE `creature_template` SET `ScriptName` = 'npc_lever' WHERE `entry` = 72281;
UPDATE `creature_template` SET `ScriptName` = 'npc_jaina_or_sylvana' WHERE `entry` = 72302;
UPDATE `creature_template` SET `ScriptName` = 'npc_varian_or_lorthemar' WHERE `entry` = 72311;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_ebon_stalker' WHERE `entry` = 72352;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_flameslinger' WHERE `entry` = 72353;
UPDATE `creature_template` SET `ScriptName` = 'npc_high_enforcer_thranok' WHERE `entry` = 72355;
UPDATE `creature_template` SET `ScriptName` = 'npc_master_cannoneer_dagryn' WHERE `entry` = 72356;
UPDATE `creature_template` SET `ScriptName` = 'npc_lieutenant_krugruk' WHERE `entry` = 72357;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_cannon' WHERE `entry` = 72358;
UPDATE `creature_template` SET `ScriptName` = 'npc_antiair_turret' WHERE `entry` = 72408;
UPDATE `creature_template` SET `ScriptName` = 'npc_korgra_the_snake' WHERE `entry` = 72456;
UPDATE `creature_template` SET `ScriptName` = 'npc_stone_statue' WHERE `entry` = 72535;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_residual_corruption' WHERE `entry` = 72550;
UPDATE `creature_template` SET `ScriptName` = 'npc_varian_or_lorthemar' WHERE `entry` = 72560;
UPDATE `creature_template` SET `ScriptName` = 'npc_jaina_or_sylvana' WHERE `entry` = 72561;
UPDATE `creature_template` SET `ScriptName` = 'npc_blind_hatred' WHERE `entry` = 72565;
UPDATE `creature_template` SET `ScriptName` = 'npc_blind_hatred_base' WHERE `entry` = 72595;
UPDATE `creature_template` SET `ScriptName` = 'npc_wildhammer_shaman' WHERE `entry` = 72640;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_passenger' WHERE `entry` = 72694;
UPDATE `creature_template` SET `ScriptName` = 'npc_blackfuse_trigger' WHERE `entry` = 72710;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 72787;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 72810;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 72828;
UPDATE `creature_template` SET `ScriptName` = 'npc_sha_of_pride_rift_of_corruption' WHERE `entry` = 72846;
UPDATE `creature_template` SET `ScriptName` = 'npc_norushen_lowerwalker' WHERE `entry` = 72872;
UPDATE `creature_template` SET `ScriptName` = 'npc_pressure_mine' WHERE `entry` = 72910;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_grunt' WHERE `entry` = 72941;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_flagbearer' WHERE `entry` = 72942;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_proto_drake' WHERE `entry` = 72943;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_bonecrusher' WHERE `entry` = 72945;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_demolisher' WHERE `entry` = 72947;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_tidal_shaman' WHERE `entry` = 72958;
UPDATE `creature_template` SET `ScriptName` = 'npc_lift_hook' WHERE `entry` = 72972;
UPDATE `creature_template` SET `ScriptName` = 'npc_unstable_iron_star' WHERE `entry` = 73059;
UPDATE `creature_template` SET `ScriptName` = 'npc_korkron_gunship' WHERE `entry` = 73065;
UPDATE `creature_template` SET `ScriptName` = 'npc_unstable_spark' WHERE `entry` = 73104;
UPDATE `creature_template` SET `ScriptName` = 'npc_starved_yeti' WHERE `entry` = 73184;
UPDATE `creature_template` SET `ScriptName` = 'npc_lorewalker_cho' WHERE `entry` = 73330;
UPDATE `creature_template` SET `ScriptName` = 'npc_demolitions' WHERE `entry` = 73493;
UPDATE `creature_template` SET `ScriptName` = 'npc_demolitions' WHERE `entry` = 73495;
UPDATE `creature_template` SET `ScriptName` = 'npc_captive_cave_bat' WHERE `entry` = 73522;
UPDATE `creature_template` SET `ScriptName` = 'npc_dragonmaw_grunt_h' WHERE `entry` = 73530;
UPDATE `creature_template` SET `ScriptName` = 'npc_demolitions' WHERE `entry` = 73550;
UPDATE `creature_template` SET `ScriptName` = 'npc_demolitions' WHERE `entry` = 73552;
UPDATE `creature_template` SET `ScriptName` = 'npc_galakras_south_tower' WHERE `entry` = 73565;
UPDATE `creature_template` SET `ScriptName` = 'npc_galakras_north_tower' WHERE `entry` = 73628;
UPDATE `creature_template` SET `ScriptName` = 'npc_horde_cannon' WHERE `entry` = 73665;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_spoil' WHERE `entry` = 73720;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_spoil' WHERE `entry` = 73721;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_spoil' WHERE `entry` = 73722;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 73723;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 73724;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 73725;
UPDATE `creature_template` SET `ScriptName` = 'npc_verees_or_aethas' WHERE `entry` = 73909;
UPDATE `creature_template` SET `ScriptName` = 'npc_verees_or_aethas' WHERE `entry` = 73910;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 73948;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 73949;
UPDATE `creature_template` SET `ScriptName` = 'npc_generic_sop_units' WHERE `entry` = 73951;
UPDATE `creature_template` SET `ScriptName` = 'npc_portal_to_reality' WHERE `entry` = 74007;
UPDATE `creature_template` SET `ScriptName` = 'npc_puddle_point' WHERE `entry` = 90000;
UPDATE `creature_template` SET `ScriptName` = 'npc_falling_ash_ground_stalker' WHERE `entry` = 90007;
UPDATE `gameobject_template` SET `ScriptName` = 'go_ssop_spoils' WHERE `entry` = 220823;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison' WHERE `entry` = 221676;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison' WHERE `entry` = 221677;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison' WHERE `entry` = 221678;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison' WHERE `entry` = 221679;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221750;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221751;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221752;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221753;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221754;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221755;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221756;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221757;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221758;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221759;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221760;
UPDATE `gameobject_template` SET `ScriptName` = 'go_sha_of_pride_corupted_prison_button' WHERE `entry` = 221761;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_lever' WHERE `entry` = 221771;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_lever' WHERE `entry` = 221773;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221804;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221816;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221820;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221822;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221878;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221885;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221893;
UPDATE `gameobject_template` SET `ScriptName` = 'go_generic_sop_box' WHERE `entry` = 221906;
UPDATE `gameobject_template` SET `ScriptName` = 'go_rope_skein' WHERE `entry` = 223281;
UPDATE `gameobject_template` SET `ScriptName` = 'go_rope_skein' WHERE `entry` = 223282;
UPDATE `gameobject_template` SET `ScriptName` = 'go_rope_skein' WHERE `entry` = 223287;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_OO_clash','spell_OO_corrupted_brew','spell_OO_dark_meditation','spell_OO_gouge','spell_after_extra_spell_effect','spell_ancient_barrier','spell_ancient_miasma','spell_asher_wall','spell_blackfuse_launch_sawblade','spell_blacksue_cm_explose','spell_blind_hatred','spell_blind_hatred_periodic','spell_boss_gusting_bomb','spell_boss_matter_scramble','spell_boss_matter_scramble_filter','spell_bottomless_pit','spell_bound_of_golden_lotus','spell_break_in_period','spell_breath_of_fire','spell_breath_of_yshaarj_dummy','spell_burst_of_anger','spell_call_bombartment','spell_caustic_blood','spell_clump_check','spell_corrosive_blast','spell_corrupt','spell_corrupted_prison','spell_crushing_fear','spell_cutter_laser_target','spell_death_from_above','spell_diminish','spell_disintegration_laser','spell_displased_energy','spell_eerie_fog','spell_empovered_gripping_despair','spell_empovered_whirling_corruption','spell_empowering_corruption','spell_encase_in_amber','spell_enter_realm_of_yshaarj','spell_essence_expel_corruption','spell_essence_of_yshaarj','spell_exploding_iron_star','spell_explosive_tar','spell_fallen_protectors_calamity','spell_fallen_protectors_defile_ground','spell_fallen_protectors_inferno_strike','spell_fallen_protectors_mark_of_anguish','spell_fallen_protectors_mark_of_anguish_select_first_target','spell_fallen_protectors_mark_of_anguish_transfer','spell_fallen_protectors_shadow_word_bane','spell_faulty_mutation','spell_fiery_edge_dmg','spell_fiery_edge_dummy','spell_fiery_edge_pre_dummy','spell_fixate','spell_fixate_iron_star','spell_forbidden_magic','spell_fracture','spell_freezing_breath','spell_galakras_flames_of_galakrond','spell_galakras_shattering_roar','spell_gene_splice','spell_generic_modifier_pride','spell_generic_stance','spell_genetic_modifications','spell_gift_of_titans','spell_gift_of_titans_aura','spell_growing_power','spell_gusting_bomb_dmg','spell_gusting_crane_kick','spell_hellscream_warsong','spell_heroic_catalyst','spell_heroic_shockwave','spell_hisek_fire','spell_hungry_periodic','spell_hurl_amber','spell_icy_blood','spell_icy_fear_dmg','spell_insane_calc_fiery_edge','spell_iron_prison','spell_iron_prison_dmg','spell_iron_tomb','spell_jade_tempest','spell_kds_unlock','spell_klaxxi_aim','spell_klaxxi_bloodletting','spell_klaxxi_gouge','spell_klaxxi_injection','spell_klaxxi_multi_shot','spell_klaxxi_mutate','spell_klaxxi_rapid_fire','spell_klaxxi_reave','spell_kunchong_devour','spell_landing_pose','spell_last_word','spell_lingering_corruption','spell_malice_dummy','spell_manifest_rage','spell_molten_fist','spell_mortar_barrage','spell_most_complicated_bomb','spell_norushen_blind_hatred','spell_norushen_challenge','spell_norushen_heal_test_dd','spell_on_conveyor','spell_pheromone_cloud','spell_player_touch_of_yshaarj','spell_power_iron_star','spell_power_regen','spell_rage_of_the_empress','spell_reaction_blue','spell_realm_of_yshaarj','spell_reave','spell_seismic_activity','spell_self_absorbed','spell_set_to_blow','spell_sha_of_pride_mark_of_arrogance','spell_sha_of_pride_overcome','spell_sha_of_pride_projection','spell_sha_of_pride_self_reflection','spell_sha_pool','spell_sha_pool_p_s','spell_shadow_volley','spell_shockwave_missile','spell_shockwave_missiles_tm','spell_snipe','spell_sonic_projection','spell_spark_of_life_creater','spell_split_visual','spell_spoils_encapsulated_pheromones','spell_spoils_staff_of_resonating_water','spell_stone_statue_summon','spell_store_kinetic_energy','spell_strength_of_the_stone','spell_sundering_blow','spell_supernova','spell_swelling_pride','spell_swirl','spell_swirl_searcher','spell_tenderizing_strikes_dmg','spell_thok_deafening_screech','spell_torment','spell_torment_periodic','spell_touch_of_yshaarj','spell_toxic_mist','spell_transition_visual','spell_unleashed_anger','spell_unlocking','spell_unstable_defense_system_dummy','spell_unstable_iron_star_dummy','spell_vicious_assaullt','spell_vicious_assaullt_periodic','spell_weakened_resolve','spell_whirling','spell_whirling_corruption','spell_whirling_target');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(143501, 'spell_after_extra_spell_effect'),
(143503, 'spell_after_extra_spell_effect'),
(143716, 'spell_after_extra_spell_effect'),
(143872, 'spell_after_extra_spell_effect'),
(142862, 'spell_ancient_barrier'),
(142861, 'spell_ancient_miasma'),
(144070, 'spell_asher_wall'),
(143265, 'spell_blackfuse_launch_sawblade'),
(149146, 'spell_blacksue_cm_explose'),
(145227, 'spell_blind_hatred'),
(145573, 'spell_blind_hatred_periodic'),
(145712, 'spell_boss_gusting_bomb'),
(145288, 'spell_boss_matter_scramble'),
(145369, 'spell_boss_matter_scramble_filter'),
(146703, 'spell_bottomless_pit'),
(143497, 'spell_bound_of_golden_lotus'),
(145269, 'spell_break_in_period'),
(146222, 'spell_breath_of_fire'),
(142842, 'spell_breath_of_yshaarj_dummy'),
(147082, 'spell_burst_of_anger'),
(147120, 'spell_call_bombartment'),
(142315, 'spell_caustic_blood'),
(143430, 'spell_clump_check'),
(143436, 'spell_corrosive_blast'),
(145052, 'spell_corrupt'),
(144574, 'spell_corrupted_prison'),
(144636, 'spell_corrupted_prison'),
(144683, 'spell_corrupted_prison'),
(144684, 'spell_corrupted_prison'),
(147319, 'spell_crushing_fear'),
(146325, 'spell_cutter_laser_target'),
(144210, 'spell_death_from_above'),
(143666, 'spell_diminish'),
(143867, 'spell_disintegration_laser'),
(142913, 'spell_displased_energy'),
(142945, 'spell_eerie_fog'),
(145195, 'spell_empovered_gripping_despair'),
(145037, 'spell_empovered_whirling_corruption'),
(145043, 'spell_empowering_corruption'),
(149536, 'spell_empowering_corruption'),
(142564, 'spell_encase_in_amber'),
(144867, 'spell_enter_realm_of_yshaarj'),
(144479, 'spell_essence_expel_corruption'),
(143857, 'spell_essence_of_yshaarj'),
(144798, 'spell_exploding_iron_star'),
(144919, 'spell_explosive_tar'),
(143491, 'spell_fallen_protectors_calamity'),
(143961, 'spell_fallen_protectors_defile_ground'),
(143962, 'spell_fallen_protectors_inferno_strike'),
(143840, 'spell_fallen_protectors_mark_of_anguish'),
(143822, 'spell_fallen_protectors_mark_of_anguish_select_first_target'),
(143842, 'spell_fallen_protectors_mark_of_anguish_transfer'),
(143434, 'spell_fallen_protectors_shadow_word_bane'),
(148589, 'spell_faulty_mutation'),
(142809, 'spell_fiery_edge_dmg'),
(142808, 'spell_fiery_edge_dummy'),
(142811, 'spell_fiery_edge_pre_dummy'),
(143445, 'spell_fixate'),
(147665, 'spell_fixate_iron_star'),
(145230, 'spell_forbidden_magic'),
(148513, 'spell_fracture'),
(143773, 'spell_freezing_breath'),
(146991, 'spell_galakras_flames_of_galakrond'),
(147204, 'spell_galakras_shattering_roar'),
(144379, 'spell_generic_modifier_pride'),
(144774, 'spell_generic_modifier_pride'),
(144788, 'spell_generic_modifier_pride'),
(144836, 'spell_generic_modifier_pride'),
(144911, 'spell_generic_modifier_pride'),
(145320, 'spell_generic_modifier_pride'),
(146818, 'spell_generic_modifier_pride'),
(147198, 'spell_generic_modifier_pride'),
(147207, 'spell_generic_modifier_pride'),
(143589, 'spell_generic_stance'),
(143593, 'spell_generic_stance'),
(143594, 'spell_generic_stance'),
(143355, 'spell_genetic_modifications'),
(143373, 'spell_gene_splice'),
(146595, 'spell_gift_of_titans'),
(144359, 'spell_gift_of_titans_aura'),
(146999, 'spell_growing_power'),
(145716, 'spell_gusting_bomb_dmg'),
(146180, 'spell_gusting_crane_kick'),
(144821, 'spell_hellscream_warsong'),
(142729, 'spell_heroic_catalyst'),
(142730, 'spell_heroic_catalyst'),
(143716, 'spell_heroic_shockwave'),
(142950, 'spell_hisek_fire'),
(142630, 'spell_hungry_periodic'),
(143759, 'spell_hurl_amber'),
(143800, 'spell_icy_blood'),
(145735, 'spell_icy_fear_dmg'),
(142416, 'spell_insane_calc_fiery_edge'),
(144330, 'spell_iron_prison'),
(144331, 'spell_iron_prison_dmg'),
(144328, 'spell_iron_tomb'),
(148582, 'spell_jade_tempest'),
(145690, 'spell_kds_unlock'),
(142948, 'spell_klaxxi_aim'),
(143280, 'spell_klaxxi_bloodletting'),
(143939, 'spell_klaxxi_gouge'),
(143339, 'spell_klaxxi_injection'),
(144839, 'spell_klaxxi_multi_shot'),
(143337, 'spell_klaxxi_mutate'),
(143243, 'spell_klaxxi_rapid_fire'),
(148676, 'spell_klaxxi_reave'),
(142649, 'spell_kunchong_devour'),
(144157, 'spell_landing_pose'),
(144370, 'spell_last_word'),
(144514, 'spell_lingering_corruption'),
(147229, 'spell_malice_dummy'),
(147011, 'spell_manifest_rage'),
(148518, 'spell_molten_fist'),
(144554, 'spell_mortar_barrage'),
(147897, 'spell_most_complicated_bomb'),
(147916, 'spell_most_complicated_bomb'),
(145571, 'spell_norushen_blind_hatred'),
(144849, 'spell_norushen_challenge'),
(144850, 'spell_norushen_challenge'),
(144851, 'spell_norushen_challenge'),
(144521, 'spell_norushen_heal_test_dd'),
(144287, 'spell_on_conveyor'),
(143027, 'spell_OO_clash'),
(143019, 'spell_OO_corrupted_brew'),
(143546, 'spell_OO_dark_meditation'),
(143301, 'spell_OO_gouge'),
(148762, 'spell_pheromone_cloud'),
(145599, 'spell_player_touch_of_yshaarj'),
(144616, 'spell_power_iron_star'),
(143345, 'spell_power_regen'),
(145812, 'spell_rage_of_the_empress'),
(142935, 'spell_reaction_blue'),
(144954, 'spell_realm_of_yshaarj'),
(142272, 'spell_reave'),
(144483, 'spell_seismic_activity'),
(145861, 'spell_self_absorbed'),
(145987, 'spell_set_to_blow'),
(148515, 'spell_shadow_volley'),
(144351, 'spell_sha_of_pride_mark_of_arrogance'),
(144843, 'spell_sha_of_pride_overcome'),
(146822, 'spell_sha_of_pride_projection'),
(144800, 'spell_sha_of_pride_self_reflection'),
(143460, 'spell_sha_pool'),
(143461, 'spell_sha_pool_p_s'),
(144660, 'spell_shockwave_missile'),
(144661, 'spell_shockwave_missile'),
(144662, 'spell_shockwave_missile'),
(144663, 'spell_shockwave_missile'),
(144664, 'spell_shockwave_missile'),
(143641, 'spell_shockwave_missiles_tm'),
(144658, 'spell_shockwave_missiles_tm'),
(143217, 'spell_snipe'),
(143765, 'spell_sonic_projection'),
(142695, 'spell_spark_of_life_creater'),
(143020, 'spell_split_visual'),
(142524, 'spell_spoils_encapsulated_pheromones'),
(146098, 'spell_spoils_staff_of_resonating_water'),
(145489, 'spell_stone_statue_summon'),
(143709, 'spell_store_kinetic_energy'),
(145998, 'spell_strength_of_the_stone'),
(143494, 'spell_sundering_blow'),
(146815, 'spell_supernova'),
(144400, 'spell_swelling_pride'),
(143309, 'spell_swirl'),
(125925, 'spell_swirl_searcher'),
(142929, 'spell_tenderizing_strikes_dmg'),
(143343, 'spell_thok_deafening_screech'),
(142942, 'spell_torment'),
(142983, 'spell_torment_periodic'),
(145065, 'spell_touch_of_yshaarj'),
(145171, 'spell_touch_of_yshaarj'),
(144089, 'spell_toxic_mist'),
(144852, 'spell_transition_visual'),
(145222, 'spell_transition_visual'),
(145216, 'spell_unleashed_anger'),
(146589, 'spell_unlocking'),
(145685, 'spell_unstable_defense_system_dummy'),
(148299, 'spell_unstable_iron_star_dummy'),
(143980, 'spell_vicious_assaullt'),
(143981, 'spell_vicious_assaullt'),
(143982, 'spell_vicious_assaullt'),
(143984, 'spell_vicious_assaullt'),
(143985, 'spell_vicious_assaullt'),
(143977, 'spell_vicious_assaullt_periodic'),
(147207, 'spell_weakened_resolve'),
(143701, 'spell_whirling'),
(144989, 'spell_whirling_corruption'),
(143704, 'spell_whirling_target');
DELETE FROM `areatrigger_scripts` WHERE `entry` IN (9189,9190,9194,9238,9239,9240,9250,9251,9252,9253,9357,9360,9361,9371,9493);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(9189, 'at_blackfuse_pipe'),
(9190, 'at_blackfuse_pipe'),
(9194, 'at_blackfuse_pipe'),
(9238, 'at_blackfuse_pipe'),
(9239, 'at_blackfuse_pipe'),
(9240, 'at_blackfuse_pipe'),
(9250, 'at_blackfuse_pipe'),
(9251, 'at_blackfuse_pipe'),
(9252, 'at_blackfuse_pipe'),
(9253, 'at_blackfuse_pipe'),
(9357, 'at_siege_of_orgrimmar_sniper_shoot_me'),
(9360, 'at_galakras_towers'),
(9361, 'at_galakras_towers'),
(9371, 'at_blackfuse_pipe'),
(9493, 'at_blackfuse_pipe');
-- not bound to anything in LegionCore's database either: at_siege_of_orgrimmar_portal_to_orgrimmar, npc_amber_player, npc_flash_stalker, npc_foul_slime, npc_mortar_barrage, npc_ravager, npc_thok_ice_tomb, npc_toxic_storm, npc_toxic_tornado, spell_fallen_protectors_shadow_weakness_proc, spell_galakras_tower_rope_jump
