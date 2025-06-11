import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class CSVHandler {
    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    public void append(String input) {
        String timestamp = LocalDateTime.now().format(formatter);
        String line = String.format("\"%s\",\"%s\"\n", input, timestamp);

        try (FileWriter writer = new FileWriter("output.csv", true)) {
            writer.write(line);
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}
