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

/*
 * Modified from scim_sinhala_imengine_factory.cpp in scim-sinhala-0.1.0. 
 * Copyright (C) Hiroyuki Ikezoe <poincare@ikezoe.net>
 * Copyright (C) 2005 Kazuki Ohta <mover@hct.zaq.ne.jp>
 */

/*
 * The original code is scim_uim_imengine.cpp in scim-uim-0.1.3. 
 * Copyright (C) 2004 James Su <suzhe@tsinghua.org.cn>
 */

#define Uses_SCIM_UTILITY
#define Uses_SCIM_IMENGINE
#define Uses_SCIM_CONFIG_BASE

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <scim.h>
#include "scim_thai_imengine_factory.h"
#include "scim_thai_imengine.h"
#include "intl.h"

/* SCIM Related Definitions */
#define scim_module_init thai_LTX_scim_module_init
#define scim_module_exit thai_LTX_scim_module_exit
#define scim_imengine_module_init thai_LTX_scim_imengine_module_init
#define scim_imengine_module_create_factory thai_LTX_scim_imengine_module_create_factory
#ifndef SCIM_THAI_ICON_FILE
    #define SCIM_THAI_ICON_FILE           (SCIM_ICONDIR"/scim-thai.png")
#endif

static ConfigPointer _scim_config (0);

extern "C" {
    void scim_module_init (void)
    {
        bindtextdomain (GETTEXT_PACKAGE, SCIM_THAI_LOCALEDIR);
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    }

    void scim_module_exit (void)
    {
        _scim_config.reset ();
    }

    uint32 scim_imengine_module_init (const ConfigPointer& config)
    {
        SCIM_DEBUG_IMENGINE(1) << "Initialize THAI Engine.\n";

        _scim_config = config;

        return 1;
    }

    IMEngineFactoryPointer scim_imengine_module_create_factory (uint32 engine)
    {
        ThaiIMEngineFactory *factory = 0;

        try {
            factory = new ThaiIMEngineFactory (String ("63752e02-c9cb-420c-bac6-f17f60a16822"),
                                               _scim_config);
        } catch (...) {
            delete factory;
            factory = 0;
        }

        return factory;
    }
}


ThaiIMEngineFactory::ThaiIMEngineFactory (const String&        uuid,
                                          const ConfigPointer& config)
    : m_uuid (uuid),
      m_config (config)
{
    SCIM_DEBUG_IMENGINE(1) << "Create Thai Factory :\n";
    SCIM_DEBUG_IMENGINE(1) << "  UUID : " << uuid << "\n";

    set_languages (String ("th"));

    // config
    reload_config (m_config);
    m_reload_signal_connection
        = m_config->signal_connect_reload (slot (this, &ThaiIMEngineFactory::reload_config));
}

ThaiIMEngineFactory::~ThaiIMEngineFactory ()
{
    m_reload_signal_connection.disconnect ();
}

WideString
ThaiIMEngineFactory::get_name () const
{
    return utf8_mbstowcs (String (_("Thai")));
}

WideString
ThaiIMEngineFactory::get_authors () const
{
    return utf8_mbstowcs (String ("Theppitak Karoonboonyanan <thep@linux.thai.net>"));
}

WideString
ThaiIMEngineFactory::get_credits () const
{
    return WideString ();
}

WideString
ThaiIMEngineFactory::get_help () const
{
    return WideString ();
}

String
ThaiIMEngineFactory::get_uuid () const
{
    return m_uuid;
}

String
ThaiIMEngineFactory::get_icon_file () const
{
    return String (SCIM_THAI_ICON_FILE);
}

IMEngineInstancePointer
ThaiIMEngineFactory::create_instance (const String& encoding, int id)
{
    return new ThaiIMEngineInstance (this, encoding, id);
}

void
ThaiIMEngineFactory::reload_config (const ConfigPointer& config)
{
    if (!config) return;
}

/*
vi:ts=4:nowrap:ai:expandtab
*/