import java.util.function.BiConsumer;

public enum TcpClientStateController {
    GAMES((cli, mes) -> {
        cli.state.setGames(mes.data[mes.data.length - 1]);
        System.out.println(cli.state);

        if(cli.state.getGames() == 0){
            cli.sender.sendNewpl("12345678", "1234");
        }
    }),
    OGAME((cli, mes) -> {
        byte m = mes.data[mes.data.length - 3];
        byte s = mes.data[mes.data.length - 1];
        cli.state.setOgame(m, s);
        System.out.println(cli.state);

        if(cli.state.getRegok() == -1){
            cli.sender.sendRegis("12345678", "1234", m);
        }
    }),
    REGOK((cli, mes) -> {
        int m = mes.data[mes.data.length - 1];
        cli.state.setRegok(m);
        System.out.println(cli.state);
    }),
    SIZE_((cli, mes) -> {

    });

    private final BiConsumer<TcpClient, TcpClientMessage> action;

    TcpClientStateController(BiConsumer<TcpClient, TcpClientMessage> action){
        this.action = action;
    }

    public BiConsumer<TcpClient, TcpClientMessage> getHandler(){
        return this.action;
    }
}
