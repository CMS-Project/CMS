#include <QtCore>
#include <TreeFrogView>
#include "cms.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT cms_operator_centerView : public TActionView
{
  Q_OBJECT
public:
  cms_operator_centerView() : TActionView() { }
  cms_operator_centerView(const cms_operator_centerView &) : TActionView() { }
  QString toString();
};

QString cms_operator_centerView::toString()
{
  responsebody.reserve(902);
  responsebody += tr("<!DOCTYPE html>\r\n");
    tfetch(Cms, cms);
  responsebody += tr("<html>\r\n<head>\r\n  <meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\" />\r\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += tr("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<h1>Operator Center</h1>\r\n\r\n<ul>\r\n<ol>");
  responsebody += QVariant(linkTo("DD", urla("#"))).toString();
  responsebody += tr("</ol>\r\n<ol>");
  responsebody += QVariant(linkTo("EE", urla("#"))).toString();
  responsebody += tr("</ol>\r\n<ol>");
  responsebody += QVariant(linkTo("FF", urla("#"))).toString();
  responsebody += tr("</ol>\r\n</ul>\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

Q_DECLARE_METATYPE(cms_operator_centerView)
T_REGISTER_VIEW(cms_operator_centerView)

#include "cms_operator_centerView.moc"
