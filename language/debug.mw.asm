
../debug.mw.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000400430 <_init>:
  400430:	48 83 ec 08          	sub    $0x8,%rsp
  400434:	e8 97 00 00 00       	callq  4004d0 <call_gmon_start>
  400439:	e8 22 01 00 00       	callq  400560 <frame_dummy>
  40043e:	e8 1d 03 00 00       	callq  400760 <__do_global_ctors_aux>
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
  400496:	e8 e5 01 00 00       	callq  400680 <func_main>
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
  4004b3:	49 c7 c0 50 07 40 00 	mov    $0x400750,%r8
  4004ba:	48 c7 c1 c0 06 40 00 	mov    $0x4006c0,%rcx
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
  4004f9:	80 3d 60 0b 20 00 00 	cmpb   $0x0,0x200b60(%rip)        # 601060 <__bss_start>
  400500:	75 4b                	jne    40054d <__do_global_dtors_aux+0x5d>
  400502:	bb 40 0e 60 00       	mov    $0x600e40,%ebx
  400507:	48 8b 05 5a 0b 20 00 	mov    0x200b5a(%rip),%rax        # 601068 <dtor_idx.6460>
  40050e:	48 81 eb 38 0e 60 00 	sub    $0x600e38,%rbx
  400515:	48 c1 fb 03          	sar    $0x3,%rbx
  400519:	48 83 eb 01          	sub    $0x1,%rbx
  40051d:	48 39 d8             	cmp    %rbx,%rax
  400520:	73 24                	jae    400546 <__do_global_dtors_aux+0x56>
  400522:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  400528:	48 83 c0 01          	add    $0x1,%rax
  40052c:	48 89 05 35 0b 20 00 	mov    %rax,0x200b35(%rip)        # 601068 <dtor_idx.6460>
  400533:	ff 14 c5 38 0e 60 00 	callq  *0x600e38(,%rax,8)
  40053a:	48 8b 05 27 0b 20 00 	mov    0x200b27(%rip),%rax        # 601068 <dtor_idx.6460>
  400541:	48 39 d8             	cmp    %rbx,%rax
  400544:	72 e2                	jb     400528 <__do_global_dtors_aux+0x38>
  400546:	c6 05 13 0b 20 00 01 	movb   $0x1,0x200b13(%rip)        # 601060 <__bss_start>
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

0000000000400590 <showType>:
  400590:	48 83 ec 08          	sub    $0x8,%rsp
  400594:	48 85 ff             	test   %rdi,%rdi
  400597:	74 1f                	je     4005b8 <showType+0x28>
  400599:	48 8b 07             	mov    (%rdi),%rax
  40059c:	be ba 07 40 00       	mov    $0x4007ba,%esi
  4005a1:	bf 01 00 00 00       	mov    $0x1,%edi
  4005a6:	48 8b 50 08          	mov    0x8(%rax),%rdx
  4005aa:	31 c0                	xor    %eax,%eax
  4005ac:	e8 cf fe ff ff       	callq  400480 <__printf_chk@plt>
  4005b1:	31 c0                	xor    %eax,%eax
  4005b3:	48 83 c4 08          	add    $0x8,%rsp
  4005b7:	c3                   	retq   
  4005b8:	b9 10 08 40 00       	mov    $0x400810,%ecx
  4005bd:	ba 10 00 00 00       	mov    $0x10,%edx
  4005c2:	be ac 07 40 00       	mov    $0x4007ac,%esi
  4005c7:	bf d8 07 40 00       	mov    $0x4007d8,%edi
  4005cc:	e8 8f fe ff ff       	callq  400460 <__assert_fail@plt>
  4005d1:	66 66 66 66 66 66 2e 	data32 data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  4005d8:	0f 1f 84 00 00 00 00 
  4005df:	00 

00000000004005e0 <operator_3D>:
  4005e0:	8b 06                	mov    (%rsi),%eax
  4005e2:	89 07                	mov    %eax,(%rdi)
  4005e4:	c3                   	retq   
  4005e5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4005ec:	00 00 00 00 

