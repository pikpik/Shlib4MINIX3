/*	$NetBSD: execl.c,v 1.16 2008/01/09 11:26:03 simonb Exp $	*/

/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
#if 0
static char sccsid[] = "@(#)exec.c	8.1 (Berkeley) 6/4/93";
#else
__RCSID("$NetBSD: execl.c,v 1.16 2008/01/09 11:26:03 simonb Exp $");
#endif
#endif /* LIBC_SCCS and not lint */

#include "namespace.h"
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "reentrant.h"

#ifdef __weak_alias
__weak_alias(execl,_execl)
#endif


extern char **environ;

int
execl(const char *name, const char *arg, ...)
{
	int r;
#if (defined(__i386__) || defined(__m68k__)) && !defined(__minix)
	r = execve(name, __UNCONST(&arg), environ);
	return r;
#else
	va_list ap;
	char **argv;
	int i;

	va_start(ap, arg);
	for (i = 2; va_arg(ap, char *) != NULL; i++)
		continue;
	va_end(ap);

	if ((argv = alloca(i * sizeof (char *))) == NULL) {
		errno = ENOMEM;
		return -1;
	}
	
	va_start(ap, arg);
	argv[0] = __UNCONST(arg);
	for (i = 1; (argv[i] = va_arg(ap, char *)) != NULL; i++) 
		continue;
	va_end(ap);
	
	r = execve(name, argv, environ);
	return r;
#endif
}
