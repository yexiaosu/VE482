/* SPDX-License-Identifier: Zlib */

#ifndef CONFIG_H
#define CONFIG_H

#include "zathura.h"

/**
 * This function loads the default values of the configuration
 *
 * @param zathura The zathura session
 */
void config_load_default(zathura_t* zathura);

/**
 * Loads and evaluates a configuration file
 *
 * @param zathura The zathura session
 */
void config_load_files(zathura_t* zathura);

#endif // CONFIG_H
