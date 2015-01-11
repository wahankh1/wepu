//
// Copyright 2015 Wahankh <dev@wahankh.co.uk>
//

#include "core.h"

//
//
//
gint wepu_browser_search_pid(struct _browser *list)
{
    GCancellable *cancel = g_cancellable_new();
    GError *error = NULL;
    GFileInfo *info;
    GFileType file_type;
    gchar *directory_path;
    const gchar *browser[] = { "firefox", "iceweasel", "seamonkey", "midori" };
    gint number = WEPU_ARRAY_SIZE(browser);
    gint index = 0;
    
    //
    GFile *directory = g_file_new_for_path(WEPU_PROC);
    GFileEnumerator *enumerator = g_file_enumerate_children(directory, NULL, 
        G_FILE_QUERY_INFO_NONE, cancel, &error);
        
    directory_path = g_file_get_path(directory);
        
    if(enumerator)
    {
        while(!g_cancellable_is_cancelled(cancel) && (info = g_file_enumerator_next_file(enumerator, cancel, &error)) != NULL)
        {
            if(info)
            {
                const gchar *file_name;
                const gchar *fd;
                gchar *file_path;
                
                // file info
                file_type = g_file_info_get_file_type(info);
                file_name = g_file_info_get_name(info);
                file_path = g_strdup_printf("%s/%s", directory_path, file_name);
                
                // directory
                if(file_type == G_FILE_TYPE_DIRECTORY)
                {
                    GDir *directory;
                    
                    #ifdef DEBUG
                        debug(g_strdup_printf("[+] Opening : %s ...", file_path));
                    #endif
                    
                    if(!(directory = g_dir_open(file_path, 0, &error)))
                    {
                        return -1;
                    }
                    
                    // read directory content
                    while((fd = g_dir_read_name(directory)))
                    {                        
                        // status file
                        if(g_strcmp0(fd, "status") == 0)
                        {
                            GIOChannel *gio_channel;
                            GIOStatus gio_status;
                            gchar *fd_status;
                            gchar *buffer;
                            gboolean found = FALSE;
                            
                            fd_status = g_strdup_printf("%s/%s", file_path, fd);
                            
                            #ifdef DEBUG
                                debug(g_strdup_printf("[+]\t%s", fd_status));
                            #endif
                            
                            // open status file
                            if((gio_channel = g_io_channel_new_file(fd_status, "r", &error)) == NULL)
                            {
                                #ifdef DEBUG
                                    debug(error->message);
                                #endif
                                
                                g_error_free(error);
                                return -1;
                            }
                            
                            // read status file
                            while((gio_status = g_io_channel_read_line(gio_channel, &buffer, NULL, NULL, &error)))
                            {
                                if(gio_status == G_IO_STATUS_NORMAL)
                                {
                                    for(gint i = 0; i < number; i++)
                                    {
                                        // found ref to browser
                                        if(g_strstr_len(buffer, -1, browser[i]) != NULL)
                                        {                                            
                                            #ifdef DEBUG
                                                debug(g_strdup_printf("[+] FOUND %s", browser[i]));
                                            #endif
                                            
                                            list[index].id = index+1;
                                            list[index].name = browser[i];
                                            
                                            found = TRUE;
                                        }
                                    }
                                    
                                    // browser found get pid
                                    if(found)
                                    {
                                        if(g_strstr_len(buffer, -1, "Pid") != NULL)
                                        {
                                            #ifdef DEBUG
                                                debug(g_strdup_printf("pid: %d", wepu_browser_extract_pid(buffer)));
                                            #endif
                                            
                                            list[index].pid = wepu_browser_extract_pid(buffer);
                                            index = index + 1;
                                            //
                                            //
                                            //
                                            
                                            break;
                                        }
                                    }
                                }
                                
                                if(gio_status == G_IO_STATUS_ERROR)
                                {
                                    #ifdef DEBUG
                                        debug(error->message);
                                    #endif
                                    
                                    g_error_free(error);
                                }
                                
                                if(gio_status == G_IO_STATUS_EOF)
                                {
                                    break;
                                }
                            }
                            
                            g_free(buffer);
                            g_free(fd_status);
                            g_io_channel_shutdown(gio_channel, FALSE, &error);
                            g_io_channel_unref(gio_channel);
                        }
                    }
                    g_dir_close(directory);
                }
            }
        }
    }
    
    g_free(directory_path);
    
    return index;
}

//
//
//
gint wepu_browser_extract_pid(gchar *data)
{
    gint pid;
    
    if((sscanf(data, "%*[^0-9]%d", &pid)) == 1)
    {
        return pid;
    }
    
    return 0;
}

//
//
//

