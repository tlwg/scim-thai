/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
#include "scim_thai_imengine_config.h"
#include "intl.h"

/* SCIM Related Definitions */
#define scim_module_init thai_LTX_scim_module_init
#define scim_module_exit thai_LTX_scim_module_exit
#define scim_imengine_module_init thai_LTX_scim_imengine_module_init
#define scim_imengine_module_create_factory thai_LTX_scim_imengine_module_create_factory

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
        ThaiFactory *factory = 0;

        try {
            factory = new ThaiFactory (String ("63752e02-c9cb-420c-bac6-f17f60a16822"),
                                       _scim_config);
        } catch (...) {
            delete factory;
            factory = 0;
        }

        return factory;
    }
}


ThaiFactory::ThaiFactory (const String&        uuid,
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
        = m_config->signal_connect_reload (slot (this, &ThaiFactory::reload_config));
}

ThaiFactory::~ThaiFactory ()
{
    m_reload_signal_connection.disconnect ();
}

WideString
ThaiFactory::get_name () const
{
    return utf8_mbstowcs (String (_("Thai")));
}

WideString
ThaiFactory::get_authors () const
{
    return utf8_mbstowcs (String ("Theppitak Karoonboonyanan <theppitak@gmail.com>"));
}

WideString
ThaiFactory::get_credits () const
{
    return WideString ();
}

WideString
ThaiFactory::get_help () const
{
    return WideString ();
}

String
ThaiFactory::get_uuid () const
{
    return m_uuid;
}

String
ThaiFactory::get_icon_file () const
{
    return String (SCIM_THAI_ICON_FILE);
}

IMEngineInstancePointer
ThaiFactory::create_instance (const String& encoding, int id)
{
    return new ThaiInstance (this, encoding, id,
                             m_pref_kb_layout, m_pref_isc_mode);
}

void
ThaiFactory::reload_config (const ConfigPointer& config)
{
    if (!config) return;

    String str;

    /* Read Keyboard Layout */
    str = config->read (String (SCIM_CONFIG_IMENGINE_THAI_KB_LAYOUT),
                        String ("Ketmanee"));

    if (str == String ("Ketmanee"))
        m_pref_kb_layout = ThaiKeymap::THAI_KEYBOARD_KETMANEE;
    else if (str == String ("TIS-820.2538"))
        m_pref_kb_layout = ThaiKeymap::THAI_KEYBOARD_TIS820_2538;
    else if (str == String ("Pattachote"))
        m_pref_kb_layout = ThaiKeymap::THAI_KEYBOARD_PATTACHOTE;
    else
    {
        SCIM_DEBUG_IMENGINE(1) << "Unknown Keyboard Layout '"
                               << str.c_str()
                               << "', default to 'Ketmanee'.\n";
        m_pref_kb_layout = ThaiKeymap::THAI_KEYBOARD_KETMANEE;
    }

    /* Read Input Sequence Check Mode */
    str = config->read (String (SCIM_CONFIG_IMENGINE_THAI_ISC_MODE),
                        String ("BasicCheck"));

    if (str == String ("BasicCheck"))
        m_pref_isc_mode = ISC_BASICCHECK;
    else if (str == String ("Passthrough"))
        m_pref_isc_mode = ISC_PASSTHROUGH;
    else if (str == String ("Strict"))
        m_pref_isc_mode = ISC_STRICT;
    else
    {
        SCIM_DEBUG_IMENGINE(1) << "Unknown Input Sequence Check Mode '"
                               << str.c_str()
                               << "', default to 'BasicCheck'.\n";
        m_pref_isc_mode = ISC_BASICCHECK;
    }
}

/*
vi:ts=4:nowrap:ai:expandtab
*/
