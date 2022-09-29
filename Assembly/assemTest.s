PIO_PER equ 0x400E0E00
PIO_OER equ 0x400E0E10
PIO_SODR equ 0x400E0E30
PIO_CODR equ 0x400E0E34
PIO_ISR equ 0x400E0E4C
PIO_IER equ 0x400E0E40
PIO_PDSR equ 0x400E0E3C


  area mycode, code, readonly
  export __main
  entry
  
__main
  bl enable_pio
  
  
  


  

  
  
loop
  mov r4,#2_1000
  mov r7,#2_10000
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r4,r6
  beq offbutton
  cmp r7,r6
  bne loop
  bl led_on1
  bl led_on2
  bl led_on3  ;111
  bl delay  ;1
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_off3  ;110
  bl delay  ;2
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_on3
  bl led_off2  ;101
  bl delay  ;3
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_off3
  bl led_off1  ;000
  bl delay  ;4
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_on2
  bl led_on3  ;011
  bl delay  ;5
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_off3  ;010
  bl delay  ;6
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_on1
  bl led_off2
  bl led_on3  ;101
  bl delay  ;7
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_on3  ;100
  bl delay  ;8
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_on1
  bl led_on2
  bl led_on3  ;111
  bl delay  ;9
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_off1
  bl led_off3  ;010
  bl delay  ;10
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_off2
  bl led_on3  ;001
  bl delay  ;11
  ldr r5, =PIO_ISR
  ldr r6,[r5]
  cmp r6,#2_1000
  beq offbutton
  bl led_off3  ;000
  bl delay
  b loop
  
  

  
  

  
offbutton
  bl led_off1
  bl led_off2
  bl led_off3
  
  bl loop

  
enable_pio 
  mov r4, #2_1 ;36
  ldr r5, =PIO_PER
  str r4,[r5]
  
  ldr r5, =PIO_OER
  str r4, [r5]
  
  ldr r5, =PIO_IER
  str r4, [r5]
  
  mov r4, #2_100;32
  ldr r5, =PIO_PER
  str r4,[r5]
  
  ldr r5, =PIO_OER
  str r4, [r5]
  
  ldr r5, =PIO_IER
  str r4, [r5]
  
  mov r4, #2_010;35
  ldr r5, =PIO_PER
  str r4,[r5]
  
  ldr r5, =PIO_OER
  str r4, [r5]
  
  ldr r5, =PIO_IER
  str r4, [r5]
  

  
  bx lr
  
led_on1
  mov r4, #2_1
  ldr r5, =PIO_SODR
  str r4,[r5]
  
  bx lr
  
led_on2
  mov r4, #2_010
  ldr r5, =PIO_SODR
  str r4,[r5]
  
  bx lr
  
led_on3
  mov r4, #2_100
  ldr r5, =PIO_SODR
  str r4,[r5]
  
  bx lr

  
led_off1
  mov r4, #2_1
  ldr r5, =PIO_CODR
  str r4,[r5]
  
  bx lr
  
led_off2
  mov r4, #2_010
  ldr r5, =PIO_CODR
  str r4,[r5]
  
  bx lr
  
led_off3
  mov r4, #2_100
  ldr r5, =PIO_CODR
  str r4,[r5]
  
  bx lr

delay
  mov r4,#0
  ldr r5, =0x00A0000



loop_delay
  add r4, r4, #1
  cmp r4, r5
  bne loop_delay
  bx lr
  
  
  end