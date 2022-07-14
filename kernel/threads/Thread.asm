;*****************************************************************************
;*                                                                           *
;*                               T H R E A D                                 *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Beschreibung:    Assemblerdarstellung der struct ThreadState aus          *
;*                  ThreadState.h                                            *
;*                                                                           *
;*                  Die Reihenfolge der Registerbezeichnungen muss unbedingt *
;*                  mit der von struct ThreadState uebereinstimmen.          *
;*                                                                           *
;*                  Jetzt werden alle Register beruecksichtigt!              *
;*                                                                           *
;* Autor:           Olaf Spinczyk, TU Dortmund                               *
;*                  Michael Schoettner, HHU, 1.1.2017                        *
;*****************************************************************************

%include "kernel/threads/Thread.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL Thread_switch]
[GLOBAL Thread_start]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; Thread_START : Startet den ersten Thread ueberhaupt.
;
; C Prototyp: void Thread_start (struct ThreadState* regs);

; Normaler Stack (bottom-up):
; 2. Parameter
; 1. Parameter
; Ruecksprungadresse
; altes ebp             <- ebp
; lokale Variablen      <- esp
;
; Praeparierter Stack (bottom-up):
; 2. Parameter
; 1. Parameter
; "Ruecksprungadresse" 0x131155
; lokale Variablen      <- esp

; Task
Thread_start:

    mov ecx, [esp + 0x04]  ; Lade ThreadState

    ; Lade Register aus ThreadState
    mov ebx, [ecx + ebx_offset]
    mov esi, [ecx + esi_offset]
    mov edi, [ecx + edi_offset]
    mov ebp, [ecx + ebp_offset]
    mov esp, [ecx + esp_offset]

    ret  ; Starte Thread


; Thread_SWITCH : Threadnumschaltung. Der aktuelle Registersatz wird
;                 gesichert und der Registersatz des neuen Threads
;                 wird in den Prozessor eingelesen.
;
; C Prototyp: void Thread_switch (struct ThreadState* regs_now,
;                                 struct ThreadState* reg_then);
;
; Achtung: Die Parameter werden von rechts nach links uebergeben.

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



