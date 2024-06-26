[![Build Status](https://github.com/Lind-Project/Lind-GlibC/actions/workflows/lind-selfhost.yml/badge.svg?branch=develop)](https://github.com/Lind-Project/Lind-GlibC/actions/workflows/lind-selfhost.yml)

This directory contains the version 2.7 release of the GNU C Library.

The GNU C Library is the standard system C library for all GNU systems,
and is an important part of what makes up a GNU system.  It provides the
system API for all programs written in C and C-compatible languages such
as C++ and Objective C; the runtime facilities of other programming
languages use the C library to access the underlying operating system.

In GNU/Linux systems, the C library works with the Linux kernel to
implement the operating system behavior seen by user applications.
In GNU/Hurd systems, it works with a microkernel and Hurd servers.

The GNU C Library implements much of the POSIX.1 functionality in the
GNU/Hurd system, using configurations i[34567]86-*-gnu.

When working with Linux kernels, the GNU C Library version 2.4 is
intended primarily for use with Linux kernel version 2.6.0 and later.
We only support using the NPTL implementation of pthreads, which is now
the default configuration.  Most of the C library will continue to work
on older Linux kernels and many programs will not require a 2.6 kernel
to run correctly.  However, pthreads and related functionality will not
work at all on old kernels and we do not recommend using glibc 2.4 with
any Linux kernel prior to 2.6.

All Linux kernel versions prior to 2.6.16 are known to have some bugs that
may cause some of the tests related to pthreads in "make check" to fail.
If you see such problems, please try the test suite on the most recent
Linux kernel version that you can use, before pursuing those bugs further.

The old LinuxThreads add-on implementation of pthreads for older Linux
kernels is no longer supported, and we are not distributing it with this
release.  Someone has volunteered to revive its maintenance unofficially
for at least a short time for the benefit of those using Linux kernels
older than 2.6, but a working version is not presently available.  When
it is in working condition, we will make it available alongside future
glibc releases.  LinuxThreads will not be supported.

The GNU C Library supports these configurations for using Linux kernels:

	i[34567]86-*-linux-gnu
	x86_64-*-linux-gnu
	powerpc-*-linux-gnu
	powerpc64-*-linux-gnu
	s390-*-linux-gnu
	s390x-*-linux-gnu
	ia64-*-linux-gnu
	sparc*-*-linux-gnu
	sparc64*-*-linux-gnu

	alpha*-*-linux-gnu	Requires Linux 2.6.9 for NPTL
	sh[34]-*-linux-gnu	Requires Linux 2.6.11

The code for other CPU configurations supported by volunteers outside of
the core glibc maintenance effort is contained in the separate `ports'
add-on.  You can find glibc-ports-2.7 distributed separately in the
same place where you got the main glibc distribution files.
Currently these configurations are known to work using the `ports' add-on:

	arm-*-linux-gnu		Requires Linux 2.6.15 for NPTL, no SMP support
	arm-*-linux-gnueabi	Requires Linux 2.6.16-rc1 for NPTL, no SMP
	mips-*-linux-gnu	Requires Linux 2.6.12 for NPTL
	mips64-*-linux-gnu	Requires Linux 2.6.12 for NPTL

The ports distribution also contains code for other configurations that
do not work or have not been maintained recently, but will be of use to
anyone trying to make a new configuration work.  If you are interested
in doing a port, please contact the glibc maintainers; see
http://www.gnu.org/software/libc/ for more information.

See the file INSTALL to find out how to configure, build, and install
the GNU C Library.  You might also consider reading the WWW pages for
the C library at http://www.gnu.org/software/libc/.

The GNU C Library is (almost) completely documented by the Texinfo manual
found in the `manual/' subdirectory.  The manual is still being updated
and contains some known errors and omissions; we regret that we do not
have the resources to work on the manual as much as we would like.  For
corrections to the manual, please file a bug in the `manual' component,
following the bug-reporting instructions below.  Please be sure to check
the manual in the current development sources to see if your problem has
already been corrected.

The file NOTES contains a description of the feature-test macros used
in the GNU C library, explaining how you can tell the library what
facilities you want it to make available.

Please see http://www.gnu.org/software/libc/bugs.html for bug reporting
information.  We are now using the Bugzilla system to track all bug reports.
This web page gives detailed information on how to report bugs properly.

The GNU C Library is free software.  See the file COPYING.LIB for copying
conditions, and LICENSES for notices about a few contributions that require
these additional notices to be distributed.
