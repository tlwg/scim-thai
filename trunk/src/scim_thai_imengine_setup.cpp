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

#define Uses_SCIM_UTILITY
#define Uses_SCIM_CONFIG_BASE
#define Uses_SCIM_IMENGINE

#include <gtk/gtk.h>
#include <gtk/scimkeyselection.h>
#include <scim.h>
#include "scim_thai_imengine.h"
#include "scim_thai_imengine_config.h"
#include "intl.h"

using namespace scim;

#define scim_module_init thai_imengine_setup_LTX_scim_module_init
#define scim_module_exit thai_imengine_setup_LTX_scim_module_exit

#define scim_setup_module_create_ui       thai_imengine_setup_LTX_scim_setup_module_create_ui
#define scim_setup_module_get_category    thai_imengine_setup_LTX_scim_setup_module_get_category
#define scim_setup_module_get_name        thai_imengine_setup_LTX_scim_setup_module_get_name
#define scim_setup_module_get_description thai_imengine_setup_LTX_scim_setup_module_get_description
#define scim_setup_module_load_config     thai_imengine_setup_LTX_scim_setup_module_load_config
#define scim_setup_module_save_config     thai_imengine_setup_LTX_scim_setup_module_save_config
#define scim_setup_module_query_changed   thai_imengine_setup_LTX_scim_setup_module_query_changed

#define LIST_ICON_SIZE 20 

static GtkWidget * create_setup_window ();
static void        load_config (const ConfigPointer& config);
static void        save_config (const ConfigPointer& config);
static bool        query_changed ();

// Module Interface.
extern "C" {
    void scim_module_init (void)
    {
        bindtextdomain (GETTEXT_PACKAGE, SCIM_THAI_LOCALEDIR);
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    }

    void scim_module_exit (void)
    {
    }

    GtkWidget * scim_setup_module_create_ui (void)
    {
        return create_setup_window ();
    }

    String scim_setup_module_get_category (void)
    {
        return String ("IMEngine");
    }

    String scim_setup_module_get_name (void)
    {
        return String (_("Thai"));
    }

    String scim_setup_module_get_description (void)
    {
        return String (_("An IMEngine Module for Thai."));
    }

    void scim_setup_module_load_config (const ConfigPointer &config)
    {
        load_config (config);
    }

    void scim_setup_module_save_config (const ConfigPointer &config)
    {
        save_config (config);
    }

    bool scim_setup_module_query_changed ()
    {
        return query_changed ();
    }
} // extern "C"

// Internal data declaration.

// current config data
static ThaiKeymap::Layout     __config_kb_layout = ThaiKeymap::THAI_KEYBOARD_KETMANEE;
static ThaiInstance::TISCMode __config_isc_mode  = ISC_BASICCHECK;

// GUI status
static bool       __have_changed      = false;

// Key config widgets
static GtkWidget* __ketmanee_radio    = 0;
static GtkWidget* __tis820_2538_radio = 0;
static GtkWidget* __pattachote_radio  = 0;
static GtkWidget* __nocheck_radio     = 0;
static GtkWidget* __basiccheck_radio  = 0;
static GtkWidget* __strictcheck_radio = 0;

// Thai keyboard layout config string
static const char* __layout_config_string [] = {
    "Ketmanee",
    "TIS-820.2538",
    "Pattachote",
};

// Thai input sequence check mode config string
static const char* __isc_config_string [] = {
    "Passthrough",
    "BasicCheck",
    "Strict",
};

// Declaration of internal functions.
static void
setup_widget_value ();

static void
on_ketmanee_radio_toggled              (GtkToggleButton* togglebutton,
                                        gpointer         user_data);
static void
on_tis820_2538_radio_toggled           (GtkToggleButton* togglebutton,
                                        gpointer         user_data);
static void
on_pattachote_radio_toggled            (GtkToggleButton* togglebutton,
                                        gpointer         user_data);

static void
on_nocheck_radio_toggled               (GtkToggleButton* togglebutton,
                                        gpointer         user_data);

