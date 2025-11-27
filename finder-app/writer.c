#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char **argv)
{
    const char *writefile;
    const char *writestr;
    FILE *fwritefile;

    /* Optional but clearer ident/options */
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <write_string>\n", argv[0]);
        syslog(LOG_ERR, "Invalid arguments: expected 2, got %d", argc - 1);
        closelog();
        return EXIT_FAILURE;
    }

    writefile = argv[1];
    writestr  = argv[2];

    fwritefile = fopen(writefile, "w");
    if (fwritefile == NULL) {
        syslog(LOG_ERR, "Error opening file %s: %m", writefile);
        closelog();
        return EXIT_FAILURE;
    }

    if (fprintf(fwritefile, "%s\n", writestr) < 0) {
        syslog(LOG_ERR, "Error writing to file %s: %m", writefile);
        fclose(fwritefile);
        closelog();
        return EXIT_FAILURE;
    }

    if (fclose(fwritefile) == EOF) {
        syslog(LOG_ERR, "Error closing file %s: %m", writefile);
        closelog();
        return EXIT_FAILURE;
    }

    syslog(LOG_DEBUG, "Successfully wrote \"%s\" to %s", writestr, writefile);
    closelog();
    return EXIT_SUCCESS;
}
