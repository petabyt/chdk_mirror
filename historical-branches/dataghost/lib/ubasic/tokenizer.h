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
#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

typedef enum {
  TOKENIZER_ERROR,
  TOKENIZER_ENDOFINPUT,
  TOKENIZER_NUMBER,
  TOKENIZER_STRING,
  TOKENIZER_VARIABLE,
  TOKENIZER_LET,
  TOKENIZER_PRINT_SCREEN,
  TOKENIZER_PRINT,
  TOKENIZER_IF,
  TOKENIZER_THEN,
  TOKENIZER_ELSE,
  TOKENIZER_ENDIF,
  TOKENIZER_FOR,
  TOKENIZER_TO,
  TOKENIZER_NEXT,
  TOKENIZER_STEP,
  TOKENIZER_GOTO,
  TOKENIZER_DO,
  TOKENIZER_UNTIL,
  TOKENIZER_WHILE,
  TOKENIZER_WEND,
  TOKENIZER_GOSUB,
  TOKENIZER_RETURN,
  TOKENIZER_CALL,
  TOKENIZER_REM,
  TOKENIZER_END,
  TOKENIZER_CLS,
  TOKENIZER_COMMA,
  TOKENIZER_SEMICOLON,
  TOKENIZER_PLUS,
  TOKENIZER_MINUS,
  TOKENIZER_AND,
  TOKENIZER_OR,
  TOKENIZER_XOR,
  TOKENIZER_ASTR,
  TOKENIZER_SLASH,
  TOKENIZER_MOD,
  TOKENIZER_LEFTPAREN,
  TOKENIZER_RIGHTPAREN,
  TOKENIZER_LT,
  TOKENIZER_GT,
  TOKENIZER_EQ,
  TOKENIZER_NE,
  TOKENIZER_LE,
  TOKENIZER_GE,
  TOKENIZER_LNOT,
  TOKENIZER_LAND,
  TOKENIZER_LOR,
  TOKENIZER_CR,
  TOKENIZER_LABEL,
  TOKENIZER_SLEEP,
  TOKENIZER_CLICK,
  TOKENIZER_PRESS,
  TOKENIZER_RELEASE,
  TOKENIZER_SHOOT,
  TOKENIZER_GET_TV96,
  TOKENIZER_GET_USER_TV96,
  TOKENIZER_GET_USER_TV_ID,
  TOKENIZER_SET_TV96_DIRECT,
  TOKENIZER_SET_TV96,
  TOKENIZER_SET_SHUTTER_SPEED,
  TOKENIZER_SET_USER_TV96,
  TOKENIZER_SET_USER_TV_BY_ID,
  TOKENIZER_SET_USER_TV_BY_ID_REL,
  TOKENIZER_GET_AV96,
  TOKENIZER_GET_USER_AV96,
  TOKENIZER_GET_USER_AV_ID,
  TOKENIZER_SET_AV96_DIRECT,
  TOKENIZER_SET_AV96,
  TOKENIZER_SET_USER_AV96,
  TOKENIZER_SET_USER_AV_BY_ID,
  TOKENIZER_SET_USER_AV_BY_ID_REL,
  TOKENIZER_GET_DAY_SECONDS,
  TOKENIZER_GET_TICK_COUNT,
  TOKENIZER_GET_ZOOM,
  TOKENIZER_SET_ZOOM,
  TOKENIZER_SET_ZOOM_REL,
  TOKENIZER_SET_ZOOM_SPEED,
  TOKENIZER_GET_FOCUS,
  TOKENIZER_SET_FOCUS,
  TOKENIZER_GET_NEAR_LIMIT,
  TOKENIZER_GET_FAR_LIMIT,
  TOKENIZER_GET_DOF,
  TOKENIZER_GET_HYPERFOCAL_DIST,
  TOKENIZER_GET_ISO_MARKET,
  TOKENIZER_GET_ISO_REAL,
  TOKENIZER_GET_BV96,
  TOKENIZER_GET_SV96,
  TOKENIZER_GET_ISO_MODE,
  //TOKENIZER_SET_ISO_DL_F_B,
  //TOKENIZER_SET_ISO_MARKET,
  TOKENIZER_SET_ISO_REAL,
  TOKENIZER_SET_ISO_MODE,
  TOKENIZER_SET_SV96,
  TOKENIZER_GET_PROP,
  TOKENIZER_SET_PROP,
  TOKENIZER_GET_VBATT,
  TOKENIZER_SET_LED,
  TOKENIZER_SET_ISO_DIRECT,
  TOKENIZER_WAIT_CLICK,
  TOKENIZER_IS_KEY,
  TOKENIZER_WHEEL_LEFT,
  TOKENIZER_WHEEL_RIGHT,
  TOKENIZER_MD_DETECT_MOTION,
  TOKENIZER_MD_GET_CELL_DIFF,
  TOKENIZER_MEM_DUMP,
  TOKENIZER_SET_RAW_NR,
  TOKENIZER_GET_RAW_NR,
  TOKENIZER_SET_RAW,
  TOKENIZER_SCRIPT_AUTOSTART,
  TOKENIZER_SET_SCRIPT_AUTOSTART,
  TOKENIZER_GET_USB_POWER,
  TOKENIZER_EXIT_ALT,
  TOKENIZER_SHUT_DOWN,
  TOKENIZER_SET_ND_FILTER,
  TOKENIZER_GET_DISK_SIZE,
  TOKENIZER_GET_FREE_DISK_SPACE,
  TOKENIZER_GET_JPG_COUNT,
  TOKENIZER_GET_RAW_COUNT,
  
} ubasic_token;

void tokenizer_init(const char *program);
void tokenizer_next(void);
int tokenizer_token(void);
int tokenizer_num(void);
int tokenizer_variable_num(void);
void tokenizer_string(char *dest, int len);
void tokenizer_label(char *dest, int len);

int tokenizer_line_number(void);

int tokenizer_finished(void);
void tokenizer_error_print(void);

#endif /* __TOKENIZER_H__ */
