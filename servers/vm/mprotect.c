
#define _SYSTEM 1

#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/config.h>
#include <minix/const.h>
#include <minix/ds.h>
#include <minix/endpoint.h>
#include <minix/keymap.h>
#include <minix/minlib.h>
#include <minix/type.h>
#include <minix/ipc.h>
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/safecopies.h>
#include <minix/bitmap.h>
#include <minix/debug.h>

#include <sys/mman.h>

#include <errno.h>
#include <assert.h>
#include <string.h>
#include <env.h>
#include <stdio.h>
#include <fcntl.h>
#include <memory.h>

#include "glo.h"
#include "proto.h"
#include "util.h"
#include "region.h"

/*===========================================================================*
 *				do_mprotect				     *
 *===========================================================================*/
PUBLIC int do_mprotect(message *m)
{
	int r, n;
	struct vmproc *vmp;
	int mfflags = 0;
	struct vir_region *vr = NULL;

	if((r=vm_isokendpt(m->m_source, &n)) != OK) {
		panic("do_mmap: message from strange source: %d", m->m_source);
	}

	vmp = &vmproc[n];

	if(!(vmp->vm_flags & VMF_HASPT))
		return ENXIO;


	/* We're green. */


	/* Let's say hello. */

	printf ( "Konnichwa?" );


	return OK;
}
