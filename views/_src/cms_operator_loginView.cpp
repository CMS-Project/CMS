#include <QtCore>
#include <TreeFrogView>
#include "cms.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT cms_operator_loginView : public TActionView
{
  Q_OBJECT
public:
  cms_operator_loginView() : TActionView() { }
  cms_operator_loginView(const cms_operator_loginView &) : TActionView() { }
  QString toString();
};

QString cms_operator_loginView::toString()
{
  responsebody.reserve(1276);
  responsebody += tr("<!DOCTYPE html>\r\n");
    tfetch(QVariantMap, cms);
  responsebody += tr("<html>\r\n<head>\r\n  <meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\" />\r\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += tr("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<h1>Operator Login</h1>\r\n\r\n");
  responsebody += QVariant(formTag(urla("operatorlogin"), Tf::Post)).toString();
  responsebody += tr("\r\n  <p>\r\n    <label>NumberID<br /><input name=\"cms[numberID]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["numberID"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n\r\n  <p>\r\n    <label>Password<br /><input type=\"password\" name=\"cms[password]\" value=\"");
  responsebody += THttpUtility::htmlEscape(cms["password"]);
  responsebody += tr("\" /></label>\r\n  </p>\r\n \r\n  <p>\r\n    <input type=\"submit\" value=\"Login\" />\r\n  </p>\r\n</form>\r\n\r\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += tr("\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

Q_DECLARE_METATYPE(cms_operator_loginView)
T_REGISTER_VIEW(cms_operator_loginView)

#include "cms_operator_loginView.moc"
