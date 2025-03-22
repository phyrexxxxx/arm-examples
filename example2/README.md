## 使用 `arm-linux-gnueabihf-objdump -d` 來 Disassemble
```
$ arm-linux-gnueabihf-objdump -d example2 > dump.txt
```
這樣會把反組譯 (disassemble) `example2` 執行檔的結果輸出到 `dump.txt` 檔案中

擷取 `dump.txt` 中的 Assembly Code:
```arm
00000544 <multiply>:
 544:	fb01 f000 	mul.w	r0, r1, r0
 548:	4770      	bx	lr
 54a:	bf00      	nop

0000054c <multiplyadd>:
 54c:	fb01 2000 	mla	r0, r1, r0, r2
 550:	4770      	bx	lr
 552:	bf00      	nop

00000554 <multiplysub>:
 554:	fb01 2010 	mls	r0, r1, r0, r2
 558:	4770      	bx	lr
 55a:	bf00      	nop
```
