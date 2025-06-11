import java.sql.*;
import java.util.Scanner;

public class ClientDB extends GenericDB {
    public ClientDB(Scanner in) { super(in); table = "Client"; }
    @Override
    void customGetAll() {
        try {
            Statement stat = con.createStatement();
            ResultSet res = stat.executeQuery("SELECT * FROM Client;");

            while (res.next()) {
                String str = res.getString(1) + ". " + res.getString(2) + " (VIP:" + res.getString(3) + ")";
                System.out.println(str);
            
            }
            res.close();
            stat.close();
        } catch (SQLException e) {
            System.out.println( e.getMessage() );
        }
    }
        
    @Override
    void customInsert() {
        System.out.println("Nume: , vip: (0/1)");
        String nume = scanner.nextLine();
        int vip = scanner.nextInt();
        try {
            PreparedStatement stat = con.prepareStatement("INSERT INTO Client (nume, vip) VALUES (?, ?);");
            stat.setString(1, nume);
            stat.setBoolean(2, vip == 1);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    void customDelete(int id) {
        try {
            PreparedStatement stat = con.prepareStatement("DELETE FROM Client WHERE ID = ?");
            stat.setInt(1, id);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}