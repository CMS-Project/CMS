#include <QtCore>
#include <TreeFrogView>
#include "cms.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT cms_indexView : public TActionView
{
  Q_OBJECT
public:
  cms_indexView() : TActionView() { }
  cms_indexView(const cms_indexView &) : TActionView() { }
  QString toString();
};

QString cms_indexView::toString()
{
  responsebody.reserve(684);
  responsebody += tr("<!DOCTYPE html>\r\n");
    responsebody += tr("<html>\r\n<head>\r\n  <meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\" />\r\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n</head>\r\n<body>\r\n\r\n<h1>CMS SYSTEM</h1>\r\n\r\n");
  responsebody += QVariant(linkTo("Administrator_Login", urla("admin_login"))).toString();
  responsebody += tr("<br />\r\n<br />\r\n\r\n");
  responsebody += QVariant(linkTo("Operator_Login", urla("operator_login"))).toString();
  responsebody += tr("<br />\r\n<br />\r\n\r\n\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

Q_DECLARE_METATYPE(cms_indexView)
T_REGISTER_VIEW(cms_indexView)

#include "cms_indexView.moc"
