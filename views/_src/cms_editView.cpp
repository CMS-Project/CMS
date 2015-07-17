#include <QtCore>
#include <TreeFrogView>
#include "cms.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT cms_editView : public TActionView
{
  Q_OBJECT
public:
  cms_editView() : TActionView() { }
  cms_editView(const cms_editView &) : TActionView() { }
  QString toString();
};

QString cms_editView::toString()
{
  responsebody.reserve(2769);
  responsebody += tr("<!DOCTYPE html>\r\n");
    tfetch(QVariantMap, cms);
  responsebody += tr("<html>\r\n<head>\r\n  <meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\" />\r\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += tr("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<h1>Editing Cms</h1>\r\n\r\n");
  responsebody += QVariant(formTag(urla("save", cms["numberID"]), Tf::Post)).toString();
  responsebody += tr("\r\n  <p>\r\n    <label>NumberID<br /><input type=\"text\" name=\"cms[numberID]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["numberID"]);
  responsebody += tr("\" readonly=\"readonly\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Name<br /><input type=\"text\" name=\"cms[name]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["name"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Nickname<br /><input type=\"text\" name=\"cms[nickname]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["nickname"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Password<br /><input type=\"text\" name=\"cms[password]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["password"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>ID<br /><input type=\"text\" name=\"cms[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["id"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Phone<br /><input type=\"text\" name=\"cms[phone]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["phone"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Belong<br /><input type=\"text\" name=\"cms[belong]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["belong"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>User Number<br /><input type=\"text\" name=\"cms[userNumber]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["userNumber"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <label>Role<br /><input type=\"text\" name=\"cms[role]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["role"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n  <p>\r\n    <input type=\"submit\" value=\"Update\" />\r\n  </p>\r\n</form>\r\n\r\n");
  responsebody += QVariant(linkTo("Show", urla("show", cms["numberID"]))).toString();
  responsebody += tr(" |\r\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += tr("\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

Q_DECLARE_METATYPE(cms_editView)
T_REGISTER_VIEW(cms_editView)

#include "cms_editView.moc"
