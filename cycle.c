#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>

int
main(int argc, char **argv)
{
	FILE *f;
	int fd;
	char buf[4096];
	ssize_t nr;

	(void)argv;

	if (argc != 1) {
		fputs("usage: ... | cycle | ...\n", stderr);
		return 1;
	}

	/* if we can seek we don't need to buffer */
	if (lseek(STDIN_FILENO, 0, SEEK_SET) != -1)
		fd = STDIN_FILENO;
	else if (errno != ESPIPE)
		err(1, "lseek on stdin");
	else {
		/* we can't seek, so tee to a temp file */

		if (!(f = tmpfile()))
			err(1, "lseek on stdin");
		fd = fileno(f);

		while ((nr = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
			if (write(STDOUT_FILENO, buf, (size_t)nr) == -1)
				err(1, "stdout");
			if (write(fd, buf, (size_t)nr) == -1)
				err(1, "temporary file");
		}

		if (nr == -1)
			err(1, "stdin");
		if (lseek(fd, 0, SEEK_SET) == -1)
			err(1, "lseek on temporary file");
	}

	while (1) {
		while ((nr = read(fd, buf, sizeof(buf))) > 0)
			if (write(1, buf, (size_t)nr) == -1)
				err(1, "stdout");
		if (nr == -1)
			err(1, "read");
		if (lseek(fd, 0, SEEK_SET) == -1)
			err(1, "lseek");
	}
}
