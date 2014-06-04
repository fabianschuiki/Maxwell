$(document).ready(function(){
	$("code").each(function(){
		var code = $(this).html();
		
		code = code.replace(/(^|[^=])(\"[^\"]*\")/g, "$1<span class=\"string\">$2</span>");
		code = code.replace(/(#\w*)/g, "<span class=\"tag\">$1</span>");
		code = code.replace(/([^\w])(\.?\d[\d\.]*)/g, "$1<span class=\"number\">$2</span>");
		code = code.replace(/(var\s+|isa\s+)([\w|]+)/g, "$1<span class=\"type\">$2</span>");
		code = code.replace(/(\w+)\(/g, "<span class=\"function\">$1</span>(");
		code = code.replace(/(^|[^\w\"])(null|nil|true|false)([^\w\"]|$)/g, "$1<span class=\"constant\">$2</span>$3");
		code = code.replace(/(^|[^\w\"])(var|if|else|isa|func|import|package|type|return|for|incase|otherwise|typeclass|interface|tag|where|or|throw|defer|error|value|object)([^\w\"]|$)/g, "$1<span class=\"keyword\">$2</span>$3");
		code = code.replace(/(\/\/.*?$|\/\*.*?\*\/)/mg, "<span class=\"comment\">$1</span>");
		
		$(this).html(code);
	});
});