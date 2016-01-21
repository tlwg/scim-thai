/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 2006 Theppitak Karoonboonyanan <theppitak@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <utility>

#include "scim_thai_keymap.h"

static const uint32 __us_to_thai_ketmanee [] = {
  /* SCIM_KEY_exclam */             SCIM_KEY_plus,
  /* SCIM_KEY_quotedbl */           SCIM_KEY_period,
  /* SCIM_KEY_numbersign */         SCIM_KEY_Thai_leksong,
  /* SCIM_KEY_dollar */             SCIM_KEY_Thai_leksam,
  /* SCIM_KEY_percent */            SCIM_KEY_Thai_leksi,
  /* SCIM_KEY_ampersand */          SCIM_KEY_Thai_baht,
  /* SCIM_KEY_quoteright */         SCIM_KEY_Thai_ngongu,
  /* SCIM_KEY_parenleft */          SCIM_KEY_Thai_lekhok,
  /* SCIM_KEY_parenright */         SCIM_KEY_Thai_lekchet,
  /* SCIM_KEY_asterisk */           SCIM_KEY_Thai_lekha,
  /* SCIM_KEY_plus */               SCIM_KEY_Thai_lekkao,
  /* SCIM_KEY_comma */              SCIM_KEY_Thai_moma,
  /* SCIM_KEY_minus */              SCIM_KEY_Thai_khokhai,
  /* SCIM_KEY_period */             SCIM_KEY_Thai_saraaimaimuan,
  /* SCIM_KEY_slash */              SCIM_KEY_Thai_fofa,
  /* SCIM_KEY_0 */                  SCIM_KEY_Thai_chochan,
  /* SCIM_KEY_1 */                  SCIM_KEY_Thai_lakkhangyao,
  /* SCIM_KEY_2 */                  SCIM_KEY_slash,
  /* SCIM_KEY_3 */                  SCIM_KEY_minus,
  /* SCIM_KEY_4 */                  SCIM_KEY_Thai_phosamphao,
  /* SCIM_KEY_5 */                  SCIM_KEY_Thai_thothung,
  /* SCIM_KEY_6 */                  SCIM_KEY_Thai_sarau,
  /* SCIM_KEY_7 */                  SCIM_KEY_Thai_saraue,
  /* SCIM_KEY_8 */                  SCIM_KEY_Thai_khokhwai,
  /* SCIM_KEY_9 */                  SCIM_KEY_Thai_totao,
  /* SCIM_KEY_colon */              SCIM_KEY_Thai_soso,
  /* SCIM_KEY_semicolon */          SCIM_KEY_Thai_wowaen,
  /* SCIM_KEY_less */               SCIM_KEY_Thai_thophuthao,
  /* SCIM_KEY_equal */              SCIM_KEY_Thai_chochang,
  /* SCIM_KEY_greater */            SCIM_KEY_Thai_lochula,
  /* SCIM_KEY_question */           SCIM_KEY_Thai_lu,
  /* SCIM_KEY_at */                 SCIM_KEY_Thai_leknung,
  /* SCIM_KEY_A */                  SCIM_KEY_Thai_ru,
  /* SCIM_KEY_B */                  SCIM_KEY_Thai_phinthu,
  /* SCIM_KEY_C */                  SCIM_KEY_Thai_choching,
  /* SCIM_KEY_D */                  SCIM_KEY_Thai_topatak,
  /* SCIM_KEY_E */                  SCIM_KEY_Thai_dochada,
  /* SCIM_KEY_F */                  SCIM_KEY_Thai_sarao,
  /* SCIM_KEY_G */                  SCIM_KEY_Thai_chochoe,
  /* SCIM_KEY_H */                  SCIM_KEY_Thai_maitaikhu,
  /* SCIM_KEY_I */                  SCIM_KEY_Thai_nonen,
  /* SCIM_KEY_J */                  SCIM_KEY_Thai_maichattawa,
  /* SCIM_KEY_K */                  SCIM_KEY_Thai_sorusi,
  /* SCIM_KEY_L */                  SCIM_KEY_Thai_sosala,
  /* SCIM_KEY_M */                  SCIM_KEY_question,
  /* SCIM_KEY_N */                  SCIM_KEY_Thai_thanthakhat,
  /* SCIM_KEY_O */                  SCIM_KEY_Thai_paiyannoi,
  /* SCIM_KEY_P */                  SCIM_KEY_Thai_yoying,
  /* SCIM_KEY_Q */                  SCIM_KEY_Thai_leksun,
  /* SCIM_KEY_R */                  SCIM_KEY_Thai_thonangmontho,
  /* SCIM_KEY_S */                  SCIM_KEY_Thai_khorakhang,
  /* SCIM_KEY_T */                  SCIM_KEY_Thai_thothong,
  /* SCIM_KEY_U */                  SCIM_KEY_Thai_maitri,
  /* SCIM_KEY_V */                  SCIM_KEY_Thai_honokhuk,
  /* SCIM_KEY_W */                  SCIM_KEY_quotedbl,
  /* SCIM_KEY_X */                  SCIM_KEY_parenright,
  /* SCIM_KEY_Y */                  SCIM_KEY_Thai_nikhahit,
  /* SCIM_KEY_Z */                  SCIM_KEY_parenleft,
  /* SCIM_KEY_bracketleft */        SCIM_KEY_Thai_bobaimai,
  /* SCIM_KEY_backslash */          SCIM_KEY_Thai_khokhuat,
  /* SCIM_KEY_bracketright */       SCIM_KEY_Thai_loling,
  /* SCIM_KEY_asciicircum */        SCIM_KEY_Thai_sarauu,
  /* SCIM_KEY_underscore */         SCIM_KEY_Thai_lekpaet,
  /* SCIM_KEY_grave */              SCIM_KEY_underscore,
  /* SCIM_KEY_a */                  SCIM_KEY_Thai_fofan,
  /* SCIM_KEY_b */                  SCIM_KEY_Thai_sarai,
  /* SCIM_KEY_c */                  SCIM_KEY_Thai_saraae,
  /* SCIM_KEY_d */                  SCIM_KEY_Thai_kokai,
  /* SCIM_KEY_e */                  SCIM_KEY_Thai_saraam,
  /* SCIM_KEY_f */                  SCIM_KEY_Thai_dodek,
  /* SCIM_KEY_g */                  SCIM_KEY_Thai_sarae,
  /* SCIM_KEY_h */                  SCIM_KEY_Thai_maitho,
  /* SCIM_KEY_i */                  SCIM_KEY_Thai_rorua,
  /* SCIM_KEY_j */                  SCIM_KEY_Thai_maiek,
  /* SCIM_KEY_k */                  SCIM_KEY_Thai_saraaa,
  /* SCIM_KEY_l */                  SCIM_KEY_Thai_sosua,
  /* SCIM_KEY_m */                  SCIM_KEY_Thai_thothahan,
  /* SCIM_KEY_n */                  SCIM_KEY_Thai_sarauee,
  /* SCIM_KEY_o */                  SCIM_KEY_Thai_nonu,
  /* SCIM_KEY_p */                  SCIM_KEY_Thai_yoyak,
  /* SCIM_KEY_q */                  SCIM_KEY_Thai_maiyamok,
  /* SCIM_KEY_r */                  SCIM_KEY_Thai_phophan,
  /* SCIM_KEY_s */                  SCIM_KEY_Thai_hohip,
  /* SCIM_KEY_t */                  SCIM_KEY_Thai_saraa,
  /* SCIM_KEY_u */                  SCIM_KEY_Thai_saraii,
  /* SCIM_KEY_v */                  SCIM_KEY_Thai_oang,
  /* SCIM_KEY_w */                  SCIM_KEY_Thai_saraaimaimalai,
  /* SCIM_KEY_x */                  SCIM_KEY_Thai_popla,
  /* SCIM_KEY_y */                  SCIM_KEY_Thai_maihanakat,
  /* SCIM_KEY_z */                  SCIM_KEY_Thai_phophung,
  /* SCIM_KEY_braceleft */          SCIM_KEY_Thai_thothan,
  /* SCIM_KEY_bar */                SCIM_KEY_Thai_khokhon,
  /* SCIM_KEY_braceright */         SCIM_KEY_comma,
  /* SCIM_KEY_asciitilde */         SCIM_KEY_percent,
};

