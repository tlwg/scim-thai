/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#ifndef __SCIM_THAI_KEYMAP_H__
#define __SCIM_THAI_KEYMAP_H__

#include <scim.h>
#include <scim_event.h>

using namespace scim;

class ThaiKeymap
{
public:
    enum ThaiKeyboardLayout {
        THAI_KEYBOARD_KETMANEE      = 0,
        THAI_KEYBOARD_TIS820_2538   = 1,
        THAI_KEYBOARD_PATTACHOTE    = 2,
        THAI_KEYBOARD_NUM_LAYOUTS   = 3
    };

public:
    explicit ThaiKeymap (ThaiKeyboardLayout layout = THAI_KEYBOARD_KETMANEE);

    void               set_layout (ThaiKeyboardLayout layout);
    ThaiKeyboardLayout get_layout () const;

    KeyEvent           map_key (const KeyEvent& rawkey);

private:
    ThaiKeyboardLayout m_layout;
};

inline
ThaiKeymap::ThaiKeymap (ThaiKeyboardLayout layout)
    : m_layout (layout)
{
}

inline void
ThaiKeymap::set_layout (ThaiKeyboardLayout layout)
{
    m_layout = layout;
}

inline ThaiKeymap::ThaiKeyboardLayout
ThaiKeymap::get_layout () const
{
    return m_layout;
}

#endif /* __SCIM_THAI_KEYMAP_H__ */
/*
vi:ts=4:nowrap:ai:expandtab
*/
