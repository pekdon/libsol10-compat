AC_INIT([libsol10-compat],[0.1.0],[pekdon@gmail.com])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([])
LT_INIT([])
AC_PROG_CC
AC_PROG_CC_C99

AC_CHECK_HEADER([sys/file.h],
		[loc_sys_file_h='#define LIBSOL10_COMPAT_HAVE_SYS_FILE_H 1'],
		[])
AC_CHECK_HEADER([sys/random.h],
		[loc_sys_random_h='#define LIBSOL10_COMPAT_HAVE_SYS_RANDOM_H 1'],
		[])
AC_CHECK_HEADER([endian.h],
		[loc_endian_h='#define LIBSOL10_COMPAT_HAVE_ENDIAN_H 1'], [])
AC_CHECK_HEADER([err.h],
		[loc_err_h='#define LIBSOL10_COMPAT_HAVE_ERR_H 1'], [])
AC_CHECK_HEADER([paths.h],
		[loc_paths_h='#define LIBSOL10_COMPAT_HAVE_PATHS_H 1'], [])
AC_CHECK_HEADER([strings.h],
		[loc_strings_h='#define LIBSOL10_COMPAT_HAVE_STRINGS_H 1'], [])

AC_CHECK_FUNC([dirfd], [dirfd_func=yes], [dirfd_fund=no])
AX_CHECK_DEFINE([dirent.h], [dirfd], [dirfd_macro=yes], [dirfd_macro=no])
if test "x${dirfd_func}" = "xyes" -o "x${dirfd_macro}" = "xyes"; then
	loc_dirfd='#define LIBSOL10_COMPAT_HAVE_DIRFD 1'
fi

AC_CHECK_FUNC([getdelim],
	      [loc_getdelim='#define LIBSOL10_COMPAT_HAVE_GETDELIM 1'], [])
AC_CHECK_FUNC([getline],
	      [loc_getline='#define LIBSOL10_COMPAT_HAVE_GETLINE 1'], [])
AC_CHECK_FUNC([posix_memalign],
	      [loc_posix_memalign='#define LIBSOL10_COMPAT_HAVE_POSIX_MEMALIGN 1'],
	      [])
AC_CHECK_FUNC([strnlen],
	      [loc_strnlen='#define LIBSOL10_COMPAT_HAVE_STRNLEN 1'], [])
AC_CHECK_FUNC([strndup],
	      [loc_strndup='#define LIBSOL10_COMPAT_HAVE_STRNDUP 1'], [])
AC_CHECK_FUNC([strncasecmp],
	      [loc_strncasecmp='#define LIBSOL10_COMPAT_HAVE_STRNCASECMP 1'], [])
AC_CHECK_FUNC([strcasestr],
	      [loc_strcasestr='#define LIBSOL10_COMPAT_HAVE_STRCASESTR 1'], [])
AC_CHECK_FUNC([strlcat],
	      [loc_strlcat='#define LIBSOL10_COMPAT_HAVE_STRLCAT 1'], [])
AC_CHECK_FUNC([strsep],
	      [loc_strsep='#define LIBSOL10_COMPAT_HAVE_STRSEP 1'], [])
AC_CHECK_FUNC([memmem],
	      [loc_memmem='#define LIBSOL10_COMPAT_HAVE_MEMMEM 1'], [])
AC_CHECK_FUNC([flock],
	      [loc_flock='#define LIBSOL10_COMPAT_HAVE_FLOCK 1'], [])
AC_CHECK_FUNC([getrandom],
	      [loc_getrandom='#define LIBSOL10_COMPAT_HAVE_GETRANDOM 1'], [])
AC_CHECK_FUNC([getentropy],
	      [loc_getentropy='#define LIBSOL10_COMPAT_HAVE_GETENTROPY 1'], [])
AC_CHECK_FUNC([openpty],
	      [loc_openpty='#define LIBSOL10_COMPAT_HAVE_OPENPTY 1'], [])
AC_CHECK_FUNC([login_tty],
	      [loc_login_tty='#define LIBSOL10_COMPAT_HAVE_LOGIN_TTY 1'], [])
AC_CHECK_FUNC([forkpty],
	      [loc_forkpty='#define LIBSOL10_COMPAT_HAVE_FORKPTY 1'], [])
AC_CHECK_FUNC([timelocal],
	      [loc_timelocal='#define LIBSOL10_COMPAT_HAVE_TIMELOCAL 1'], [])
AC_CHECK_FUNC([timegm],
	      [loc_timegm='#define LIBSOL10_COMPAT_HAVE_TIMEGM 1'], [])
AC_CHECK_FUNC([faccessat],
	      [loc_faccessat='#define LIBSOL10_COMPAT_HAVE_FACCESSAT 1'], [])
AC_CHECK_FUNC([readlinkat],
	      [loc_readlinkat='#define LIBSOL10_COMPAT_HAVE_READLINKAT 1'], [])

AC_CHECK_LIB([util], [forkpty])

AC_SUBST([LIBSOL10_COMPAT_HAVE_SYS_FILE_H], [${loc_sys_file_h}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_SYS_RANDOM_H], [${loc_sys_random_h}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_ENDIAN_H], [${loc_endian_h}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_ERR_H], [${loc_err_h}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_PATHS_H], [${loc_paths_h}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_STRINGS_H], [${loc_strings_h}])

AC_SUBST([LIBSOL10_COMPAT_HAVE_DIRFD], [${loc_dirfd}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_GETDELIM], [${loc_getdelim}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_GETLINE], [${loc_getline}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_POSIX_MEMALIGN], [${loc_posix_memalign}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_STRNLEN], [${loc_strnlen}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_STRNDUP], [${loc_strndup}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_STRNCASECMP], [${loc_strncasecmp}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_STRCASESTR], [${loc_strcasestr}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_STRLCAT], [${loc_strlcat}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_STRSEP], [${loc_strsep}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_MEMMEM], [${loc_memmem}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_FLOCK], [${loc_flock}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_GETRANDOM], [${loc_getrandom}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_GETENTROPY], [${loc_getentropy}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_OPENPTY], [${loc_openpty}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_LOGIN_TTY], [${loc_login_tty}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_FORKPTY], [${loc_forkpty}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_TIMELOCAL], [${loc_timelocal}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_TIMEGM], [${loc_timegm}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_FACCESSAT], [${loc_faccessat}])
AC_SUBST([LIBSOL10_COMPAT_HAVE_READLINKAT], [${loc_readlinkat}])


AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([libsol10-compat.pc
		 include/libsol10-compat/libsol10-compat-config.h
		 Makefile
		 include/Makefile
		 pkgsrc/Makefile
		 src/Makefile
		 util/Makefile
		 test/Makefile])

AC_ARG_ENABLE([tests], [--enable-tests    Enable tests],
[case "${enableval}" in
  yes) tests=true ;;
  no)  tests=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-tests]) ;;
esac], [tests=false])
AM_CONDITIONAL([TESTS], [test x$tests = xtrue])

AC_OUTPUT
