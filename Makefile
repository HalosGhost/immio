CFLAGS	+=	-Os -Wall
PROG		=	immio
PREFIX	?=	/usr
VER		=	1.0

${PROG}: ${PROG}.c
	@${CC} ${CFLAGS} -o ${PROG} ${PROG}.c
	@strip ${PROG}

clean:
	@rm -f ${PROG}

install:
	@install -Dm755 ${PROG} ${DESTDIR}${PREFIX}/bin/${PROG}
