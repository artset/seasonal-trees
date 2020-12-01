/*!
 Settings.h
 CS123 Support Code
 @author  Evan Wallace (edwallac)
 @date    9/1/2010
 This file contains various settings and enumerations that you will need to
 use in the various assignments. The settings are bound to the GUI via static
 data bindings.
**/

#include "Settings.h"
#include <QFile>
#include <QSettings>

Settings settings;


/**
 * Loads the application settings, or, if no saved settings are available, loads default values for
 * the settings. You can change the defaults here.
 */
void Settings::loadSettingsOrDefaults() {
    // Set the default values below
    QSettings s("CS123", "CS123");

    recursions = s.value("recursions", 4).toInt();
    angle = s.value("angle", 25.f).toFloat();
    season = s.value("season", 0).toInt();

}

void Settings::saveSettings() {
    QSettings s("CS123", "CS123");

    s.setValue("recursions", recursions);
    s.setValue("angle", angle);
    s.setValue("season", season);

}

