var sCon = " ";
var sSort = " order by UserID";
var iCurrentPageIndex = 1;
var iPageSize = 10;
var iTotalPageCount = 0;

$(function () {
    DataBind();
})

function DataBind() {
    var data = "sCon=" + sCon + "&sSort=" + sSort + "&iPageSize=" + iPageSize + "&iCurrentPageIndex=" + iCurrentPageIndex;
    $.ajax({
        type: "POST",
        url: "./cgi-bin/Tbl_User_InfoFindPage.cgi",
        contentType: "application/x-www-form-urlencoded",
        data: data,
        success: function (json) {
            var list = eval("(" + json + ")");
            if (!noresultSet(list.iTotalPageCount)) return false;
            UnitPage(list.iTotalPageCount);
            $(".table1>tbody>tr").remove();
            $.each(list.jsn, function (i, n) {
                var str = "<tr>";
                str += "<td class=\"alignM\">" + n.UserID + "</td>";
                str += "<td class=\"alignL\">" + n.UserName + "</td>";
                str += "<td class=\"alignL\">" + n.NickName + "</td>";
                switch (parseInt(n.RoleID)) {
                    case 1:
                        str += "<td class=\"alignM\">超级管理员</td>";
                        break;
                    case 2:
                        str += "<td class=\"alignM\">管理员</td>";
                        break;
                    case 3:
                        str += "<td class=\"alignM\">一般用户</td>";
                        break;
                }
                str += "<td class=\"alignM\">" +
                    "<a target=\"_self\" href=\"EditUser.html?UserID=" + n.UserID + "\"><input type=\"button\" value=\"修改\"/>" +
                    "<a target=\"_self\" href=\"###\"><input type=\"button\" value=\"删除\"  onclick=\"isDelete(" + n.UserID + ")\" />" +
                    "</a></td>";
                str += "</tr>";
                $(".table1>tbody").append(str);
                setTable();
            });

        }
    });
}

function btnQuery_Click() {
    sCon = "";

    if ($("#txtUserName").val() != "") {
        sCon += " and UserName = '" + $("#txtUserName").val() + "'";
    }
    iCurrentPageIndex = 1;
    DataBind();
};

function isDelete(UserID) {
    if (!confirm("确实要删除吗？")) return false;
    $.ajax({
        type: "POST",
        url: "./cgi-bin/Tbl_User_InfoDelete.cgi",
        contentType: "application/x-www-form-urlencoded",
        data: "sCon= and UserID='" + UserID + "'",
        success: function (json) {
            list = eval("(" + json + ")");
            if (list.jsn == 0) {
                alert("删除失败");
            } else {
                alert("删除成功");
                DataBind();
            }
        }
    });
}