static void
on_basiccheck_radio_toggled            (GtkToggleButton* togglebutton,
                                        gpointer         user_data);

static void
on_strictcheck_radio_toggled           (GtkToggleButton* togglebutton,
                                        gpointer         user_data);

// Function implementations.

static GtkWidget*
create_setup_window ()
{
    static GtkWidget* window = 0;

    if (!window) {
        GtkWidget*   label;
        GtkWidget*   vbox;
        GtkWidget*   alignment;
        GSList*      layout_radiobutton_group = NULL;
        GSList*      isc_radiobutton_group = NULL;

        // Create the top level box.
        window = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_show (window);

        // Keyboard Layout section
        label = gtk_label_new (_("Keyboard layout:"));
        gtk_widget_show (label);
        gtk_box_pack_start (GTK_BOX (window), label, FALSE, FALSE, 0);
        gtk_label_set_xalign (GTK_LABEL (label), 0);
        gtk_label_set_yalign (GTK_LABEL (label), 0.5);

        vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_show (vbox);
        gtk_widget_set_margin_start (vbox, 12);
        gtk_box_pack_start (GTK_BOX (window), vbox, FALSE, FALSE, 0);

        // - Ketmanee keyboard layout
        __ketmanee_radio
            = gtk_radio_button_new_with_mnemonic (NULL, _("_Ketmanee"));
        gtk_widget_show (__ketmanee_radio);
        gtk_box_pack_start (GTK_BOX (vbox), __ketmanee_radio,
                            FALSE, FALSE, 0);
        gtk_widget_set_tooltip_text (
            __ketmanee_radio,
            _("The traditional typewriter layout, the most "
            "popular one in the market.")
        );
        gtk_radio_button_set_group (GTK_RADIO_BUTTON (__ketmanee_radio),
                                    layout_radiobutton_group);
        layout_radiobutton_group
            = gtk_radio_button_get_group (GTK_RADIO_BUTTON (__ketmanee_radio));

        // - TIS-820.2538 keyboard layout
        __tis820_2538_radio
            = gtk_radio_button_new_with_mnemonic (NULL, _("_TIS-820.2538"));
        gtk_widget_show (__tis820_2538_radio);
        gtk_box_pack_start (GTK_BOX (vbox), __tis820_2538_radio,
                            FALSE, FALSE, 0);
        gtk_widget_set_tooltip_text (
            __tis820_2538_radio,
            _("National standard layout derived from Ketmanee, "
            "with some extra characters.")
        );
        gtk_radio_button_set_group (GTK_RADIO_BUTTON (__tis820_2538_radio),
                                    layout_radiobutton_group);
        layout_radiobutton_group
            = gtk_radio_button_get_group (GTK_RADIO_BUTTON (__tis820_2538_radio));

        // - Pattachote keyboard layout
        __pattachote_radio
            = gtk_radio_button_new_with_mnemonic (NULL, _("_Pattachote"));
        gtk_widget_show (__pattachote_radio);
        gtk_box_pack_start (GTK_BOX (vbox), __pattachote_radio,
                            FALSE, FALSE, 0);
        gtk_widget_set_tooltip_text (
            __pattachote_radio,
            _("Keyboard layout designed by Sarit Pattachote "
            "from a statistical research.")
        );
        gtk_radio_button_set_group (GTK_RADIO_BUTTON (__pattachote_radio),
                                    layout_radiobutton_group);
        layout_radiobutton_group
            = gtk_radio_button_get_group (GTK_RADIO_BUTTON (__pattachote_radio));

        // Input Sequence Check section
        label = gtk_label_new (_("Input sequence check mode:"));
        gtk_widget_show (label);
        gtk_box_pack_start (GTK_BOX (window), label, FALSE, FALSE, 0);
        gtk_label_set_xalign (GTK_LABEL (label), 0);
        gtk_label_set_yalign (GTK_LABEL (label), 0.5);

        vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_show (vbox);
        gtk_widget_set_margin_start (vbox, 12);
        gtk_box_pack_start (GTK_BOX (window), vbox, FALSE, FALSE, 0);

        // - "No Check" choice
        __nocheck_radio
            = gtk_radio_button_new_with_mnemonic (NULL, _("_No Check"));
        gtk_widget_show (__nocheck_radio);
        gtk_box_pack_start (GTK_BOX (vbox), __nocheck_radio, FALSE, FALSE, 0);
        gtk_widget_set_tooltip_text (
            __nocheck_radio,
            _("Let all key sequences pass through.")
        );
        gtk_radio_button_set_group (GTK_RADIO_BUTTON (__nocheck_radio),
                                    isc_radiobutton_group);
        isc_radiobutton_group
            = gtk_radio_button_get_group (GTK_RADIO_BUTTON (__nocheck_radio));

        // - "Basic Check" choice
        __basiccheck_radio
            = gtk_radio_button_new_with_mnemonic (NULL, _("_Basic Check"));
        gtk_widget_show (__basiccheck_radio);
        gtk_box_pack_start (GTK_BOX (vbox), __basiccheck_radio,
                            FALSE, FALSE, 0);
        gtk_widget_set_tooltip_text (
            __basiccheck_radio,
            _("Check using basic rule, just to guarantee "
            "character order to be suitable for display.")
        );
        gtk_radio_button_set_group (GTK_RADIO_BUTTON (__basiccheck_radio),
                                    isc_radiobutton_group);
        isc_radiobutton_group
            = gtk_radio_button_get_group (GTK_RADIO_BUTTON (__basiccheck_radio));

        // - "Strict Check" choice
        __strictcheck_radio
            = gtk_radio_button_new_with_mnemonic (NULL, _("_Strict Check"));
        gtk_widget_show (__strictcheck_radio);
        gtk_box_pack_start (GTK_BOX (vbox), __strictcheck_radio,
                            FALSE, FALSE, 0);
        gtk_widget_set_tooltip_text (
            __strictcheck_radio,
            _("Check using more strict orthographical rules.")
        );
        gtk_radio_button_set_group (GTK_RADIO_BUTTON (__strictcheck_radio),
                                    isc_radiobutton_group);
        isc_radiobutton_group
            = gtk_radio_button_get_group (GTK_RADIO_BUTTON (__strictcheck_radio));

        // Signals
        g_signal_connect ((gpointer) __ketmanee_radio, "toggled",
                          G_CALLBACK (on_ketmanee_radio_toggled),
                          NULL);
        g_signal_connect ((gpointer) __tis820_2538_radio, "toggled",
                          G_CALLBACK (on_tis820_2538_radio_toggled),
                          NULL);
        g_signal_connect ((gpointer) __pattachote_radio, "toggled",
                          G_CALLBACK (on_pattachote_radio_toggled),
                          NULL);
        g_signal_connect ((gpointer) __nocheck_radio, "toggled",
                          G_CALLBACK (on_nocheck_radio_toggled),
                          NULL);
        g_signal_connect ((gpointer) __basiccheck_radio, "toggled",
                          G_CALLBACK (on_basiccheck_radio_toggled),
                          NULL);
        g_signal_connect ((gpointer) __strictcheck_radio, "toggled",
                          G_CALLBACK (on_strictcheck_radio_toggled),
                          NULL);

        setup_widget_value ();
    }

    return window;
}

