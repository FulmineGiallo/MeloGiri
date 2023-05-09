import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) throws IOException {
        String serverAddress = "localhost"; // indirizzo IP del server
        int port = 8080; // porta del server

        try (Socket socket = new Socket(serverAddress, port)) {
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);

            String message = "1carmine@email.com&$1234prova";
            writer.println(message);

            InputStream inputStream = socket.getInputStream();
            System.out.println("Messaggio inviato al server: " + message);
            byte[] buffer = new byte[10000];
            int bytesRead = inputStream.read(buffer);
            String receivedMessage = new String(buffer, 0, bytesRead);

            System.out.println("Received message from C socket server: " + receivedMessage);
            //CREO OGGETTO JSON


            // Close the socket
            socket.close();

        } catch (UnknownHostException ex) {
            System.err.println("Indirizzo IP del server non valido: " + serverAddress);
        } catch (IOException ex) {
            System.err.println("Errore di I/O durante la connessione al server: " + serverAddress);
        }
    }
}
