<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface RootCodeInterface
{
	public function setIndepDeclCode($indepDeclCode, $notify = true);
	public function getIndepDeclCode($enforce = true);
	
	public function setDepDeclCode($depDeclCode, $notify = true);
	public function getDepDeclCode($enforce = true);
	
	public function setIndepDefCode($indepDefCode, $notify = true);
	public function getIndepDefCode($enforce = true);
	
	public function setDepDefCode($depDefCode, $notify = true);
	public function getDepDefCode($enforce = true);
}