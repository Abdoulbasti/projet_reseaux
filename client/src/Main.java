import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) {
        try {
            TcpClient client = new TcpClient(args[0], Integer.parseInt(args[1]));
            TcpClientMessageConsumer message_handler = new TcpClientMessageConsumer(client);
            
            for(TcpClientStateController controller : TcpClientStateController.values()){
                message_handler.onMessage(controller.name().replace('_', '!'), controller.getHandler());
            }

            client.startReceive(message_handler);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

/**
 * 
 * public class JavaFX
 * 
 */