;*****************************************************************************
;*                                                                           *
;*                            C O R O U T I N E                              *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Beschreibung:    Assemblerdarstellung der 'struct ThreadState' aus     *
;*                  ThreadState.h                                         *
;*                                                                           *
;*                  Die Reihenfolge der Registerbezeichnungen muss unbedingt *
;*                  mit der von 'struct ThreadState' uebereinstimmen.     *
;*                                                                           *
;* Autor:           Olaf Spinczyk, TU Dortmund                               *
;*****************************************************************************

%include "kernel/threads/Thread.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL Thread_switch]
[GLOBAL Thread_start]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; COROUTINE_START : Startet die erste Thread ueberhaupt.
;
; C Prototyp: void Thread_start (struct ThreadState* regs);

Thread_start:

; *
; * Hier muss Code eingefuegt werden
; *
	; load registers with content of &regs argument passed
	mov ecx, [esp+4]  ; &regs
	mov ebx, [ecx+ebx_offset]
	mov edi, [ecx+edi_offset]
	mov esi, [ecx+esi_offset]
	mov esp, [ecx+esp_offset]  ; at entry this is normal stack but this line switches it to app_stack
	mov ebp, [ecx+ebp_offset]

	; kickoff
	ret
	



; COROUTINE_SWITCH : Threadnumschaltung. Der aktuelle Registersatz wird
;                    gesichert und der Registersatz der neuen Thread
;                    wird in den Prozessor eingelesen.
;
; C Prototyp: void Thread_switch (struct ThreadState* regs_now,
;                                    struct ThreadState* reg_then);
;
; Achtung: Die Parameter werden von rechts nach links uebergeben.
;
Thread_switch:

; *
; * Hier muss Code eingefuegt werden
; *
	mov ecx, [esp+4]  ; now, to be saved
	mov edx, [esp+8]  ; then, to be loaded

	; saving
	mov [ecx+ebx_offset], ebx
	mov [ecx+edi_offset], edi
	mov [ecx+esi_offset], esi
	mov [ecx+esp_offset], esp
	mov [ecx+ebp_offset], ebp

	; loading
	mov ebx, [edx+ebx_offset]
	mov edi, [edx+edi_offset]
	mov esi, [edx+esi_offset]
	mov esp, [edx+esp_offset]
	mov ebp, [edx+ebp_offset]

	; kickoff if first time or back to switch2next
	ret