00000000004005f0 <operator_2B>:
  4005f0:	8b 07                	mov    (%rdi),%eax
  4005f2:	03 06                	add    (%rsi),%eax
  4005f4:	c3                   	retq   
  4005f5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4005fc:	00 00 00 00 

0000000000400600 <operator_2A>:
  400600:	8b 07                	mov    (%rdi),%eax
  400602:	0f af 06             	imul   (%rsi),%eax
  400605:	c3                   	retq   
  400606:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40060d:	00 00 00 

0000000000400610 <operator_2F>:
  400610:	8b 07                	mov    (%rdi),%eax
  400612:	89 c2                	mov    %eax,%edx
  400614:	c1 fa 1f             	sar    $0x1f,%edx
  400617:	f7 3e                	idivl  (%rsi)
  400619:	c3                   	retq   
  40061a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400620 <operator_3D3D>:
  400620:	8b 06                	mov    (%rsi),%eax
  400622:	39 07                	cmp    %eax,(%rdi)
  400624:	0f 94 c0             	sete   %al
  400627:	0f b6 c0             	movzbl %al,%eax
  40062a:	c3                   	retq   
  40062b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400630 <operator_3C>:
  400630:	8b 06                	mov    (%rsi),%eax
  400632:	39 07                	cmp    %eax,(%rdi)
  400634:	0f 9c c0             	setl   %al
  400637:	0f b6 c0             	movzbl %al,%eax
  40063a:	c3                   	retq   
  40063b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400640 <unary_2D>:
  400640:	8b 07                	mov    (%rdi),%eax
  400642:	f7 d8                	neg    %eax
  400644:	c3                   	retq   
  400645:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40064c:	00 00 00 00 

0000000000400650 <show>:
  400650:	48 83 ec 08          	sub    $0x8,%rsp
  400654:	8b 17                	mov    (%rdi),%edx
  400656:	be bf 07 40 00       	mov    $0x4007bf,%esi
  40065b:	bf 01 00 00 00       	mov    $0x1,%edi
  400660:	31 c0                	xor    %eax,%eax
  400662:	e8 19 fe ff ff       	callq  400480 <__printf_chk@plt>
  400667:	31 c0                	xor    %eax,%eax
  400669:	48 83 c4 08          	add    $0x8,%rsp
  40066d:	c3                   	retq   
  40066e:	66 90                	xchg   %ax,%ax

0000000000400670 <func_showClass>:
  400670:	f3 c3                	repz retq 
  400672:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  400679:	1f 84 00 00 00 00 00 

0000000000400680 <func_main>:
  400680:	48 83 ec 08          	sub    $0x8,%rsp
  400684:	48 8b 15 cd 09 20 00 	mov    0x2009cd(%rip),%rdx        # 601058 <type_Type+0x8>
  40068b:	be ba 07 40 00       	mov    $0x4007ba,%esi
  400690:	bf 01 00 00 00       	mov    $0x1,%edi
  400695:	31 c0                	xor    %eax,%eax
  400697:	e8 e4 fd ff ff       	callq  400480 <__printf_chk@plt>
  40069c:	48 8b 15 a5 09 20 00 	mov    0x2009a5(%rip),%rdx        # 601048 <type_Int+0x8>
  4006a3:	be ba 07 40 00       	mov    $0x4007ba,%esi
  4006a8:	bf 01 00 00 00       	mov    $0x1,%edi
  4006ad:	31 c0                	xor    %eax,%eax
  4006af:	48 83 c4 08          	add    $0x8,%rsp
  4006b3:	e9 c8 fd ff ff       	jmpq   400480 <__printf_chk@plt>
  4006b8:	90                   	nop
  4006b9:	90                   	nop
  4006ba:	90                   	nop
  4006bb:	90                   	nop
  4006bc:	90                   	nop
  4006bd:	90                   	nop
  4006be:	90                   	nop
  4006bf:	90                   	nop

