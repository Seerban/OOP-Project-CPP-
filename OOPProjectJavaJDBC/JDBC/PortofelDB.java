import java.sql.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class PortofelDB extends GenericDB {
    public PortofelDB(Scanner in) { super(in); table = "Portofel"; }
    @Override
    void customGetAll() {
        try {
            Statement stat = con.createStatement();
            ResultSet res = stat.executeQuery("SELECT * FROM Portofel");

            while (res.next()) {
                String str = "BAL: " + res.getString(2);
                System.out.println(str);
            }
            stat.close();
            res.close();
        } catch (SQLException e) {
            System.out.println( e.getMessage() );
        }
        try {
            Statement stat = con.createStatement();
            ResultSet res = stat.executeQuery("SELECT * FROM Tranzactie ORDER BY id DESC LIMIT 8;");

            List<String> tranz = new ArrayList<>();
            while (res.next()) {
                String str = res.getString(1) + ". " + res.getInt(3);
                tranz.add(str);
            }
            for (String i : tranz) {
            System.out.println(i);
            }
            stat.close();
            res.close();
        } catch (SQLException e) {
            System.out.println( e.getMessage() );
        }
    }

    int getBalance() {
        csv.append("Check Balance");
        int rez = 0;
        try {
            Statement stat = con.createStatement();
            ResultSet res = stat.executeQuery("SELECT * FROM Portofel");
            res.next();
            rez = res.getInt(2);
            stat.close();
            res.close();
        } catch (SQLException e) {
            System.out.println( e.getMessage() );
        }
        return rez;
    }

    void tranzactie(int val) {
        csv.append("Tranzactie (" + val + ")");
        try {
            PreparedStatement stat = con.prepareStatement("INSERT INTO Tranzactie (portofel_id, valoare) VALUES (?, ?);");
            stat.setInt(1, 1);
            stat.setInt(2, val);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        try {
            PreparedStatement stat = con.prepareStatement("UPDATE Portofel SET balance = balance + ? WHERE id = ?;");
            stat.setInt(1, val);
            stat.setInt(2, 1);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}