var active = null;

function activate(humanSpan)
{
	if (humanSpan == active) return;
	if (active) active.parent().toggleClass("active", false);
	active = humanSpan;
	if (active) active.parent().toggleClass("active", true);
}

function deactivate(humanSpan)
{
	if (humanSpan != active) return;
	if (active) active.parent().toggleClass("active", false);
	active = null;
}

function showInfo()
{
	activate($(this));
}

function hideInfo()
{
	deactivate($(this));
}

//Initialize stuff.
$(document).ready(function(){
	var entities = $("span.entity > span.human");
	entities.each(function(_,e){
		$(e).mouseenter(showInfo);
		$(e).mouseleave(hideInfo);
	});
});