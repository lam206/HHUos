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

; Task
Thread_switch:

    ; Lade Adresse des aktuellen ThreadStates
    mov ecx, [esp + 0x04]

    ; Sichere den aktuellen Registersatz auf dem Stack
    mov [ecx + ebx_offset], ebx
    mov [ecx + esi_offset], esi
    mov [ecx + edi_offset], edi
    mov [ecx + ebp_offset], ebp
    mov [ecx + esp_offset], esp

    ; Sichere den aktuellen fluechtigen Registersatz auf dem Stack
    mov [ecx + eax_offset], eax
    mov [ecx + ecx_offset], ecx
    mov [ecx + edx_offset], edx
    pushf                        ; Nutze eax als Zwischenspeicher fuer Flags
    pop eax
    mov [ecx + efl_offset], eax

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

    sti  ; Schalte Interrupts wieder ein
    ret  ; Starte den folgenden Thread
