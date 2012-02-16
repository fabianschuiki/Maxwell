
../debug.mw.out:     file format elf64-x86-64


Disassembly of section .init:

00000000004003f0 <_init>:
  4003f0:	48 83 ec 08          	sub    $0x8,%rsp
  4003f4:	e8 7b 00 00 00       	callq  400474 <call_gmon_start>
  4003f9:	e8 02 01 00 00       	callq  400500 <frame_dummy>
  4003fe:	e8 6d 02 00 00       	callq  400670 <__do_global_ctors_aux>
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
  400440:	31 c0                	xor    %eax,%eax
  400442:	e9 69 01 00 00       	jmpq   4005b0 <func_main>
  400447:	90                   	nop

0000000000400448 <_start>:
  400448:	31 ed                	xor    %ebp,%ebp
  40044a:	49 89 d1             	mov    %rdx,%r9
  40044d:	5e                   	pop    %rsi
  40044e:	48 89 e2             	mov    %rsp,%rdx
  400451:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400455:	50                   	push   %rax
  400456:	54                   	push   %rsp
  400457:	49 c7 c0 60 06 40 00 	mov    $0x400660,%r8
  40045e:	48 c7 c1 d0 05 40 00 	mov    $0x4005d0,%rcx
  400465:	48 c7 c7 40 04 40 00 	mov    $0x400440,%rdi
  40046c:	e8 af ff ff ff       	callq  400420 <__libc_start_main@plt>
  400471:	f4                   	hlt    
  400472:	90                   	nop
  400473:	90                   	nop

0000000000400474 <call_gmon_start>:
  400474:	48 83 ec 08          	sub    $0x8,%rsp
  400478:	48 8b 05 61 0b 20 00 	mov    0x200b61(%rip),%rax        # 600fe0 <_DYNAMIC+0x190>
  40047f:	48 85 c0             	test   %rax,%rax
  400482:	74 02                	je     400486 <call_gmon_start+0x12>
  400484:	ff d0                	callq  *%rax
  400486:	48 83 c4 08          	add    $0x8,%rsp
  40048a:	c3                   	retq   
  40048b:	90                   	nop
  40048c:	90                   	nop
  40048d:	90                   	nop
  40048e:	90                   	nop
  40048f:	90                   	nop

0000000000400490 <__do_global_dtors_aux>:
  400490:	55                   	push   %rbp
  400491:	48 89 e5             	mov    %rsp,%rbp
  400494:	53                   	push   %rbx
  400495:	48 83 ec 08          	sub    $0x8,%rsp
  400499:	80 3d 80 0b 20 00 00 	cmpb   $0x0,0x200b80(%rip)        # 601020 <__bss_start>
  4004a0:	75 4b                	jne    4004ed <__do_global_dtors_aux+0x5d>
  4004a2:	bb 40 0e 60 00       	mov    $0x600e40,%ebx
  4004a7:	48 8b 05 7a 0b 20 00 	mov    0x200b7a(%rip),%rax        # 601028 <dtor_idx.6460>
  4004ae:	48 81 eb 38 0e 60 00 	sub    $0x600e38,%rbx
  4004b5:	48 c1 fb 03          	sar    $0x3,%rbx
  4004b9:	48 83 eb 01          	sub    $0x1,%rbx
  4004bd:	48 39 d8             	cmp    %rbx,%rax
  4004c0:	73 24                	jae    4004e6 <__do_global_dtors_aux+0x56>
  4004c2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  4004c8:	48 83 c0 01          	add    $0x1,%rax
  4004cc:	48 89 05 55 0b 20 00 	mov    %rax,0x200b55(%rip)        # 601028 <dtor_idx.6460>
  4004d3:	ff 14 c5 38 0e 60 00 	callq  *0x600e38(,%rax,8)
  4004da:	48 8b 05 47 0b 20 00 	mov    0x200b47(%rip),%rax        # 601028 <dtor_idx.6460>
  4004e1:	48 39 d8             	cmp    %rbx,%rax
  4004e4:	72 e2                	jb     4004c8 <__do_global_dtors_aux+0x38>
  4004e6:	c6 05 33 0b 20 00 01 	movb   $0x1,0x200b33(%rip)        # 601020 <__bss_start>
  4004ed:	48 83 c4 08          	add    $0x8,%rsp
  4004f1:	5b                   	pop    %rbx
  4004f2:	5d                   	pop    %rbp
  4004f3:	c3                   	retq   
  4004f4:	66 66 66 2e 0f 1f 84 	data32 data32 nopw %cs:0x0(%rax,%rax,1)
  4004fb:	00 00 00 00 00 

