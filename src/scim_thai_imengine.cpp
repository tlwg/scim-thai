/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 2006 Theppitak Karoonboonyanan <thep@linux.thai.net>
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

#define Uses_SCIM_UTILITY
#define Uses_SCIM_IMENGINE
#define Uses_SCIM_LOOKUP_TABLE
#define Uses_SCIM_CONFIG_BASE

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <scim.h>
#include <thai/thwctype.h>
#include "scim_thai_imengine_factory.h"
#include "scim_thai_imengine.h"
#include "intl.h"

static bool __is_context_lost_key (uint32 keycode);
static bool __is_context_intact_key (uint32 keycode);


ThaiIMEngineInstance::ThaiIMEngineInstance (ThaiIMEngineFactory*  factory,
                                            const String&         encoding,
                                            int                   id,
                                            ThaiKeymap::ThaiKeyboardLayout layout,
                                            TISCMode              isc_mode)
    : IMEngineInstanceBase (factory, encoding, id),
      m_keymap (layout),
      m_isc_mode (isc_mode),
      m_buff_tail (0)
{
    memset (m_char_buff, 0, sizeof m_char_buff);
}

ThaiIMEngineInstance::~ThaiIMEngineInstance ()
{
}

void
ThaiIMEngineInstance::_forget_previous_chars ()
{
    m_char_buff [0] = '\0';
    m_buff_tail = 0;
}

void
ThaiIMEngineInstance::_remember_previous_char (thchar_t c)
{
    if (m_buff_tail == sizeof m_char_buff)
    {
        memmove (m_char_buff, m_char_buff + 1, sizeof m_char_buff - 1);
        --m_buff_tail;
    }
    m_char_buff [m_buff_tail++] = c;
}

thcell_t
ThaiIMEngineInstance::_get_previous_cell ()
{
    WideString surrounding;
    int        cursor_index;
    thcell_t   the_cell;

    th_init_cell (&the_cell);

    if (get_surrounding_text (surrounding, cursor_index))
    {
        thchar_t* tis_text = new thchar_t [cursor_index+1];
        if (!tis_text)
            goto exit_point;

        tis_text [cursor_index] = '\0';
        int begin_index = cursor_index;
        while (begin_index > 0)
        {
            thchar_t c = th_uni2tis (surrounding [begin_index-1]);
            if (c == THCHAR_ERR)
                break;
            tis_text [--begin_index] = c;
        }
        if (begin_index < cursor_index)
        {
            th_prev_cell (tis_text + begin_index, cursor_index - begin_index,
                          &the_cell, true);
        }
        delete tis_text;
    }
    else
    {
        th_prev_cell (m_char_buff, m_buff_tail, &the_cell, true);
    }

exit_point:
    return the_cell;
}

static bool
__is_context_lost_key (uint32 keycode)
{
  return ((keycode & 0xFF00) == 0xFF00) &&
          (keycode == SCIM_KEY_BackSpace ||
           keycode == SCIM_KEY_Tab ||
           keycode == SCIM_KEY_Linefeed ||
           keycode == SCIM_KEY_Clear ||
           keycode == SCIM_KEY_Return ||
           keycode == SCIM_KEY_Pause ||
           keycode == SCIM_KEY_Scroll_Lock ||
           keycode == SCIM_KEY_Sys_Req ||
           keycode == SCIM_KEY_Escape ||
           keycode == SCIM_KEY_Delete ||
           (SCIM_KEY_Home <= keycode && keycode <= SCIM_KEY_Begin) || /* IsCursorkey */
           (SCIM_KEY_KP_Space <= keycode && keycode <= SCIM_KEY_KP_Delete) || /* IsKeypadKey, non-chars only */
           (SCIM_KEY_Select <= keycode && keycode <= SCIM_KEY_Break) || /* IsMiscFunctionKey */
           (SCIM_KEY_F1 <= keycode && keycode <= SCIM_KEY_F35)); /* IsFunctionKey */
}

static bool
__is_context_intact_key (uint32 keycode)
{
  return (((keycode & 0xFF00) == 0xFF00) &&
          ((SCIM_KEY_Shift_L <= keycode && keycode <= SCIM_KEY_Hyper_R) || /* IsModifierKey */
           (keycode == SCIM_KEY_Mode_switch) ||
           (keycode == SCIM_KEY_Num_Lock))) ||
         (((keycode & 0xFE00) == 0xFE00) &&
          (SCIM_KEY_ISO_Lock <= keycode && keycode <= SCIM_KEY_ISO_Last_Group_Lock));
}

bool
ThaiIMEngineInstance::process_key_event (const KeyEvent& key)
{
    if (key.is_key_release()
        || key.code == 0
        || __is_context_intact_key (key.code))
    {
        return false;
    }

    if (key.mask & (SCIM_KEY_AllMasks
                    & ~(SCIM_KEY_ShiftMask | SCIM_KEY_CapsLockMask)) ||
        __is_context_lost_key (key.code))
    {
        _forget_previous_chars ();
        return false;
    }

    KeyEvent  thai_key = m_keymap.map_key (key);
    ucs4_t    thai_uni = thai_key.get_unicode_code ();

    if (!th_wcistis (thai_uni))
        return false;

    thchar_t thai_tis = th_uni2tis (thai_uni);

    thcell_t    context_cell = _get_previous_cell ();
    thinpconv_t conv;
    if (th_validate (context_cell, thai_tis, &conv))
    {
        if (conv.offset < 0)
            if (!delete_surrounding_text (conv.offset, -conv.offset))
                return false;
        _forget_previous_chars ();
        _remember_previous_char (thai_tis);

        WideString str;
        for (int i = 0; conv.conv [i]; i++)
            str.push_back (th_tis2uni (conv.conv [i]));
        commit_string (str);
    }
    else
    {
        beep ();
    }

    return true;
}

void
ThaiIMEngineInstance::reset ()
{
}

/*
vi:ts=4:nowrap:ai:expandtab
*/
