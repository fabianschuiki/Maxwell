<?php
namespace Store;

class Token
{
	protected $manager;
	protected $dir;
	
	public function __construct(Manager $manager)
	{
		$this->manager = $manager;
		$this->dir = $manager->getDirectory()."/tokens";
	}
	
	public function allocateId()
	{
		return $this->manager->allocateId();
	}
}