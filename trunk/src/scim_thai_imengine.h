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
#include "scim_thai_keymap.h"

using namespace scim;

class ThaiIMEngineInstance : public IMEngineInstanceBase
{
public:
    ThaiIMEngineInstance (ThaiIMEngineFactory*  factory,
                          const String&         encoding,
                          int                   id = -1);
    virtual ~ThaiIMEngineInstance ();

    virtual bool process_key_event             (const KeyEvent& key);
    virtual void reset                         (void);

private:
    ThaiIMEngineFactory*    m_factory;

    ThaiKeymap              m_keymap;

    KeyEvent                m_prev_key;
};
#endif /* __SCIM_THAI_IMENGINE_H__ */
/*
vi:ts=4:nowrap:ai:expandtab
*/
