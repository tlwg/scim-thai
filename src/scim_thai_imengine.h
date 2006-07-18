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

#ifndef __SCIM_THAI_IMENGINE_H__
#define __SCIM_THAI_IMENGINE_H__

#include <scim.h>
#include <thai/thinp.h>
#include "scim_thai_keymap.h"

using namespace scim;

class ThaiIMEngineInstance : public IMEngineInstanceBase
{
public:
    typedef thstrict_t TISCMode;

public:
    ThaiIMEngineInstance (ThaiIMEngineFactory*  factory,
                          const String&         encoding,
                          int                   id = -1,
                          ThaiKeymap::ThaiKeyboardLayout layout = ThaiKeymap::THAI_KEYBOARD_KETMANEE,
                          TISCMode              isc_mode = ISC_BASICCHECK);
    virtual ~ThaiIMEngineInstance ();

    void         set_isc_mode (TISCMode mode);
    void         set_keyboard_layout (ThaiKeymap::ThaiKeyboardLayout layout);

    TISCMode     get_isc_mode () const;
    ThaiKeymap::ThaiKeyboardLayout get_keyboard_layout () const;

    // IMEngineInstanceBase virtual methods
    virtual bool process_key_event             (const KeyEvent& key);
    virtual void reset                         (void);

private:
    void      _forget_previous_chars ();
    void      _remember_previous_char (thchar_t c);
    thcell_t  _get_previous_cell ();

private:
    ThaiKeymap              m_keymap;

    TISCMode                m_isc_mode;
    thchar_t                m_char_buff[4];
    short                   m_buff_tail;
};

inline void
ThaiIMEngineInstance::set_isc_mode (TISCMode mode)
{
    m_isc_mode = mode;
}

inline void
ThaiIMEngineInstance::set_keyboard_layout (ThaiKeymap::ThaiKeyboardLayout layout)
{
    m_keymap.set_layout (layout);
}

inline ThaiIMEngineInstance::TISCMode
ThaiIMEngineInstance::get_isc_mode () const
{
    return m_isc_mode;
}

inline ThaiKeymap::ThaiKeyboardLayout
ThaiIMEngineInstance::get_keyboard_layout () const
{
    return m_keymap.get_layout ();
}

#endif /* __SCIM_THAI_IMENGINE_H__ */
/*
vi:ts=4:nowrap:ai:expandtab
*/
