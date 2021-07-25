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

Author
------
Sijmen J. Mulder (<ik@sjmulder.nl>)
