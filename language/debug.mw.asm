
../debug.mw.out:     file format elf64-x86-64


Disassembly of section .init:

00000000004003f0 <_init>:
  4003f0:	48 83 ec 08          	sub    $0x8,%rsp
  4003f4:	e8 87 00 00 00       	callq  400480 <call_gmon_start>
  4003f9:	e8 12 01 00 00       	callq  400510 <frame_dummy>
  4003fe:	e8 1d 02 00 00       	callq  400620 <__do_global_ctors_aux>
  400403:	48 83 c4 08          	add    $0x8,%rsp
  400407:	c3                   	retq   

Disassembly of section .plt:

0000000000400410 <__libc_start_main@plt-0x10>:
  400410:	ff 35 da 0b 20 00    	pushq  0x200bda(%rip)        # 600ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  400416:	ff 25 dc 0b 20 00    	jmpq   *0x200bdc(%rip)        # 600ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40041c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400420 <__libc_start_main@plt>:
  400420:	ff 25 da 0b 20 00    	jmpq   *0x200bda(%rip)        # 601000 <_GLOBAL_OFFSET_TABLE_+0x18>
  400426:	68 00 00 00 00       	pushq  $0x0
  40042b:	e9 e0 ff ff ff       	jmpq   400410 <_init+0x20>

0000000000400430 <__printf_chk@plt>:
  400430:	ff 25 d2 0b 20 00    	jmpq   *0x200bd2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x20>
  400436:	68 01 00 00 00       	pushq  $0x1
  40043b:	e9 d0 ff ff ff       	jmpq   400410 <_init+0x20>

Disassembly of section .text:

0000000000400440 <main>:
  400440:	48 83 ec 08          	sub    $0x8,%rsp
  400444:	31 c0                	xor    %eax,%eax
  400446:	e8 15 01 00 00       	callq  400560 <func_main>
  40044b:	31 c0                	xor    %eax,%eax
  40044d:	48 83 c4 08          	add    $0x8,%rsp
  400451:	c3                   	retq   
  400452:	90                   	nop
  400453:	90                   	nop

0000000000400454 <_start>:
  400454:	31 ed                	xor    %ebp,%ebp
  400456:	49 89 d1             	mov    %rdx,%r9
  400459:	5e                   	pop    %rsi
  40045a:	48 89 e2             	mov    %rsp,%rdx
  40045d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400461:	50                   	push   %rax
  400462:	54                   	push   %rsp
  400463:	49 c7 c0 10 06 40 00 	mov    $0x400610,%r8
  40046a:	48 c7 c1 80 05 40 00 	mov    $0x400580,%rcx
  400471:	48 c7 c7 40 04 40 00 	mov    $0x400440,%rdi
  400478:	e8 a3 ff ff ff       	callq  400420 <__libc_start_main@plt>
  40047d:	f4                   	hlt    
  40047e:	90                   	nop
  40047f:	90                   	nop

0000000000400480 <call_gmon_start>:
  400480:	48 83 ec 08          	sub    $0x8,%rsp
  400484:	48 8b 05 55 0b 20 00 	mov    0x200b55(%rip),%rax        # 600fe0 <_DYNAMIC+0x190>
  40048b:	48 85 c0             	test   %rax,%rax
  40048e:	74 02                	je     400492 <call_gmon_start+0x12>
  400490:	ff d0                	callq  *%rax
  400492:	48 83 c4 08          	add    $0x8,%rsp
  400496:	c3                   	retq   
  400497:	90                   	nop
  400498:	90                   	nop
  400499:	90                   	nop
  40049a:	90                   	nop
  40049b:	90                   	nop
  40049c:	90                   	nop
  40049d:	90                   	nop
  40049e:	90                   	nop
  40049f:	90                   	nop

