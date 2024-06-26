/* getifaddrs -- get names and addresses of all network interfaces
   Copyright (C) 2003-2007, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <irt_syscalls.h>


int __no_netlink_support = 1;


/* Create a linked list of `struct ifaddrs' structures, one for each
   network interface on the host machine.  If successful, store the
   list in *IFAP and 2004, 2005, 2006, return 0.  On errors, return -1 and set `errno'.  */
#define IFADDRS_BUFSIZE 2048

void 
__netlink_free_handle (struct netlink_handle *h)
{
	return;
}

int
__netlink_request (struct netlink_handle *h, int type)
{
	return -EOPNOTSUPP;
}

static int
__netlink_sendreq (struct netlink_handle *h, int type) {
	return -EOPNOTSUPP;
}

void
__netlink_close (struct netlink_handle *h)
{
	return;
}

int
__netlink_open (struct netlink_handle *h)
{
	return -EOPNOTSUPP;
}


/**
 * LIND: we've replaced libc's getifaddrs with our own to avoid using NETLINK protocols
 * Instead here we generate net devices in safeposix on startup.
 * Our implementation sends a buffer to rustposix to populate with device information.
 * Here, we parse that buffer into ifaddrs structs and set them up as a linked list.
 * strtok is used to parse by newline, and scanf populates the relevant fields.
 **/

int
getifaddrs (struct ifaddrs **ifap)
{
	char* buf = malloc(IFADDRS_BUFSIZE);
	int result = __nacl_irt_getifaddrs(buf, IFADDRS_BUFSIZE);

	if (result < 0) {
		free(buf);
		__set_errno(-result);
		return -1;
	}

	const char s[2] = "\n";
	char *token;
	struct ifaddrs *ifa;

	ifa = malloc(sizeof(struct ifaddrs));
	*ifap = ifa;

	/* get the first token */
	token = strtok(buf, s);

	/* walk through other tokens */
	while( token != NULL ) {

		ifa->ifa_name = calloc(1, sizeof(char) * IF_NAMESIZE);
		ifa->ifa_addr = malloc(sizeof(struct sockaddr));
		ifa->ifa_netmask = malloc(sizeof(struct sockaddr));
		ifa->ifa_broadaddr = malloc(sizeof(struct sockaddr));
		int flags;

		char name[IF_NAMESIZE];
		char addr[40];
		char naddr[40];
		char bdaddr[40];

		sscanf(token, "%s %d %s %s %s", name, &flags, addr, naddr, bdaddr);

		struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
		struct sockaddr_in *na = (struct sockaddr_in *)ifa->ifa_netmask;
		struct sockaddr_in *bda = (struct sockaddr_in *)ifa->ifa_broadaddr;

		strncpy(ifa->ifa_name, name, IF_NAMESIZE - 1);
		ifa->ifa_flags = flags;

		sa->sin_family = AF_INET;
		sa->sin_port = htons(0);
		inet_aton(addr, &(sa->sin_addr));

		na->sin_family = AF_INET;
		na->sin_port = htons(0);
		inet_aton(naddr, &(na->sin_addr));

		bda->sin_family = AF_INET;
		bda->sin_port = htons(0);
		inet_aton(bdaddr, &(bda->sin_addr));

		ifa->ifa_data = NULL;

		token = strtok(NULL, s);

		if (token != NULL) {
			ifa->ifa_next = malloc(sizeof(struct ifaddrs));
			ifa = ifa->ifa_next;
		} else {
			ifa->ifa_next = NULL;
		}
	}

	free(buf);
  
  	return result;
}
libc_hidden_def (getifaddrs)


void
freeifaddrs (struct ifaddrs *ifa)
{
	struct ifaddrs *ifas = ifa;
	while (ifas != NULL) {
		free(ifas->ifa_name);
		free(ifas->ifa_addr);
		free(ifas->ifa_netmask);
		free(ifas->ifa_broadaddr);
		struct ifaddrs *tmp = ifas;
		ifas = ifas->ifa_next;
		free (tmp);
	}
}
libc_hidden_def (freeifaddrs)
