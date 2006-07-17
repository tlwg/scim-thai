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
#include "scim_thai_imengine_factory.h"
#include "scim_thai_imengine.h"
#include "intl.h"

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

ThaiIMEngineInstance::ThaiIMEngineInstance (ThaiIMEngineFactory*  factory,
                                            const String&         encoding,
                                            int                   id)
    : IMEngineInstanceBase (factory, encoding, id),
      m_factory (factory),
      m_keymap (ThaiKeymap::THAI_KEYBOARD_KETMANEE),
      m_prev_key (0, 0)
{
    SCIM_DEBUG_IMENGINE(1) << "Create THAI Instance : ";
}

ThaiIMEngineInstance::~ThaiIMEngineInstance ()
{
}

bool
ThaiIMEngineInstance::process_key_event (const KeyEvent& key)
{
    SCIM_DEBUG_IMENGINE(2) << "process_key_event ";
    SCIM_DEBUG_IMENGINE(2) << "(" << std::hex << key.code << ","
                           << std::hex << key.mask << ","
                           << key.layout << ")\n";

    if (key.is_key_release())
        return false;

    if (key.mask & (SCIM_KEY_AllMasks
                    & ~(SCIM_KEY_ShiftMask | SCIM_KEY_CapsLockMask)) ||
        __is_context_lost_key (key.code))
    {
        return false;
    }
    if (key.code == 0 || __is_context_intact_key (key.code))
    {
        return false;
    }

    KeyEvent thai_key = m_keymap.map_key (key);

    WideString str;
    str.push_back (thai_key.get_unicode_code());
    commit_string (str);

    return true;
}

void
ThaiIMEngineInstance::reset ()
{
    SCIM_DEBUG_IMENGINE(2) << "reset.\n";
}

/*
vi:ts=4:nowrap:ai:expandtab
*/
