import java.sql.*;


public class InsertRecords {
public static void main(String argv[]) throws Exception {
		Connection con;
		Statement stmt;
		try {
			//Class.forName("com.mysql.jdbc.Driver");
			Class.forName("com.mysql.cj.jdbc.Driver");
			String url = "jdbc:mysql://localhost:3306/DBMS_LAB";
			con = DriverManager.getConnection(url, "root", "Cyborg54@967645");
			String sql = "INSERT INTO Students (column1, column2) VALUES ('value1', 'value2')";
			stmt = con.createStatement();
			int x = stmt.executeUpdate(sql);
			System.out.println("Record Inserted: " + x + " row(s) affected");
			stmt.close();
			con.close();
		} catch (Exception e) {
			System.out.println("** Error on data select. ** " + e);

		}
    }
}