static const uint32 __us_to_thai_tis820_2538 [] = {
  /* SCIM_KEY_exclam */             SCIM_KEY_Thai_lakkhangyao,
  /* SCIM_KEY_quotedbl */           SCIM_KEY_period,
  /* SCIM_KEY_numbersign */         SCIM_KEY_Thai_leksong,
  /* SCIM_KEY_dollar */             SCIM_KEY_Thai_leksam,
  /* SCIM_KEY_percent */            SCIM_KEY_Thai_leksi,
  /* SCIM_KEY_ampersand */          0x1000e4e,
  /* SCIM_KEY_quoteright */         SCIM_KEY_Thai_ngongu,
  /* SCIM_KEY_parenleft */          SCIM_KEY_Thai_lekhok,
  /* SCIM_KEY_parenright */         SCIM_KEY_Thai_lekchet,
  /* SCIM_KEY_asterisk */           SCIM_KEY_Thai_lekha,
  /* SCIM_KEY_plus */               SCIM_KEY_Thai_lekkao,
  /* SCIM_KEY_comma */              SCIM_KEY_Thai_moma,
  /* SCIM_KEY_minus */              SCIM_KEY_Thai_khokhai,
  /* SCIM_KEY_period */             SCIM_KEY_Thai_saraaimaimuan,
  /* SCIM_KEY_slash */              SCIM_KEY_Thai_fofa,
  /* SCIM_KEY_0 */                  SCIM_KEY_Thai_chochan,
  /* SCIM_KEY_1 */                  SCIM_KEY_Thai_baht,
  /* SCIM_KEY_2 */                  SCIM_KEY_slash,
  /* SCIM_KEY_3 */                  SCIM_KEY_minus,
  /* SCIM_KEY_4 */                  SCIM_KEY_Thai_phosamphao,
  /* SCIM_KEY_5 */                  SCIM_KEY_Thai_thothung,
  /* SCIM_KEY_6 */                  SCIM_KEY_Thai_sarau,
  /* SCIM_KEY_7 */                  SCIM_KEY_Thai_saraue,
  /* SCIM_KEY_8 */                  SCIM_KEY_Thai_khokhwai,
  /* SCIM_KEY_9 */                  SCIM_KEY_Thai_totao,
  /* SCIM_KEY_colon */              SCIM_KEY_Thai_soso,
  /* SCIM_KEY_semicolon */          SCIM_KEY_Thai_wowaen,
  /* SCIM_KEY_less */               SCIM_KEY_Thai_thophuthao,
  /* SCIM_KEY_equal */              SCIM_KEY_Thai_chochang,
  /* SCIM_KEY_greater */            SCIM_KEY_Thai_lochula,
  /* SCIM_KEY_question */           SCIM_KEY_Thai_lu,
  /* SCIM_KEY_at */                 SCIM_KEY_Thai_leknung,
  /* SCIM_KEY_A */                  SCIM_KEY_Thai_ru,
  /* SCIM_KEY_B */                  SCIM_KEY_Thai_phinthu,
  /* SCIM_KEY_C */                  SCIM_KEY_Thai_choching,
  /* SCIM_KEY_D */                  SCIM_KEY_Thai_topatak,
  /* SCIM_KEY_E */                  SCIM_KEY_Thai_dochada,
  /* SCIM_KEY_F */                  SCIM_KEY_Thai_sarao,
  /* SCIM_KEY_G */                  SCIM_KEY_Thai_chochoe,
  /* SCIM_KEY_H */                  SCIM_KEY_Thai_maitaikhu,
  /* SCIM_KEY_I */                  SCIM_KEY_Thai_nonen,
  /* SCIM_KEY_J */                  SCIM_KEY_Thai_maichattawa,
  /* SCIM_KEY_K */                  SCIM_KEY_Thai_sorusi,
  /* SCIM_KEY_L */                  SCIM_KEY_Thai_sosala,
  /* SCIM_KEY_M */                  SCIM_KEY_question,
  /* SCIM_KEY_N */                  SCIM_KEY_Thai_thanthakhat,
  /* SCIM_KEY_O */                  SCIM_KEY_Thai_paiyannoi,
  /* SCIM_KEY_P */                  SCIM_KEY_Thai_yoying,
  /* SCIM_KEY_Q */                  SCIM_KEY_Thai_leksun,
  /* SCIM_KEY_R */                  SCIM_KEY_Thai_thonangmontho,
  /* SCIM_KEY_S */                  SCIM_KEY_Thai_khorakhang,
  /* SCIM_KEY_T */                  SCIM_KEY_Thai_thothong,
  /* SCIM_KEY_U */                  SCIM_KEY_Thai_maitri,
  /* SCIM_KEY_V */                  SCIM_KEY_Thai_honokhuk,
  /* SCIM_KEY_W */                  SCIM_KEY_quotedbl,
  /* SCIM_KEY_X */                  SCIM_KEY_parenright,
  /* SCIM_KEY_Y */                  SCIM_KEY_Thai_nikhahit,
  /* SCIM_KEY_Z */                  SCIM_KEY_parenleft,
  /* SCIM_KEY_bracketleft */        SCIM_KEY_Thai_bobaimai,
  /* SCIM_KEY_backslash */          SCIM_KEY_Thai_khokhon,
  /* SCIM_KEY_bracketright */       SCIM_KEY_Thai_loling,
  /* SCIM_KEY_asciicircum */        SCIM_KEY_Thai_sarauu,
  /* SCIM_KEY_underscore */         SCIM_KEY_Thai_lekpaet,
  /* SCIM_KEY_grave */              0x1000e4f,
  /* SCIM_KEY_a */                  SCIM_KEY_Thai_fofan,
  /* SCIM_KEY_b */                  SCIM_KEY_Thai_sarai,
  /* SCIM_KEY_c */                  SCIM_KEY_Thai_saraae,
  /* SCIM_KEY_d */                  SCIM_KEY_Thai_kokai,
  /* SCIM_KEY_e */                  SCIM_KEY_Thai_saraam,
  /* SCIM_KEY_f */                  SCIM_KEY_Thai_dodek,
  /* SCIM_KEY_g */                  SCIM_KEY_Thai_sarae,
  /* SCIM_KEY_h */                  SCIM_KEY_Thai_maitho,
  /* SCIM_KEY_i */                  SCIM_KEY_Thai_rorua,
  /* SCIM_KEY_j */                  SCIM_KEY_Thai_maiek,
  /* SCIM_KEY_k */                  SCIM_KEY_Thai_saraaa,
  /* SCIM_KEY_l */                  SCIM_KEY_Thai_sosua,
  /* SCIM_KEY_m */                  SCIM_KEY_Thai_thothahan,
  /* SCIM_KEY_n */                  SCIM_KEY_Thai_sarauee,
  /* SCIM_KEY_o */                  SCIM_KEY_Thai_nonu,
  /* SCIM_KEY_p */                  SCIM_KEY_Thai_yoyak,
  /* SCIM_KEY_q */                  SCIM_KEY_Thai_maiyamok,
  /* SCIM_KEY_r */                  SCIM_KEY_Thai_phophan,
  /* SCIM_KEY_s */                  SCIM_KEY_Thai_hohip,
  /* SCIM_KEY_t */                  SCIM_KEY_Thai_saraa,
  /* SCIM_KEY_u */                  SCIM_KEY_Thai_saraii,
  /* SCIM_KEY_v */                  SCIM_KEY_Thai_oang,
  /* SCIM_KEY_w */                  SCIM_KEY_Thai_saraaimaimalai,
  /* SCIM_KEY_x */                  SCIM_KEY_Thai_popla,
  /* SCIM_KEY_y */                  SCIM_KEY_Thai_maihanakat,
  /* SCIM_KEY_z */                  SCIM_KEY_Thai_phophung,
  /* SCIM_KEY_braceleft */          SCIM_KEY_Thai_thothan,
  /* SCIM_KEY_bar */                SCIM_KEY_Thai_khokhuat,
  /* SCIM_KEY_braceright */         SCIM_KEY_comma,
  /* SCIM_KEY_asciitilde */         0x1000e5b,
};

