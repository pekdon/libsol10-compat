# $NetBSD$

BUILDLINK_TREE+=	libsol10-compat

.if !defined(LIBSOL10_COMPAT_BUILDLINK3_MK)
LIBSOL10_COMPAT_BUILDLINK3_MK:=

.include "../../mk/bsd.fast.prefs.mk"

.if ${OPSYS} == "SunOS"
BUILDLINK_API_DEPENDS.libsol10-compat+=	libsol10-compat>=0.1.0
BUILDLINK_ABI_DEPENDS.libsol10-compat+=	libsol10-compat>=0.1.0
BUILDLINK_PKGSRCDIR.libsol10-compat?=	../../devel/libsol10-compat
BUILDLINK_CPPFLAGS.libsol10-compat+=	-I${BUILDLINK_PREFIX.libsol10-compat}/include/libsol10-compat
BUILDLINK_LDFLAGS.libsol10-compat+=	-L${BUILDLINK_PREFIX.libsol10-compat}/lib -Wl,-R${BUILDLINK_PREFIX.libsol10-compat}/lib -lsol10_compat
.endif

.endif	# LIBSOL10_COMPAT_BUILDLINK3_MK

BUILDLINK_TREE+=	-tevent
