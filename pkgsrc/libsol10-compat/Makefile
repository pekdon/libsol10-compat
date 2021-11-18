# $NetBSD$

DISTNAME=	libsol10-compat-0.1.0
PKGREVISION=	0
CATEGORIES=	devel
MASTER_SITES=	https://github.com/pekdon/libsol10-compat/

MAINTAINER=	pekdon@gmail.com
HOMEPAGE=	https://github.com/pekdon/libsol10-compat/
COMMENT=	Legacy OS compatability library0
LICENSE=	mit

HAS_CONFIGURE=		yes
CONFIGURE_ARGS+=	--prefix=${PREFIX}
PKGCONFIG_OVERRIDE+=	libsol10-compat.pc.in

.include "../../mk/bsd.pkg.mk"