static const uint32 __us_to_thai_pattachote [] = {
  /* SCIM_KEY_exclam */             SCIM_KEY_plus,
  /* SCIM_KEY_quotedbl */           SCIM_KEY_Thai_thonangmontho,
  /* SCIM_KEY_numbersign */         SCIM_KEY_slash,
  /* SCIM_KEY_dollar */             SCIM_KEY_comma,
  /* SCIM_KEY_percent */            SCIM_KEY_question,
  /* SCIM_KEY_ampersand */          SCIM_KEY_underscore,
  /* SCIM_KEY_quoteright */         SCIM_KEY_Thai_khokhai,
  /* SCIM_KEY_parenleft */          SCIM_KEY_parenleft,
  /* SCIM_KEY_parenright */         SCIM_KEY_parenright,
  /* SCIM_KEY_asterisk */           SCIM_KEY_period,
  /* SCIM_KEY_plus */               SCIM_KEY_percent,
  /* SCIM_KEY_comma */              SCIM_KEY_Thai_saraa,
  /* SCIM_KEY_minus */              SCIM_KEY_Thai_leknung,
  /* SCIM_KEY_period */             SCIM_KEY_Thai_chochan,
  /* SCIM_KEY_slash */              SCIM_KEY_Thai_phophan,
  /* SCIM_KEY_0 */                  SCIM_KEY_Thai_leksun,
  /* SCIM_KEY_1 */                  SCIM_KEY_equal,
  /* SCIM_KEY_2 */                  SCIM_KEY_Thai_leksong,
  /* SCIM_KEY_3 */                  SCIM_KEY_Thai_leksam,
  /* SCIM_KEY_4 */                  SCIM_KEY_Thai_leksi,
  /* SCIM_KEY_5 */                  SCIM_KEY_Thai_lekha,
  /* SCIM_KEY_6 */                  SCIM_KEY_Thai_sarauu,
  /* SCIM_KEY_7 */                  SCIM_KEY_Thai_lekchet,
  /* SCIM_KEY_8 */                  SCIM_KEY_Thai_lekpaet,
  /* SCIM_KEY_9 */                  SCIM_KEY_Thai_lekkao,
  /* SCIM_KEY_colon */              SCIM_KEY_Thai_khorakhang,
  /* SCIM_KEY_semicolon */          SCIM_KEY_Thai_saraaimaimalai,
  /* SCIM_KEY_less */               SCIM_KEY_Thai_fofan,
  /* SCIM_KEY_equal */              SCIM_KEY_Thai_lekhok,
  /* SCIM_KEY_greater */            SCIM_KEY_Thai_choching,
  /* SCIM_KEY_question */           SCIM_KEY_Thai_lochula,
  /* SCIM_KEY_at */                 SCIM_KEY_quotedbl,
  /* SCIM_KEY_A */                  SCIM_KEY_Thai_maichattawa,
  /* SCIM_KEY_B */                  SCIM_KEY_Thai_phinthu,
  /* SCIM_KEY_C */                  SCIM_KEY_Thai_thothan,
  /* SCIM_KEY_D */                  SCIM_KEY_Thai_saraam,
  /* SCIM_KEY_E */                  SCIM_KEY_Thai_maiyamok,
  /* SCIM_KEY_F */                  SCIM_KEY_Thai_nonen,
  /* SCIM_KEY_G */                  SCIM_KEY_Thai_thanthakhat,
  /* SCIM_KEY_H */                  SCIM_KEY_Thai_sarauee,
  /* SCIM_KEY_I */                  SCIM_KEY_Thai_soso,
  /* SCIM_KEY_J */                  SCIM_KEY_Thai_phophung,
  /* SCIM_KEY_K */                  SCIM_KEY_Thai_chochang,
  /* SCIM_KEY_L */                  SCIM_KEY_Thai_sarao,
  /* SCIM_KEY_M */                  SCIM_KEY_Thai_honokhuk,
  /* SCIM_KEY_N */                  SCIM_KEY_Thai_sosala,
  /* SCIM_KEY_O */                  SCIM_KEY_Thai_thothung,
  /* SCIM_KEY_P */                  SCIM_KEY_Thai_thophuthao,
  /* SCIM_KEY_Q */                  SCIM_KEY_Thai_maitri,
  /* SCIM_KEY_R */                  SCIM_KEY_Thai_yoying,
  /* SCIM_KEY_S */                  SCIM_KEY_Thai_thothong,
  /* SCIM_KEY_T */                  SCIM_KEY_Thai_sorusi,
  /* SCIM_KEY_U */                  SCIM_KEY_Thai_fofa,
  /* SCIM_KEY_V */                  SCIM_KEY_Thai_phosamphao,
  /* SCIM_KEY_W */                  SCIM_KEY_Thai_ru,
  /* SCIM_KEY_X */                  SCIM_KEY_Thai_topatak,
  /* SCIM_KEY_Y */                  SCIM_KEY_Thai_saraue,
  /* SCIM_KEY_Z */                  SCIM_KEY_Thai_dochada,
  /* SCIM_KEY_bracketleft */        SCIM_KEY_Thai_saraaimaimuan,
  /* SCIM_KEY_backslash */          SCIM_KEY_Thai_lakkhangyao,
  /* SCIM_KEY_bracketright */       SCIM_KEY_Thai_chochoe,
  /* SCIM_KEY_asciicircum */        SCIM_KEY_Thai_sarau,
  /* SCIM_KEY_underscore */         SCIM_KEY_minus,
  /* SCIM_KEY_grave */              SCIM_KEY_underscore,
  /* SCIM_KEY_a */                  SCIM_KEY_Thai_maitho,
  /* SCIM_KEY_b */                  SCIM_KEY_Thai_sarai,
  /* SCIM_KEY_c */                  SCIM_KEY_Thai_loling,
  /* SCIM_KEY_d */                  SCIM_KEY_Thai_ngongu,
  /* SCIM_KEY_e */                  SCIM_KEY_Thai_yoyak,
  /* SCIM_KEY_f */                  SCIM_KEY_Thai_kokai,
  /* SCIM_KEY_g */                  SCIM_KEY_Thai_maihanakat,
  /* SCIM_KEY_h */                  SCIM_KEY_Thai_saraii,
  /* SCIM_KEY_i */                  SCIM_KEY_Thai_moma,
  /* SCIM_KEY_j */                  SCIM_KEY_Thai_saraaa,
  /* SCIM_KEY_k */                  SCIM_KEY_Thai_nonu,
  /* SCIM_KEY_l */                  SCIM_KEY_Thai_sarae,
  /* SCIM_KEY_m */                  SCIM_KEY_Thai_sosua,
  /* SCIM_KEY_n */                  SCIM_KEY_Thai_khokhwai,
  /* SCIM_KEY_o */                  SCIM_KEY_Thai_wowaen,
  /* SCIM_KEY_p */                  SCIM_KEY_Thai_saraae,
  /* SCIM_KEY_q */                  SCIM_KEY_Thai_maitaikhu,
  /* SCIM_KEY_r */                  SCIM_KEY_Thai_oang,
  /* SCIM_KEY_s */                  SCIM_KEY_Thai_thothahan,
  /* SCIM_KEY_t */                  SCIM_KEY_Thai_rorua,
  /* SCIM_KEY_u */                  SCIM_KEY_Thai_dodek,
  /* SCIM_KEY_v */                  SCIM_KEY_Thai_hohip,
  /* SCIM_KEY_w */                  SCIM_KEY_Thai_totao,
  /* SCIM_KEY_x */                  SCIM_KEY_Thai_popla,
  /* SCIM_KEY_y */                  SCIM_KEY_Thai_maiek,
  /* SCIM_KEY_z */                  SCIM_KEY_Thai_bobaimai,
  /* SCIM_KEY_braceleft */          SCIM_KEY_Thai_paiyannoi,
  /* SCIM_KEY_bar */                SCIM_KEY_Thai_nikhahit,
  /* SCIM_KEY_braceright */         SCIM_KEY_Thai_lu,
  /* SCIM_KEY_asciitilde */         SCIM_KEY_Thai_baht,
};

