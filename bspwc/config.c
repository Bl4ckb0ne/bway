#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <wlr/util/log.h>

#include "bspwc/config.h"

extern char **environ;

// config file is executed.
bool load_config_file(const char* file)
{
	wlr_log(WLR_INFO, "Loading config file %s", file);
	int status;
	if (fork() == 0)
	{
		execle(file, file, NULL, environ);
		exit(EXIT_FAILURE);
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
			return true;
	}
	return false;
}