0000000000400500 <frame_dummy>:
  400500:	48 83 3d 40 09 20 00 	cmpq   $0x0,0x200940(%rip)        # 600e48 <__JCR_END__>
  400507:	00 
  400508:	55                   	push   %rbp
  400509:	48 89 e5             	mov    %rsp,%rbp
  40050c:	74 12                	je     400520 <frame_dummy+0x20>
  40050e:	b8 00 00 00 00       	mov    $0x0,%eax
  400513:	48 85 c0             	test   %rax,%rax
  400516:	74 08                	je     400520 <frame_dummy+0x20>
  400518:	5d                   	pop    %rbp
  400519:	bf 48 0e 60 00       	mov    $0x600e48,%edi
  40051e:	ff e0                	jmpq   *%rax
  400520:	5d                   	pop    %rbp
  400521:	c3                   	retq   
  400522:	90                   	nop
  400523:	90                   	nop
  400524:	90                   	nop
  400525:	90                   	nop
  400526:	90                   	nop
  400527:	90                   	nop
  400528:	90                   	nop
  400529:	90                   	nop
  40052a:	90                   	nop
  40052b:	90                   	nop
  40052c:	90                   	nop
  40052d:	90                   	nop
  40052e:	90                   	nop
  40052f:	90                   	nop

0000000000400530 <operator_3D>:
  400530:	8b 06                	mov    (%rsi),%eax
  400532:	89 07                	mov    %eax,(%rdi)
  400534:	c3                   	retq   
  400535:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40053c:	00 00 00 00 

0000000000400540 <operator_2B>:
  400540:	8b 07                	mov    (%rdi),%eax
  400542:	03 06                	add    (%rsi),%eax
  400544:	c3                   	retq   
  400545:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40054c:	00 00 00 00 

0000000000400550 <operator_2A>:
  400550:	8b 07                	mov    (%rdi),%eax
  400552:	0f af 06             	imul   (%rsi),%eax
  400555:	c3                   	retq   
  400556:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40055d:	00 00 00 

0000000000400560 <operator_2F>:
  400560:	8b 07                	mov    (%rdi),%eax
  400562:	89 c2                	mov    %eax,%edx
  400564:	c1 fa 1f             	sar    $0x1f,%edx
  400567:	f7 3e                	idivl  (%rsi)
  400569:	c3                   	retq   
  40056a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400570 <operator_3D3D>:
  400570:	8b 0e                	mov    (%rsi),%ecx
  400572:	b8 01 00 00 00       	mov    $0x1,%eax
  400577:	85 c9                	test   %ecx,%ecx
  400579:	7e 0f                	jle    40058a <operator_3D3D+0x1a>
  40057b:	8b 37                	mov    (%rdi),%esi
  40057d:	31 d2                	xor    %edx,%edx
  40057f:	90                   	nop
  400580:	83 c2 01             	add    $0x1,%edx
  400583:	0f af c6             	imul   %esi,%eax
  400586:	39 ca                	cmp    %ecx,%edx
  400588:	75 f6                	jne    400580 <operator_3D3D+0x10>
  40058a:	f3 c3                	repz retq 
  40058c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400590 <show>:
  400590:	48 83 ec 08          	sub    $0x8,%rsp
  400594:	8b 17                	mov    (%rdi),%edx
  400596:	be bc 06 40 00       	mov    $0x4006bc,%esi
  40059b:	bf 01 00 00 00       	mov    $0x1,%edi
  4005a0:	31 c0                	xor    %eax,%eax
  4005a2:	e8 89 fe ff ff       	callq  400430 <__printf_chk@plt>
  4005a7:	31 c0                	xor    %eax,%eax
  4005a9:	48 83 c4 08          	add    $0x8,%rsp
  4005ad:	c3                   	retq   
  4005ae:	66 90                	xchg   %ax,%ax

