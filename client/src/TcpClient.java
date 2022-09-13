import java.net.Socket;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.function.Consumer;
import java.util.stream.IntStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class TcpClient extends Socket {
    public static String ENDLINE = "***";

    private BufferedReader reader;
    private PrintWriter writer;

    private List<Byte> received_buffer;
    private int received_buffer_offset;

    public final TcpClientSender sender; 
    public final TcpClientState state;

    public TcpClient(String host, int port) throws IOException {
        super(host, port);

        this.reader = new BufferedReader(new InputStreamReader(this.getInputStream()));
        this.writer = new PrintWriter(new OutputStreamWriter(this.getOutputStream()));

        this.received_buffer = new ArrayList<Byte>();
        this.received_buffer_offset = 0;

        this.sender = new TcpClientSender(this);
        this.state = new TcpClientState();
    }

    private int getEndIndex(Collection<Byte> collection, String endline) {
        Byte[] array = collection.toArray(Byte[]::new);

        for (int i = 0; i < array.length; i++) {
            if (array[i] == endline.charAt(0) && (array.length - i >= endline.length())) {
                boolean found = true;
                for (int j = 0; j < endline.length(); j++) {
                    if (array[i + j] != (byte)endline.charAt(j)) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    return i;
                }
            }
        }
        return -1;
    }

    public void startReceive(Consumer<TcpClientMessage> onReceive) throws IOException {
        List<Byte> buffer;
        
        do {
            buffer = this.receive();
            this.received_buffer.addAll(buffer);
            this.received_buffer_offset += buffer.size();

            int index;
            while((index = getEndIndex(this.received_buffer, ENDLINE)) > 0){
                List<Byte> message_list = this.received_buffer.subList(0, index);
                
                this.received_buffer = this.received_buffer.subList(index + ENDLINE.length(), this.received_buffer_offset);
                this.received_buffer_offset -= index + ENDLINE.length();

                onReceive.accept(TcpClientMessage.build(message_list));
            }            
        } while (!buffer.isEmpty());

        this.close();
    }

    public List<Byte> receive() {
        try {
            char[] buffer = new char[2048];
            int len = this.reader.read(buffer);
            if (len < 0) {
                return new ArrayList<Byte>(0);
            }
            
            return IntStream.range(0, len)
                            .mapToObj(i -> (byte)buffer[i])
                            .toList();
        } catch (Exception e) {
            e.printStackTrace();
            return new ArrayList<Byte>(0);
        }
    }

    public void send(byte[] data) {
        this.writer.print(new String(data));
        this.writer.flush();
    }
}