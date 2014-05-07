<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Builtin;

class BuiltinRootObject extends BuiltinObject
{
	protected $repository;
	protected $id;

	public function __construct(\Repository $repo, $id)
	{
		$this->repository = $repo;
		$this->id = $id;
	}

	public function getId() { return $this->id; }
	public function getRepository() { return $this->repository; }
}