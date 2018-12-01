/*
 * cycle.c
 * Copyright (c) 2018, Sijmen J. Mulder <ik@sjmulder.nl>
 *
 * cycle is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * cycle is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with cycle. If not, see <https://www.gnu.org/licenses/>.
 */

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
