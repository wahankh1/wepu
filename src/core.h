//
// Copyright 2015 Wahankh <dev@wahankh.co.uk>
//

#ifndef _CORE_H
#define _CORE_H

#include "wepu.h"

struct _browser
{
    gint id;
    const gchar *name;
    gint pid;
};

gint wepu_browser_search_pid(struct _browser *list);
gint wepu_browser_extract_pid(gchar *data);

#endif
