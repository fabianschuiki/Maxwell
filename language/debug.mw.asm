
../debug.mw.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000400430 <_init>:
  400430:	48 83 ec 08          	sub    $0x8,%rsp
  400434:	e8 97 00 00 00       	callq  4004d0 <call_gmon_start>
  400439:	e8 22 01 00 00       	callq  400560 <frame_dummy>
  40043e:	e8 fd 02 00 00       	callq  400740 <__do_global_ctors_aux>
  400443:	48 83 c4 08          	add    $0x8,%rsp
  400447:	c3                   	retq   

Disassembly of section .plt:

0000000000400450 <__assert_fail@plt-0x10>:
  400450:	ff 35 9a 0b 20 00    	pushq  0x200b9a(%rip)        # 600ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  400456:	ff 25 9c 0b 20 00    	jmpq   *0x200b9c(%rip)        # 600ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40045c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400460 <__assert_fail@plt>:
  400460:	ff 25 9a 0b 20 00    	jmpq   *0x200b9a(%rip)        # 601000 <_GLOBAL_OFFSET_TABLE_+0x18>
  400466:	68 00 00 00 00       	pushq  $0x0
  40046b:	e9 e0 ff ff ff       	jmpq   400450 <_init+0x20>

0000000000400470 <__libc_start_main@plt>:
  400470:	ff 25 92 0b 20 00    	jmpq   *0x200b92(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x20>
  400476:	68 01 00 00 00       	pushq  $0x1
  40047b:	e9 d0 ff ff ff       	jmpq   400450 <_init+0x20>

0000000000400480 <__printf_chk@plt>:
  400480:	ff 25 8a 0b 20 00    	jmpq   *0x200b8a(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x28>
  400486:	68 02 00 00 00       	pushq  $0x2
  40048b:	e9 c0 ff ff ff       	jmpq   400450 <_init+0x20>

Disassembly of section .text:

0000000000400490 <main>:
  400490:	48 83 ec 08          	sub    $0x8,%rsp
  400494:	31 c0                	xor    %eax,%eax
  400496:	e8 c5 01 00 00       	callq  400660 <func_main>
  40049b:	31 c0                	xor    %eax,%eax
  40049d:	48 83 c4 08          	add    $0x8,%rsp
  4004a1:	c3                   	retq   
  4004a2:	90                   	nop
  4004a3:	90                   	nop

00000000004004a4 <_start>:
  4004a4:	31 ed                	xor    %ebp,%ebp
  4004a6:	49 89 d1             	mov    %rdx,%r9
  4004a9:	5e                   	pop    %rsi
  4004aa:	48 89 e2             	mov    %rsp,%rdx
  4004ad:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4004b1:	50                   	push   %rax
  4004b2:	54                   	push   %rsp
  4004b3:	49 c7 c0 30 07 40 00 	mov    $0x400730,%r8
  4004ba:	48 c7 c1 a0 06 40 00 	mov    $0x4006a0,%rcx
  4004c1:	48 c7 c7 90 04 40 00 	mov    $0x400490,%rdi
  4004c8:	e8 a3 ff ff ff       	callq  400470 <__libc_start_main@plt>
  4004cd:	f4                   	hlt    
  4004ce:	90                   	nop
  4004cf:	90                   	nop

00000000004004d0 <call_gmon_start>:
  4004d0:	48 83 ec 08          	sub    $0x8,%rsp
  4004d4:	48 8b 05 05 0b 20 00 	mov    0x200b05(%rip),%rax        # 600fe0 <_DYNAMIC+0x190>
  4004db:	48 85 c0             	test   %rax,%rax
  4004de:	74 02                	je     4004e2 <call_gmon_start+0x12>
  4004e0:	ff d0                	callq  *%rax
  4004e2:	48 83 c4 08          	add    $0x8,%rsp
  4004e6:	c3                   	retq   
  4004e7:	90                   	nop
  4004e8:	90                   	nop
  4004e9:	90                   	nop
  4004ea:	90                   	nop
  4004eb:	90                   	nop
  4004ec:	90                   	nop
  4004ed:	90                   	nop
  4004ee:	90                   	nop
  4004ef:	90                   	nop

00000000004004f0 <__do_global_dtors_aux>:
  4004f0:	55                   	push   %rbp
  4004f1:	48 89 e5             	mov    %rsp,%rbp
  4004f4:	53                   	push   %rbx
  4004f5:	48 83 ec 08          	sub    $0x8,%rsp
  4004f9:	80 3d 40 0b 20 00 00 	cmpb   $0x0,0x200b40(%rip)        # 601040 <__bss_start>
  400500:	75 4b                	jne    40054d <__do_global_dtors_aux+0x5d>
  400502:	bb 40 0e 60 00       	mov    $0x600e40,%ebx
  400507:	48 8b 05 3a 0b 20 00 	mov    0x200b3a(%rip),%rax        # 601048 <dtor_idx.6460>
  40050e:	48 81 eb 38 0e 60 00 	sub    $0x600e38,%rbx
  400515:	48 c1 fb 03          	sar    $0x3,%rbx
  400519:	48 83 eb 01          	sub    $0x1,%rbx
  40051d:	48 39 d8             	cmp    %rbx,%rax
  400520:	73 24                	jae    400546 <__do_global_dtors_aux+0x56>
  400522:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  400528:	48 83 c0 01          	add    $0x1,%rax
  40052c:	48 89 05 15 0b 20 00 	mov    %rax,0x200b15(%rip)        # 601048 <dtor_idx.6460>
  400533:	ff 14 c5 38 0e 60 00 	callq  *0x600e38(,%rax,8)
  40053a:	48 8b 05 07 0b 20 00 	mov    0x200b07(%rip),%rax        # 601048 <dtor_idx.6460>
  400541:	48 39 d8             	cmp    %rbx,%rax
  400544:	72 e2                	jb     400528 <__do_global_dtors_aux+0x38>
  400546:	c6 05 f3 0a 20 00 01 	movb   $0x1,0x200af3(%rip)        # 601040 <__bss_start>
  40054d:	48 83 c4 08          	add    $0x8,%rsp
  400551:	5b                   	pop    %rbx
  400552:	5d                   	pop    %rbp
  400553:	c3                   	retq   
  400554:	66 66 66 2e 0f 1f 84 	data32 data32 nopw %cs:0x0(%rax,%rax,1)
  40055b:	00 00 00 00 00 

0000000000400560 <frame_dummy>:
  400560:	48 83 3d e0 08 20 00 	cmpq   $0x0,0x2008e0(%rip)        # 600e48 <__JCR_END__>
  400567:	00 
  400568:	55                   	push   %rbp
  400569:	48 89 e5             	mov    %rsp,%rbp
  40056c:	74 12                	je     400580 <frame_dummy+0x20>
  40056e:	b8 00 00 00 00       	mov    $0x0,%eax
  400573:	48 85 c0             	test   %rax,%rax
  400576:	74 08                	je     400580 <frame_dummy+0x20>
  400578:	5d                   	pop    %rbp
  400579:	bf 48 0e 60 00       	mov    $0x600e48,%edi
  40057e:	ff e0                	jmpq   *%rax
  400580:	5d                   	pop    %rbp
  400581:	c3                   	retq   
  400582:	90                   	nop
  400583:	90                   	nop
  400584:	90                   	nop
  400585:	90                   	nop
  400586:	90                   	nop
  400587:	90                   	nop
  400588:	90                   	nop
  400589:	90                   	nop
  40058a:	90                   	nop
  40058b:	90                   	nop
  40058c:	90                   	nop
  40058d:	90                   	nop
  40058e:	90                   	nop
  40058f:	90                   	nop

0000000000400590 <showClass>:
  400590:	48 83 ec 08          	sub    $0x8,%rsp
  400594:	48 85 ff             	test   %rdi,%rdi
  400597:	74 1e                	je     4005b7 <showClass+0x27>
  400599:	48 8b 07             	mov    (%rdi),%rax
  40059c:	be 9a 07 40 00       	mov    $0x40079a,%esi
  4005a1:	bf 01 00 00 00       	mov    $0x1,%edi
  4005a6:	48 8b 10             	mov    (%rax),%rdx
  4005a9:	31 c0                	xor    %eax,%eax
  4005ab:	e8 d0 fe ff ff       	callq  400480 <__printf_chk@plt>
  4005b0:	31 c0                	xor    %eax,%eax
  4005b2:	48 83 c4 08          	add    $0x8,%rsp
  4005b6:	c3                   	retq   
  4005b7:	b9 f8 07 40 00       	mov    $0x4007f8,%ecx
  4005bc:	ba 0e 00 00 00       	mov    $0xe,%edx
  4005c1:	be 8c 07 40 00       	mov    $0x40078c,%esi
  4005c6:	bf c0 07 40 00       	mov    $0x4007c0,%edi
  4005cb:	e8 90 fe ff ff       	callq  400460 <__assert_fail@plt>

00000000004005d0 <operator_3D>:
  4005d0:	8b 06                	mov    (%rsi),%eax
  4005d2:	89 07                	mov    %eax,(%rdi)
  4005d4:	c3                   	retq   
  4005d5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4005dc:	00 00 00 00 

00000000004005e0 <operator_2B>:
  4005e0:	8b 07                	mov    (%rdi),%eax
  4005e2:	03 06                	add    (%rsi),%eax
  4005e4:	c3                   	retq   
  4005e5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4005ec:	00 00 00 00 

00000000004005f0 <operator_2A>:
  4005f0:	8b 07                	mov    (%rdi),%eax
  4005f2:	0f af 06             	imul   (%rsi),%eax
  4005f5:	c3                   	retq   
  4005f6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4005fd:	00 00 00 

0000000000400600 <operator_2F>:
  400600:	8b 07                	mov    (%rdi),%eax
  400602:	89 c2                	mov    %eax,%edx
  400604:	c1 fa 1f             	sar    $0x1f,%edx
  400607:	f7 3e                	idivl  (%rsi)
  400609:	c3                   	retq   
  40060a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400610 <operator_3D3D>:
  400610:	8b 06                	mov    (%rsi),%eax
  400612:	39 07                	cmp    %eax,(%rdi)
  400614:	0f 94 c0             	sete   %al
  400617:	0f b6 c0             	movzbl %al,%eax
  40061a:	c3                   	retq   
  40061b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400620 <operator_3C>:
  400620:	8b 06                	mov    (%rsi),%eax
  400622:	39 07                	cmp    %eax,(%rdi)
  400624:	0f 9c c0             	setl   %al
  400627:	0f b6 c0             	movzbl %al,%eax
  40062a:	c3                   	retq   
  40062b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400630 <unary_2D>:
  400630:	8b 07                	mov    (%rdi),%eax
  400632:	f7 d8                	neg    %eax
  400634:	c3                   	retq   
  400635:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40063c:	00 00 00 00 

0000000000400640 <show>:
  400640:	48 83 ec 08          	sub    $0x8,%rsp
  400644:	8b 17                	mov    (%rdi),%edx
  400646:	be a4 07 40 00       	mov    $0x4007a4,%esi
  40064b:	bf 01 00 00 00       	mov    $0x1,%edi
  400650:	31 c0                	xor    %eax,%eax
  400652:	e8 29 fe ff ff       	callq  400480 <__printf_chk@plt>
  400657:	31 c0                	xor    %eax,%eax
  400659:	48 83 c4 08          	add    $0x8,%rsp
  40065d:	c3                   	retq   
  40065e:	66 90                	xchg   %ax,%ax

0000000000400660 <func_main>:
  400660:	48 83 ec 08          	sub    $0x8,%rsp
  400664:	48 8b 15 c5 09 20 00 	mov    0x2009c5(%rip),%rdx        # 601030 <class_Int>
  40066b:	be 9a 07 40 00       	mov    $0x40079a,%esi
  400670:	bf 01 00 00 00       	mov    $0x1,%edi
  400675:	31 c0                	xor    %eax,%eax
  400677:	e8 04 fe ff ff       	callq  400480 <__printf_chk@plt>
  40067c:	48 8b 15 a5 09 20 00 	mov    0x2009a5(%rip),%rdx        # 601028 <class_Vector>
  400683:	be 9a 07 40 00       	mov    $0x40079a,%esi
  400688:	bf 01 00 00 00       	mov    $0x1,%edi
  40068d:	31 c0                	xor    %eax,%eax
  40068f:	48 83 c4 08          	add    $0x8,%rsp
  400693:	e9 e8 fd ff ff       	jmpq   400480 <__printf_chk@plt>
  400698:	90                   	nop
  400699:	90                   	nop
  40069a:	90                   	nop
  40069b:	90                   	nop
  40069c:	90                   	nop
  40069d:	90                   	nop
  40069e:	90                   	nop
  40069f:	90                   	nop

00000000004006a0 <__libc_csu_init>:
  4006a0:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  4006a5:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  4006aa:	48 8d 2d 73 07 20 00 	lea    0x200773(%rip),%rbp        # 600e24 <__init_array_end>
  4006b1:	4c 8d 25 6c 07 20 00 	lea    0x20076c(%rip),%r12        # 600e24 <__init_array_end>
  4006b8:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  4006bd:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  4006c2:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  4006c7:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  4006cc:	48 83 ec 38          	sub    $0x38,%rsp
  4006d0:	4c 29 e5             	sub    %r12,%rbp
  4006d3:	41 89 fd             	mov    %edi,%r13d
  4006d6:	49 89 f6             	mov    %rsi,%r14
  4006d9:	48 c1 fd 03          	sar    $0x3,%rbp
  4006dd:	49 89 d7             	mov    %rdx,%r15
  4006e0:	e8 4b fd ff ff       	callq  400430 <_init>
  4006e5:	48 85 ed             	test   %rbp,%rbp
  4006e8:	74 1c                	je     400706 <__libc_csu_init+0x66>
  4006ea:	31 db                	xor    %ebx,%ebx
  4006ec:	0f 1f 40 00          	nopl   0x0(%rax)
  4006f0:	4c 89 fa             	mov    %r15,%rdx
  4006f3:	4c 89 f6             	mov    %r14,%rsi
  4006f6:	44 89 ef             	mov    %r13d,%edi
  4006f9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006fd:	48 83 c3 01          	add    $0x1,%rbx
  400701:	48 39 eb             	cmp    %rbp,%rbx
  400704:	75 ea                	jne    4006f0 <__libc_csu_init+0x50>
  400706:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40070b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  400710:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  400715:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40071a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40071f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400724:	48 83 c4 38          	add    $0x38,%rsp
  400728:	c3                   	retq   
  400729:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400730 <__libc_csu_fini>:
  400730:	f3 c3                	repz retq 
  400732:	90                   	nop
  400733:	90                   	nop
  400734:	90                   	nop
  400735:	90                   	nop
  400736:	90                   	nop
  400737:	90                   	nop
  400738:	90                   	nop
  400739:	90                   	nop
  40073a:	90                   	nop
  40073b:	90                   	nop
  40073c:	90                   	nop
  40073d:	90                   	nop
  40073e:	90                   	nop
  40073f:	90                   	nop

0000000000400740 <__do_global_ctors_aux>:
  400740:	55                   	push   %rbp
  400741:	48 89 e5             	mov    %rsp,%rbp
  400744:	53                   	push   %rbx
  400745:	48 83 ec 08          	sub    $0x8,%rsp
  400749:	48 8b 05 d8 06 20 00 	mov    0x2006d8(%rip),%rax        # 600e28 <__CTOR_LIST__>
  400750:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  400754:	74 19                	je     40076f <__do_global_ctors_aux+0x2f>
  400756:	bb 28 0e 60 00       	mov    $0x600e28,%ebx
  40075b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400760:	48 83 eb 08          	sub    $0x8,%rbx
  400764:	ff d0                	callq  *%rax
  400766:	48 8b 03             	mov    (%rbx),%rax
  400769:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  40076d:	75 f1                	jne    400760 <__do_global_ctors_aux+0x20>
  40076f:	48 83 c4 08          	add    $0x8,%rsp
  400773:	5b                   	pop    %rbx
  400774:	5d                   	pop    %rbp
  400775:	c3                   	retq   
  400776:	90                   	nop
  400777:	90                   	nop

Disassembly of section .fini:

0000000000400778 <_fini>:
  400778:	48 83 ec 08          	sub    $0x8,%rsp
  40077c:	e8 6f fd ff ff       	callq  4004f0 <__do_global_dtors_aux>
  400781:	48 83 c4 08          	add    $0x8,%rsp
  400785:	c3                   	retq   
