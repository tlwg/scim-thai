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

#ifndef __SCIM_THAI_KEYMAP_H__
#define __SCIM_THAI_KEYMAP_H__

#include <scim.h>
#include <scim_event.h>

using namespace scim;

class ThaiKeymap
{
public:
    enum Layout {
        THAI_KEYBOARD_KETMANEE      = 0,
        THAI_KEYBOARD_TIS820_2538   = 1,
        THAI_KEYBOARD_PATTACHOTE    = 2,
        THAI_KEYBOARD_NUM_LAYOUTS   = 3
    };

public:
    explicit ThaiKeymap (Layout layout = THAI_KEYBOARD_KETMANEE);

    void      set_layout (Layout layout);
    Layout    get_layout () const;

    KeyEvent  map_key (const KeyEvent& rawkey);

private:
    Layout  m_layout;
};

inline
ThaiKeymap::ThaiKeymap (Layout layout)
    : m_layout (layout)
{
}

inline void
ThaiKeymap::set_layout (Layout layout)
{
    m_layout = layout;
}

inline ThaiKeymap::Layout
ThaiKeymap::get_layout () const
{
    return m_layout;
}

#endif /* __SCIM_THAI_KEYMAP_H__ */
/*
vi:ts=4:nowrap:ai:expandtab
*/
