javac -d bin -cp mysql-connector-java-9.3.0.jar \
                JDBC/GenericDB.java \
                JDBC/PartDB.java \
                JDBC/MasinaDB.java \
                JDBC/ClientDB.java \
                JDBC/PortofelDB.java \
                CSVHandler.java \
                Portofel.java \
                Client.java \
                Part.java \
                Masina.java \
                Inventar/Inventar.java \
                Inventar/PartInventar.java \
                Inventar/MasinaInventar.java \
                Service.java \
                Main.java \
&& java -cp "bin:.:mysql-connector-java-9.3.0.jar" Main