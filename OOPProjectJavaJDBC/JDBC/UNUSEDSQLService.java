import java.sql.*;

// unused sql class for generic functions since tables use custom implementation anyway

public class SQLService {
    static Connection conn = null;

    public void connect() {
        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Dealer?user=root&password=redacted");
            System.out.println("Connected to DB");
        } catch (SQLException e) {
            System.out.println("Connection failed: " + e.getMessage());
        }
    }

    public void selectAll(String table) {
        String query = "SELECT * FROM " + table;

        try {
            Statement stat = conn.createStatement();
            ResultSet res = stat.executeQuery(query);

            ResultSetMetaData data = res.getMetaData();
            int cols = data.getColumnCount();

            while (res.next()) {
                for (int i = 1; i <= cols; i++) {
                    String colName = data.getColumnName(i);
                    String value = res.getString(i);
                    System.out.print(colName + ": " + value + '\t');
                }
                System.out.println();
            }

        } catch (SQLException e) {
            System.out.println( e.getMessage() );
        }
    }
}
