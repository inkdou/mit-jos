#include <inc/lib.h>
#include <lwip/sockets.h>
#include <lwip/inet.h>

#define PORT 7

#define BUFFSIZE 32
#define MAXPENDING 5    // Max connection requests
struct sockaddr_in echoserver, echoclient;
socklen_t clilen = sizeof(struct sockaddr_in);

static void
die(char *m)
{
	printf("%s\n", m);
	exit();
}

void
handle_client(int sock, struct sockaddr *sockaddr, socklen_t *clilenp)
{
	char buffer[BUFFSIZE];
	int received = -1;
	// Receive message
	if ((received = recvfrom(sock, buffer, BUFFSIZE, 0, sockaddr, clilenp)) < 0)
		die("Failed to receive initial bytes from client");

	// Send bytes and check for more incoming data in loop
	while (received > 0) {
		// Send back received data
        //cprintf("received data %s\n", buffer);
        //cprintf("from addr %s len = %d\n", inet_ntoa(echoclient.sin_addr), *clilenp);
		if (sendto(sock, buffer, received, 0, sockaddr, *clilenp) != received)
			die("Failed to send bytes to client");

		// Check for more data
		if ((received = recvfrom(sock, buffer, BUFFSIZE,0, sockaddr, clilenp)) < 0)
			die("Failed to receive additional bytes from client");
	}
	close(sock);
}

void
umain(int argc, char **argv)
{
	int serversock, clientsock;
	char buffer[BUFFSIZE];
	unsigned int echolen;
	int received = 0;

	// Create the UDP socket
	if ((serversock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		die("Failed to create socket");

	printf("opened socket\n");

	// Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));       // Clear struct
	echoserver.sin_family = AF_INET;                  // Internet/IP
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   // IP address
	echoserver.sin_port = htons(PORT);		  // server port

	printf("trying to bind\n");

	// Bind the server socket
	if (bind(serversock, (struct sockaddr *) &echoserver,
		 sizeof(echoserver)) < 0) {
		die("Failed to bind the server socket");
	}

	// Run until canceled
	while (1) {
		handle_client(serversock, (struct sockaddr*)&echoclient, &clilen);
	}

	close(serversock);

}