static void
setup_widget_value ()
{
    switch (__config_kb_layout)
    {
        case ThaiKeymap::THAI_KEYBOARD_KETMANEE:
            gtk_toggle_button_set_active (
                GTK_TOGGLE_BUTTON (__ketmanee_radio),
                true);
            break;
        case ThaiKeymap::THAI_KEYBOARD_TIS820_2538:
            gtk_toggle_button_set_active (
                GTK_TOGGLE_BUTTON (__tis820_2538_radio),
                true);
            break;
        case ThaiKeymap::THAI_KEYBOARD_PATTACHOTE:
            gtk_toggle_button_set_active (
                GTK_TOGGLE_BUTTON (__pattachote_radio),
                true);
            break;
    }

    switch (__config_isc_mode)
    {
        case ISC_PASSTHROUGH:
            gtk_toggle_button_set_active (
                GTK_TOGGLE_BUTTON (__nocheck_radio),
                true);
            break;
        case ISC_BASICCHECK:
            gtk_toggle_button_set_active (
                GTK_TOGGLE_BUTTON (__basiccheck_radio),
                true);
            break;
        case ISC_STRICT:
            gtk_toggle_button_set_active (
                GTK_TOGGLE_BUTTON (__strictcheck_radio),
                true);
            break;
    }
}

