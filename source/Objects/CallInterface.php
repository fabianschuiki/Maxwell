<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface CallInterface
{
	public function setCallName($callName, $notify = true);
	public function getCallName($enforce = true);
	
	public function setCallArguments($callArguments, $notify = true);
	public function setCallArgumentsRef($callArguments, \Repository $repository, $notify = true);
	public function getCallArguments($enforce = true, $unref = true);
	
	public function setCallCandidates($callCandidates, $notify = true);
	public function setCallCandidatesRef($callCandidates, \Repository $repository, $notify = true);
	public function getCallCandidates($enforce = true, $unref = true);
	
	public function setSelectedCallCandidate($selectedCallCandidate, $notify = true);
	public function setSelectedCallCandidateRef($selectedCallCandidate, \Repository $repository, $notify = true);
	public function getSelectedCallCandidate($enforce = true, $unref = true);
}