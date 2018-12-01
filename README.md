cycle
=====

Repeat a file or stream forever.

... | **cycle** | ...


Description
-----------

**cycle** copies standard input to standard output, repeating forever. The
input is buffered to a temporary file if it does not support seeking.


Examples
--------

Repeat a stream:

    $ echo test | cycle
    test
    test
    ...
    ^C

Repeat a file:

    $ cycle <foo.txt

Repeat multiple files:

    $ cat foo.txt bar.txt | cycle


Running
-------

Should work with any Unix, including Linux and macOS.

Mac users can install from
[my Homebrew tap](https://github.com/sjmulder/homebrew-tap)

    brew install sjmulder/tap/cycle

To compile, install and uninstall from source:

    make
    make install   [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]
    make uninstall [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]


Legal
-----

Copyright (c) 2018, Sijmen J. Mulder (<ik@sjmulder.nl>)

cycle is free software: you can redistribute it and/or modify it under
the terms of the GNU Affero General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

cycle is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
more details.

You should have received a copy of the GNU Affero General Public License
along with cycle. If not, see <https://www.gnu.org/licenses/>.
