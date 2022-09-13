#include "server/server.h"

int main(int argc, char **argv)
{
    srandom(getpid());
    int s = -1;
    errno = 0;
    int opt;
    char *strtoull_endp;

    int log = STDOUT_FILENO;
    char *file_log_dir = NULL;

    while ((opt = getopt(argc, argv, "p:l:m:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            set_server_port((uint16_t)strtoul(optarg, &strtoull_endp, 10));
            if (strtoull_endp == optarg || strtoull_endp[0] != '\0')
                goto error;
            break;
        case 'm':
            set_server_multi_port((uint16_t)strtoul(optarg, &strtoull_endp, 10));
            if (strtoull_endp == optarg || strtoull_endp[0] != '\0')
                goto error;
            break;
        case 'l':
            file_log_dir = optarg;
            break;
        }
    }

    if (file_log_dir == NULL || (log = open(file_log_dir, O_WRONLY | O_CREAT, 0700)) < 0)
    {
        init_logger(STDOUT_FILENO);
        if (log < 0)
        {
            logger("error", "failed to open or create '%s'", file_log_dir);
        }
    }
    else
    {
        init_logger(log);
    }

    if ((s = server_tcp_create(get_server_port())) < 0)
    {
        goto error;
    }

    if (server_tcp_accept(s, server_tcp_receive, tcp_message_handler) < 0)
    {
        goto error;
    }

    return EXIT_SUCCESS;

error:
    if (errno != 0)
    {
        perror("main");
    }
    if (s > 0)
    {
        close(s);
    }
    return EXIT_FAILURE;
}