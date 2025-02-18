/*
 * Copyright (c) 2006, Adam Dunkels
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef __UBASIC_H__
#define __UBASIC_H__

enum ubasic_errors
{
    UBASIC_E_NONE = 0,
    UBASIC_E_PARSE,
    UBASIC_E_UNK_STATEMENT,
    UBASIC_E_UNK_KEY,
    UBASIC_E_UNK_LABEL,
    UBASIC_E_GOSUB_STACK_EXHAUSTED,
    UBASIC_E_UNMATCHED_RETURN,
    UBASIC_E_IF_STACK_EXHAUSTED,
    UBASIC_E_UNMATCHED_IF,
    UBASIC_E_SELECT_STACK_EXHAUSTED,
    UBASIC_E_UNMATCHED_END_SELECT,
    UBASIC_E_FOR_STACK_EXHAUSTED,
    UBASIC_E_UNMATCHED_NEXT,
    UBASIC_E_DO_STACK_EXHAUSTED,
    UBASIC_E_UNMATCHED_UNTIL,
    UBASIC_E_WHILE_STACK_EXHAUSTED,
    UBASIC_E_UNMATCHED_WEND,
    UBASIC_E_UNKNOWN_ERROR,
    UBASIC_E_ENDMARK
};

/** holds short error messages for all known ubasic_errors */
extern const char *ubasic_errstrings[UBASIC_E_ENDMARK];

extern int ubasic_error;

void ubasic_init(const char *program);
void ubasic_run(void);
int ubasic_finished(void);
void ubasic_end();
int ubasic_linenumber();
int jump_label(char * label);

int ubasic_get_variable(int varnum);
void ubasic_set_variable(int varum, int value);
void ubasic_set_md_ret(int md_ret);

#endif /* __UBASIC_H__ */
