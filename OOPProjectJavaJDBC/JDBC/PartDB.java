import java.sql.*;
import java.util.Scanner;

public class PartDB extends GenericDB {
    public PartDB(Scanner in) { super(in); table = "Part"; }
    @Override
    void customGetAll() {
        try {
            Statement stat = con.createStatement();
            ResultSet res = stat.executeQuery("""
                    SELECT *
                    FROM Part WHERE id NOT IN (
                        SELECT sasiu FROM Masina
                        UNION
                        SELECT roti FROM Masina
                        UNION
                        SELECT motor FROM Masina
                );
                """);

            while (res.next()) {
                String str = res.getString(1) + ". " + res.getString(4) + " " + res.getString(5) + " " + res.getString(2) + "(Price:" + res.getString(3) + ")";
                System.out.println(str);
            }
            stat.close();
            res.close();
        } catch (SQLException e) {
            System.out.println( e.getMessage() );
        }
    }
    
    @Override
       void customGetID(int id) {
        try {
            Statement stat = con.createStatement();
            ResultSet res = stat.executeQuery("""
                    SELECT *
                    FROM Part WHERE id = """ + id + """
                    AND id NOT IN (
                        SELECT sasiu FROM Masina
                        UNION
                        SELECT roti FROM Masina
                        UNION
                        SELECT motor FROM Masina
                );
                """);

            while (res.next()) {
                String str = res.getString(1) + ". " + res.getString(4) + " " + res.getString(5) + " " + res.getString(2) + "(Price:" + res.getString(3) + ")";
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
            PreparedStatement pretstat = con.prepareStatement("SELECT pret FROM Part WHERE ID = ?");
            pretstat.setInt(1, id);
            ResultSet res = pretstat.executeQuery();
            res.next();
            int valoare = res.getInt(1);
            
            PreparedStatement stat = con.prepareStatement("DELETE FROM Part WHERE ID = ?");
            stat.setInt(1, id);
            stat.executeUpdate();

            PortofelDB temp = new PortofelDB(scanner);
            temp.tranzactie(valoare);

            pretstat.close();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    void customInsert() {
        System.out.println("Adauga part: ( nume, pret, an, categorie(Motor/Roti/Sasiu) )");
        String nume, cat_aux;
        int pret, an;
        nume = scanner.next();
        pret = scanner.nextInt();
        an = scanner.nextInt();
        cat_aux = scanner.next();
        try {
            PreparedStatement stat = con.prepareStatement("INSERT INTO Part (nume, pret, an, categorie) VALUES (?, ?, ?, ?);");
            stat.setString(1, nume);
            stat.setInt(2, pret);
            stat.setInt(3, an);
            stat.setString(4, cat_aux);
            stat.executeUpdate();
            stat.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

}