00000000004006c0 <__libc_csu_init>:
  4006c0:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  4006c5:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  4006ca:	48 8d 2d 53 07 20 00 	lea    0x200753(%rip),%rbp        # 600e24 <__init_array_end>
  4006d1:	4c 8d 25 4c 07 20 00 	lea    0x20074c(%rip),%r12        # 600e24 <__init_array_end>
  4006d8:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  4006dd:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  4006e2:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  4006e7:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  4006ec:	48 83 ec 38          	sub    $0x38,%rsp
  4006f0:	4c 29 e5             	sub    %r12,%rbp
  4006f3:	41 89 fd             	mov    %edi,%r13d
  4006f6:	49 89 f6             	mov    %rsi,%r14
  4006f9:	48 c1 fd 03          	sar    $0x3,%rbp
  4006fd:	49 89 d7             	mov    %rdx,%r15
  400700:	e8 2b fd ff ff       	callq  400430 <_init>
  400705:	48 85 ed             	test   %rbp,%rbp
  400708:	74 1c                	je     400726 <__libc_csu_init+0x66>
  40070a:	31 db                	xor    %ebx,%ebx
  40070c:	0f 1f 40 00          	nopl   0x0(%rax)
  400710:	4c 89 fa             	mov    %r15,%rdx
  400713:	4c 89 f6             	mov    %r14,%rsi
  400716:	44 89 ef             	mov    %r13d,%edi
  400719:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40071d:	48 83 c3 01          	add    $0x1,%rbx
  400721:	48 39 eb             	cmp    %rbp,%rbx
  400724:	75 ea                	jne    400710 <__libc_csu_init+0x50>
  400726:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40072b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  400730:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  400735:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40073a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40073f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400744:	48 83 c4 38          	add    $0x38,%rsp
  400748:	c3                   	retq   
  400749:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400750 <__libc_csu_fini>:
  400750:	f3 c3                	repz retq 
  400752:	90                   	nop
  400753:	90                   	nop
  400754:	90                   	nop
  400755:	90                   	nop
  400756:	90                   	nop
  400757:	90                   	nop
  400758:	90                   	nop
  400759:	90                   	nop
  40075a:	90                   	nop
  40075b:	90                   	nop
  40075c:	90                   	nop
  40075d:	90                   	nop
  40075e:	90                   	nop
  40075f:	90                   	nop

0000000000400760 <__do_global_ctors_aux>:
  400760:	55                   	push   %rbp
  400761:	48 89 e5             	mov    %rsp,%rbp
  400764:	53                   	push   %rbx
  400765:	48 83 ec 08          	sub    $0x8,%rsp
  400769:	48 8b 05 b8 06 20 00 	mov    0x2006b8(%rip),%rax        # 600e28 <__CTOR_LIST__>
  400770:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  400774:	74 19                	je     40078f <__do_global_ctors_aux+0x2f>
  400776:	bb 28 0e 60 00       	mov    $0x600e28,%ebx
  40077b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400780:	48 83 eb 08          	sub    $0x8,%rbx
  400784:	ff d0                	callq  *%rax
  400786:	48 8b 03             	mov    (%rbx),%rax
  400789:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  40078d:	75 f1                	jne    400780 <__do_global_ctors_aux+0x20>
  40078f:	48 83 c4 08          	add    $0x8,%rsp
  400793:	5b                   	pop    %rbx
  400794:	5d                   	pop    %rbp
  400795:	c3                   	retq   
  400796:	90                   	nop
  400797:	90                   	nop

Disassembly of section .fini:

0000000000400798 <_fini>:
  400798:	48 83 ec 08          	sub    $0x8,%rsp
  40079c:	e8 4f fd ff ff       	callq  4004f0 <__do_global_dtors_aux>
  4007a1:	48 83 c4 08          	add    $0x8,%rsp
  4007a5:	c3                   	retq   
