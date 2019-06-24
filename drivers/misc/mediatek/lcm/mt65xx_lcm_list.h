/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef __MT65XX_LCM_LIST_H__
#define __MT65XX_LCM_LIST_H__

#include <lcm_drv.h>

#ifdef VENDOR_EDIT
/* LiPing-m@PSW.MM.Display.LCD.Machine, 2017/11/03, Add for porting 17331 lcd driver */
extern LCM_DRIVER oppo17321_tianma_td4310_1080p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17321_boe_td4310_1080p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17321_dsjm_td4310_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2017/12/08, Add for lcm ic himax83221b */
extern LCM_DRIVER oppo_himax83112b_1080p_dsi_cmd_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2017/12/22, Add for lcm ic td4330 */
extern LCM_DRIVER oppo_jdi_td4330_1080p_dsi_cmd_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2017/12/27, Add for lcm ic samsung ams628nw */
extern LCM_DRIVER oppo_samsung_ams628nw_1080p_dsi_cmd_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/1/20, Add for lcm ic jdi td4310 */
extern LCM_DRIVER oppo_jdi_td4310_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/1/23, Add for lcm ic truly nt36672 */
extern LCM_DRIVER oppo_truly_nt36672_auo_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/1/24, Add for lcm ic tianma nt36672 */
extern LCM_DRIVER oppo_tianma_nt36672_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/2/5, Add for lcm ic jdi nt36672 */
extern LCM_DRIVER oppo_jdi_nt36672_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/2/5, Add for lcm ic auo nt36672 */
extern LCM_DRIVER oppo_auo_nt36672_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/2/27, Add for lcm ic dpt jdi nt36672 */
extern LCM_DRIVER oppo_dpt_jdi_nt36672_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/2/27, Add for lcm ic dsjm nt36672 */
extern LCM_DRIVER oppo_dsjm_nt36672_1080p_dsi_vdo_lcm_drv;
/* Ling.Guo@PSW.MM.Display.LCD.Machine 2018/3/27, Add for lcm ic samsung ams628nw lsi */
extern LCM_DRIVER oppo_samsung_ams628nw_lsi_1080p_dsi_cmd_lcm_drv;
/* Guoqiang.jiang@PSW.MM.Display.LCD.Machine 2018/4/13, Add for lcm ic dpt hx83112a */
extern LCM_DRIVER oppo_dpt_jdi_hx83112a_1080p_dsi_vdo_lcm_drv;
/* Guoqiang.jiang@PSW.MM.Display.LCD.Machine 2018/4/27, Add for project 17111 */
extern LCM_DRIVER oppo17051_tianma_ft8006m_720p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17051_boe_ft8006m_720p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17101_truly_ft8006m_720p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17101_truly_nt36525_720p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17101_tianma_nt36525_720p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17101_innolux_nt36525_720p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17101_boe_nt36525_720p_dsi_vdo_lcm_drv;
extern LCM_DRIVER oppo17101_boeb8_ft8006m_720p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/5/21, Add for lcm ic tianma nt36672a */
extern LCM_DRIVER oppo18311_tianma_nt36672_1080p_dsi_vdo_lcm_drv;
/* Guoqiang.jiang@PSW.MM.Display.LCD.Machine 2018/5/21, Add for lcm ic dpt jdi td4330*/
extern LCM_DRIVER oppo_dpt_jdi_td4330_1080p_dsi_cmd_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/6/1, Add for lcm ic depute nt36672a */
extern LCM_DRIVER oppo18311_depute_nt36672_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/6/8, Add for lcm ic dsjm himax83112a */
extern LCM_DRIVER oppo18311_dsjm_himax83112a_1080p_dsi_vdo_lcm_drv;
/* LiPing-m@PSW.MM.Display.LCD.Machine 2018/7/9, Add for lcm ic truly td4320 */
extern LCM_DRIVER oppo18311_truly_td4320_1080p_dsi_vdo_lcm_drv;
/* Shizeke@PSW.MM.Display.LCD.Machine 2018/8/24, Add for lcm ic dsjm himax83112a */
extern LCM_DRIVER oppo18611_dsjm_himax83112a_1080p_dsi_vdo_lcm_drv;
#endif /* VENDOR_EDIT */
extern LCM_DRIVER otm1282a_hd720_dsi_vdo_60hz_lcm_drv;
extern LCM_DRIVER otm1282a_hd720_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_8163_lcm_drv;
extern LCM_DRIVER nt35523_wxga_dsi_vdo_8163_lcm_drv;
extern LCM_DRIVER vvx10f008b00_wuxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER r63319_wqhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER nt35598_wqhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER lp079x01_lcm_drv;
extern LCM_DRIVER hx8369_lcm_drv;
extern LCM_DRIVER hx8369_6575_lcm_drv;
extern LCM_DRIVER hx8363_6575_dsi_lcm_drv;
extern LCM_DRIVER hx8363_6575_dsi_hvga_lcm_drv;
extern LCM_DRIVER hx8363_6575_dsi_qvga_lcm_drv;
extern LCM_DRIVER hx8363b_wvga_dsi_cmd_drv;
extern LCM_DRIVER bm8578_lcm_drv;
extern LCM_DRIVER nt35582_mcu_lcm_drv;
extern LCM_DRIVER nt35582_mcu_6575_lcm_drv;
extern LCM_DRIVER nt35582_rgb_6575_lcm_drv;
extern LCM_DRIVER hx8357b_lcm_drv;
extern LCM_DRIVER hx8357c_hvga_dsi_cmd_drv;
extern LCM_DRIVER hx8369_dsi_lcm_drv;
extern LCM_DRIVER hx8369_dsi_6575_lcm_drv;
extern LCM_DRIVER hx8369_dsi_6575_hvga_lcm_drv;
extern LCM_DRIVER hx8369_dsi_6575_qvga_lcm_drv;
extern LCM_DRIVER ili9881c_hd_dsi_vdo_ilitek_nt50358_lcm_drv;
extern LCM_DRIVER hx8369_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8369b_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8369b_wvga_dsi_vdo_drv;
extern LCM_DRIVER hx8389b_qhd_dsi_vdo_drv;
extern LCM_DRIVER hx8369_hvga_lcm_drv;
extern LCM_DRIVER ili9481_lcm_drv;
extern LCM_DRIVER nt35582_lcm_drv;
extern LCM_DRIVER s6d0170_lcm_drv;
extern LCM_DRIVER spfd5461a_lcm_drv;
extern LCM_DRIVER ta7601_lcm_drv;
extern LCM_DRIVER tft1p3037_lcm_drv;
extern LCM_DRIVER ha5266_lcm_drv;
extern LCM_DRIVER hsd070idw1_lcm_drv;
extern LCM_DRIVER lg4571_lcm_drv;
extern LCM_DRIVER lg4573b_wvga_dsi_vdo_lh430mv1_drv;
extern LCM_DRIVER lvds_wsvga_lcm_drv;
extern LCM_DRIVER lvds_wsvga_ti_lcm_drv;
extern LCM_DRIVER lvds_wsvga_ti_n_lcm_drv;
extern LCM_DRIVER nt35565_3d_lcm_drv;
extern LCM_DRIVER tm070ddh03_lcm_drv;
extern LCM_DRIVER r61408_lcm_drv;
extern LCM_DRIVER r61408_wvga_dsi_cmd_drv;
extern LCM_DRIVER nt35510_lcm_drv;
extern LCM_DRIVER nt35510_dpi_lcm_drv;
extern LCM_DRIVER nt35510_hvga_lcm_drv;
extern LCM_DRIVER nt35510_qvga_lcm_drv;
extern LCM_DRIVER nt35510_wvga_dsi_cmd_drv;
extern LCM_DRIVER nt35510_6517_lcm_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_hvga_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_fwvga_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_qvga_drv;
extern LCM_DRIVER nt35510_dsi_vdo_6572_drv;
extern LCM_DRIVER nt35510_dpi_6572_lcm_drv;
extern LCM_DRIVER nt35510_mcu_6572_lcm_drv;
extern LCM_DRIVER nt51012_hd720_dsi_vdo_lcm_drv;
extern LCM_DRIVER r63303_idisplay_lcm_drv;
extern LCM_DRIVER hj080ia_lcm_drv;
extern LCM_DRIVER hj101na02a_lcm_drv;
extern LCM_DRIVER hj101na02a_8135_lcm_drv;
extern LCM_DRIVER hsd070pfw3_lcm_drv;
extern LCM_DRIVER hsd070pfw3_8135_lcm_drv;
extern LCM_DRIVER cm_n070ice_dsi_vdo_lcm_drv;
extern LCM_DRIVER ej101ia_lcm_drv;
extern LCM_DRIVER scf0700m48ggu02_lcm_drv;
extern LCM_DRIVER nt35510_fwvga_lcm_drv;
#if defined(GN_SSD2825_SMD_S6E8AA)
extern LCM_DRIVER gn_ssd2825_smd_s6e8aa;
#endif
extern LCM_DRIVER nt35517_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8369_dsi_bld_lcm_drv;
extern LCM_DRIVER hx8369_dsi_tm_lcm_drv;
extern LCM_DRIVER otm1280a_hd720_dsi_cmd_drv;
extern LCM_DRIVER otm8018b_dsi_vdo_lcm_drv;
extern LCM_DRIVER otm8018b_dsi_vdo_txd_fwvga_lcm_drv;
extern LCM_DRIVER nt35512_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35512_wvga_dsi_vdo_boe_drv;
extern LCM_DRIVER hx8369_rgb_6585_fpga_lcm_drv;
extern LCM_DRIVER hx8369_rgb_6572_fpga_lcm_drv;
extern LCM_DRIVER hx8369_mcu_6572_lcm_drv;
extern LCM_DRIVER hx8369a_wvga_dsi_cmd_drv;
extern LCM_DRIVER hx8369a_wvga_dsi_vdo_drv;
extern LCM_DRIVER hx8392a_dsi_cmd_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_cmd_3lane_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_cmd_wvga_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_cmd_fwvga_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_cmd_fwvga_plus_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_cmd_qhd_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_vdo_2lane_lcm_drv;
extern LCM_DRIVER hx8392a_dsi_vdo_3lane_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER ssd2075_hd720_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_fwvga_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_wvga_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_qhd_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_cmi_lcm_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_ipsboe_lcm_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_ipsboe_wvga_lcm_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_ipsboe_fwvga_lcm_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_ips9k1431_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_tft9k1342_drv;
extern LCM_DRIVER bp070ws1_lcm_drv;
extern LCM_DRIVER bp101wx1_lcm_drv;
extern LCM_DRIVER bp101wx1_n_lcm_drv;
extern LCM_DRIVER nt35516_qhd_rav4_lcm_drv;
extern LCM_DRIVER r63311_fhd_dsi_vdo_sharp_lcm_drv;
extern LCM_DRIVER r81592_hvga_dsi_cmd_drv;
extern LCM_DRIVER rm68190_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35596_fhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_tps65132_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_vdo_truly_tps65132_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_vdo_truly_nt50358_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_720p_lcm_drv;
extern LCM_DRIVER nt35521_hd_dsi_vdo_truly_nt50358_lcm_drv;
extern LCM_DRIVER nt35521_hd_dsi_vdo_truly_nt50358_fwvga_lcm_drv;
extern LCM_DRIVER nt35521_hd_dsi_vdo_truly_nt50358_qhd_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_qhd_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_fwvga_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_wvga_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_tps65132_720p_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_6735_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_6735_720p_lcm_drv;
extern LCM_DRIVER nt35596_fhd_dsi_vdo_yassy_lcm_drv;
extern LCM_DRIVER nt35596_hd720_dsi_vdo_truly_tps65132_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_truly2_lcm_drv;
extern LCM_DRIVER nt36672_fhdp_dsi_vdo_auo_lcm_drv;
extern LCM_DRIVER nt36672_fhdp_dsi_vdo_auo_laneswap_lcm_drv;
extern LCM_DRIVER otm9608_wvga_dsi_cmd_drv;
extern LCM_DRIVER otm9608_fwvga_dsi_cmd_drv;
extern LCM_DRIVER otm9608_qhd_dsi_cmd_drv;
extern LCM_DRIVER otm9608_qhd_dsi_vdo_drv;
extern LCM_DRIVER otm8009a_fwvga_dsi_cmd_tianma_lcm_drv;
extern LCM_DRIVER otm8009a_fwvga_dsi_vdo_tianma_lcm_drv;
extern LCM_DRIVER hx8389b_qhd_dsi_vdo_tianma_lcm_drv;
extern LCM_DRIVER cm_otc3108bhv161_dsi_vdo_lcm_drv;
extern LCM_DRIVER auo_b079xat02_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8389b_qhd_dsi_vdo_tianma055xdhp_lcm_drv;
extern LCM_DRIVER cpt_claa101fp01_dsi_vdo_lcm_drv;
extern LCM_DRIVER cpt_claa101fp01_dsi_vdo_8163_lcm_drv;
extern LCM_DRIVER h070d_18dm_lcm_drv;
extern LCM_DRIVER hx8394a_hd720_dsi_vdo_tianma_lcm_drv;
extern LCM_DRIVER hx8394d_hd720_dsi_vdo_tianma_lcm_drv;
extern LCM_DRIVER cpt_clap070wp03xg_sn65dsi83_lcm_drv;
extern LCM_DRIVER nt35520_hd720_tm_lcm_drv;
extern LCM_DRIVER nt35520_hd720_boe_lcm_drv;
extern LCM_DRIVER nt35521_hd720_dsi_vdo_boe_lcm_drv;
extern LCM_DRIVER nt35521_hd720_tm_lcm_drv;
extern LCM_DRIVER r69429_wuxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER r69429_wuxga_dsi_cmd_lcm_drv;
extern LCM_DRIVER rm68210_hd720_dsi_ufoe_cmd_lcm_drv;
extern LCM_DRIVER r63311_fhd_dsi_vedio_lcm_drv;
extern LCM_DRIVER otm1283a_6589_hd_dsi;
extern LCM_DRIVER hx8394a_hd720_dsi_vdo_tianma_v2_lcm_drv;
extern LCM_DRIVER cpt_clap070wp03xg_lvds_lcm_drv;
extern LCM_DRIVER hx8369_dsi_cmd_6571_lcm_drv;
extern LCM_DRIVER hx8369_dsi_vdo_6571_lcm_drv;
extern LCM_DRIVER hx8369_dbi_6571_lcm_drv;
extern LCM_DRIVER hx8369_dpi_6571_lcm_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6571_lcm_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6571_hvga_lcm_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6571_qvga_lcm_drv;
extern LCM_DRIVER nt35510_dsi_vdo_6571_lcm_drv;
extern LCM_DRIVER nt35510_dbi_6571_lcm_drv;
extern LCM_DRIVER nt35510_dpi_6571_lcm_drv;
extern LCM_DRIVER nt35590_dsi_cmd_6571_fwvga_lcm_drv;
extern LCM_DRIVER nt35590_dsi_cmd_6571_qhd_lcm_drv;
extern LCM_DRIVER it6151_edp_dsi_video_sharp_lcm_drv;
extern LCM_DRIVER nt35517_qhd_dsi_vdo_lcm_drv;
extern LCM_DRIVER otm1283a_hd720_dsi_vdo_tm_lcm_drv;
extern LCM_DRIVER otm1284a_hd720_dsi_vdo_tm_lcm_drv;
extern LCM_DRIVER otm1285a_hd720_dsi_vdo_tm_lcm_drv;
extern LCM_DRIVER hx8389b_qhd_dsi_vdo_lgd_lcm_drv;
extern LCM_DRIVER it6151_fhd_edp_dsi_video_auo_lcm_drv;
extern LCM_DRIVER tf070mc_rgb_v18_mt6571_lcm_drv;
extern LCM_DRIVER zs070ih5015b3h6_mt6571_lcm_drv;
extern LCM_DRIVER a080ean01_dsi_vdo_lcm_drv;
extern LCM_DRIVER it6121_g156xw01v1_lvds_vdo_lcm_drv;
extern LCM_DRIVER cpt_clap070wp03xg_lvds_lcm_drv;
extern LCM_DRIVER r63315_fhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER it6151_lp079qx1_edp_dsi_video_lcm_drv;
extern LCM_DRIVER RX_498HX_615B_lcm_drv;
extern LCM_DRIVER RX_498HX_615B_82_lcm_drv;
extern LCM_DRIVER ili9806c_dsi_vdo_djn_fwvga_lcm_drv;
extern LCM_DRIVER hx8389b_hd720_dsi_vdo_drv;
extern LCM_DRIVER r69338_hd720_dsi_vdo_jdi_drv;
extern LCM_DRIVER r69338_hd720_5in_dsi_vdo_jdi_dw8768_drv;
extern LCM_DRIVER db7436_dsi_vdo_fwvga_drv;
extern LCM_DRIVER r63417_fhd_dsi_cmd_truly_nt50358_lcm_drv;
extern LCM_DRIVER r63417_fhd_dsi_cmd_truly_nt50358_720p_lcm_drv;
extern LCM_DRIVER r63417_fhd_dsi_cmd_truly_nt50358_qhd_lcm_drv;
extern LCM_DRIVER r63417_fhd_dsi_vdo_truly_nt50358_lcm_drv;
extern LCM_DRIVER r63419_wqhd_truly_phantom_cmd_lcm_drv;
extern LCM_DRIVER r63419_wqhd_truly_phantom_vdo_lcm_drv;
extern LCM_DRIVER r63419_fhd_truly_phantom_lcm_drv;
extern LCM_DRIVER r63423_wqhd_truly_phantom_lcm_drv;
extern LCM_DRIVER kd070d5450nha6_rgb_dpi_lcm_drv;
extern LCM_DRIVER kr101ia2s_dsi_vdo_lcm_drv;
extern LCM_DRIVER kr070ia4t_dsi_vdo_lcm_drv;
extern LCM_DRIVER r69338_hd720_dsi_vdo_jdi_dw8755a_drv;
extern LCM_DRIVER otm9605a_qhd_dsi_vdo_drv;
extern LCM_DRIVER ili9806e_dsi_vdo_fwvga_drv;
extern LCM_DRIVER otm1906a_fhd_dsi_cmd_auto_lcm_drv;
extern LCM_DRIVER clap070wp03xg_lvds_lcm_drv;
extern LCM_DRIVER nt35523_wxga_dsi_vdo_boe_lcm_drv;
extern LCM_DRIVER otm1906b_fhd_dsi_cmd_jdi_tps65132_lcm_drv;
extern LCM_DRIVER otm1906b_fhd_dsi_cmd_jdi_tps65132_mt6797_lcm_drv;
extern LCM_DRIVER otm1906b_fhd_dsi_vdo_jdi_tps65132_mt6797_lcm_drv;
extern LCM_DRIVER s6e3fa2_fhd1080_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35523_wsvga_dsi_vdo_boe_lcm_drv;
extern LCM_DRIVER ek79023_dsi_wsvga_vdo_lcm_drv;
extern LCM_DRIVER nt35532_fhd_dsi_vdo_sharp_lcm_drv;
extern LCM_DRIVER s6d7aa0_wxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8394c_wxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER it6151_lp079qx1_edp_dsi_video_8163evb_lcm_drv;
extern LCM_DRIVER sy20810800210132_wuxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_cmd_truly_nt50358_720p_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_cmd_truly_nt50358_qhd_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_cmd_truly_nt50358_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_vdo_truly_nt50358_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_truly_nt50358_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_cmd_truly_rt5081_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_vdo_truly_rt5081_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_vdo_truly_rt5081_720p_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_vdo_truly_rt5081_qhd_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_truly_rt5081_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_truly_rt5081_720p_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_truly_rt5081_qhd_lcm_drv;
extern LCM_DRIVER nt35510_dsi_cmd_lcm_drv;
extern LCM_DRIVER rm69032_dsi_cmd_lcm_drv;
extern LCM_DRIVER st7789h2_dbi_lcm_drv;
extern LCM_DRIVER ek79007_wsvgalnl_dsi_vdo_lcm_drv;
extern LCM_DRIVER cm_n070ice_dsi_vdo_mt8173_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_extern_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_2th_lcm_drv;
extern LCM_DRIVER r69429_wqxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8394c_wxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35595_truly_fhd_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt36850_wqhd_dsi_2k_cmd_lcm_drv;
extern LCM_DRIVER s6e3ha3_wqhd_2k_cmd_lcm_drv;
extern LCM_DRIVER s6e3fa3_fhd_cmd_lcm_drv;
extern LCM_DRIVER nt35595_fhd_dsi_cmd_truly_nt50358_720p_extern_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_cmd_auo_nt50358_laneswap_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_vdo_auo_nt50358_laneswap_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_cmd_auo_nt50358_laneswap_mt6799_lcm_drv;
extern LCM_DRIVER nt35695_fhd_dsi_vdo_auo_nt50358_laneswap_mt6799_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_auo_rt5081_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_auo_rt5081_720p_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_auo_rt5081_qhd_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_vdo_auo_rt5081_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_vdo_auo_rt5081_720p_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_vdo_auo_rt5081_qhd_lcm_drv;
extern LCM_DRIVER claa101fp01_dsi_vdo_lcm_drv;
extern LCM_DRIVER r61322_fhd_dsi_vdo_sharp_lfr_lcm_drv;
extern LCM_DRIVER s6e3ha3_wqhd_2k_cmd_laneswap_drv;
extern LCM_DRIVER nt36380_wqhd_vdo_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_auo_nt50358_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_vdo_auo_nt50358_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_auo_nt50358_720p_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_auo_nt50358_hdp_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_cmd_auo_nt50358_qhd_lcm_drv;
extern LCM_DRIVER ili9881c_hdp_dsi_vdo_ilitek_rt5081_lcm_drv;
extern LCM_DRIVER oppo_tianma_td4310_fhdp_dsi_vdo_rt5081_lcm_drv;
extern LCM_DRIVER otm1287_wxga_dsi_vdo_auo_guoxian_lcm_drv;
extern LCM_DRIVER jd9365_wxga_dsi_vdo_hsd_pingbo_lcm_drv;
extern LCM_DRIVER nt35695B_fhd_dsi_vdo_auo_rt5081_hdp_lcm_drv;
extern LCM_DRIVER oppo_tianma_td4310_fhdp_dsi_vdo_nt50358_lcm_drv;
extern LCM_DRIVER nt36672_fhdp_dsi_vdo_tianma_nt50358_lcm_drv;
extern LCM_DRIVER jd9365_hd720_dsi_lcm_drv;
extern LCM_DRIVER otm1901a_fhd_dsi_vdo_tpv_lcm_drv;
extern LCM_DRIVER st7789h2_dbi_c_3wire_lcm_drv;
#ifdef BUILD_LK
extern void mdelay(unsigned long msec);
#endif

#endif
