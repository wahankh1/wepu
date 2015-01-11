//
// Copyright 2015 Wahankh <dev@wahankh.co.uk>
//

#include "wepu.h"

 gint main(gint argc, gchar **argv)
 {
     struct _browser browsers[WEPU_BROWSER_MAX];
     gint index = 0;
     
     #ifdef DEBUG
        debug(WEPU_BUILD);
     #endif
     
     index = wepu_browser_search_pid(browsers);
     
     #ifdef DEBUG
        debug(g_strdup_printf("%s at %d", browsers[0].name, browsers[0].pid));
     #endif
     
     return WEPU_SUCCESS;
 }
