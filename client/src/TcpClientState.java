import java.util.HashMap;
import java.util.Map;

public class TcpClientState {
    private int games = -1;
    private Map<Integer, Integer> ogames = null;
    private int regok = -1;

    public String toString(){
        return "games: " + this.games + "\n"
            + "ogames: " + this.ogames.size() + "\n"
            + "regok: " + this.regok;
    }

    /*
    
    SET
    
    */
    public void setGames(int n) {
        this.games = n;
        this.ogames = new HashMap<Integer, Integer>();
    }

    public void setOgame(int m, int s) {
        if (ogames == null || this.games < 0) {
            return;
        }

        this.ogames.put(m, s);
    }

    public void setRegok(int m){
        this.regok = m;
    }

    /*
    
    GET
    
    */
    public int getGames() {
        return this.games;
    }

    public Map<Integer, Integer> getOgames(int m) {
        return this.ogames;
    }

    public int getRegok(){
        return this.regok;
    }
}
