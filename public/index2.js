function addTab_BSC(title, url){
	if ($('#ContentTab_BSC').tabs('exists', title)){
		$('#ContentTab_BSC').tabs('select', title);
	} else {
		var content = '<iframe scrolling="auto" frameborder="0"  src="'+url+'" style="width:100%;height:100%;"></iframe>';
		$('#ContentTab_BSC').tabs('add',{
			title:title,
			content:content,
			closable:true
		});
	}
}