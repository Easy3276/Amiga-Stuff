/*
 * cancellation.c
 * 
 * Asynchronously-cancellable function calls.
 * 
 * Written & released by Keir Fraser <keir.xen@gmail.com>
 * 
 * This is free and unencumbered software released into the public domain.
 * See the file COPYING for more details, or visit <http://unlicense.org>.
 */

asm (
    ".global _call_cancellable_fn      \n"
    "_call_cancellable_fn:             \n"
    "    movem.l %d2-%d7/%a2-%a6,-(%sp)\n" /* (SP += 44) */
    "    move.l  44+4(%sp),%a0         \n" /* A0 = c */
    "    move.l  %sp,(%a0)             \n" /* c->sp = SP */
    "    move.l  44+8(%sp),%a0         \n" /* A0 = fn */
    "    move.l  44+12(%sp),-(%sp)     \n" /* push arg */
    "    jsr     (%a0)                 \n" /* (*fn)(arg) */
    "    lea     4(%sp),%sp            \n" /* pop arg */
    "    move.l  44+4(%sp),%a0         \n" /* A0 = c */
    "    move.l  #0,(%a0)              \n" /* c->sp = NULL */
    "1:  movem.l (%sp)+,%d2-%d7/%a2-%a6\n" /* (SP -= 44) */
    "    rts                           \n"
    "_do_cancel:                       \n"
    "    move.l  %d0,%sp               \n" /* SP = c->sp as saved above */
    "    moveq   #-1,%d0               \n" /* D0 = return code = -1 */
    "    jra     1b                    \n"
    );

void do_cancel(void);

struct c_exception_frame *user_frame;

void cancel_call(struct cancellation *c)
{
    struct c_exception_frame *frame;

    if (c->sp == NULL)
        return;

    /* Modify return frame: Jump to cancellation exit path of
     * call_cancellable_fn() with original SP in D0. */
    frame = user_frame;
    frame->d0 = (uint32_t)c->sp;
    frame->pc = (uint32_t)do_cancel;
    frame->sr &= 0x2000; /* Preserve Supervisor mode; clear everything else */

    /* Do this work at most once per invocation of call_cancellable_fn. */
    c->sp = NULL;
}

/*
 * Local variables:
 * mode: C
 * c-file-style: "Linux"
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 */
