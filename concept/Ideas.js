$(document).ready(function(){
	$("code").each(function(){
		var code = $(this).html();
		
		code = code.replace(/(\"[^\"]*\")/g, "<span class=\"string\">$1</span>");
		code = code.replace(/([^\w])(\.?\d[\d\.]*)/g, "$1<span class=\"number\">$2</span>");
		code = code.replace(/(var\s+|isa\s+)([\w|]+)/g, "$1<span class=\"type\">$2</span>");
		code = code.replace(/(\w+)\(/g, "<span class=\"function\">$1</span>(");
		code = code.replace(/(^|\s)(var|if|else|isa|func|type)(\s|$)/g, "$1<span class=\"keyword\">$2</span>$3");
		code = code.replace(/(\/\/.*?$|\/\*.*?\*\/)/mg, "<span class=\"comment\">$1</span>");
		
		$(this).html(code);
	});
});