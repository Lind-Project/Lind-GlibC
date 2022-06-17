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

int
getifaddrs (struct ifaddrs **ifap)
{
	char* buf = malloc(IFADDRS_BUFSIZE); //"lo 65609 127.0.0.1 127.0.0.1 none\nwlp0s20f3 69699 192.168.1.255 192.168.1.255 192.168.1.255\n";
	int result = __nacl_irt_getifaddrs(buf, IFADDRS_BUFSIZE);

	if (result < 0) {
		free(buf);
		errno = result;
		return -1;
	}

	const char s[2] = "\n";
	char *token;
	struct ifaddrs *ifa;

	ifa = calloc(1, sizeof(struct ifaddrs));
	printf("allocating ifa %p\n", ifa);
	printf("size of ifa %d", sizeof(struct ifaddrs));
	fflush(stdout);
	*ifap = ifa;

	/* get the first token */
	token = strtok(buf, s);

	/* walk through other tokens */
	while( token != NULL ) {
		char* hostname = calloc(1, IF_NAMESIZE);
		printf("allocating hostname %p\n", hostname);
		fflush(stdout);
		char addr[16] = {0};
		char naddr[16] = {0};
		char bdaddr[16] = {0};
		struct sockaddr_in *sa = malloc(sizeof(struct sockaddr_in));
		struct sockaddr_in *na = malloc(sizeof(struct sockaddr_in));
		struct sockaddr_in *bda = malloc(sizeof(struct sockaddr_in));
		int flags;

		sscanf(token, "%s %d %s %s %s", hostname, &flags, addr, naddr, bdaddr);
		int bdflag = strncmp(bdaddr, "none", 4);

		sa->sin_family = AF_INET;
		sa->sin_port = htons(0);
		inet_aton(addr, &(sa->sin_addr));

		na->sin_family = AF_INET;
		na->sin_port = htons(0);
		inet_aton(naddr, &(na->sin_addr));

		bda->sin_family = AF_INET;
		bda->sin_port = htons(0);
		if (bdflag) inet_aton(bdaddr, &(bda->sin_addr));
		else inet_aton("0.0.0.0", &(bda->sin_addr));

		ifa->ifa_name = hostname;
		printf("added hostname to ifa_name %p\n", ifa->ifa_name);
		fflush(stdout);
		ifa->ifa_flags = flags;
		ifa->ifa_addr = (struct sockaddr*) sa;
		ifa->ifa_netmask = (struct sockaddr*) na;
		ifa->ifa_broadaddr = (struct sockaddr*) bda;
		ifa->ifa_data = NULL;

		token = strtok(NULL, s);

		if (token != NULL) {
			ifa->ifa_next = calloc(1, sizeof(struct ifaddrs));
			ifa = ifa->ifa_next;
			printf("allocating ifa %p\n", ifa);
			fflush(stdout);
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
		printf("freeing ifa %p\n", ifas);
		fflush(stdout);
		printf("freeing name %p\n", ifas->ifa_name);
		fflush(stdout);
		free(ifas->ifa_name);
		printf("freeing addr\n");
		fflush(stdout);
		free(ifas->ifa_addr);
		printf("freeing netmask\n");
		fflush(stdout);
		free(ifas->ifa_netmask);
		printf("freeing broadaddr\n");
		fflush(stdout);
		free(ifas->ifa_broadaddr);
		struct ifaddrs *tmp = ifas;
		ifas = ifas->ifa_next;
		printf("freeing struct\n");
		fflush(stdout);
		free (tmp);
	}
}
libc_hidden_def (freeifaddrs)
