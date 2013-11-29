CFLAGS	+=	-Os -Wall
LIBS		=	-lcurl
PROG		=	immio
PREFIX	?=	/usr
VER		=	1.0
MANDIR	?=	/share/man

${PROG}: ${PROG}.c
	@${CC} ${CFLAGS} ${LIBS} -o ${PROG} ${PROG}.c
	@strip ${PROG}

clean:
	@rm -f ${PROG}

docs:
	@latex2man man1.tex ${PROG}.1

install:
	@install -Dm755 ${PROG} ${DESTDIR}${PREFIX}/bin/${PROG}
	@install -Dm644 ${PROG}.1 ${DESTDIR}${PREFIX}${MANDIR}/man1/${PROG}.1
