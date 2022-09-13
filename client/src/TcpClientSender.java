public class TcpClientSender {
    private final TcpClient client;

    public TcpClientSender(TcpClient client){
        this.client = client;
    }

    private void sendMessage(byte[] data){
        byte[] send_data = new byte[data.length + TcpClient.ENDLINE.length()];

        System.arraycopy(data, 0, send_data, 0, data.length);
        System.arraycopy(TcpClient.ENDLINE.getBytes(), 0, send_data, data.length, TcpClient.ENDLINE.length());
        this.client.send(send_data);
    }

    public void sendNewpl(String id, String port){
        this.sendMessage(("NEWPL " + id + " " + port).getBytes());
    }

    public void sendRegis(String id, String port, byte m){
        byte[] data = ("REGIS " + id + " " + port + " X").getBytes();
        data[data.length - 1] = m;
        this.sendMessage(data);
    }
}