static uint32
__lookup_key (const uint32 map[], uint32 sym)
{
  if (SCIM_KEY_exclam <= sym && sym <= SCIM_KEY_asciitilde)
    sym = map [sym - SCIM_KEY_exclam];
  return sym;
}

static uint32
__revert_shift (uint32 sym)
{
    if (SCIM_KEY_A <= sym && sym <= SCIM_KEY_Z)
        sym += SCIM_KEY_a - SCIM_KEY_A;
    else if (SCIM_KEY_a <= sym && sym <= SCIM_KEY_z)
        sym -= SCIM_KEY_a - SCIM_KEY_A;
    return sym;
}

KeyEvent
ThaiKeymap::map_key (const KeyEvent& rawkey)
{
    KeyEvent key = rawkey.map_to_layout (SCIM_KEYBOARD_US);

    // cancel the CapsLock effect
    if (key.is_caps_lock_down())
        key.code = __revert_shift (key.code);

    switch (m_layout)
    {
        case THAI_KEYBOARD_KETMANEE:
            key.code = __lookup_key (__us_to_thai_ketmanee, key.code);
            break;
        case THAI_KEYBOARD_TIS820_2538:
            key.code = __lookup_key (__us_to_thai_tis820_2538, key.code);
            break;
        case THAI_KEYBOARD_PATTACHOTE:
            key.code = __lookup_key (__us_to_thai_pattachote, key.code);
            break;
        default:
            break;
    }

    return key;
}

/*
vi:ts=4:nowrap:ai:expandtab
*/