00000000004004a0 <__do_global_dtors_aux>:
  4004a0:	55                   	push   %rbp
  4004a1:	48 89 e5             	mov    %rsp,%rbp
  4004a4:	53                   	push   %rbx
  4004a5:	48 83 ec 08          	sub    $0x8,%rsp
  4004a9:	80 3d b0 0b 20 00 00 	cmpb   $0x0,0x200bb0(%rip)        # 601060 <__bss_start>
  4004b0:	75 4b                	jne    4004fd <__do_global_dtors_aux+0x5d>
  4004b2:	bb 40 0e 60 00       	mov    $0x600e40,%ebx
  4004b7:	48 8b 05 aa 0b 20 00 	mov    0x200baa(%rip),%rax        # 601068 <dtor_idx.6460>
  4004be:	48 81 eb 38 0e 60 00 	sub    $0x600e38,%rbx
  4004c5:	48 c1 fb 03          	sar    $0x3,%rbx
  4004c9:	48 83 eb 01          	sub    $0x1,%rbx
  4004cd:	48 39 d8             	cmp    %rbx,%rax
  4004d0:	73 24                	jae    4004f6 <__do_global_dtors_aux+0x56>
  4004d2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  4004d8:	48 83 c0 01          	add    $0x1,%rax
  4004dc:	48 89 05 85 0b 20 00 	mov    %rax,0x200b85(%rip)        # 601068 <dtor_idx.6460>
  4004e3:	ff 14 c5 38 0e 60 00 	callq  *0x600e38(,%rax,8)
  4004ea:	48 8b 05 77 0b 20 00 	mov    0x200b77(%rip),%rax        # 601068 <dtor_idx.6460>
  4004f1:	48 39 d8             	cmp    %rbx,%rax
  4004f4:	72 e2                	jb     4004d8 <__do_global_dtors_aux+0x38>
  4004f6:	c6 05 63 0b 20 00 01 	movb   $0x1,0x200b63(%rip)        # 601060 <__bss_start>
  4004fd:	48 83 c4 08          	add    $0x8,%rsp
  400501:	5b                   	pop    %rbx
  400502:	5d                   	pop    %rbp
  400503:	c3                   	retq   
  400504:	66 66 66 2e 0f 1f 84 	data32 data32 nopw %cs:0x0(%rax,%rax,1)
  40050b:	00 00 00 00 00 

0000000000400510 <frame_dummy>:
  400510:	48 83 3d 30 09 20 00 	cmpq   $0x0,0x200930(%rip)        # 600e48 <__JCR_END__>
  400517:	00 
  400518:	55                   	push   %rbp
  400519:	48 89 e5             	mov    %rsp,%rbp
  40051c:	74 12                	je     400530 <frame_dummy+0x20>
  40051e:	b8 00 00 00 00       	mov    $0x0,%eax
  400523:	48 85 c0             	test   %rax,%rax
  400526:	74 08                	je     400530 <frame_dummy+0x20>
  400528:	5d                   	pop    %rbp
  400529:	bf 48 0e 60 00       	mov    $0x600e48,%edi
  40052e:	ff e0                	jmpq   *%rax
  400530:	5d                   	pop    %rbp
  400531:	c3                   	retq   
  400532:	90                   	nop
  400533:	90                   	nop
  400534:	90                   	nop
  400535:	90                   	nop
  400536:	90                   	nop
  400537:	90                   	nop
  400538:	90                   	nop
  400539:	90                   	nop
  40053a:	90                   	nop
  40053b:	90                   	nop
  40053c:	90                   	nop
  40053d:	90                   	nop
  40053e:	90                   	nop
  40053f:	90                   	nop

0000000000400540 <func_test>:
  400540:	f3 c3                	repz retq 
  400542:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  400549:	1f 84 00 00 00 00 00 

0000000000400550 <func_cast>:
  400550:	f3 c3                	repz retq 
  400552:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  400559:	1f 84 00 00 00 00 00 

0000000000400560 <func_main>:
  400560:	ba 03 00 00 00       	mov    $0x3,%edx
  400565:	be 6c 06 40 00       	mov    $0x40066c,%esi
  40056a:	bf 01 00 00 00       	mov    $0x1,%edi
  40056f:	31 c0                	xor    %eax,%eax
  400571:	e9 ba fe ff ff       	jmpq   400430 <__printf_chk@plt>
  400576:	90                   	nop
  400577:	90                   	nop
  400578:	90                   	nop
  400579:	90                   	nop
  40057a:	90                   	nop
  40057b:	90                   	nop
  40057c:	90                   	nop
  40057d:	90                   	nop
  40057e:	90                   	nop
  40057f:	90                   	nop

