<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface CallInterface
{
	public function setCallName($callName, $notify = true);
	public function getCallName($enforce = true);
	
	public function setCallArguments(CallArgumentTuple $callArguments = null, $notify = true);
	public function getCallArguments($enforce = true);
	
	public function setCallCandidates(\RepositoryObjectArray $callCandidates = null, $notify = true);
	public function getCallCandidates($enforce = true);
	
	public function setSelectedCallCandidate(\RepositoryObjectReference $selectedCallCandidate = null, $notify = true);
	public function getSelectedCallCandidate($enforce = true);
}