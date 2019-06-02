#define DEFAULT_PROTOCOL 0
 #define PORT 8702
 #define HOST "localhost"
 /* #define HOST "127.0.0.1" */
 /* #define HOST "cmopc018" */
 #define TYPE SOCK_STREAM
 int main (void)
 {
 struct hostent *phe;
 struct sockaddr_in sin;
 int s;

 s = socket (PF_INET, TYPE, DEFAULT_PROTOCOL);
 if (s < 0)
 raise_report (LEVEL_FATAL, "tiny_echo", "can't create socket:
 %s", strerror (errno));
 /*
 * connect to the socket
 */

 memset (&sin, 0, sizeof sin);
 sin.sin_family = AF_INET;
 sin.sin_port = PORT;
 if ((phe = gethostbyname (HOST)))
 {
 memcpy (&sin.sin_addr, phe->h_addr_list[0], phe->h_length);
 raise_report (LEVEL_INFO, "tiny_echo", "addr is %X",
 sin.sin_addr);
 }
 else
 if ((sin.sin_addr.s_addr = inet_addr (HOST)) == INADDR_NONE)
 raise_report (LEVEL_FATAL, "tiny_echo", "can't get \"%s\"
 host entry", HOST);

 if (connect (s, (struct sockaddr *)&sin, sizeof sin) < 0)
 raise_report (LEVEL_FATAL, "tiny_echo", "can't connect to
 %s.%d: %s", HOST, sin.sin_port, strerror (errno));

 raise_report (LEVEL_INFO, "tiny_echo", "CONNECTED");

return 0;
 }