0000000000400580 <__libc_csu_init>:
  400580:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  400585:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  40058a:	48 8d 2d 93 08 20 00 	lea    0x200893(%rip),%rbp        # 600e24 <__init_array_end>
  400591:	4c 8d 25 8c 08 20 00 	lea    0x20088c(%rip),%r12        # 600e24 <__init_array_end>
  400598:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  40059d:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  4005a2:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  4005a7:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  4005ac:	48 83 ec 38          	sub    $0x38,%rsp
  4005b0:	4c 29 e5             	sub    %r12,%rbp
  4005b3:	41 89 fd             	mov    %edi,%r13d
  4005b6:	49 89 f6             	mov    %rsi,%r14
  4005b9:	48 c1 fd 03          	sar    $0x3,%rbp
  4005bd:	49 89 d7             	mov    %rdx,%r15
  4005c0:	e8 2b fe ff ff       	callq  4003f0 <_init>
  4005c5:	48 85 ed             	test   %rbp,%rbp
  4005c8:	74 1c                	je     4005e6 <__libc_csu_init+0x66>
  4005ca:	31 db                	xor    %ebx,%ebx
  4005cc:	0f 1f 40 00          	nopl   0x0(%rax)
  4005d0:	4c 89 fa             	mov    %r15,%rdx
  4005d3:	4c 89 f6             	mov    %r14,%rsi
  4005d6:	44 89 ef             	mov    %r13d,%edi
  4005d9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4005dd:	48 83 c3 01          	add    $0x1,%rbx
  4005e1:	48 39 eb             	cmp    %rbp,%rbx
  4005e4:	75 ea                	jne    4005d0 <__libc_csu_init+0x50>
  4005e6:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  4005eb:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  4005f0:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  4005f5:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  4005fa:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  4005ff:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400604:	48 83 c4 38          	add    $0x38,%rsp
  400608:	c3                   	retq   
  400609:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400610 <__libc_csu_fini>:
  400610:	f3 c3                	repz retq 
  400612:	90                   	nop
  400613:	90                   	nop
  400614:	90                   	nop
  400615:	90                   	nop
  400616:	90                   	nop
  400617:	90                   	nop
  400618:	90                   	nop
  400619:	90                   	nop
  40061a:	90                   	nop
  40061b:	90                   	nop
  40061c:	90                   	nop
  40061d:	90                   	nop
  40061e:	90                   	nop
  40061f:	90                   	nop

0000000000400620 <__do_global_ctors_aux>:
  400620:	55                   	push   %rbp
  400621:	48 89 e5             	mov    %rsp,%rbp
  400624:	53                   	push   %rbx
  400625:	48 83 ec 08          	sub    $0x8,%rsp
  400629:	48 8b 05 f8 07 20 00 	mov    0x2007f8(%rip),%rax        # 600e28 <__CTOR_LIST__>
  400630:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  400634:	74 19                	je     40064f <__do_global_ctors_aux+0x2f>
  400636:	bb 28 0e 60 00       	mov    $0x600e28,%ebx
  40063b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400640:	48 83 eb 08          	sub    $0x8,%rbx
  400644:	ff d0                	callq  *%rax
  400646:	48 8b 03             	mov    (%rbx),%rax
  400649:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  40064d:	75 f1                	jne    400640 <__do_global_ctors_aux+0x20>
  40064f:	48 83 c4 08          	add    $0x8,%rsp
  400653:	5b                   	pop    %rbx
  400654:	5d                   	pop    %rbp
  400655:	c3                   	retq   
  400656:	90                   	nop
  400657:	90                   	nop

Disassembly of section .fini:

0000000000400658 <_fini>:
  400658:	48 83 ec 08          	sub    $0x8,%rsp
  40065c:	e8 3f fe ff ff       	callq  4004a0 <__do_global_dtors_aux>
  400661:	48 83 c4 08          	add    $0x8,%rsp
  400665:	c3                   	retq   
