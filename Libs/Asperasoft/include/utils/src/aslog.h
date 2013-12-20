/*
 * aslog.h
 *
 * Logging module (syslog or log file)
 */

#ifndef _AS_LOG_H_
#define _AS_LOG_H_

#include "asdefs.h"
#include "astypes.h"

/* Log types 
 *
 * If the type is set to AS_LOG_SYSLOG, it will use syslog on Unix and
 * a log file on Windows.
 */
#define AS_LOG_SYSLOG   1
#define AS_LOG_FILE     2

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief   Init log file
 * Initialize log file
 * @param   type        Log type
 * @param   logfile     Log file name
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_log_init(
    int type, 
    const char *logfile);

/*
 * @brief   Close log file and release resources 
 *
 */
ASUTILS_API void 
as_log_cleanup(void);

/*
 * @brief   Enable/disable as_log
 * Set on/off switch for as_log.
 * @param   on_off      Flag 
 */
ASUTILS_API void 
as_log_set(
    int on_off);

/*
 * @brief   Get as_log status
 */
ASUTILS_API int
as_log_get(void);

/*
 * @brief   Get log path.  Shown to user to help diagnose
 * problems.  May return "<Unknown>", a directory or a final
 * file path depending on where as_log_init() broke down.
 */
ASUTILS_API const char *
as_log_get_path_desc(void);

/*
 * @brief   Enable/disable as_dbg
 * Set on/off switch for as_dbg.
 * @param   on_off      Flag
 */
ASUTILS_API void 
as_dbg_set(
    int on_off);

/*
 * @brief   Get as_dbg status
 */
ASUTILS_API int 
as_dbg_get(void);

/*
 * Write logging info to a file
 */
#ifndef __GNUC__
#define __attribute__(x) 
#endif

extern int g_dbg_level;
extern int g_log_enabled;
extern int g_debug_enabled;
extern int g_dbg_all;

/*
 *  @brief  Log a message using printf primitives.
 *  @param  msg     Message foramt with printf style directives
 */
ASUTILS_API int 
as_err(char const *msg, ...)
    __attribute__((format(printf, 1, 2)));

ASUTILS_API int 
as_log(char const *msg, ...)
    __attribute__((format(printf, 1, 2)));

ASUTILS_API int 
as_dbg(char const *msg, ...)
    __attribute__((format(printf, 1, 2)));


/*
   Produce a debug message with (e.g.):

      as_dbg2(("receive: block %u sum %u", block_num, checksum));

   Note the double parentheses, "((...))".  Most debug messages should 
   use level 2, as above; the highest is 4.  The default debug level 
   for development builds is 1; as_dbg1(()) statements should be used 
   for generic infrequent-event internal logging.  (Use as_log directly 
   only for reports of broad interest to users, such as final session
   statistics.)  Use level 3 to report entering and exiting functions,
   level 4 for extremely detailed reporting.  Builds ship with as_dbg3 
   and as_dbg4 statements #if'd out entirely.  They run, by default,
   at debug level zero, but it may be set to 1 or 2 from the command 
   line for troubleshooting.

   For each subsystem to be tracked, define somewhere a static or 
   global object of type as_dbg_subsys_t, e.g.:

     static as_dbg_subsys_t  dbg_fasp_xfer = { 2, "fasp_xfer" };

   On entry to a subsystem, push a pointer to it, and on exit, pop it:

   {
     as_dbug_subsys_t *old_subsys = as_dbg_push(&dbg_fasp_xfer);
     ...
     as_dbg_pop(old_subsys);
   }

   To force a common reporting level N for all subsystems, call
   as_dbg_set_all(N).  (Perhaps N is zero when you suspect a timing 
   dependency, or 2 just to see how far the program gets before 
   crashing.)  Call as_dbg_set_all(-1) to restore per-subsystem level 
   reporting.  Note that the new as_dbg_set_all() level is applied
   only after the next push or pop.

     (gdb) set dbg_fasp_xfer.level = 3;

   at a point before the thread of control enters the subsystem.
   You may also set g_dbg_level anywhere.

   To force a common level for all subsystems, use as_dbg_set_all().
   Call as_dbg_set_all(-1) to restore per-subsystem level reporting.

   For some code, you want reporting controlled independently of the 
   subsystem that calls it.  In such cases, use the as_dbgN_sys(())
   version:

     as_dbug2_sys(dbg_fasp_crypto,
         ("mac check failed, %x-%x-%x-%x", p[0], p[1], p[2], p[3])):

   Note again the peculiar parentheses.  as_dbgN_sys(s, a) is like
   "push(s); as_dbgN(a); pop(s)", but cheaper.

   Calls to as_dbgN() are cheap when the debug level is below N;
   arguments are not evaluated, and no function is called.  In cases 
   where a debug statement appears in a loop, you may test first 
   with as_is_dbgN():

      if (as_is_dbg2) {
         for (i = 0; i < N; ++i)
             as_dbg2("element %i: %d", i, element[i]);
      }

   There is a similar as_is_dbgN_sys(sys) predicate.

   Using these macros means that debug statements need not be #if'd
   out when not used, and (therefore) they won't rot as the code 
   around them changes.

 */

