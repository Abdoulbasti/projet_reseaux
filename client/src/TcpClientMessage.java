import java.util.List;

public class TcpClientMessage implements TcpClientMessageParser {
    public static byte[] toArray(List<Byte> b){
        byte[] r = new byte[b.size()];
        for(int i = 0;i < r.length;i++){
            r[i] = b.get(i);
        }
        return r;
    }

    public String type;
    public byte[] data;

    private TcpClientMessage(String type, byte[] data) {
        this.type = type;
        this.data = data;
    }

    public static TcpClientMessage build(List<Byte> characters) {
        if (characters.size() < 5) {
            return null;
        }

        List<Byte> type = characters.subList(0, 5);
        List<Byte> data = characters.subList(5, characters.size());

        return new TcpClientMessage(new String(toArray(type)), toArray(data));
    }

    public String toString() {
        return "[" + this.type + new String(data) + "]";
    }

    @Override
    public void parse() { }
}

interface TcpClientMessageParser {
    void parse();
}
