#include <QtCore>
#include <TreeFrogView>
#include "cms.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT cms_entryView : public TActionView
{
  Q_OBJECT
public:
  cms_entryView() : TActionView() { }
  cms_entryView(const cms_entryView &) : TActionView() { }
  QString toString();
};

QString cms_entryView::toString()
{
  responsebody.reserve(2488);
  responsebody += tr("<!DOCTYPE html>\r\n");
    tfetch(QVariantMap, cms);
  responsebody += tr("<html>\r\n<head>\r\n  <meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\" />\r\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += tr("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<h1>New Cms</h1>\r\n\r\n");
  responsebody += QVariant(formTag(urla("create"), Tf::Post)).toString();
  responsebody += tr("\r\n  <p>\r\n    <label>NumberID<br /><input name=\"cms[numberID]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["numberID"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Name<br /><input name=\"cms[name]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["name"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Nickname<br /><input name=\"cms[nickname]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["nickname"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Password<br /><input name=\"cms[password]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["password"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>ID<br /><input name=\"cms[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["id"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Phone<br /><input name=\"cms[phone]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["phone"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Belong<br /><input name=\"cms[belong]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["belong"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>User Number<br /><input name=\"cms[userNumber]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["userNumber"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Role<br /><input name=\"cms[role]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["role"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <input type=\"submit\" value=\"Create\" />\r\n  </p>\r\n</form>\r\n\r\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += tr("\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

Q_DECLARE_METATYPE(cms_entryView)
T_REGISTER_VIEW(cms_entryView)

#include "cms_entryView.moc"
