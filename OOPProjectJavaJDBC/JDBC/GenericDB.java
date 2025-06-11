import java.sql.*;
import java.util.Scanner;

public abstract class GenericDB {
    protected static Connection con = null;
    protected Scanner scanner;
    protected String table = "Generic";
    protected CSVHandler csv = new CSVHandler();

    public GenericDB(Scanner in) {
        try {
        con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Dealer?user=root&password=redacted]");
        } catch (SQLException e) { System.out.println( e.getMessage() ); }
        this.scanner = in;
    }

    void getAll() { 
        csv.append("Select All " + table);
        customGetAll();
    }
    void customGetAll() {}
    void getID(int id) {
        csv.append("Select Row " + table);
        customGetID(id);
    }
    void customGetID(int id) {}
    void delete(int id) {
        csv.append("Deletion " + table);
        customDelete(id);
    }
    void customDelete(int id) {}
    void update(int id) { 
        csv.append("Updated Row " + table);
        customUpdate(id);
    }
    void customUpdate(int id) {}
    void insert() { 
        csv.append("Inserted Row " + table);
        customInsert();
    }
    void customInsert() {}
}
