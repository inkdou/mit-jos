// Public definitions for the POSIX-like file descriptor emulation layer
// that our user-land support library implements for the use of applications.
// See the code in the lib directory for the implementation details.

#ifndef JOS_INC_FD_H
#define JOS_INC_FD_H

#include <inc/types.h>
#include <inc/fs.h>
#include <inc/security.h>

struct Fd;
struct Stat;
struct Dev;

// Per-device-class file descriptor operations
struct Dev {
	int dev_id;
	const char *dev_name;
	ssize_t (*dev_read)(struct Fd *fd, void *buf, size_t len);
	ssize_t (*dev_write)(struct Fd *fd, const void *buf, size_t len);
	int (*dev_close)(struct Fd *fd);
	int (*dev_stat)(struct Fd *fd, struct Stat *stat);
	int (*dev_trunc)(struct Fd *fd, off_t length);
	int (*dev_chmod)(struct Fd *fd, fsperm_t newperm);
	int (*dev_chown)(struct Fd *fd, uid_t uid);
	int (*dev_chgrp)(struct Fd *fd, gid_t gid);

    ssize_t (*dev_recvfrom)(struct Fd *fd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
    ssize_t (*dev_sendto)(struct Fd *fd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
};

struct FdFile {
	int id;
};

struct FdSock {
	int sockid;
};

struct Fd {
	int fd_dev_id;
	off_t fd_offset;
	int fd_omode;
	unsigned perm;
	gid_t gid;
	uid_t uid;
	
	union {
		// File server files
		struct FdFile fd_file;
		// Network sockets
		struct FdSock fd_sock;
	};
};

struct Stat {
	char st_name[MAXNAMELEN];
	off_t st_size;
	int st_isdir;
	struct Dev *st_dev;

	uid_t st_uid;
	gid_t st_gid;
	fsperm_t st_perm;
};

char*	fd2data(struct Fd *fd);
int	fd2num(struct Fd *fd);
int	fd_alloc(struct Fd **fd_store);
int	fd_close(struct Fd *fd, bool must_exist);
int	fd_lookup(int fdnum, struct Fd **fd_store);
int	dev_lookup(int devid, struct Dev **dev_store);

extern struct Dev devfile;
extern struct Dev devsock;
extern struct Dev devcons;
extern struct Dev devpipe;

#endif	// not JOS_INC_FD_H
