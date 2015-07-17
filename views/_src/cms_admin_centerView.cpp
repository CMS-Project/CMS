#include <QtCore>
#include <TreeFrogView>
#include "cms.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT cms_admin_centerView : public TActionView
{
  Q_OBJECT
public:
  cms_admin_centerView() : TActionView() { }
  cms_admin_centerView(const cms_admin_centerView &) : TActionView() { }
  QString toString();
};

QString cms_admin_centerView::toString()
{
  responsebody.reserve(911);
  responsebody += tr("<!DOCTYPE html>\r\n");
    tfetch(Cms, cms);
  responsebody += tr("<html>\r\n<head>\r\n  <meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\" />\r\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += tr("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<h1>Administrator Center</h1>\r\n\r\n<ul>\r\n<ol>");
  responsebody += QVariant(linkTo("AA", urla("#"))).toString();
  responsebody += tr("</ol>\r\n<ol>");
  responsebody += QVariant(linkTo("BB", urla("#"))).toString();
  responsebody += tr("</ol>\r\n<ol>");
  responsebody += QVariant(linkTo("CC", urla("#"))).toString();
  responsebody += tr("</ol>\r\n</ul>\r\n\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

Q_DECLARE_METATYPE(cms_admin_centerView)
T_REGISTER_VIEW(cms_admin_centerView)

#include "cms_admin_centerView.moc"
