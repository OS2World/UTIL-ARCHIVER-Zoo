#ifndef LINT
static char sccsid[]="$Source: /usr/home/dhesi/zoo/RCS/addbfmsc.c,v $\n\
$Id: addbfmsc.c,v 1.1 91/07/07 18:40:11 dhesi Exp $";
#endif /* LINT */

extern unsigned int crccode;
extern unsigned crctab[];

void addbfcrc(buffer,count)
char *buffer;
int count;
{
	kbhit();		/* allow keyboard interrupt to occur */

        _asm
        {
	    mov ax,crccode;	/* ax holds crccode value */
	    mov cx,count;	/* cx holds byte count */
	    les di,buffer	/* es:di holds buffer address */

	    jcxz done		/* if zero bytes, just skip */

/* loop begins here */
xloop:
	    sub bh,bh
	    mov bl,al
	    xor bl,es:[di]	/* now bx = (crccode xor c) & 0x00ff */
            shl bx,1            /* shifts _BX left (2-byte items) */
            mov dx,crctab[bx];	/* dx <= *buffer == exp2 */
	    sub bh,bh		/* bh = 0 */
	    mov bl,ah		/* bx <- exp1 */
	    xor bx,dx		/* bx <- exp1 xor exp2 */
	    mov ax,bx		/* crccode <- exp1 xor exp2 */
	    inc di		/* inc buffer pointer */
	    loop xloop		/* dec CX, jump if not zero */
/* loop ends here */

	    mov crccode,ax;	/* put back calculated CRC value */
done:
	}
}
