# CMS
基于Qt库和TreeFrog MVC框架的web应用，支持Windows、Mac OS X、Linux平台

## 用法说明

1、安装Qt5，说明文档http://doc.qt.io/qt-5/gettingstarted.html

2、安装TreeFrog，说明文档http://www.treefrogframework.org/documents/install

3、安装数据库服务器，建议使用MySQL

4、下载CMS代码https://github.com/CMS-Project/CMS

5、配置数据库

   运行CMS.sql建立数据库。
   修改CMS/config/database.ini文件，配置相关信息。

6、编译运行

   Windows下，使用TreeFrog Command Prompt，进入CMS目录

   ````
         qmake -r "CONFIG+=release"
         mingw32-make
         treefrogd.exe -e dev

   ````

   Linux、Mac OS X下，进入CMS目录

   ````
       qmake -r "CONFIG+=release"
       make
       treefrog -e dev

   ````

   打开浏览器输入http://localhost:8800/cms