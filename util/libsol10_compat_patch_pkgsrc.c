#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INCLUDE_MK_PREFIX  ".include \"../../mk/"
#define INCLUDE_PREFIX  ".include \"../../"

#define INCLUDE_SOL10_COMPAT \
	".include \"../../devel/libsol10-compat/buildlink3.mk\""

static void usage(const char *name)
{
	fprintf(stderr, "usage: %s package-list pkgsrc-dir\n", name);
	exit(1);
}

static char *path_join(const char *dir, const char *name)
{
	char buf[PATH_MAX] = {0};

	strlcat(buf, dir, sizeof(buf));
	if (buf[0] != '\0' && buf[strlen(buf) - 1] != '/') {
		strlcat(buf, "/", sizeof(buf));
	}
	strlcat(buf, name, sizeof(buf));
	return strdup(buf);
}

static void path_replace(const char *from, const char *to)
{
	char to_orig[PATH_MAX] = {0};
	snprintf(to_orig, sizeof(to_orig), "%s.orig", to);
	rename(to, to_orig);
	rename(from, to);
}

static int fgets_nonl(char *buf, size_t bufsiz, FILE *fp)
{
	if (fgets(buf, bufsiz, fp) == NULL) {
		return 1;
	}
	size_t buf_len = strlen(buf);
	if (buf_len && buf[buf_len - 1] == '\n') {
		buf[buf_len - 1] = '\0';
	}
	return 0;
}

static int do_patch_package_makefile(FILE *fp_in, FILE *fp_out, int is_common)
{
	int patched = 0;
	char buf[4096];
	while (fgets(buf, sizeof(buf), fp_in)) {
		if (strstr(buf, INCLUDE_SOL10_COMPAT) == buf) {
			if (patched) {
				buf[0] = '\n';
				buf[1] = '\0';
			} else {
				patched = 1;
			}
		} else if (! patched
			   && strstr(buf, INCLUDE_MK_PREFIX) == buf) {
			fprintf(fp_out, "%s\n", INCLUDE_SOL10_COMPAT);
			patched = 1;
		}
		fprintf(fp_out, "%s", buf);
	}

	if (! patched && is_common) {
		fprintf(fp_out, "%s\n", INCLUDE_SOL10_COMPAT);
		patched = 1;
	}

	return ! patched;
}

static int patch_package_makefile(const char *package_dir)
{
	int res = 1, is_common = 1;
	char *makefile_path = path_join(package_dir, "Makefile.common");
	FILE *fp_in = fopen(makefile_path, "r");
	if (fp_in == NULL) {
		free(makefile_path);

		is_common = 0;
		makefile_path = path_join(package_dir, "Makefile");
		fp_in = fopen(makefile_path, "r");
		if (fp_in == NULL) {
			fprintf(stderr, "failed to open %s for reading\n",
				makefile_path);
		}
	}

	if (fp_in != NULL) {
		char *makefile_tmp_path =
		  path_join(package_dir, "Makefile.sol10-compat");
		FILE *fp_out = fopen(makefile_tmp_path, "w");
		if (fp_out == NULL) {
			fprintf(stderr, "failed to open %s for writing\n",
				makefile_tmp_path);
		} else {
			res = do_patch_package_makefile(fp_in, fp_out, is_common);
			fclose(fp_out);
		}
		fclose(fp_in);

		if (res) {
			unlink(makefile_tmp_path);
		} else {
			path_replace(makefile_tmp_path, makefile_path);
		}

		free(makefile_tmp_path);
	}

	free(makefile_path);

	return res;
}

static int do_patch_package_buildlink3_mk(FILE *fp_in, FILE *fp_out)
{
	int patched = 0;
	char buf[4096];
	while (fgets(buf, sizeof(buf), fp_in)) {
		if (strstr(buf, INCLUDE_SOL10_COMPAT) == buf) {
			if (patched) {
				buf[0] = '\n';
				buf[1] = '\0';
			} else {
				patched = 1;
			}
		} else if (! patched
			   && ! strstr(buf, INCLUDE_MK_PREFIX)
			   && strstr(buf, INCLUDE_PREFIX) == buf) {
			fprintf(fp_out, "%s\n", INCLUDE_SOL10_COMPAT);
			patched = 1;
		}
		fprintf(fp_out, "%s", buf);
	}

	if (! patched) {
		fprintf(fp_out, "%s\n", INCLUDE_SOL10_COMPAT);
	}

	return 0;
}

static int patch_package_buildlink3_mk(const char *package_dir)
{
	int res = 1;
	char *buildlink_path = path_join(package_dir, "buildlink3.mk");
	FILE *fp_in = fopen(buildlink_path, "r");
	if (fp_in == NULL) {
		if (errno == ENOENT) {
			/* no buildlink3.mk is ok, skip patch */
			res = 0;
		} else {
			fprintf(stderr, "failed to open %s for reading\n",
				buildlink_path);
		}
	} else {
		char *buildlink_tmp_path =
		  path_join(package_dir, "buildlink3.mk.sol10-compat");
		FILE *fp_out = fopen(buildlink_tmp_path, "w");
		if (fp_out == NULL) {
			fprintf(stderr, "failed to open %s for writing\n",
				buildlink_tmp_path);
		} else {
			res = do_patch_package_buildlink3_mk(fp_in, fp_out);
			fclose(fp_out);
		}
		fclose(fp_in);

		if (res) {
			unlink(buildlink_tmp_path);
		} else {
			path_replace(buildlink_tmp_path, buildlink_path);
		}

		free(buildlink_tmp_path);
	}

	free(buildlink_path);

	return res;
}

static int patch_package(const char *pkgsrc_dir, const char *package)
{
	int res = 1;
	char *package_dir = path_join(pkgsrc_dir, package);

	printf("patching %s...", package_dir);
	if (patch_package_makefile(package_dir)) {
		printf(" ERROR (Makefile)\n");
	} else if (patch_package_buildlink3_mk(package_dir)) {
		printf(" ERROR (buildlink3.mk)\n");
	} else {
		printf(" ok\n");
		res = 0;
	}
	free(package_dir);
	return res;
}

int main(int argc, char *argv[])
{
	int res;
	FILE *fp;
	const char *package_list;
	const char *pkgsrc_dir;

	if (argc != 3) {
		usage(argv[0]);
	}
	
	package_list = argv[1];
	pkgsrc_dir = argv[2];

	fp = fopen(package_list, "r");
	if (fp) {
		char buf[1024];
		while (! fgets_nonl(buf, sizeof(buf), fp)) {
			if (buf[0] != '#' && buf[0] != '\0') {
				patch_package(pkgsrc_dir, buf);
			}
		}
		fclose(fp);
	} else {
		fprintf(stderr, "failed to open package-list %s\n",
			package_list);
	}

	return 0;
}
