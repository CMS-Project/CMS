-- MySQL dump 10.13  Distrib 5.6.24, for Win64 (x86_64)
--
-- Host: 192.168.0.119    Database: CMS
-- ------------------------------------------------------
-- Server version	5.1.73

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `AUOperationRecord`
--

DROP TABLE IF EXISTS `AUOperationRecord`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `AUOperationRecord` (
  `opID` int(11) NOT NULL AUTO_INCREMENT,
  `operatorID` varchar(10) NOT NULL,
  `type` char(15) NOT NULL,
  `result` char(5) NOT NULL,
  `time` datetime NOT NULL,
  `remarks` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`opID`),
  KEY `FK_OperatorID_idx` (`operatorID`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `AUOperationRecord`
--

LOCK TABLES `AUOperationRecord` WRITE;
/*!40000 ALTER TABLE `AUOperationRecord` DISABLE KEYS */;
INSERT INTO `AUOperationRecord` VALUES (3,'123','资产单元添加','成功','2015-08-04 10:51:22','创建资产单元: ID: 20, 名称: 88889'),(4,'123','资产单元添加','失败','2015-08-04 11:06:06','创建资产单元: ID: 6, 名称: 55555aaaa'),(10,'123','交易单元修改','失败','2015-08-04 11:09:00','修改交易单元: ID: \0, 名称变更: 测试2'),(11,'123','交易单元修改','失败','2015-08-04 11:09:09','修改交易单元: ID: \0, 名称变更: 测试555');
/*!40000 ALTER TABLE `AUOperationRecord` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `admins`
--

DROP TABLE IF EXISTS `admins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admins` (
  `adminID` varchar(10) NOT NULL,
  `adminName` varchar(10) NOT NULL,
  `adminPassword` varchar(15) NOT NULL,
  PRIMARY KEY (`adminID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admins`
--

LOCK TABLES `admins` WRITE;
/*!40000 ALTER TABLE `admins` DISABLE KEYS */;
INSERT INTO `admins` VALUES ('001','liying','123456'),('002','wer','123456');
/*!40000 ALTER TABLE `admins` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `assetsUnit`
--

DROP TABLE IF EXISTS `assetsUnit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `assetsUnit` (
  `assetsUnitID` int(11) NOT NULL,
  `managerID` int(11) NOT NULL,
  `assetsUnitShortname` char(20) NOT NULL,
  `assetsBalance` decimal(2,0) DEFAULT '0',
  PRIMARY KEY (`assetsUnitID`,`managerID`),
  KEY `FK_managerID` (`managerID`),
  CONSTRAINT `FK_managerID` FOREIGN KEY (`managerID`) REFERENCES `assetsunitmanager` (`managerID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `assetsUnit`
--

LOCK TABLES `assetsUnit` WRITE;
/*!40000 ALTER TABLE `assetsUnit` DISABLE KEYS */;
INSERT INTO `assetsUnit` VALUES (1,4,'资产单元7第三方的手',0),(2,4,'fdbdvb',0),(4,0,'资产单元45',0),(5,0,'公费',0),(12,0,'32132132',0),(13,0,'ghjh',NULL),(14,0,'89',NULL);
/*!40000 ALTER TABLE `assetsUnit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `assetsunitmanager`
--

DROP TABLE IF EXISTS `assetsunitmanager`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `assetsunitmanager` (
  `managerID` int(11) NOT NULL,
  `managerNname` char(30) NOT NULL,
  `managerShortname` char(20) NOT NULL,
  `managerState` char(5) NOT NULL,
  PRIMARY KEY (`managerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `assetsunitmanager`
--

LOCK TABLES `assetsunitmanager` WRITE;
/*!40000 ALTER TABLE `assetsunitmanager` DISABLE KEYS */;
INSERT INTO `assetsunitmanager` VALUES (0,'管理人0','管理人0','可用'),(1,'管理人1','管理人1jc','可用'),(2,'管理人2','管理人2jc','可用'),(3,'管理人3','管理人3jc','可用'),(4,'管理人4','管理人4jc','冻结'),(101,'管理人101','管理人101jc','可用');
/*!40000 ALTER TABLE `assetsunitmanager` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cms`
--

DROP TABLE IF EXISTS `cms`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cms` (
  `numberID` varchar(10) NOT NULL,
  `name` varchar(10) NOT NULL,
  `nickname` varchar(10) NOT NULL,
  `password` varchar(15) NOT NULL,
  `ID` varchar(19) NOT NULL,
  `phone` decimal(12,0) NOT NULL,
  `belong` varchar(7) NOT NULL,
  `user_number` varchar(20) NOT NULL,
  `role` decimal(2,0) NOT NULL,
  `status` varchar(4) NOT NULL,
  PRIMARY KEY (`numberID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cms`
--

LOCK TABLES `cms` WRITE;
/*!40000 ALTER TABLE `cms` DISABLE KEYS */;
/*!40000 ALTER TABLE `cms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `connection`
--

DROP TABLE IF EXISTS `connection`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `connection` (
  `adminID` varchar(10) NOT NULL,
  `operatorID` varchar(10) NOT NULL,
  KEY `adminID` (`adminID`),
  KEY `operatorID` (`operatorID`),
  CONSTRAINT `connection_ibfk_1` FOREIGN KEY (`adminID`) REFERENCES `admins` (`adminID`),
  CONSTRAINT `connection_ibfk_2` FOREIGN KEY (`operatorID`) REFERENCES `operators` (`operatorID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `connection`
--

LOCK TABLES `connection` WRITE;
/*!40000 ALTER TABLE `connection` DISABLE KEYS */;
INSERT INTO `connection` VALUES ('001','Zhaolaoba'),('001','001'),('002','123');
/*!40000 ALTER TABLE `connection` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `log`
--

DROP TABLE IF EXISTS `log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `log` (
  `adminID` varchar(20) NOT NULL,
  `userID` varchar(20) NOT NULL,
  `role` varchar(10) NOT NULL,
  `time` varchar(30) NOT NULL,
  `way` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log`
--

LOCK TABLES `log` WRITE;
/*!40000 ALTER TABLE `log` DISABLE KEYS */;
/*!40000 ALTER TABLE `log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `marketingunit`
--

DROP TABLE IF EXISTS `marketingunit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `marketingunit` (
  `MUid` int(11) NOT NULL AUTO_INCREMENT,
  `MUvalue` int(11) DEFAULT NULL,
  `MUsname` varchar(45) NOT NULL,
  `MUname` varchar(45) DEFAULT NULL,
  `MUdate` date DEFAULT NULL,
  `srcUnitID` int(11) DEFAULT NULL,
  `destUnitID` int(11) DEFAULT NULL,
  `operatorID` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`MUid`),
  KEY `FK_srcUnitID_idx` (`srcUnitID`),
  KEY `FK_destUnitID_idx` (`destUnitID`),
  KEY `FK_operatorID_idx` (`operatorID`),
  CONSTRAINT `FK_operatorID` FOREIGN KEY (`operatorID`) REFERENCES `operators` (`operatorID`) ON UPDATE CASCADE,
  CONSTRAINT `FK_destUnitID` FOREIGN KEY (`destUnitID`) REFERENCES `assetsUnit` (`assetsUnitID`) ON UPDATE CASCADE,
  CONSTRAINT `FK_srcUnitID` FOREIGN KEY (`srcUnitID`) REFERENCES `assetsUnit` (`assetsUnitID`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `marketingunit`
--

LOCK TABLES `marketingunit` WRITE;
/*!40000 ALTER TABLE `marketingunit` DISABLE KEYS */;
INSERT INTO `marketingunit` VALUES (13,10,'fdgfd','dafdfadfdsaf','2015-07-30',1,2,'001'),(14,100000,'7890000','dsfadsfdsfdsa','2015-07-30',4,5,'123'),(18,10,'fbxccv','opopopo','2015-08-12',1,4,'123'),(19,456,'yui','ipp','2015-07-31',2,5,'123'),(20,100,'测试','洒洒水','2015-07-31',2,4,'123'),(21,1111,'少时诵诗书','','2015-07-31',2,5,'123'),(23,14234,'交易','','2015-07-31',2,5,'123'),(24,100,'jianchenkkkkkkk','','2015-07-31',2,4,'123'),(26,100,'测试一号','测试测试一号','2015-08-03',12,2,NULL);
/*!40000 ALTER TABLE `marketingunit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `operators`
--

DROP TABLE IF EXISTS `operators`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `operators` (
  `operatorID` varchar(10) NOT NULL,
  `operatorName` varchar(10) NOT NULL,
  `operatorNickname` varchar(10) NOT NULL,
  `operatorPassword` varchar(15) NOT NULL,
  `operatorPhone` varchar(12) NOT NULL,
  `ID` varchar(20) NOT NULL,
  `operatorRole` varchar(5) NOT NULL,
  `operatorStatus` varchar(5) NOT NULL,
  `assetID` int(11) NOT NULL,
  `tradeID` int(11) NOT NULL,
  PRIMARY KEY (`operatorID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `operators`
--

LOCK TABLES `operators` WRITE;
/*!40000 ALTER TABLE `operators` DISABLE KEYS */;
INSERT INTO `operators` VALUES ('001','你好啊','001','123456','','','','正常',201,104),('123','test','001','123456','123','132','13','正常',101,201),('Zhaolaoba','赵老八','Zhaolaoba','123','112','513122199111160982','1','正常',112,105);
/*!40000 ALTER TABLE `operators` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-08-04 16:48:47
