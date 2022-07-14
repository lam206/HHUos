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
	push ecx  ; need to save all registers to specific adress but need one register to point to the adress
	mov ecx, [esp+8]  ; now, to be saved. now 8 because pushed ecx to stack.
	; saving
	mov [ecx+ebx_offset], ebx
	mov [ecx+edi_offset], edi
	mov [ecx+esi_offset], esi
	add esp, 4
	mov [ecx+esp_offset], esp ; add and sub because esp was changed by ecx push
	sub esp, 4
	mov [ecx+ebp_offset], ebp
	; additional registers. saving the real eax first and then saving efl via eax.
	mov [ecx+eax_offset], eax
	mov [ecx+edx_offset], edx
	pushf
	pop eax
	mov [ecx+efl_offset], eax
	; save the ecx used for pointing
	pop eax
	mov [ecx+ecx_offset], eax

	; Lade Adresse des nachfolgenden ThreadStates
    mov edx, [esp + 0x08]

    ; Lade den Registersatz des nachfolgenden Threads
    mov ebx, [edx + ebx_offset]
    mov esi, [edx + esi_offset]
    mov edi, [edx + edi_offset]
    mov ebp, [edx + ebp_offset]
    mov esp, [edx + esp_offset]

    ; Lade fluechtige Register des nachfolgenden Threads
    mov eax, [edx + efl_offset]  ; Nutze eax als Zwischenspeicher fuer Flags
    push eax
    popf
    mov eax, [edx + eax_offset]  ; Muss nach Flag-Operation passieren
    mov ecx, [edx + ecx_offset]
    mov edx, [edx + edx_offset]  ; Muss am Ende passieren, sonst Adresse weg



	; kickoff if first time or back to switch2next
	sti  ; set all register right for the next thread. no other code will run hereafter other than the target thread because that would mess up the registers again.
	ret





