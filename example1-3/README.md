## 如何執行?
執行:
```
$ cd example1-3
$ make default qemu
```

輸出以下訊息:
```
arm-linux-gnueabihf-gcc -c -O2 -ggdb -Wall -mcpu=cortex-a15 -fno-stack-protector -o example1.o example1.c
arm-linux-gnueabihf-gcc -o example1 example1.o
0
```
輸出: `0`

也就是使用以下指令 Cross Compile `example1.c`:
```
arm-linux-gnueabihf-gcc -c -O2 -ggdb -Wall -mcpu=cortex-a15 -fno-stack-protector -o example1.o example1.c
```

### 使用 `arm-linux-gnueabihf-objdump -d` 來 Disassemble
```
$ arm-linux-gnueabihf-objdump -d example1 > dump.txt
```
這樣會把反組譯 (disassemble) `example1` 執行檔的結果輸出到 `dump.txt` 檔案中，然後可以用 `grep` 來搜尋 `sdiv`:
```
$ grep sdiv dump.txt
```
擷取 `dump.txt` 中 `sdiv` 的 Assembly Code:
```
000004fc <div>:
 4fc:	fb90 f0f1 	sdiv	r0, r0, r1
 500:	4770      	bx	lr
 502:	bf00      	nop
```
這就表示成功觀察到 `div(int a, int b)` 函式在反組譯後確實使用了 `sdiv` 指令

### `sdiv`
- `sdiv` (Signed Divide) 是 ARMv7-A (例如 Cortex-A15) 以後才支援的「有號整數除法指令」
- 語法範例:
  ```asm
  sdiv r0, r1, r2   ; r0 = r1 / r2
  ```

⭐ `-mcpu=cortex-a15` 是關鍵，因為較舊的 ARM CPU 沒有內建 `sdiv` 指令

### 【實驗】將 Makefile 中的 `-mcpu=cortex-a15` 移除
```diff
- CFLAGS	= -O2 -ggdb -Wall -mcpu=cortex-a15
+ CFLAGS	= -O2 -ggdb -Wall
```

執行:
```
$ cd example1-3
$ make default qemu
```

使用 `arm-linux-gnueabihf-objdump -d` 來 Disassemble
```
$ arm-linux-gnueabihf-objdump -d example1 > dump.txt
```
這樣會把反組譯 (disassemble) `example1` 執行檔的結果輸出到 `dump.txt` 檔案中

擷取 `dump.txt` 中的 Assembly Code:
```
000007c4 <__aeabi_idivmod>:
 7c4:	2900      	cmp	r1, #0
 7c6:	d0f4      	beq.n	7b2 <.divsi3_skip_div0_test+0x27c>
 7c8:	e92d 4003 	stmdb	sp!, {r0, r1, lr}
 7cc:	f7ff feb3 	bl	536 <.divsi3_skip_div0_test>
 7d0:	e8bd 4006 	ldmia.w	sp!, {r1, r2, lr}
 7d4:	fb02 f300 	mul.w	r3, r2, r0
 7d8:	eba1 0103 	sub.w	r1, r1, r3
 7dc:	4770      	bx	lr
 7de:	bf00      	nop

000007e0 <__aeabi_ldiv0>:
 7e0:	b502      	push	{r1, lr}
 7e2:	f04f 0008 	mov.w	r0, #8
 7e6:	f7ff ee00 	blx	3e8 <raise@plt>
 7ea:	bd02      	pop	{r1, pc}
```

📓 會發現若沒有加入 `-mcpu=cortex-a15`，則 GCC 不會生成 `sdiv`，而是改用一套軟體模擬除法的程式碼 (稱為 `__aeabi_idiv`) ，這在某些嵌入式系統中效能會很差