00000000004005b0 <func_main>:
  4005b0:	ba 05 00 00 00       	mov    $0x5,%edx
  4005b5:	be bc 06 40 00       	mov    $0x4006bc,%esi
  4005ba:	bf 01 00 00 00       	mov    $0x1,%edi
  4005bf:	31 c0                	xor    %eax,%eax
  4005c1:	e9 6a fe ff ff       	jmpq   400430 <__printf_chk@plt>
  4005c6:	90                   	nop
  4005c7:	90                   	nop
  4005c8:	90                   	nop
  4005c9:	90                   	nop
  4005ca:	90                   	nop
  4005cb:	90                   	nop
  4005cc:	90                   	nop
  4005cd:	90                   	nop
  4005ce:	90                   	nop
  4005cf:	90                   	nop

00000000004005d0 <__libc_csu_init>:
  4005d0:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  4005d5:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  4005da:	48 8d 2d 43 08 20 00 	lea    0x200843(%rip),%rbp        # 600e24 <__init_array_end>
  4005e1:	4c 8d 25 3c 08 20 00 	lea    0x20083c(%rip),%r12        # 600e24 <__init_array_end>
  4005e8:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  4005ed:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  4005f2:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  4005f7:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  4005fc:	48 83 ec 38          	sub    $0x38,%rsp
  400600:	4c 29 e5             	sub    %r12,%rbp
  400603:	41 89 fd             	mov    %edi,%r13d
  400606:	49 89 f6             	mov    %rsi,%r14
  400609:	48 c1 fd 03          	sar    $0x3,%rbp
  40060d:	49 89 d7             	mov    %rdx,%r15
  400610:	e8 db fd ff ff       	callq  4003f0 <_init>
  400615:	48 85 ed             	test   %rbp,%rbp
  400618:	74 1c                	je     400636 <__libc_csu_init+0x66>
  40061a:	31 db                	xor    %ebx,%ebx
  40061c:	0f 1f 40 00          	nopl   0x0(%rax)
  400620:	4c 89 fa             	mov    %r15,%rdx
  400623:	4c 89 f6             	mov    %r14,%rsi
  400626:	44 89 ef             	mov    %r13d,%edi
  400629:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40062d:	48 83 c3 01          	add    $0x1,%rbx
  400631:	48 39 eb             	cmp    %rbp,%rbx
  400634:	75 ea                	jne    400620 <__libc_csu_init+0x50>
  400636:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40063b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  400640:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  400645:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40064a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40064f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400654:	48 83 c4 38          	add    $0x38,%rsp
  400658:	c3                   	retq   
  400659:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400660 <__libc_csu_fini>:
  400660:	f3 c3                	repz retq 
  400662:	90                   	nop
  400663:	90                   	nop
  400664:	90                   	nop
  400665:	90                   	nop
  400666:	90                   	nop
  400667:	90                   	nop
  400668:	90                   	nop
  400669:	90                   	nop
  40066a:	90                   	nop
  40066b:	90                   	nop
  40066c:	90                   	nop
  40066d:	90                   	nop
  40066e:	90                   	nop
  40066f:	90                   	nop

0000000000400670 <__do_global_ctors_aux>:
  400670:	55                   	push   %rbp
  400671:	48 89 e5             	mov    %rsp,%rbp
  400674:	53                   	push   %rbx
  400675:	48 83 ec 08          	sub    $0x8,%rsp
  400679:	48 8b 05 a8 07 20 00 	mov    0x2007a8(%rip),%rax        # 600e28 <__CTOR_LIST__>
  400680:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  400684:	74 19                	je     40069f <__do_global_ctors_aux+0x2f>
  400686:	bb 28 0e 60 00       	mov    $0x600e28,%ebx
  40068b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400690:	48 83 eb 08          	sub    $0x8,%rbx
  400694:	ff d0                	callq  *%rax
  400696:	48 8b 03             	mov    (%rbx),%rax
  400699:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  40069d:	75 f1                	jne    400690 <__do_global_ctors_aux+0x20>
  40069f:	48 83 c4 08          	add    $0x8,%rsp
  4006a3:	5b                   	pop    %rbx
  4006a4:	5d                   	pop    %rbp
  4006a5:	c3                   	retq   
  4006a6:	90                   	nop
  4006a7:	90                   	nop

Disassembly of section .fini:

00000000004006a8 <_fini>:
  4006a8:	48 83 ec 08          	sub    $0x8,%rsp
  4006ac:	e8 df fd ff ff       	callq  400490 <__do_global_dtors_aux>
  4006b1:	48 83 c4 08          	add    $0x8,%rsp
  4006b5:	c3                   	retq   
