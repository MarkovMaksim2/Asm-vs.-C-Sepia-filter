%macro to_float 1
    pmovzxbd %1, %1
    cvtdq2ps %1, %1
%endmacro

%macro clamp_asm 1
    cmp %1, rdx
    cmovg %1, rdx
%endmacro

%macro component_apply 1
  movdqu xmm4, xmm3
  mulps  xmm4, %1
  haddps xmm4, xmm4
  haddps xmm4, xmm4

  cvtps2dq xmm4, xmm4
  extractps rax, xmm4, 0
%endmacro

section .rodata

coeff_red: dd 0.189, 0.769, 0.393, 0
coeff_green: dd 0.168, 0.686, 0.349, 0
coeff_blue: dd 0.131, 0.534, 0.272, 0

section .text
global pixel_filter_asm

pixel_filter_asm:
      movdqu xmm0, [rel coeff_red]
      movdqu xmm1, [rel coeff_green]
      movdqu xmm2, [rel coeff_blue]

      movdqu xmm3, [rdi]
      to_float xmm3

      mov rdx, 255
      component_apply xmm0
      clamp_asm rax
      mov byte[rdi + 2], al
      component_apply xmm1
      clamp_asm rax
      mov byte[rdi + 1], al
      component_apply xmm2
      clamp_asm rax
      mov byte[rdi], al
      ret