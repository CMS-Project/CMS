#include <QtCore>
#include <TreeFrogView>
#include "cms.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT cms_showView : public TActionView
{
  Q_OBJECT
public:
  cms_showView() : TActionView() { }
  cms_showView(const cms_showView &) : TActionView() { }
  QString toString();
};

QString cms_showView::toString()
{
  responsebody.reserve(1854);
  responsebody += tr("<!DOCTYPE html>\r\n");
    tfetch(Cms, cms);
  responsebody += tr("<html>\r\n<head>\r\n  <meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\" />\r\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += tr("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<h1>Showing Cms</h1>\r\n<dt>NumberID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.numberID());
  responsebody += tr("</dd><br />\r\n<dt>Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.name());
  responsebody += tr("</dd><br />\r\n<dt>Nickname</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.nickname());
  responsebody += tr("</dd><br />\r\n<dt>Password</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.password());
  responsebody += tr("</dd><br />\r\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.id());
  responsebody += tr("</dd><br />\r\n<dt>Phone</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.phone());
  responsebody += tr("</dd><br />\r\n<dt>Belong</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.belong());
  responsebody += tr("</dd><br />\r\n<dt>User Number</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.userNumber());
  responsebody += tr("</dd><br />\r\n<dt>Role</dt><dd>");
  responsebody += THttpUtility::htmlEscape(cms.role());
  responsebody += tr("</dd><br />\r\n\r\n");
  responsebody += QVariant(linkTo("Edit", urla("edit", cms.numberID()))).toString();
  responsebody += tr(" |\r\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += tr("\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

Q_DECLARE_METATYPE(cms_showView)
T_REGISTER_VIEW(cms_showView)

#include "cms_showView.moc"
