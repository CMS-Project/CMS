
var url;

function doSearch_table1(val, name){
	$('#table1').datagrid({queryParams:{category:name, value:val}});
}
function doSearch_table2(val, name){
	$('#table2').datagrid({queryParams:{category:name, value:val}});
}
function newManager(){
	url = '/AssetsUnit/createAssetsUnit';
	var row = $('#table1').datagrid('getSelected');
	if(row){
		$('#dlg').dialog('open').dialog('setTitle','资产单元管理');
		$('#fm').form('clear');

		$('#fm').form('load',{
			'assetsUnit[managerID]':row['managerID'],
		});

		$('#input_m').textbox('readonly');
		$('#input_au').textbox('readonly', false);
		$('#input_ab').textbox('readonly', false);
	}else{
		alert('未选择资产管理人');
	}
}
function editManager(){
	url = '/AssetsUnit/editAssetsUnit';
	var row = $('#table1').datagrid('getSelected');
	if(row && row['assetsUnitID'] != ""){
		$('#dlg').dialog('open').dialog('setTitle','资产单元管理');
		$('#fm').form('clear');

		$('#fm').form('load',{
			'assetsUnit[managerID]':row['managerID'],
			'assetsUnit[assetsUnitID]':row['assetsUnitID'],
			'assetsUnit[assetsUnitShortname]':row['assetsUnitShortname'],
			'assetsUnit[assetsBalance]':row['assetsBalance']
		});

		$('#input_m').textbox('readonly');
		$('#input_au').textbox('readonly');
		$('#input_ab').textbox('readonly');
	}else{
		alert('未选择资产单元');
	}
}
function saveManager(){
	$('#fm').form('submit',{
		url:url,
		onSubmit: function(){
			return $(this).form('validate');
		},
		success: function(result){
			$('#response', parent.document).text(result);
			$('#dlg').dialog('close');        // close the dialog
			$('#table1').datagrid('reload');    // reload the user data	
		}
	});
}
function deleteManager(){
	var row = $('#table1').datagrid('getSelected');
	if (row && row['assetsUnitID'] != ""){
		$.messager.defaults.ok='确定'
		$.messager.defaults.cancel='取消';
		$.messager.confirm('删除','是否删除该资产单元?',function(r){
			if (r){
				$.post('/Assetsunit/removeAssetsUnit/',
					{managerID:row['managerID'],assetsUnitID:row['assetsUnitID']},
					function(result){
						$('#response', parent.document).text(result);
						$('#table1').datagrid('reload');    // reload the user data
				},'text');
			}
		});
	}else{
		alert('未选择资产单元');
	}
}
function editMarketingUnit(){
	url = '/AssetsUnit/editMarketingUnit';
	var row = $('#table2').datagrid('getSelected');
	if(row){
		$('#dlg1').dialog('open').dialog('setTitle','交易单元管理');
		$('#fm1').form('clear');

		$('#fm1').form('load',{
			'marketingUnit[marketingUnitID]':row['marketingUnitID'],
			'marketingUnit[m_assetsUnitID]':row['m_assetsUnitID'],
			'marketingUnit[marketingUnitShortname]':row['marketingUnitShortname']
		});
	}else{
		alert('未选择交易单元');
	}
}
function saveMU(){
	$('#fm1').form('submit',{
		url:url,
		onSubmit: function(){
			return $(this).form('validate');
		},
		success: function(result){
			$('#response', parent.document).text(result);
			$('#dlg1').dialog('close');        // close the dialog
			$('#table2').datagrid('reload');    // reload the user data	
		}
	});
}
function Transfer(){
	 var row = $('#table1').datagrid('getSelected');
	if(row && row['assetsUnitID'] != ""){
		$('#dlg2').dialog('open');
		$('#form2').form('clear');
		$('#form2').form('load',{
			'assetsTransfer[srcUnitID]':row['assetsUnitID'],
			'assetsTransfer[srcAUManager]':row['managerID']
		});
		// load data to combobox
		var rows = $('#table1').datagrid('getRows');
		var mgs = [];
		var fields = [];
		for(var i=0; i < rows.length; ++i) {
			if(rows[i]["managerID"] != row['managerID'])
				mgs.push(rows[i]["managerID"]);
		}
		function noRepeat() { return arguments[0].join('‖').match(/(\b[^‖]+\b)(?!.*‖\1\b)/ig); };
		mgs = noRepeat(mgs);
		for(var i=0; i < mgs.length; ++i) {
			fields.push({"text":mgs[i], "value":mgs[i]});
		}
		$('#at_mg').combobox({valueField:'value', textField:'text', data:fields});
	}else{
		alert('未选择资产单元');
	}
}
function Allot(){
	 var row = $('#table1').datagrid('getSelected');
	if(row && row['assetsUnitID'] != ""){
		$('#dlg3').dialog('open');
		$('#form1').form('clear');
		$('#form1').form('load',{
			'assetsAllot[assetsUnitID]':row['assetsUnitID'],
			'assetsAllot[managerID]':row['managerID']				
		});
	}else{
		alert('未选择资产单元');
	}
}
function assetsTransfer(){ 
	$('#form2').form('submit',{
		url:'/AssetsUnit/assetsTransfer',
		onSubmit: function(){
			return $(this).form('validate');
		},
		success: function(result){
			$('#response', parent.document).text(result);
			$('#dlg2').dialog('close');        // close the dialog
			$('#table1').datagrid('reload');
		}
	});
}
function assetsAllot(){
	$('#form1').form('submit',{
		url:'/AssetsUnit/assetsAllot',
		onSubmit: function(){
			return $(this).form('validate');
		},
		success: function(result){
			$('#response', parent.document).text(result);
			$('#dlg3').dialog('close');        // close the dialog
			$('#table1').datagrid('reload');
		}
	});
}