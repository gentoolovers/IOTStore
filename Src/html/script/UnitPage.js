//进行查询结果无数据的设置的函数
function noresultSet(TotalPage) {
    $(".table1>tbody>tr").remove();
    if (TotalPage == 0) {
        $("#labPageInfo").html('提示: 对不起，当前没有要显示的记录！');
        sCon = "";
        return false;
    }
    iTotalPageCount = TotalPage;
    return true;
}


//分页初始化设置
function UnitPage(TotalPage) {
    $("#btnFirst").attr('disabled', false);
    $("#btnPrev").attr('disabled', false);
    $("#btnNext").attr('disabled', false);
    $("#btnLast").attr('disabled', false);
    $('#selPage>option').remove();
    if (TotalPage != 0) {
        var selP = "";
        for (var i = 1; i <= TotalPage; i++) {
            selP += '<option value="' + i + '">' + i + '</option>';
        }
        $("#selPage").append(selP);
        $("#selPage").val(iCurrentPageIndex);
    }
    if (iCurrentPageIndex == 1) {
        $("#btnFirst").attr('disabled', true);
        $("#btnPrev").attr('disabled', true);
    }
    if (iCurrentPageIndex == TotalPage) {
        $("#btnNext").attr('disabled', true);
        $("#btnLast").attr('disabled', true);
    }
    if (TotalPage == 0) {
        $("#btnFirst").attr('disabled', true);
        $("#btnPrev").attr('disabled', true);
        $("#btnNext").attr('disabled', true);
        $("#btnLast").attr('disabled', true);
        return;
    }
    var PageInfo = "";
    if (TotalPage == undefined) TotalPage = 0;
    if (iCurrentPageIndex == undefined) iCurrentPageIndex = 0;
    PageInfo = '共' + TotalPage + '页，当前第' + iCurrentPageIndex + '页';
    $("#labPageInfo").html(PageInfo);
};
//按钮点击设置
function btnPage_Click(sCommandName) {
    switch (sCommandName) {
        case "First": iCurrentPageIndex = 1; break;
        case "Prev": if (iCurrentPageIndex > 1) iCurrentPageIndex--; break;
        case "Next": if (iCurrentPageIndex < iTotalPageCount) iCurrentPageIndex++; break;
        case "Last": iCurrentPageIndex = iTotalPageCount; break;
    }
    $("#selPage").val(iCurrentPageIndex);
    DataBind();
}
//分页跳转事件
function SelPage_SelectedIndexChanged() {
    if ($("#selPage").val() != iCurrentPageIndex) {
        iCurrentPageIndex = $("#selPage").val();
        DataBind();
    }
}