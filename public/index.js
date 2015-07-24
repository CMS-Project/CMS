function addTab(title, url){
	if ($('#contentTab').tabs('exists', title)){
		$('#contentTab').tabs('select', title);
	} else {
		var content = '<iframe scrolling="auto" frameborder="0"  src="'+url+'" style="width:100%;height:100%;"></iframe>';
		$('#contentTab').tabs('add',{
			title:title,
			content:content,
			closable:true
		});
	}
}