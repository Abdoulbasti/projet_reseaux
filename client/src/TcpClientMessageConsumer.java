import java.util.HashMap;
import java.util.Map;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public class TcpClientMessageConsumer implements Consumer<TcpClientMessage> {
    private final TcpClient client;
    private final Map<String, BiConsumer<TcpClient, TcpClientMessage>> messageEvents;

    public TcpClientMessageConsumer(TcpClient client){
        this.client = client;
        this.messageEvents = new HashMap<String, BiConsumer<TcpClient, TcpClientMessage>>();
    }

    @Override
    public void accept(TcpClientMessage message) {
        BiConsumer<TcpClient, TcpClientMessage> event = this.messageEvents.get(message.type);
        if(event != null){
            event.accept(this.client, message);
        }else{
            System.out.println("not found " + message.type);
        }
    }   
    
    public void onMessage(String type, BiConsumer<TcpClient, TcpClientMessage> action){
        this.messageEvents.put(type, action);
    }
}
