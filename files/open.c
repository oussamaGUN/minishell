#include "../main.h"


int open_files(t_token *token)
{
    t_token *itter = token;
    int file;
    while (itter)
    {
        if (itter->type == FILE_OUT)    
        {
            file = open(itter->content, O_CREAT | O_WRONLY, 0644);
            if (file == -1)
                return 1;
        }
        if (itter->type == FILE_APP)    
        {
            file = open(itter->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (file == -1)
                return 1;
        }
        if (itter->type == FILE_IN)    
        {
            file = open(itter->content,  O_RDONLY);
            if (file == -1)
            {
                printf("file not found\n");
                return 1;
            }
        }
        itter = itter->next;
    }
    return 0;
}
