//
// Copyright 2015 Wahankh <dev@wahankh.co.uk>
//

#ifndef _COMMON_H
#define _COMMON_H

#define WEPU_SUCCESS 0
#define WEPU_FAILURE 1

#define WEPU_NAME "wepu"
#define WEPU_VERSION "1.0"
#define WEPU_BUILD "~DEV/110115"

#define WEPU_PROC "/proc"
#define WEPU_BROWSER_MAX 5
#define WEPU_ARRAY_SIZE(x) ((gint)(sizeof(x)/sizeof(x[0])))

#ifdef DEBUG
    #define debug(message) do { if(DEBUG) g_print("[DEBUG] %s\n", message); } while(0)
#endif

#endif
