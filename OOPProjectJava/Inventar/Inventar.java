public abstract class Inventar {
    private int capacitate;
    private int cantitate;

    public Inventar(int len) {
        this.capacitate = len;
    }

    public int getCapacitate() {
        return capacitate;
    }

    public int getCantitate () {
        return cantitate;
    }

    public void setCantitate(int x) {
        this.cantitate = x;
    }

    abstract void show();
}