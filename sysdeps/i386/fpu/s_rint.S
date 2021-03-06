/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <machine/asm.h>

RCSID("$NetBSD: s_rint.S,v 1.4 1995/05/09 00:16:08 jtc Exp $")

ENTRY(__rint)
	fldl	4(%esp)
	frndint
	NACLRET
END (__rint)
weak_alias (__rint, rint)
