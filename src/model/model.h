#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <gtk/gtk.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "../manager/manager.h"
#include "../manager/theme.h"
#include "../manager/config.h"
#include "../data/grid.h"
#include "../manager/json/json.h"
#include "../manager/json/file.h"

/* Types of views that may be used */
#define MENU  0
#define GAME  1
#define PREF  2

/** @brief
 *
 */
typedef struct
{
	 /** @brief
     *
     */
	int type;

} Model;


#endif /* MODEL_H_ */
