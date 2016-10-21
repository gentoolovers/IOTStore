// JavaScript Document
$(function(){
	
	/*会有溢出问题
	$(".li1").toggle(
		function(){
			$(this).next().slideDown("slow");
		},
		function(){
			$(this).next().slideUp("slow");
		}
	);
	*/
	
	$(".li1").click(function(){
		if(!$(this).next().is(":visible"))
		{
			$(".li2:visible").slideUp("fast");
			$(this).next().slideDown("fast");
		}
	});
	
	$.initFrameSize();
	
	$("#menuStart").toggle(
		function(){
			$("#lefter").css("left","-200px");
			$(this).css("left",2);			
			$("#mainFrame").width($("#cov").width()-8).css("left","15px");
		},
		function(){
			$("#lefter").css("left","0");
			$(this).css("left","203px");
			$("#mainFrame").width($("#cov").width()-215).css("left","215px");
		}
	);
	
	$(window).resize(function(){
		$.initFrameSize();
	});
	
	$(function(){
	$(".searForm>li:odd").addClass("oddColor");
		$(".table1>tbody>tr:odd").addClass("oddColor");
		$(".table1>tbody>tr").hover(
			function(){
				$(this).addClass("overColor");
			},
			function(){
				$(this).removeClass("overColor");
			}
		);
})
	
});

$.initFrameSize = function(){
	var frameW = $("#cov").width()-215;
	var frameH = $("#cov").height()-61;
	$("#mainFrame").width(frameW).height(frameH);
}