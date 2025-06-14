import java.sql.*;

class DBConnet {
    public static void main(String[] args) {
        try {
            String url = "jdbc:mysql://localhost:3306/DBMS_LAB";
            String pass = "Cyborg54@967645";
            String user = "root";
            Connection conn;
            Statement stmt;
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(user, pass, url);
            stmt = conn.createStatement();
            String str = "create table tableName";
            System.out.println("Successfully created !");
            stmt.executeUpdate(str);
            conn.close();
            stmt.close();
        }catch(Exception e ){
            System.out.println("Exception occured");
        }finally {
            System.out.println("This will execute eventually");
        }
    }
}