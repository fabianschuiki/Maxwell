#!/usr/bin/php
<?php
require __DIR__.'/../php/lib/Language.php';

//Open the mw.lang file.
$lang = file_get_contents(__DIR__.'/mw.lang');
if (!$lang) {
	die("*** mw.lang not found\n");
}

/** Update the keywords. */
$kws = "<!--keywords-start-->";
$kwe = "<!--keywords-end-->";
$keywords = "$kws\n\t\t\t";
foreach (Language::$keywords as $keyword) {
	$keywords .= "<keyword>$keyword</keyword>\n\t\t\t";
}
$keywords .= "$kwe";
$lang = preg_replace('/'.preg_quote($kws).'.*?'.preg_quote($kwe).'/ms', $keywords, $lang);


//Store the new mw.lang file.
file_put_contents(__DIR__.'/mw.lang', $lang);

