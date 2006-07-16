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

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <scim.h>
#include "scim_thai_imengine_factory.h"
#include "scim_thai_imengine.h"
#include "intl.h"

ThaiIMEngineInstance::ThaiIMEngineInstance (ThaiIMEngineFactory   *factory,
                                            const String   &encoding,
                                            int             id)
    : IMEngineInstanceBase (factory, encoding, id),
      m_factory (factory),
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
    SCIM_DEBUG_IMENGINE(2) << "process_key_event.\n";

    return false;
}

void
ThaiIMEngineInstance::reset ()
{
    SCIM_DEBUG_IMENGINE(2) << "reset.\n";
}

/*
vi:ts=4:nowrap:ai:expandtab
*/