void
load_config (const ConfigPointer& config)
{
    if (!config) return;

    String str;
    int i;

    // Read Keyboard Layout
    str = config->read (String (SCIM_CONFIG_IMENGINE_THAI_KB_LAYOUT),
                        String ("Ketmanee"));

    __config_kb_layout = ThaiKeymap::THAI_KEYBOARD_KETMANEE;
    for (i = 0;
         i < sizeof (__layout_config_string)/sizeof (*__layout_config_string);
         ++i)
    {
        if (str == __layout_config_string [i])
            __config_kb_layout = ThaiKeymap::Layout (i);
    }

    // Read Input Sequence Check Mode
    str = config->read (String (SCIM_CONFIG_IMENGINE_THAI_ISC_MODE),
                        String ("BasicCheck"));

    __config_isc_mode = ISC_BASICCHECK;
    for (i = 0;
         i < sizeof (__isc_config_string)/sizeof (*__isc_config_string);
         ++i)
    {
        if (str == __isc_config_string [i])
            __config_isc_mode = ThaiInstance::TISCMode (i);
    }

    setup_widget_value ();
}

void
save_config (const ConfigPointer& config)
{
    if (!config.null ()) {
        if (__config_kb_layout < 0 ||
            ThaiKeymap::THAI_KEYBOARD_NUM_LAYOUTS <= __config_kb_layout)
        {
            __config_kb_layout = ThaiKeymap::THAI_KEYBOARD_KETMANEE;
        }
        config->write (String (SCIM_CONFIG_IMENGINE_THAI_KB_LAYOUT),
                        String (__layout_config_string [__config_kb_layout]));

        if (__config_isc_mode < 0 || ISC_STRICT < __config_isc_mode)
        {
            __config_isc_mode = ISC_BASICCHECK;
        }
        config->write (String (SCIM_CONFIG_IMENGINE_THAI_ISC_MODE),
                        String (__isc_config_string [__config_isc_mode]));

        __have_changed = false;
    }
}

bool
query_changed ()
{
    return __have_changed;
}

// Declaration of internal functions.
static void
on_ketmanee_radio_toggled              (GtkToggleButton* togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active (togglebutton)) {
        __config_kb_layout = ThaiKeymap::THAI_KEYBOARD_KETMANEE;
        __have_changed = true;
    }
}

static void
on_tis820_2538_radio_toggled           (GtkToggleButton* togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active (togglebutton)) {
        __config_kb_layout = ThaiKeymap::THAI_KEYBOARD_TIS820_2538;
        __have_changed = true;
    }
}

static void
on_pattachote_radio_toggled            (GtkToggleButton* togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active (togglebutton)) {
        __config_kb_layout = ThaiKeymap::THAI_KEYBOARD_PATTACHOTE;
        __have_changed = true;
    }
}

static void
on_nocheck_radio_toggled               (GtkToggleButton* togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active (togglebutton)) {
        __config_isc_mode = ISC_PASSTHROUGH;
        __have_changed = true;
    }
}

static void
on_basiccheck_radio_toggled            (GtkToggleButton* togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active (togglebutton)) {
        __config_isc_mode = ISC_BASICCHECK;
        __have_changed = true;
    }
}

static void
on_strictcheck_radio_toggled           (GtkToggleButton* togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active (togglebutton)) {
        __config_isc_mode = ISC_STRICT;
        __have_changed = true;
    }
}

/*
vi:ts=4:nowrap:expandtab
*/
