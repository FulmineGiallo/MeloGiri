-- MySQL dump 10.13  Distrib 8.0.32, for Linux (x86_64)
--
-- Host: localhost    Database: melogiri
-- ------------------------------------------------------
-- Server version	8.0.32-0ubuntu0.22.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bevanda`
--

DROP TABLE IF EXISTS `bevanda`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bevanda` (
  `idbevanda` int NOT NULL,
  `nome` varchar(45) NOT NULL,
  `photo_url` varchar(255) NOT NULL,
  `livello_alcolico` int NOT NULL,
  `descrizione` varchar(255) DEFAULT NULL,
  `categoria` enum('softdrink','drinkanalcolici','drinkalcolici','vini') NOT NULL,
  `prezzo` float NOT NULL,
  PRIMARY KEY (`idbevanda`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bevanda`
--

LOCK TABLES `bevanda` WRITE;
/*!40000 ALTER TABLE `bevanda` DISABLE KEYS */;
INSERT INTO `bevanda` VALUES (1,'gin tonic','asdfsfdcs.it',4,'drink leggero','drinkalcolici',12.99),(2,'Coca Cola','https://www.example.com/coca-cola.jpg',0,'Bevanda analcolica al gusto di cola','drinkanalcolici',1.5),(3,'Vodka Smirnoff','https://www.example.com/vodka-smirnoff.jpg',40,'Vodka di alta qualità','softdrink',3.5),(4,'Red Bull','https://www.example.com/red-bull.jpg',0,'Bevanda energetica','drinkanalcolici',2.5),(5,'Coca Cola Zero','https://www.example.com/coca-cola-zero.jpg',0,'Bevanda analcolica al gusto di cola senza zucchero','drinkanalcolici',1.5),(6,'Acqua Minerale','https://www.example.com/acqua-minerale.jpg',0,'Acqua naturale italiana','drinkanalcolici',1),(7,'Birra Guinness','https://www.example.com/birra-guinness.jpg',4,'Birra scura irlandese di qualità','drinkalcolici',4),(8,'Tequila Jose Cuervo','https://www.example.com/tequila-jose-cuervo.jpg',38,'Tequila di alta qualità','drinkalcolici',4.5),(9,'Fanta','https://www.example.com/fanta.jpg',0,'Bevanda analcolica all\'arancia','drinkanalcolici',1.5);
/*!40000 ALTER TABLE `bevanda` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `carrello`
--

DROP TABLE IF EXISTS `carrello`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `carrello` (
  `quantita_bevanda` int NOT NULL,
  `fk_bevanda` int NOT NULL AUTO_INCREMENT,
  `fk_ordine` int NOT NULL,
  KEY `fk_bevanda_idx` (`fk_bevanda`),
  KEY `fk_ordine_idx` (`fk_ordine`),
  CONSTRAINT `fk_ordine` FOREIGN KEY (`fk_ordine`) REFERENCES `ordine` (`idordine`)
) ENGINE=InnoDB AUTO_INCREMENT=32 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `carrello`
--

LOCK TABLES `carrello` WRITE;
/*!40000 ALTER TABLE `carrello` DISABLE KEYS */;
INSERT INTO `carrello` VALUES (133,2,30),(222,3,30),(133,2,31),(222,3,31),(133,2,32),(222,3,32);
/*!40000 ALTER TABLE `carrello` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ordine`
--

DROP TABLE IF EXISTS `ordine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ordine` (
  `idordine` int NOT NULL AUTO_INCREMENT,
  `stato` varchar(255) NOT NULL,
  `tot_prezzo` varchar(50) DEFAULT NULL,
  `data_ordine` timestamp NULL DEFAULT NULL,
  `fk_utente` int NOT NULL,
  PRIMARY KEY (`idordine`),
  KEY `fk_utente_idx` (`fk_utente`)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ordine`
--

LOCK TABLES `ordine` WRITE;
/*!40000 ALTER TABLE `ordine` DISABLE KEYS */;
INSERT INTO `ordine` VALUES (29,'confermato','15.440000',NULL,3),(30,'confermato','15.440000',NULL,3),(31,'confermato','15.440000','2023-05-09 12:58:12',3),(32,'confermato','15.440000','2023-05-09 13:17:58',3);
/*!40000 ALTER TABLE `ordine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `utente`
--

DROP TABLE IF EXISTS `utente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `utente` (
  `idutente` int NOT NULL AUTO_INCREMENT,
  `nome` varchar(45) NOT NULL,
  `cognome` varchar(45) NOT NULL,
  `data_nascita` varchar(50) DEFAULT NULL,
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `logged_in` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`idutente`),
  UNIQUE KEY `email_UNIQUE` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `utente`
--

LOCK TABLES `utente` WRITE;
/*!40000 ALTER TABLE `utente` DISABLE KEYS */;
INSERT INTO `utente` VALUES (1,'andrea','migliorisi','1999-10-20','andrea@email.com','12345melogiri',0),(2,'carmine','guarracino','2000-01-01','carmine@email.com','1234prova',1),(3,'gianluca','leone','1990-01-01','gianluca@email.com','provatest',0),(4,'martina','ianniello','1998-07-23','martina@email.com','provatest',0),(5,'francesco','mazzo','1999-04-22','francesco@email.com','provatestc',0),(6,'davide','esposito','1999-04-22','davide@email.com','provatestd',0),(7,'mario','esposito','1999-04-22','mario@email.com','provatestm',0),(8,'giovanni','esposito','1999-04-22','giovanni@email.com','provatestg',0),(9,'alex','esposito','1999-04-22','alex@email.com','provatesta',0),(10,'alex','esposito','1999-04-22','alec@email.com','provatestac',0),(11,'gio','esposito','1999-04-22','gio@email.com','provatestagg',0),(12,'gio','esposito','1999-04-22','giose@email.com','provatestagg',0),(15,'2nome','cognome','data','email','password',0);
/*!40000 ALTER TABLE `utente` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-05-13 11:56:03
