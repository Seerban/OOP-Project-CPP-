public class Client {
    String nume;
    boolean vip;

    public Client(String nume, boolean vip) {
        this.nume = nume;
        this.vip = vip;
    }

    public Client(String nume) {
        this.nume = nume;
        this.vip = false;
    }

    public String getNume() {
        return nume;
    }

    public boolean getVIP() {
        return vip;
    }

    public void setVIP(boolean b) {
        vip = b;
    }

    @Override
    public String toString() {
        if( vip ) return "VIP " + this.nume;
        return this.nume;
    }
}