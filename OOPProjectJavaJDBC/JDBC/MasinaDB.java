import java.sql.*;
import java.util.Scanner;

public class MasinaDB extends GenericDB {
    public MasinaDB(Scanner in) { super(in); table = "Masina"; }
    @Override
    void customGetAll() {
        try {
            Statement stat = con.createStatement();
            ResultSet res = stat.executeQuery("SELECT * FROM Masina");

            while (res.next()) {
                String str = res.getString(1) + ". " + res.getString(2) + " (" + res.getString(6) + ")";
                System.out.println(str);
            }
            stat.close();
            res.close();
        } catch (SQLException e) {
            System.out.println( e.getMessage() );
        }
    }

    @Override
    void customDelete(int id) {
        try {
            System.out.println("ID Client: ");
            int idcli = scanner.nextInt();
            PreparedStatement clitstat = con.prepareStatement("UPDATE Client SET vip = true WHERE ID = ?");
            clitstat.setInt(1, idcli);
            clitstat.executeUpdate();
            clitstat.close();

            PreparedStatement pretstat = con.prepareStatement("SELECT pret, roti, motor, sasiu FROM Masina WHERE ID = ?");
            pretstat.setInt(1, id);
            ResultSet res = pretstat.executeQuery();
            res.next();
            int valoare = res.getInt(1);
            int roti = res.getInt(2);
            int motor = res.getInt(3);
            int sasiu = res.getInt(4);
            res.close();

            PreparedStatement stat = con.prepareStatement("DELETE FROM Masina WHERE ID = ?");
            stat.setInt(1, id);
            stat.executeUpdate();
            stat.close();

            PreparedStatement partstat = con.prepareStatement("DELETE FROM Part WHERE ID in (?, ?, ?);");
            partstat.setInt(1, roti);
            partstat.setInt(2, motor);
            partstat.setInt(3, sasiu);
            partstat.executeUpdate();
            partstat.close();

            PortofelDB temp = new PortofelDB(scanner);
            temp.tranzactie(valoare);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    void customInsert() {
        System.out.println("Nume masina: ");
        String nume = scanner.next();
        System.out.println("Sasiu ID: ");
        int sasiu = scanner.nextInt();
        System.out.println("Motor ID: ");
        int motor = scanner.nextInt();
        System.out.println("Roti ID: ");
        int roti = scanner.nextInt();
        System.out.println("Pret: ");
        int pret = scanner.nextInt();
        System.out.println(pret);
        try {
            PreparedStatement stat = con.prepareStatement("INSERT INTO Masina (nume, sasiu, roti, motor, pret) VALUES (?, ?, ?, ?, ?);");
            stat.setString(1, nume);
            stat.setInt(2, sasiu);
            stat.setInt(3, roti);
            stat.setInt(4, motor);
            stat.setInt(5, pret);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    void scrap(int id) {
        csv.append("Scrapped Car");
        try {
            PreparedStatement stat = con.prepareStatement("DELETE FROM Masina WHERE ID = ?");
            stat.setInt(1, id);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    void setPret(int val, int id) {
        csv.append("Set Pret Car");
        try {
            PreparedStatement stat = con.prepareStatement("UPDATE Masina SET pret = ? WHERE id = ?;");
            stat.setInt(1, val);
            stat.setInt(2, id);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}