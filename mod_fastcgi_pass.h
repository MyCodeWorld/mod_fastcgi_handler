/*
 * $Id: mod_fastcgi.h,v 1.50 2004/01/07 02:03:28 robs Exp $
 */

#ifndef MOD_FASTCGI_H
#define MOD_FASTCGI_H

#define MOD_FASTCGI_VERSION "2.4.3"

#define FASTCGI_HANDLER_NAME "fastcgi-script"

/*
 * # of idle seconds allowed to pass while connected to a FastCGI before aborting
 */
#define FCGI_DEFAULT_IDLE_TIMEOUT 30

/*
 * The number of failed starts that can occur before the application is
 * considered broken and start attempts fall back to FAILED_STARTS_DELAY.
 */
#define MAX_FAILED_STARTS 3

/*
 * The number of seconds between attempts to start an application that
 * has been declared broken (see MAX_FAILED_STARTS).
 */
#define FAILED_STARTS_DELAY 600

#define FCGI_DEFAULT_LISTEN_Q 100          /* listen queue (backlog) depth */
#define FCGI_DEFAULT_RESTART_DELAY 5       /* delay between restarts */
#define DEFAULT_INIT_START_DELAY 1         /* delay between starts */
#define FCGI_DEFAULT_PRIORITY 0            /* process priority - not used */
#define FCGI_MIN_EXEC_RETRY_DELAY 10       /* minimum number of seconds to
                                              wait before restarting */
#define MAX_INIT_ENV_VARS 64               /* max # of -initial-env options */

/* max number of chars in a line of stderr we can handle from a FastCGI Server */
#define FCGI_SERVER_MAX_STDERR_LINE_LEN 1023

/* size of the buffer the PM uses to read records from the request handlers */
#define FCGI_MSGS_BUFSIZE  32 * 512

#define SERVER_BUFSIZE 8192

/* Dynamic FastCGI applications */
#define FCGI_DEFAULT_MAX_PROCS  50         /* maximum number of processes that
                                            * are allowed to run on system */
#define FCGI_DEFAULT_MIN_PROCS  5          /* minimum number of processes that
                                            * can be run without being killed
                                            * off by the process manager */
#define FCGI_DEFAULT_MAX_CLASS_PROCS 10    /* maximum number of processes that
                                            * are allowed to run for a single
                                            * application class */
#define FCGI_DEFAULT_KILL_INTERVAL 300     /* number of seconds in which we
                                            * should execute the kill policy
                                            * by killing off extra instances */
#define FCGI_DEFAULT_UPDATE_INTERVAL 300   /* number of seconds in which we
                                            * should recalculate the value of
                                            * totalConnTime variable */
#define FCGI_DEFAULT_GAIN 0.5              /* value used as an exponent in the
                                            * calculation of the exponentially
                                            * decayed connection times;
                                            * old values are scaled by
                                            * (1-dynamicGain), so making it
                                            * smaller weights them more heavily
                                            * compared to the current value,
                                            * which is scaled by dynamicGain */
#define FCGI_DEFAULT_THRESHOLD_1 0         /* if load falls below this value
                                            * and we have only one instance
                                            * running, it is killed off */
#define FCGI_DEFAULT_THRESHOLD_N 50        /* if load falls below this value
                                            * and we have more than one
                                            * instances, one is killed off */
#define FCGI_DEFAULT_START_PROCESS_DELAY 3 /* specifies the maximum number of
                                            * seconds a server should wait in
                                            * attempt to connect to fcgi app
                                            * before sending FCGI_REQUEST_TIMEOUT_JOB */
#define	FCGI_DEFAULT_MIN_SERVER_LIFE 30    /* the default minimum number of
                                            * seconds a server must stay alive
                                            * before it's considered broken. */
#define FCGI_DEFAULT_PROCESS_SLACK 5       /* if this number combined with the
                                            * number of the currently running
                                            * processes exceeds dynamicMaxProcs, then
                                            * the KillDynamicProcs() is invoked */
#define FCGI_DEFAULT_RESTART_DYNAMIC 0     /* Do not restart dynamic processes */
#define FCGI_DEFAULT_AUTOUPDATE 0          /* do not automatically restart
                                            * fcgi apps when the binary on the
                                            * disk is changed. */

/*
 * Should data recieved from the FastCGI server be immediately flushed to
 * the client?  Default: FALSE
 */
#define FCGI_FLUSH	FALSE


/* Default dir for Unix/Domain sockets */
#define DEFAULT_SOCK_DIR  DEFAULT_REL_RUNTIMEDIR "/fastcgi"


#define FCGI_MAGIC_TYPE "application/x-httpd-fcgi"

#if defined(PATH_MAX)
#define FCGI_MAXPATH  PATH_MAX
#elif defined(MAXPATHLEN)
#define FCGI_MAXPATH  MAXPATHLEN
#else
#define FCGI_MAXPATH  512
#endif

/* FCGI_REQUEST_COMPLETE_JOB is the longest: id, path, user, gid, qtime, start */
#define FCGI_MSG_CRAP  1 + 2 + MAX_USER_NAME_LEN + 1 + MAX_GID_CHAR_LEN + (2 * 11) + 3

#if defined(PIPE_BUF) && PIPE_BUF < FCGI_MAXPATH + FCGI_MSG_CRAP
#define FCGI_MAX_MSG_LEN  PIPE_BUF
#undef FCGI_MAXPATH
#define FCGI_MAXPATH  PIPE_BUF - FCGI_MSG_CRAP
#else
#define FCGI_MAX_MSG_LEN  FCGI_MAXPATH + FCGI_MSG_CRAP
#endif

/* There is no way to reliably determiine the highest descriptor that can be
 * assigned (UNP Vol1 Ed2 p337, and APUE p43) so we pick a number. */
#if (defined FD_SETSIZE) && (FD_SETSIZE > 1024)
#define FCGI_MAX_FD FD_SETSIZE
#else
#define FCGI_MAX_FD  1024
#endif

#ifndef SUN_LEN
#define SUN_LEN(sock) \
    (sizeof(*(sock)) - sizeof((sock)->sun_path) + strlen((sock)->sun_path))
#endif

#if defined MAXLOGNAME && MAXLOGNAME > 15
#define MAX_USER_NAME_LEN MAXLOGNAME
#elif defined UT_NAMESIZE && UT_NAMESIZE > 15
#define MAX_USER_NAME_LEN UT_NAMESIZE
#else
#define MAX_USER_NAME_LEN 15     /* Max len of user name (suexec w/ ~user), */
#endif                           /* must accomodate uid printed as %ld too */
#define MAX_GID_CHAR_LEN 15      /* Max #chars in a gid printed as %ld */

#ifndef TRUE
#define TRUE  (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#define get_signal_text(a)  apr_signal_description_get(a)

typedef struct {
	int idle_timeout;
	apr_array_header_t *headers;
} fastcgi_pass_cfg;

#endif	/* MOD_FASTCGI_H */