enum as_log_level_e {
    e_as_log_err   = 0,
    e_as_log_info  = 1,
    e_as_log_debug = 2
};

typedef struct _as_dbg_subsys_t {
#ifdef __cplusplus
    _as_dbg_subsys_t( int _level = 0, char const * const _name = 0) : level(_level), name(_name) {}
#endif
    int level;
    char const* const name;
} as_dbg_subsys_t;


ASUTILS_API as_dbg_subsys_t *as_dbg_push(as_dbg_subsys_t *next); 
ASUTILS_API void             as_dbg_pop(as_dbg_subsys_t *prev); 
ASUTILS_API void             as_dbg_set_all(int level);

#ifdef  WIN32
#pragma warning( disable:4127 ) // warning C4127: conditional expression is constant
                                // The while(0) in the as_dbg macros throws this warning if you have the warning level maxed.
#endif

#define  as_is_dbg1     (g_dbg_level >= 1)
#define  as_is_dbg2     (g_dbg_level >= 2)
#ifndef NDEBUG
# define as_is_dbg3     (g_dbg_level >= 3)
# define as_is_dbg4     (g_dbg_level >= 4)
#endif

#define  as_dbg1(args) do if (g_dbg_level >= 1) as_dbg args; while (0)
#define  as_dbg2(args) do if (g_dbg_level >= 2) as_dbg args; while (0)
#ifndef NDEBUG
# define as_dbg3(args) do if (g_dbg_level >= 3) as_dbg args; while (0)
# define as_dbg4(args) do if (g_dbg_level >= 4) as_dbg args; while (0)
#endif

#define  as_is_dbg1_sys(sys) (((g_dbg_all >= 0) ? g_dbg_all : sys->level) >= 1)
#define  as_is_dbg2_sys(sys) (((g_dbg_all >= 0) ? g_dbg_all : sys->level) >= 2)
#ifndef NDEBUG
# define as_is_dbg3_sys(sys) (((g_dbg_all >= 0) ? g_dbg_all : sys->level) >= 3)
# define as_is_dbg4_sys(sys) (((g_dbg_all >= 0) ? g_dbg_all : sys->level) >= 4)
#endif

/* as_dbgN_sys(s, a) is like to "push(s); as_dbgN(a); pop(s)" but cheaper */

#define  as_dbg1_sys(sys, args) \
    do if (as_is_dbg1_sys(sys)) as_dbg args; while (0)
#define  as_dbg2_sys(sys, args) \
    do if (as_is_dbg2_sys(sys)) as_dbg args; while (0)
#ifndef NDEBUG
# define as_dbg3_sys(sys, args) \
    do if (as_is_dbg3_sys(sys)) as_dbg args; while (0)
# define as_dbg4_sys(sys, args) \
    do if (as_is_dbg4_sys(sys)) as_dbg args; while (0)
#endif

#ifdef NDEBUG
 /* For performance, Level 3 and 4 statements generate no production code */
# define as_is_dbg3 (0)
# define as_is_dbg4 (0)
# define as_dbg3(x) do ; while(0)
# define as_dbg4(x) do ; while(0)

# define as_is_dbg4_sys(sys) (0)
# define as_dbg3_sys(y, x) do ; while(0)
# define as_dbg4_sys(y, x) do ; while(0)
# define as_is_dbg3 (0)
# define as_is_dbg4 (0)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _AS_LOG_H_ */
